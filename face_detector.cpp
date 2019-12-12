#include "face_detector.h"

FaceDetector::FaceDetector ()
{
    model = EigenFaceRecognizer::create();
}

void FaceDetector::readTrainingData(std::string datasetFilePath)
{
    std::vector<std::string> personFolder;   // all the folders of training data (person)
    std::vector<Mat> trainingData;      // all the images goes here
    std::vector<int> trainingLabel;     // all the images' label
    std::cout << datasetFilePath << std::endl;
    readAllPersonDir(datasetFilePath, personFolder);
    std::cout << "folders= " << personFolder.size() << std::endl;
    // for every person (folder) of face images
    for (int i = 0; i < personFolder.size(); ++i)
    {
        std::cout << "folder name: " << personFolder[i] << std::endl;
        std::vector<String> fileNames;
        glob(datasetFilePath +
             personFolder[i].c_str() +
             "/*.jpg", fileNames); // get the filenames of a person's folder
        for (int j = 0; j < fileNames.size(); ++j)
        {
            std::cout << "[read]: filename " << fileNames[j] << std::endl;
            trainingData.push_back(imread(fileNames[j], CV_LOAD_IMAGE_GRAYSCALE));
            trainingLabel.push_back(i);
        }
    }
    trainingImage = trainingData;   // replace all the old images in trainingImage
    label = trainingLabel;
    personName = personFolder;
    std::cout << "personName [1] =" << personName[2] << std::endl;
}

void FaceDetector::readAllPersonDir (std::string path, std::vector<std::string> & folder)
{
    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir(path.c_str());
    if (dpdf != NULL){
        while (epdf = readdir(dpdf)){
            if ((epdf->d_name)[0] != '.')
                folder.push_back(epdf->d_name);
       }
    }
    closedir(dpdf);
}

void FaceDetector::train ()
{
    std::cout << "mumi learning..." << std::endl;
    model->train(trainingImage, label);
    model->write("/home/nvidia/Desktop/model/face.xml");
}

std::string FaceDetector::getNameById(int id)
{
    std::cout << "face name: " << personName.size() << std::endl;
    return personName[id];
}

std::string FaceDetector::test(Mat testData)
{
    Mat testImage;
    cvtColor(testData, testImage, CV_BGR2GRAY);
    model->read("/home/nvidia/Desktop/model/face.xml");
    std::vector<std::string> tempPersonName;
    readAllPersonDir("/home/nvidia/Desktop/face_data/", tempPersonName);
    personName = tempPersonName;
    int id = model->predict(testImage);
    return getNameById(id);
}

