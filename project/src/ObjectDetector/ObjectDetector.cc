/**
 * @file ObjectDetector.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ObjectDetector.h"

ObjectDetector::ObjectDetector(){
    this->x_pos=0;
    this->y_pos=0;
};

bool ObjectDetector::Found(cv::Mat im){

    // Read in the image 
    Mat mask, blob;

    //1- BLOB DETECT___________________________________
    Scalar highTh = Scalar(25,255,255);
    Scalar lowTh = Scalar(12,200,150);
    Mat hsv;
    cvtColor(im, hsv, COLOR_BGR2HSV);
    inRange(hsv, lowTh, highTh, mask);
    bitwise_and(hsv, hsv, blob, mask);

    //2- SET BLOB TO WHITE___________________________________
    Mat whiteBlob;
    inRange(blob, Scalar(1, 1, 1), Scalar(255, 255, 255), whiteBlob);
    blob.setTo(Scalar(255, 255, 255), whiteBlob);

    //3- CANNY EDGE DETECT___________________________________
    int lowThreshold = 40;
    int maxThreshold = 120;
    Mat greyscale,blurred,cannyimg;
    cvtColor (im, greyscale, COLOR_BGR2GRAY);
    GaussianBlur(greyscale, blurred, Size(5,5),2);
    Canny(blurred, cannyimg, lowThreshold, maxThreshold);

    // 4- COUNT THE # OF WHITE PIXELS IN BOTH IMAGES___________________________________
    vector<Point> white_pixels_blob;
    findNonZero(whiteBlob, white_pixels_blob);

    vector<Point> white_pixels_canny;
    findNonZero(cannyimg, white_pixels_canny);

    // 5- DETERMINE IF OBJECT DETECTION___________________________________
    float division;
    // just in case the drone is looking outside the map (to the sky exclusively = no edge)
    if (white_pixels_canny.size() == 0)
        division = 0;
    else
        division = (white_pixels_blob.size() * 100.0)/white_pixels_canny.size();

    std::cout << "the ratio (blob vs canny) when img process " << division << std::endl;
    if (division >= 0.15){
        // find all the contours
        std::vector<std::vector<cv::Point> > contours;
        Mat contourOutput = whiteBlob.clone();
        findContours(contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

        // choose the contour with largest area
        double maxArea = 0;
        int contourId = -1;
        for (int i =0; i < contours.size();i++){
            double area = contourArea(contours[i]);
            if (area > maxArea){
                contourId = i;
                maxArea = area;
            }
        }

        // Find the centroid of contour
        Moments m = moments(contours[contourId],false);
        this->x_pos= (int) (m.m10/m.m00);
        this->y_pos=(int)(m.m01/m.m00);

        return true;
    }

    return false;
}

void ObjectDetector::GetRobotPos(int& robot_x,int& robot_y){
    robot_x = this->x_pos;
    robot_y = this->y_pos;
}