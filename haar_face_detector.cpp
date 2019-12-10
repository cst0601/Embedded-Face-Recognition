#include "haar_face_detector.h"

HaarFaceDetector::HaarFaceDetector ()
{
    faceClassifier.load("/home/nvidia/Desktop/model/haarcascades/haarcascade_frontalface_default.xml");
}

std::vector<Rect> HaarFaceDetector::searchFace (Mat inputFrame)
{
    std::vector<Rect> peopleInstances;
    Mat grayFrame;
    cvtColor(inputFrame, grayFrame, COLOR_BGR2GRAY);
    equalizeHist(grayFrame, grayFrame);
    // detect
    faceClassifier.detectMultiScale(grayFrame, peopleInstances, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    return peopleInstances;
}
