## CSci 3081 - Project Testing

This directory contains all of the different types of tests that help to ensure that this project is functional and functions correctly. 

To compile and run these tests in aggregate:
1. Navigate up one directory to `../project`
1. Run `make -j`
1. Run `./build/test-app`

The results of all tests present within the `project/tests/` directory will be displayed on the console.

### Unit Tests  
The project specification requires **at least 10 unit tests** to test the functionality of individual classes. Below are the files in which unit tests can be found and how many unit tests are present in that file.
- 13 Unit Tests - `vector3_test.cc`

### Component Tests  
The project specification requires **at least 5 component tests** to test the functionality of the various facades present within the project. Below are the files in which component tests can be found and how many component tests are present in that file.
- 3 Component Tests - `ObjectDetector.cc`
- 2 Component Tests - `RescueSimulation.cc`

### Integration Tests  
The project specification requires **at least 5 integration tests** to test the functionality of two or more classes working together to create functionality. Below are the files in which integration tests can be found and how many integration tests are present in that file.
- 3 Integration Tests - `drone_test.cc`
- 4 Integration Tests - `CompositeEntityFactory_test.cc`

### Regression Tests  
The project specification requires **at least 5 regression tests** that should always return **true** no matter how the project may evolve over time. Below are the files in which regression tests can be found and how many regression tests are present in that file.
- 3 Regression Tests - `drone_test.cc`
- 5 Regression Tests - `CompositeEntityFactory_test.cc`
