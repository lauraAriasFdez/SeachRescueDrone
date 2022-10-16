/*! \page simulation Simulation
 * ## Running a Simulation
 * To run a rescue simulation, you first need to obtain the source code for this project. Please view \ref getting-started on how to obtain a local copy of the source code to get started. \ref getting-started has a section titled 'Running the Rescue Simulation' that describes how to compile and run the Rescue Simulation.
 * 
 * ## Interacting with a Simulation
 * Once you have compile the source code for a Rescue Simulation and have started the web server that runs the simulation, visit [127.0.0.1:8081](http://127.0.0.1:8081/) on your local machine.
 * 
 * Your web browser will open the simulation and it should begin. In the upper right-hand corder of the screen you will be able to select a dropdown and switch between different perspectives of the entities that are apart of the simulation. The simulation will track the movements of the selected entity on your screen, but you can use your mouse to move around the simulation.
 *
 * When the `%Drone` entity is selected in the dropdown, by default the drone will move autonomously through the scene. However, you as the user can manually move the drone. Whenever the simulation is running and the %drone is moving you can press 'y' key on your keyboard to enable manual movement of the drone. To control the drone, use the following keys on your keyboard:
 *  - `y`: enables manual movement
 *  - `n`: disables manual movement and puts the %drone back into autonomous movement
 *  - `right-arrow key`: move the drone to the right
 *  - `left-arrow key`: move the drone to the left
 *  - `up-arrow key`: move the drone forward
 *  - `down-arrow key`: move the drone backward
 *  - `w`: move the drone higher
 *  - `s`: move the drone lower
 * 
 * **Note:** The above keyboard controls can be used in combination to create more complex manual movement of the %drone.
 * 
 * ## %Rescue Simulation Design Structure
 * 
 * The aim of the Rescue Simulation was to develop a simulation that through computer vision techniques alongside movement techniques, 
 *  the drone was able to look for a robot inside the scene. In order to accomplish that goal we were provided with a web-based visualization
 *  system that allows our code to interact with the simulation. Overall, our simulation works by letting the drone follow a patrol strategy
 *  movement, meaning letting the drone move in a spiral movement through the web-based visualization while taking pictures. These pictures
 *  are then processed by an object detector that determines if the drone has found the robot; If that is the case then the drone will change
 *  its movement strategy and go directly to the robot. Note: In our simulation by pressing the key “y” the automatic movement of the drone will
 *  stop and the user will be able to control the drone movement through the keys. If the user wishes to go back to automatic movement, he/she
 *  can press the key “n” to switch back to beeline or patrol movement, depending on whether or not the drone has found the robot. 
 * 
 * 
* When designing our Simulation multiple design patterns and design choices were implemented; the core patterns and choices were the facade 
*   pattern for the rescue simulation, the inheritance design choice to build entities and the factory pattern to create entities inside the simulation.
*
* 
* The facade design pattern was implemented in order to allow the complexity of the system to be hidden behind a class called
*  RescueSimulation. The web server will interact with the simulation directly, and this simulation will handle the updating of objects and the 
*  sending of notifications to the web server. This simulation has a CompositeFactory and a vector of Entities, meaning it does not instantiate
*  the entities directly, but rather it delegates such a task to the CompositeFactory.
* <img alt="Rescue Simulation uml diagram" width="100%" src="../pages/images_uml/Movement.png">
*
*
* In order to create the Entities an inheritance hierarchy was used. The reason why inheritance of an interface was used is because many entities
*  share multiple methods and variables, such as a position variable, an id and a type. Thereby by allowing all entities to inherit from 
*  a base entity we reduced duplication of code. Moreover, this also allowed for polymorphism in the Rescue Simulation, as this one has a vector of
*  entities and operates on them without specifically knowing whether it is a robot, drone ...etc. This design choice also allows for 
*  extensibility as if the user wished to create another entity, the entity will have to inherit from the Entity class, and the rescue simulation 
*  will not need to be modified to handle this new entity. 
*
* <img alt="Entities uml diagram" width="100%" src="../pages/images_uml/Entities.png">
*
*
*
* A factory design pattern was used to create Entities (robot, drone, hospital...etc). By using such a pattern the simulation
*   did not instantiate the entities directly, but rather it delegated such a task to the CompositeFactory, and thereby the RescueSimulation avoids the 
*   need to know which type of entity needed to be created.
*
* <img alt="Factory Pattern uml diagram" width="100%" src="../pages/images_uml/Entity_Factory.png">
*
*
*
* In addition to core design choices, more patterns were implemented to build a simulation close for modification and open to extension. For instance,
*   in order to accomplish drone movement inside the simulation the strategy pattern was used. There are two main movement strategies, Patrol, which 
*   search for the robot, and Beeline, which moves the drone towards the robot. Both of these classes inherit from an Interface called IMovement. 
*   Depending on the status of the drone (whether the camera has found the robot or not), the drone will have either a Beeline or a Patrol object as the
*   IMovement object. Note, that since we have also implemented manual movement these strategies will be implemented if and only if the drone is 
*   in automatic movement (Please refer to the first paragraph in this section to note how to change from automatic to manual movement and vice versa).
*
* <img alt="Strategy Pattern uml diagram" width="100%" src="../pages/images_uml/Movement.png">
*
*
*Similarly in order to build the image processor that searches for the robot we built an ObjectDetector class that the Camera uses to process images
*   taken by the drone. The reason behind our separate object detector implementation is if the user wished to extend the search purpose of the simulation
*   to search for other elements other than the drone, the camera would not need to be modified, and the new object detector could inherit directly from
*   this class.  
*
* <img alt="Camera drone uml diagram" width="100%" src="../pages/images_uml/Camera.png">
*
*
*Finally, for enhancement we used the decorator pattern to allow the drone to have a battery, and thereby not allow movement of the drone if the battery
*   runs out. The reason behind constructing a battery decorator class rather than implementing a battery variable inside the drone was exclusively due to
*   extensibility purposes. By doing this, the battery functionality can be applied to other entities like a robot without changing
*   the robot entity class by wrapping the robot inside a Battery Decorator class. 
*
* <img alt="Drone Entity uml diagram" width="100%" src="../pages/images_uml/Drone_Entity.png">
*
*
* ## Copyright
* &copy; 2021 Laura Arias Fernandez, Michael Weiner, and Malik Khadar  All rights reserved.
*/