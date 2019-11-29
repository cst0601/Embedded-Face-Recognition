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
    return inputFrame;
}

void Capturer::release ()
{
    video.release();
}

Capturer * Capturer::instance = 0;

