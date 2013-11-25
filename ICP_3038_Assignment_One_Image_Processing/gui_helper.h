//
//  gui_helper.h
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Stephen Russell on 10/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __ICP_3038_Assignment_One_Image_Processing__gui_helper__
#define __ICP_3038_Assignment_One_Image_Processing__gui_helper__

#include <iostream>
#include <opencv2/opencv.hpp>

void processImage(cv::Mat*);
void setupControlWindow(int);
void controlWindowCallback(int, void*);
void colourfullnessCallback(int, void*);
void brightnessCallback(int, void*);
void contrastCallback(int, void*);

#endif /* defined(__ICP_3038_Assignment_One_Image_Processing__gui_helper__) */

