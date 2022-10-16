/*! \mainpage Gopher Search-and-Rescue (G-SAR) Simulation
 * G-SAR is a simulation of a drone with an attached camera being used for the search and rescue of one or more subjects. The onboard camera is used to take aerial pictures of a landscape, a sub-application analyzes the images using image filtering, and when the subject is detected in an image the coordinates of the subject are sent to the %drone for investigation. Once the %drone has found the subject, a larger rescue done is sent to the coordinates of the drone to rescue the subject. The rescued subject is then flown to a local hospital.
 *
 * This application is a proof-of-concept of how the use of drones in a search and rescue situation can be utilized. Where humans might have problems navigating in rural areas, after a natural disaster event, etc. a %drone can be launched quickly and in almost any location on Earth. As tablet and smartphone processors have advanced, the general application could be used in remote areas without power to conduct search and rescues. This tool could be used as a foundation for new life saving search and rescue capabilities that come with the use of this technology.
 * 
 * ## Learn About G-SAR
 * Below you will find quick links to get an overview of this application, learn how to download the source code to get started, and how to contribute new features to the codebase.
 * 1. \ref overview
 *  - Learn more about the overall structure of G-SAR and its subsystems.
 * 2. \ref getting-started
 *  - Learn more about how to clone, build, and run this project. 
 * 3. \ref contributing
 *  - Learn more about the process of contributing new features to the open-source codebase. 
 * 4. \ref image-processing
 *  - Learn more about command-line image processing application that is apart of this codebase.
 * 5. \ref simulation
 *  - Learn more about rescue simulation application that is apart of this codebase.
 *
 * ## Open Source Dependencies
 * This project does use the following header files from the [stb library](https://github.com/nothings/stb):
 * - stb_image.h
 * - stb_image_write.h
 * 
 * These header files are public domain C image loading and image writing libraries. Credit to the team at [nothings](http://nothings.org) for this great work!
 * 
 * This project uses the OpenCV library for image processing within the ObjectDetector class used for the RescueSimulation [OpenCV library](https://github.com/opencv/opencv). Credit to the team at [OpenCV](https://opencv.org/) for their amazing work!
 *
 * This project's test suite is built on [GoogleTest](https://github.com/google/googletest). A big thank you to the team at Google for this test framework foundation!
 *
 * ## References
 * The general algorithms for the Gaussian, Sobel, Non-Maximum Suppression, Double Threshold, and Hysteresis filters in the command-line %Image Processing tool were created using the algorithms defined here: https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
 * 
 * Each algorithm was modified based on the specified design of this project. Credit for the general implementation of the algorithms should be awarded to the Towards Data Science group.
 * 
 * ## Copyright
 * &copy; 2021 Laura Arias Fernandez, Michael Weiner, and Malik Khadar  All rights reserved.
 */