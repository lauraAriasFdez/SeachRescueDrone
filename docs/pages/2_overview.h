/*! \page overview Overview
 * This project consists of 2 main subsystems: Image processing and the Rescue simulation
 *
 * ***1. %Image Processing:*** subsystem in charge of applying image filters on images stored locally on your machine. Specifically,
 *  the subsystem is designed to implement a %Canny Edge detection, yet it also allows for more image filtering extensibility if the user
 *  desires to add more filters. 
 * 
 * 
 * Our design follows a facade design pattern, the complexity of the system is hidden and the ImageProcessor behaves as the interface for
 *  a user to interact with.  The %Image Processor contains the possible filters that can be applied to an image, such as `greyscale` and `canny-edge-detect`,
 *  and has a dependency to Image, which means that an Image is not held by the ImageProcessor but rather the ImageProcessor interacts with the Image class 
 *  through the ApplyFiler method based on any Filter type passed as an input parameter. The `sobel` and `non-max` filters
 *  were only designed as if they were being used as part of the canny edge detection, therefore the Image Processor cannot directly implement these two filters. Moreover, it was assumed
 *  that any image passed to the Image Processor as input existed on the filesystem. 
 * 
 * <img alt="Img processor uml diagram" width="100%" src="../pages/images_uml/ImageClass.png">
 * 
 * Images read in from the filesystem are represented as an instance of the Image class, in which each Color object represents a single pixel in the Image, thereby an Image contains 
 * a unique pointer to an array of Colors. 
 * 
 * <img alt="Color and Img class uml diagram" width="100%" src="../pages/images_uml/Color_Img.png">
 * 
 * 
 * The Filter class serves as the abstract base class from which 3 main categories are derived: SimpleFilter, RelatedPixelFilter and Canny. 
 * 
 *  <img alt="Filter uml diagram" width="100%" src="../pages/images_uml/Filter_UML.png">
 * 
 * SimpleFilter has several derived classes:
 * - DoubleThresholdFilter conducts a Double Threshold filter on an image. 
 * - GreyScaleFilter conducts a Grescyale filter on an image.
 * - ThresholdFilter conduts a Threshold filter on an image.
 * 
 * RelatedPixelFilter has several derived classes:
 * - ConvolutionFilter is an abstract, base class that represents another sub-category of filters that require neighboring pixels in an image **and** a kernel to create the new image with the filer applied. 
 * - HysteresisFilter conducts a Hysteresis filter on an image.
 * - NonMaxSupFilter conducts a Non-Max Suppression filter on an image.
 * 
 * ConvolutionFilter has several derived classes:
 * - GaussianFilter conducts a Gaussian filter on an image.
 * - MeanBlurFilter conducts a Mean Blur filter on an image.
 * - SobelFilter conducts a Sobel filter on an image.
 * 
 * The Kernel class is used by the ConvolutionFilter class, and its derived classes, to store and manipulate the kernels for calculation to apply a filter to an image.
 * 
  * ***2. Rescue Simulation:*** subsystem that consists of creating a simulation in which a drone searches for a robot in a scene. This subsystem uses a  web-based visualization system  provided by the CSCI3081
  *  staff. 
  * 
  * In the simulation there are multiple patterns that were used in order to build an extensible simulation. First, the facade design pattern was implemented in order to allow the complexity of
  *  the system to be hidden behind a class called RescueSimulation.
  * 
  * <img alt="Rescue Simulation uml diagram" width="100%" src="../pages/images_uml/Rescue_Simulation.png">
  * 
  * In order to build the Entities, we decided to use an inheritance hierarchy as that will allow for entities to share common attributes like a position or an entityID (to name a few). 
  * 
  * <img alt="All entities uml diagram" width="100%" src="../pages/images_uml/Entities.png">
  * 
  * The Factory pattern was used to create Entities (robot, drone, hospital...etc). No entity was created in the simulation directly, rather the simulation contains a composite factory that when it
  *  receives the command to create an entity it passes the `picsonjson` command to the `CreateEntity(...)` method and the appropriate factory class handles the correct entity creation.
  * 
  * <img alt="Factory Pattern uml diagram" width="100%" src="../pages/images_uml/Entity_Factory.png">
  * 
  * Additionally,the Strategy pattern was implemented for the Drone movement, thereby the Drone will rely on a member variable that points to an instance of the IMovement class to generate the set of 3D vectors the drone must move to depending on its status: looking for
  *  the robot and going to the robot will correspond to patrol and beeline movement respectively. This delegation of movement is necessary as this will allow for other objects to be added to the “movable” property more easily,
  *  if the program was to be extended.
  * 
  * <img alt="Strategy Pattern for Movement uml diagram" width="100%" src="../pages/images_uml/Movement.png">
  * 
  * Finally, in order to allow for searching the drone we created an ObjectDetector class that uses the open-source `opencv` library, rather than our %Image Processing subsystem, to perform blob detection and canny edge detect as that ended up being a much faster 
  * approach than using our filters, which took 15 sec to process a single image. 
  * 
  * <img alt="Camera uml diagram" width="100%" src="../pages/images_uml/Camera.png">
  * 
 * ## Copyright
 * &copy; 2021 Laura Arias Fernandez, Michael Weiner, and Malik Khadar  All rights reserved.
 */