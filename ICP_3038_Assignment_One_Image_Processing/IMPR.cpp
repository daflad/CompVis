//
//  IMP.cpp
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Macintosh on 19/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "IMPR.h"

IMPR::IMPR(int _col, cv::Mat *_img, cv::Mat *_hsv, cv::Mat *_hsv_clone){
    this->colourfullness = _col;
    this->img = _img;
    this->hsv = _hsv;
    this->hsv_clone = _hsv_clone;
}

void IMPR::setColourfullness(int _c){
    this->colourfullness = _c;
}

// Check input arguments and load image.
// Convert image to hsv values & clone.
// Steps 1 & 2 of assignment processing pipeline are dealt with here.
bool IMPR::checkInputArgs(int argc, const char * argv[]) {
    
    if (argc >= 2) {
        // try to load image.
        *this->img = cv::imread(argv[1], CV_32FC3);
        // check image has loaded data
        if (!this->img->empty()) {
            cv::Mat t = cv::Mat(this->img->rows, this->img->cols, this->img->type());
            this->hsv = &t;
            this->hsv_clone = &t;
            cv::cvtColor(*this->img, *this->hsv, CV_BGR2HSV);
            this->hsv->copyTo(*this->hsv_clone);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void IMPR::setupControlWindow(int imgWidth, void *ip){
    int colness = 250;
//    int brtness = 100;
//    int conness = 75;
    // open window for display
    cv::namedWindow("control", CV_WINDOW_FREERATIO);
    cv::resizeWindow("control", 300, 400);
    cv::moveWindow("control", imgWidth + 20, 0);
    //Create treackbars
    //Brighthness, Contrast, Colourfullness, Sharpness and Histogram equalisa- tion
//    cv::createTrackbar("Brighthness", "control", &brtness, 200, ImageProcessor::brightnessCallback, &ip);
//    cv::createTrackbar("Contrast", "control", &conness, 150, ImageProcessor::contrastCallback, &ip);
    cv::createTrackbar("Colourfullness", "control", &colness, 500, IMPR::colourfullnessCallback, &ip);
//    cv::createTrackbar("Hist Eq", "control", 0, 1, ImageProcessor::histEqCallback, &ip);
    //cv::createTrackbar("Sharpness", "control", 0, 1, *controlWindowCallback);
}

// Adjust colourfullness
void IMPR::adjustColourfullness(int *val) {
    // 500 is slider max value
    float ratio = (float)*val / 250;
    for (int i = 0; i < this->hsv->rows; i++) {
        for (int j = 0; j < this->hsv->cols; j++) {
            // 1 is the channel where colourfullness lies
            float new_c = this->hsv_clone->at<cv::Vec3b>(i,j)[1] * ratio;
            this->hsv->at<cv::Vec3b>(i,j)[1] = saturate_cast<uchar>( new_c );
        }
    }
}


// Process image according to the image processing pipline defined
void IMPR::processImage(){
//    if (v) {
//        histEq();
//        std::printf("hist\n");
//        brightnessContrast();
//        std::printf("bri\n");
//    }
    // open window for display
    cv::Mat out;
    printf("Rows: %i\nCols: %i", this->hsv->rows, this->hsv->cols);
    cv::cvtColor(*this->hsv, out, CV_HSV2BGR);
    // add image to window
    cv::imshow("image", out);
}

// Pass current value of slider to function as no need to scale
void IMPR::colourfullnessCallback(int val, void *ud){
    IMPR *ip = static_cast<IMPR *>(ud);
    ip->adjustColourfullness(&val);
    ip->processImage();
}