//
//  ImageProcessor.h
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Macintosh on 19/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __ICP_3038_Assignment_One_Image_Processing__ImageProcessor__
#define __ICP_3038_Assignment_One_Image_Processing__ImageProcessor__
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ImageProcessor {
    
    public :
    
    cv::Mat img;
    cv::Mat img_to_save;
    cv::Mat hsv;
    cv::Mat hsv_clone;

    double rotation;
    float brightness;
    float contrast;
    int colourfullness;
    int sharpness;
    int hist[256];
    bool eq;
    
    bool ERROR;
    string err;
    
    ImageProcessor(string filePath);
    
    bool checkInputArgs(int argc, const char * argv[]);
    void processImage(cv::Mat*, bool);
    void setupControlWindow(int);
    void adjustColourfullness(int*);
    void brightnessContrast();
    void histEq();
    void sharpnessAdjustment();
    void initHist();
    void getHist();
    cv::Mat* rotateImage(cv::Mat*);
    void writeImageToDisk(string path);

};

#endif /* defined(__ICP_3038_Assignment_One_Image_Processing__ImageProcessor__) */
