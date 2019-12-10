#ifndef CAPTURER_H
#define CAPTURER_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

class Capturer
{
public:
    static Capturer * getInstance()
    {
        if (instance == nullptr)
            instance = new Capturer();
        return instance;
    }

    Mat getFrame();
    void release ();
protected:
    Capturer ();
    static Capturer * instance;
private:
    VideoCapture video;
};



#endif // CAPTURER_H
