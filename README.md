# Embeeded Face Recognition

Face recognition software for embedded systems that could recognize people and their faces.

## To build
To make it run on embedded systems(TX2), setup Qt cross platform compile to build.
If you are building this on an embedded system, install Qt and build it using CMake.

## Requirements
- OpenCV 3.3.0
- OpenCV contrib
- Qt 5 

## Demo
![Demo](https://i.imgur.com/jxyewOi.png)
* Capture user's face. after pressing the OK button, the software will re-train the model to recognize the new addd user.
