//
//  main.cpp
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Stephen Russell on 28/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "ImageProcessor.h"



// Main Function
// Check aruments passed, Setup control & display windows,
// Display image & wait for key press
int main(int argc, const char * argv[])
{
    ImageProcessor ip(1.5f, 100.0f, 100);
    // Check any arguments have been passed
    if (ip.checkInputArgs(argc, argv)) {
        // Setup image window
        cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
        // control window
        void *ipp = static_cast< void *>(&ip);
        ip.setupControlWindow(ip.img.cols, &ipp);
        // display image
        ip.processImage(false);
        // exit on keystroke
        waitKey(0);
        return 0;
    } else {
        // Return error message
        std::cerr <<
        "Please supply a valid path to an image to be displayed."
        << endl;
        return -1;
    }
    
}

/*
 //
 //  main.cpp
 //  ICP_3038_Assignment_One_Image_Processing
 //
 //  Created by Stephen Russell on 28/10/2013.
 //  Copyright (c) 2013 Stephen John Russell. All rights reserved.
 //
 
 #include <iostream>
 #include <opencv2/opencv.hpp>
 #include "main.h"
 
 using namespace std;
 using namespace cv;
 
 cv::Mat img;
 cv::Mat hsv;
 cv::Mat hsv_clone;
 bool eq = false;
 bool hi = false;
 
 int main(int argc, const char * argv[])
 {
 contrast = 1;
 brightness = 0;
 // Check any arguments have been passed
 if (checkInputArgs(argc, argv)) {
 // Setup image window
 cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
 cv::moveWindow("image", 0, 0);
 // control window
 setupControlWindow(img.cols);
 // display image
 processImage(&hsv, false);
 // wait for key stroke
 cv::waitKey(0);
 // exit on keystroke
 } else {
 // Return error message
 std::cerr << "Please supply a valid path to an image to be displayed."
 << endl;
 return -1;
 }
 
 return 0;
 }
 
 // Process image according to the
 void processImage(cv::Mat *img, bool v){
 if (v) {
 histEq();
 brightnessContrast();
 }
 // open window for display
 cv::Mat out[3];
 cv::cvtColor(*img, *out, CV_HSV2BGR);
 // add image to window
 cv::imshow("image", *out);
 }
 
 void setupControlWindow(int imgWidth){
 int colness = 250;
 int brtness = 100;
 int conness = 100;
 // open window for display
 cv::namedWindow("control", CV_WINDOW_FREERATIO);
 cv::resizeWindow("control", 300, 400);
 cv::moveWindow("control", imgWidth + 20, 0);
 //Create treackbars
 //Brighthness, Contrast, Colourfullness, Sharpness and Histogram equalisa- tion
 cv::createTrackbar("Brighthness", "control", &brtness, 200, brightnessCallback);
 cv::createTrackbar("Contrast", "control", &conness, 200, contrastCallback);
 cv::createTrackbar("Colourfullness", "control", &colness, 500, colourfullnessCallback);
 cv::createTrackbar("Hist Eq", "control", 0, 1, histEqCallback);
 //cv::createTrackbar("Sharpness", "control", 0, 1, *controlWindowCallback);
 
 }
 
 
 void histEq() {
 if (eq) {
 // pre allocate hist array
 int hist[256] = {};
 // Calc hist
 for (int i = 0; i < hsv.rows; i++) {
 for (int j = 0; j < hsv.cols; j++) {
 hist[hsv_clone.at<cv::Vec3b>(i,j)[2]]++;
 }
 }
 float numPix = img.rows * img.cols;
 float scale = 255.0f / numPix;
 int lookUp[256] = {};
 float sum = 0;
 for (int i = 0; i < 256; i++) {
 sum += (float)hist[i];
 lookUp[i] = std::floor(sum * scale);
 }
 for (int i = 0; i < hsv.rows; i++) {
 for (int j = 0; j < hsv.cols; j++) {
 hsv_clone.at<cv::Vec3b>(i,j)[2] =
 saturate_cast<uchar>(lookUp[hsv_clone.at<cv::Vec3b>(i,j)[2]]);
 }
 }
 } else {
 cv::cvtColor(img, hsv_clone, CV_BGR2HSV);
 }
 }
 
 void brightnessContrast() {
 for (int i = 0; i < hsv.rows; i++) {
 for (int j = 0; j < hsv.cols; j++) {
 // 1 is the channel where colourfullness lies
 float offset = hsv_clone.at<cv::Vec3b>(i,j)[2] - 255;
 float new_c = (contrast * offset) + brightness + 255;
 hsv.at<cv::Vec3b>(i,j)[2] = saturate_cast<uchar>( new_c );
 }
 }
 }
 
 void adjustColourfullness(int *val) {
 // 500 is slider max value
 float ratio = (float)*val / 250;
 for (int i = 0; i < hsv.rows; i++) {
 for (int j = 0; j < hsv.cols; j++) {
 // 1 is the channel where colourfullness lies
 float new_c = hsv_clone.at<cv::Vec3b>(i,j)[1] * ratio;
 hsv.at<cv::Vec3b>(i,j)[1] = saturate_cast<uchar>( new_c );
 }
 }
 }
 
 void histEqCallback(int pos, void*){
 eq = pos == 1;
 processImage(&hsv, true);
 }
 
 void colourfullnessCallback(int val, void*){
 adjustColourfullness(&val);
 processImage(&hsv, false);
 }
 
 void brightnessCallback(int val, void*){
 brightness = val - 100;
 processImage(&hsv, true);
 }
 
 void contrastCallback(int val, void*){
 contrast = 2.5 - ((float)val / 100) + 0.5;
 contrast = 3 - contrast;
 processImage(&hsv, true);
 }
 
 // Check input arguments and load image.
 // Convert image to hsv values & clone.
 // Steps 1 & 2 of assignment processing pipeline are dealt with here.
 bool checkInputArgs(int argc, const char * argv[]) {
 
 if (argc >= 2) {
 // try to load image.
 img = cv::imread(argv[2], CV_32FC3);
 // check image has loaded data
 if (img.data) {
 cv::cvtColor(img, hsv, CV_BGR2HSV);
 hsv_clone = hsv.clone();
 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 
 }*/