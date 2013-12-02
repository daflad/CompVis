//
//  main.cpp
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Stephen Russell on 28/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "ImageProcessor.h"

//-----------------------------------------------------------------------
// Slider Callbacks
//-----------------------------------------------------------------------

// If the slider is equal to 1 the histEq perfomed.
void histEqCallback(int pos, void *ipPtr){
    ImageProcessor *ip = static_cast<ImageProcessor *>(ipPtr);
    ip->eq = pos == 1;
    ip->processImage(&ip->hsv, true);
}

// adjustColourfullness is on it's own branch for imagae processing
// send value to adjustColourfullness before calling processImage
void colourfullnessCallback(int val, void *ipPtr){
    ImageProcessor *ip = static_cast<ImageProcessor *>(ipPtr);
    ip->adjustColourfullness(&val);
    ip->processImage(&ip->hsv, false);
}

// Brightness varies from -100 to 100
// Max slider value is 200
void brightnessCallback(int val, void *ipPtr){
    ImageProcessor *ip = static_cast<ImageProcessor *>(ipPtr);
    ip->brightness = val - 100;
    ip->processImage(&ip->hsv, true);
}

// Contrast varies from 0.5 to 2
// Max slider value is 200
void contrastCallback(int val, void *ipPtr){
    ImageProcessor *ip = static_cast<ImageProcessor *>(ipPtr);
    ip->contrast = ((float)val / 100) + 0.5;
    ip->contrast = ip->contrast;
    ip->processImage(&ip->hsv, true);
}

// Sharpness varies from -1 to 2
// max slider value is 300
void sharpnessCallback(int val, void *ipPtr){
    ImageProcessor *ip = static_cast<ImageProcessor *>(ipPtr);
    ip->sharpness = ((float)val / 100) - 1;
    ip->processImage(&ip->hsv, true);
}

// Rotation varies from -30 to 30
// Max slider value is 60
// Smaller range to ensure 0 can be found again.
void rotationCallback(int val, void *ipPtr){
    ImageProcessor *ip = static_cast<ImageProcessor *>(ipPtr);
    ip->rotation = (val - 3000) / -100;
    ip->processImage(&ip->hsv, true);
}

//-----------------------------------------------------------------------
// Image & control window setup
//-----------------------------------------------------------------------

// Create windows and trackbars for application
void setupControlWindow(int imgWidth, ImageProcessor *imp){
    // Initial slider values
    int colness = 250;
    int brtness = 100;
    int conness = 100;
    int sharess = 150;
    int rotness = 3000;
    // Image window
    cv::namedWindow("image", CV_WINDOW_FREERATIO);
    // Control window
    cv::namedWindow("control", CV_WINDOW_FREERATIO);
    cv::resizeWindow("control", 400, 300);
    cv::moveWindow("control", imgWidth + 20, 0);
    //Create treackbars
    //Brighthness, Contrast, Colourfullness, Sharpness and Histogram equalisa- tion
    cv::createTrackbar("Brighthness", "control", &brtness, 200, brightnessCallback, imp);
    cv::createTrackbar("Hist Eq", "control", 0, 1, histEqCallback, imp);
    cv::createTrackbar("Contrast", "control", &conness, 200, contrastCallback, imp);
    cv::createTrackbar("Sharpness", "control", &sharess, 300, sharpnessCallback, imp);
    cv::createTrackbar("Colourfullness", "control", &colness, 500, colourfullnessCallback, imp);
    cv::createTrackbar("Rotation", "control", &rotness, 6000, rotationCallback, imp);
    
}

//-----------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    // Check any arguments have been passed
    if (argc >= 2) {
        ImageProcessor ip(argv[1]);
        if (ip.ERROR) {
            std::cerr << ip.err << endl;
            return -1;
        }
        setupControlWindow(ip.img.cols, &ip);
        // display image
        ip.processImage(&ip.hsv, false);
        // wait for key stroke
        cv::waitKey(0);
        
        if (argc >= 3) {
            ip.writeImageToDisk(argv[2]);
        }
    } else {
        // return error message
        // if not enough parameters passed at run time
        std::cerr << "Please supply a path to an image to be displayed."
        << endl;
        return -1;
    }
    return 0;
}
