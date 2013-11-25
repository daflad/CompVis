//
//  IMP.h
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Macintosh on 19/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __ICP_3038_Assignment_One_Image_Processing__IMP__
#define __ICP_3038_Assignment_One_Image_Processing__IMP__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class IMPR {
    
    public :
    
    IMPR(int, cv::Mat*, cv::Mat*, cv::Mat*);
    
    cv::Mat *img;
    cv::Mat *hsv;
    cv::Mat *hsv_clone;
    
    int colourfullness;
    void setColourfullness(int);
    
    bool checkInputArgs(int argc, const char * argv[]);
    void setupControlWindow(int, void*);
    
    void adjustColourfullness(int*);
    void processImage();
    
    static void colourfullnessCallback(int, void*);
};

#endif /* defined(__ICP_3038_Assignment_One_Image_Processing__IMP__) */
