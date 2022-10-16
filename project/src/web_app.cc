/**
 * @file web_app.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "web_app.h"
#include <fstream>
#include "util/base64.h"
    
//*****************************************************************************************
// Edit the following functions to suit your needs.  Do most of the work inside the
// simulation facade and not here.  The primary purpose of these functions are to
// communicate with the UI.
//*****************************************************************************************

void WebApp::CreateEntity(picojson::object& entityData, ICameraController& cameraController) {
    // Print out actual json:
    picojson::value val(entityData);
    std::cout << val.serialize() << std::endl;
    
    // Use the RescueSimulation facade to create a new Entity
    facade_rescue.CreateEntity(entityData, cameraController);
}

void WebApp::Update(double dt) {
    // Manual Movement
    bool start_manualMov = IsKeyDown("y") ? 1 : 0;
    bool stop_manualMov = IsKeyDown("n") ? 1 : 0;

    if (start_manualMov && !facade_rescue.GetManualMov() ){
        facade_rescue.SetManualMov();
        std::cout<<"changing to manual movement "<<std::endl;
    }
    else if (stop_manualMov && facade_rescue.GetManualMov() ){
        facade_rescue.SetManualMov();
        std::cout<<"changing to automatic movement "<<std::endl;
    }

    // Updates the simulation.  This may be called multiple times per frame.
    double x = IsKeyDown("ArrowRight") ? 1 : (IsKeyDown("ArrowLeft") ? -1 : 0);
    double y = IsKeyDown("w") ? 1 : (IsKeyDown("s") ? -1 : 0);
    double z = IsKeyDown("ArrowUp") ? -1 : (IsKeyDown("ArrowDown") ? 1 : 0);
    double rot =  IsKeyDown("a") ? 1 : (IsKeyDown("d") ? -1 : 0);
    
    // Update the simulation using the RescueSimulation facade
    // if any key touched, then use manual movement update rather than normal update
    if (facade_rescue.GetManualMov()){
        facade_rescue.UpdateManualMovement(dt,x,y,z,rot);
    } else{
        facade_rescue.Update(dt);
    }    
}

void WebApp::FinishUpdate(picojson::object& returnValue) {
    // Define a vector to store picojson objects that will be store the updated JSON information to be passed to the UI by the facade
    std::vector<picojson::object> entityUpdates;

    // Called after all updating is done for each entity
    facade_rescue.FinishUpdate(returnValue,entityUpdates);
    
    // For each entity, send the updated JSON to the UI
    for (int i=0; i<entityUpdates.size(); i++){
        picojson::value retVal(entityUpdates[i]);
        sendJSON(retVal);
    }

    entityUpdates.clear();  
}
  
//*****************************************************************************************
// The code below you probably will not need to touch.  These are the functions 
// that will talk to the UI over web sockets.
//*****************************************************************************************

WebApp::WebApp() : start(std::chrono::system_clock::now()), time(0.0), running(true) {
    imageProcessThread = new std::thread(&WebApp::ProcessImageQueue, this);
}

WebApp::~WebApp() {
    running = false;
    imageProcessCond.notify_all();
    imageProcessThread->join();
}

void WebApp::receiveJSON(picojson::value& val) {
    picojson::object data = val.get<picojson::object>();
    std::string cmd = data["command"].get<std::string>();
    picojson::object returnValue;
    returnValue["id"] = data["id"];
    ReceiveCommand(cmd, data, returnValue);
    picojson::value retVal(returnValue);
    //std::cout<<retVal.serialize()<<std::endl;
    sendJSON(retVal);
}

void WebApp::ReceiveCommand(const std::string& cmd, picojson::object& data, picojson::object& returnValue) {
    if (cmd == "image") {
        std::unique_lock<std::mutex> lock(imageProcessMutex);
        data["time"].set<double>(time);
        imageQueue.push(data);
        imageProcessCond.notify_all();
        return;
    }

    std::unique_lock<std::mutex> updateLock(updateMutex);
    if (cmd == "createEntity") {
        CreateEntity(data, *this);
    } 
    else if (cmd == "update") {
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        double delta = diff.count() - time;
        time += delta;

        double simSpeed = data["simSpeed"].get<double>();
        delta *= simSpeed;

        if (delta > 0.1) {
            for (float f = 0.0; f < delta; f+=0.01) {
                Update(0.01);
            }
        }
        else {
            Update(delta);
        }
        FinishUpdate(returnValue);
    }
    else if (cmd == "keyup") {
        KeyUp(data["key"].get<std::string>(), data["keyCode"].get<double>());
    }
    else if (cmd == "keydown") {
        KeyDown(data["key"].get<std::string>(), data["keyCode"].get<double>());
    }
    else {
        std::cout << "Unknown command: " << cmd << " - " << picojson::value(data).serialize() << std::endl;
    }
}

void WebApp::KeyUp(const std::string& key, int keyCode) {
    keyValue[key] = 0;
}

void WebApp::KeyDown(const std::string& key, int keyCode) {
    keyValue[key] = 1;
}

bool WebApp::IsKeyDown(const std::string& key) {
    std::map<std::string,int>::iterator it = keyValue.find(key);
    if (it != keyValue.end()) {
        return it->second;
    } 

    return false;
}

void WebApp::TakePicture(int cameraId) {
    picojson::object obj;
    picojson::value val;
    obj["takePicture"] = picojson::value((double)cameraId);
    picojson::value v(obj);
    sendJSON(v);
}

void WebApp::ProcessImageQueue() {
    while (running) {
        std::unique_lock<std::mutex> lock(imageProcessMutex);
        if (imageQueue.size() > 0) {
            picojson::object data = imageQueue.front();
            imageQueue.pop();
            lock.unlock();
            
            std::vector<std::string> decodedImages;
            std::vector<RawCameraImage> imageData;
            
            const picojson::array& images = data["images"].get<picojson::array>();

            for (int i = 0; i < images.size(); i++) {
                std::string decoded = base64_decode(images[i].get<std::string>().substr(23));
                decodedImages.push_back(decoded);
                RawCameraImage rawImage;
                rawImage.data = reinterpret_cast<const unsigned char*>(decodedImages[i].c_str());
                rawImage.length = decoded.length();
                imageData.push_back(rawImage);
            }

            int cameraId = data["cameraId"].get<double>();
            const picojson::array& pos = data["position"].get<picojson::array>();

            for (int i = 0; i < cameraObservers.size(); i++) {
                ICameraResult* result = cameraObservers[i]->ProcessImages(
                    cameraId,
                    pos[0].get<double>(),
                    pos[1].get<double>(),
                    pos[2].get<double>(),
                    imageData,
                    data
                );
                if (result) {
                    std::unique_lock<std::mutex> updateLock(updateMutex);
                    cameraObservers[i]->ImageProcessingComplete(result);
                }
            }
        }
        else {
          imageProcessCond.wait(lock);
        }
    }
}

void WebApp::AddObserver(ICameraObserver& observer) {
    cameraObservers.push_back(&observer);
}

void WebApp::RemoveObserver(ICameraObserver& observer) {
    cameraObservers.erase(std::remove(cameraObservers.begin(), cameraObservers.end(), &observer), cameraObservers.end()); 
}
