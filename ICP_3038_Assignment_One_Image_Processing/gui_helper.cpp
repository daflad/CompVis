//
//  gui_helper.cpp
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Stephen Russell on 10/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include <iostream>

#include <iostream>
#include <opencv2/opencv.hpp>
#include "gui_helper.h"

using namespace std;
using namespace cv;

void setupControlWindow(int imgWidth){
    int colness = 250;
    // open window for display
    cv::namedWindow("control", CV_WINDOW_FREERATIO);
    cv::resizeWindow("control", 300, 400);
    cv::moveWindow("control", imgWidth + 20, 0);
    //Create treackbars
    //Brighthness, Contrast, Colourfullness, Sharpness and Histogram equalisa- tion
    cv::createTrackbar("Brighthness", "control", 0, 200, *brightnessCallback);
    cv::createTrackbar("Contrast", "control", 0, 1, *contrastCallback);
    cv::createTrackbar("Colourfullness", "control", &colness, 500, *colourfullnessCallback);
    cv::createTrackbar("Sharpness", "control", 0, 1, *controlWindowCallback);
    
}

void controlWindowCallback(int pos, void*){
    
}

void colourfullnessCallback(int val, void*){
    
}

void brightnessCallback(int val, void*){
    
}

void contrastCallback(int val, void*){
    
}
