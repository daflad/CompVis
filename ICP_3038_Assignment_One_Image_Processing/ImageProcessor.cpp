//
//  ImageProcessor.cpp
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Macintosh on 19/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "ImageProcessor.h"

// Image Processing Setup
//-----------------------------------------------------------------------

ImageProcessor::ImageProcessor(string filePath) {
    contrast = 1.0f;
    brightness = 0.0f;
    colourfullness = 1.0f;
    eq = false;
    ERROR = false;
    err = "\nERROR : ";
    img = cv::imread(filePath, CV_32FC3);
    // check image has loaded data
    if (img.data) {
        cv::cvtColor(img, hsv, CV_BGR2HSV);
        hsv_clone = hsv.clone();
    } else {
        ERROR = true;
        err = err + "\"" + filePath + "\" is an invalid image path. " +
        "\nPlease try again with a different path.";
    }
    initHist();
}

// Image Display
//-----------------------------------------------------------------------

void ImageProcessor::processImage(cv::Mat *img, bool v){
    // if V of HSV being adjested
    if (v) {
        histEq();
        brightnessContrast();
        sharpnessAdjustment();
    }
    // The final outputted image
    cv::Mat out;
    // Return from HSV to BGR
    cv::cvtColor(*img, out, CV_HSV2BGR);
    // Find center point of image
    cv::Point2f imgCenter(img->cols/2.0F, img->rows/2.0F);
    // Construct a rotation matrix
    cv::Mat rot_mat = getRotationMatrix2D(imgCenter, rotation, 1.0);
    // Rotate
    warpAffine(out, out, rot_mat, img->size());
    // Crop image
    // if 0 then no rotation and no need to crop
    if (rotation != 0) {
        // Convert absolute value to radians
        float r = std::abs(rotation) * M_PI / 180;
        float w, h;
        // Calulate size of inner rectangle
        if (out.cols < out.rows) {
            w = ((out.cols * std::cos(r)) - (out.rows * std::sin(r))) / std::cos(2*r);
            h = out.rows * (w / out.cols);
        } else {
            h = ((out.rows * std::cos(r)) - (out.cols * std::sin(r))) / std::cos(2*r);
            w = out.cols * (h / out.rows);
        }
        // Extract from image
        cv::getRectSubPix(out, cv::Size((int)w, (int)h), imgCenter, out);
    }
    // Update save image
    img_to_save = out.clone();
    // add image to window
    cv::imshow("image", out);
}

// Histogram Calculations
//-----------------------------------------------------------------------

// Clear histogram to 0 each time it's calculated
void ImageProcessor::initHist() {
    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }
}

// Index hist with pixel values of V component of HSV image
void ImageProcessor::getHist() {
    initHist();
    for (int i = 0; i < hsv.rows; i++) {
        for (int j = 0; j < hsv.cols; j++) {
            hist[hsv_clone.at<cv::Vec3b>(i,j)[2]]++;
        }
    }
}

// Perform histogram equalisation if required.
void ImageProcessor::histEq() {
    if (eq) {
        // Must generate hist before it can be eq'd
        getHist();
        
        // Scale factor as max pixel val / total pix
        float numPix = img.rows * img.cols;
        float scale = 255.0f / numPix;
        
        // Populate look up table
        int lookUp[256] = {};
        // Will act as a cumulative histogram
        // to be scaled and rounded down for look up table
        float sum = 0;
        for (int i = 0; i < 256; i++) {
            sum += (float)hist[i];
            lookUp[i] = std::floor(sum * scale);
        }
        // Index look up table with pixel valsto get new vals
        for (int i = 0; i < hsv.rows; i++) {
            for (int j = 0; j < hsv.cols; j++) {
                hsv_clone.at<cv::Vec3b>(i,j)[2] =
                saturate_cast<uchar>(lookUp[hsv_clone.
                                            at<cv::Vec3b>(i,j)[2]]);
            }
        }
    } else {
        // If not comupting histogram the overwrite clone image
        cv::cvtColor(img, hsv_clone, CV_BGR2HSV);
    }
}

// Image Adjustments
//-----------------------------------------------------------------------

// Reduce / boost sharpeness as:
// gSharp = f + d(f - (b * f))
// where:
//          f = is original image
//          d = (float) -1 <= d <= 2
//          b = blured image
void ImageProcessor::sharpnessAdjustment() {
    // Blur
    cv::Mat blur;
    cv::GaussianBlur(hsv, blur, cv::Size(9,9), 1);
    // Perform calc for each pixel
    for (int i = 0; i < hsv.rows; i++) {
        for (int j = 0; j < hsv.cols; j++) {
            hsv.at<cv::Vec3b>(i,j)[2] =
            saturate_cast<uchar>(hsv.at<cv::Vec3b>(i,j)[2] +
                                 (sharpness *
                                  (hsv.at<cv::Vec3b>(i,j)[2] -
                                   blur.at<cv::Vec3b>(i,j)[2])));
        }
    }
}

// Adjust brightness and contrast by
// offsetting each value by - 128
// new val = (c * off) + b + 128
// where:
//          c = (float) 0.5 <= c <= 2
//          off = the offset value of the pixel
//          b = (int)
void ImageProcessor::brightnessContrast() {
    for (int i = 0; i < hsv.rows; i++) {
        for (int j = 0; j < hsv.cols; j++) {
            // 1 is the channel where colourfullness lies
            float offset = hsv_clone.at<cv::Vec3b>(i,j)[2] - 128;
            float new_c = (contrast * offset) + brightness + 128;
            hsv.at<cv::Vec3b>(i,j)[2] = saturate_cast<uchar>( new_c );
        }
    }
}

// Adjust colourfullness (S from HSV) by scaling the original
// value from 0 to 2 * OriginalValue.
void ImageProcessor::adjustColourfullness(int *val) {
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

// Save Image To Disk
//-----------------------------------------------------------------------

void ImageProcessor::writeImageToDisk(string path) {
    if (cv::imwrite(path, img_to_save)){
        std::cout << "Image saved to : " << path << endl;
    } else {
        std::cout << "Unable to save image with " << path << endl;
    }
}















