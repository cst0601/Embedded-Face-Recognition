#include "capturer.h"

Capturer::Capturer(): video(0)
{}

Mat Capturer::getFrame()
{
    Mat inputFrame;
    video >> inputFrame;
    //read frame
    if(inputFrame.empty())
    {
        std::cout << "ERROR opening camera" << std::endl;
        throw (std::string)"empty frame";
    }
    //Mat testFrame = imread("/home/nvidia/Desktop/test_pedestrian_2.jpg", IMREAD_COLOR);
    return inputFrame;
}

void Capturer::release ()
{
    video.release();
}

Capturer * Capturer::instance = 0;

