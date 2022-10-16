/*! \page getting-started Getting Started
 * ## Building and Running Project
 * This project has been built using C++ while also being portable for various operating systems and machines with the use of Docker. 
 * 
 * Using this project is achieved by obtaining the source code, meeting the base system requirements, compiling the source code, and then running an image filter on an image that you supply!
 * 
 * ### System Requirements
 * Docker is the only hard system requirement for this project. **Make sure that your system has Docker installed before proceeding.**
 * 
 * Installation instructions for Docker can be found here: [https://docs.docker.com/get-docker/](https://docs.docker.com/get-docker/).
 * 
 * Docker provides the system requirements needed to run Docker on all of the major operating systems here:
 * - [Docker System Requirements for Windows](https://docs.docker.com/desktop/windows/install/)
 * 		- WSL 2 Backend and Hyper-V Backend and Windows Containers installation options are available
 * - [Docker System Requirements for macOS](https://docs.docker.com/desktop/mac/install/#system-requirements)
 *  	- Macs with Intel Chipssets and Macs with Apple Silicon SoCs installation options are available
 * 
 * ### Obtaining the Source Code
 * This code is available within a Github repository found here: [https://github.umn.edu/umn-csci-3081-f21/repo-team-54](https://github.umn.edu/umn-csci-3081-f21/repo-team-54).
 * 
 * Visit the repository and `clone` the repo into a directory on your local machine. If you have git installed on your machine, create a directory where you would like to save the source code and run the following command to obtain a local copy of the codebase on your machine: `git clone https://github.umn.edu/umn-csci-3081-f21/repo-team-54.git` 
 * 
 * ### Running Source Code in Docker Development Environment
 * Once your have installed Docker on your machine and you have cloned the source code from Githib onto your local machine, you are now ready to run the compile and run the project source code. 
 * 
 * #### Build Docker Development Environment
 * The project provides a Dockerfile to handle most everything with Docker. To build your Docker environment:
 * 1. Start Docker Desktop on your local machine.
 * 2. Navigate to the directory on your local machine where you have stored the source code.
 * 3. Enter the command `bin/build-env.sh`. This will run the Docker file to build an image with all of the dependnecies needed for the project to run successfully.
 * 	1. **Note:** This process could take several minutes and only has to be done once. On future start ups of your Docker container, skip to step 4.
 * 4. Remain at the root of the directory on your local machine where the project source code is. Run the command `bin/run-env.sh`. This will place you into a Docker container capable of complining and running the project.
 * 	1. **Note:** The directory space in the Docker container is identical to that of the directory on your local machine where you stored the source code for this project.
 * 5. **When** you wan to exit your Docker container run the command `exit`. 
 * 	1. **Note:** Your Docker container will be deleted upon exiting. Don't worry - we will handle the clean up for you.
 * 6. When you want to re-start your Docker container, repeat steps 1, 2, and 4.
 *
 * #### Running the Rescue Simulation
 * 1. Start run the Docker container using the instructions in the **Build Docker Environment** above.
 * 2. Within your Docker container, navigate into the `project/src/` directory where the source code for the simulation is located. This can be done by running the `cd project/src/` command.
 * 3. Run the command `make clean && make -j` to compile all of the source code required to run the simulation.
 * 4. You are now ready to run the project using the following command: `./build/web-app <port> <web-server-directory>`
 * 	1. `<port>` is the port that you want to run the webserver on (e.g. `8081`)
 * 	2. `<web-server-directory>` is relative path to a directory containing all of the HTML, JS, and CSS files needed for the webserver (e.g. `web/`)
 *
 * By running the following command from the `project/src/` directory: `./build/web-app 8081 web/`, the simulation will start. The simulation can be viewed on a local web browser on your machine at [127.0.0.1:8081](http://127.0.0.1:8081/).
 * 
 * #### Running an %Image %Filter on An %Image (Command-Line Tool)
 * 1. Start run the Docker container using the instructions in the **Build Docker Environment** above.
 * 2. Within your Docker container, navigate into the `project/ImageProcessing/` directory where the source code is located. This can be done by running the `cd project/ImageProcessing/` command.
 * 3. Run the command `make clean && make -j` to compile all of the source code required to run the %image processor.
 * 4. You are now ready to run the project using the following command: `./image_processor <inputImage> <filter> <outputImage>`
 * 	1. `<inputImage>` is a string that represents the relative path to the image that you want to apply a filter to (e.g. `"data/dog.png"`)
 * 	2. `<filter>` is a string that represents the type of filter that you want to apply to your image. The filter options include:
 *			1. greyscale - Applies a Greyscale filter to the `<inputImage>` specified.
 *			2. threshold - Applies a Threshold filter with a threshold of 0.50 to the `<inputImage>` specified.
 *			3. threshold-low - Applies a Threshold filter with a threshold of 0.25 to the `<inputImage>` specified.
 *			4. threshold-high - Applies a Threshold filter with a threshold of 0.75 to the `<inputImage>` specified.
 *			5. mean_blur - Applies a Mean Blur filter to the `<inputImage>` specified.
 *			6. gaussian - Applies a Gaussian Blur filter with a kernel size of 5 and a sigma value of 2 to the `<inputImage>` specified.
 *			7. double_threshold_filter - Applies a Double Threshold filter with a low threshold ratio of 0.10 and a high threshold ratio of 0.20 to the `<inputImage>` specified.
 *			8. hysteresis_filter - Applies a Hysteresis filter with a weak threshold of 25.0 and a strong threshold of 255.0 to the `<inputImage>` specified.
 *			9. canny-edge-detect - Applies a %Canny Edge Detection to the `<inputImage>` specified.
 * 	3. `<outputImage>` is a string that represents the relative path and file name of the image that will be generated by applying the specificed filter.
 *
 * As an example, assume that in the directory on your local machine that stores this project's source code you add a directory named `data` to store the images that you want to apply filters to.
 * By running the following command from the `project/ImageProcessing/` directory: `./image_processor "data/dog.png" canny-edge-detect "data/dog-canny.png"`, the project will find the image named dog.png in the `data` directory one level up from the `project` directory. The program will then run a %Canny Edge Detection on the `dog.png` image and the resulting output image will be saved in the `data` directory with the name of `dog-canny.png`.
 * 
 * #### Running the Test Suite
 * This application does come with a test suite built on Google's Test application suite. These test can be run anytime to check that existing functionality is working and that any new functionality is not breaking existing functionality. To compile and run the tests:
 * 1. Start run the Docker container using the instructions in the **Build Docker Environment** above.
 * 2. Within your Docker container, navigate into the `project/tests/` directory where the test source code for the project is located. This can be done by running the `cd project/tests/` command.
 * 3. Run the command `make clean && make -j` to compile all of the source code required to run the simulation.
 * 4. You are now ready to run test suite using the following command: `./build/test-app`
 *
 * The test-suite will run and all tests should be have a passing state.
 * 
 * ### Run Compiled Project in Docker
 * The compiled project source code is also available in a pre-built Docker %Image.
 * 
 * To use this pre-built Docker %Image, Docker needs to be installed on your system. View the **System Requirements** section at the top of this page for resources to help get Docker installed on your machine.. 
 * 
 * Once Docker is installed on your system, you can view the pre-built image at [https://hub.docker.com/r/michaelweiner/sim](https://hub.docker.com/r/michaelweiner/sim). The Docker Hub listing has a `README` that walks you through how to pull the latest version of the Docker %Image and get it running on your machine.
 * 
 * ## Copyright
 * &copy; 2021 Laura Arias Fernandez, Michael Weiner, and Malik Khadar  All rights reserved.
 */