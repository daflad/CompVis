//
//  main.h
//  ICP_3038_Assignment_One_Image_Processing
//
//  Created by Stephen Russell on 10/11/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef ICP_3038_Assignment_One_Image_Processing_main_h
#define ICP_3038_Assignment_One_Image_Processing_main_h

bool checkInputArgs(int argc, const char * argv[]);
void processImage(cv::Mat*, bool);
void setupControlWindow(int);
void adjustColourfullness();
void brightnessCallback(int, void*);
void contrastCallback(int, void*);
void colourfullnessCallback(int, void*);
void histEqCallback(int, void*);
void brightnessContrast();
void histEq();


float brightness;
float contrast;
int colourfullness;
int rotation;
int sharpness;
int hist;

#endif
