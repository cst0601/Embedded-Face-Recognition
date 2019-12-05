#include "hogsvm_face_detector.h"

HogSvmFaceDetector::HogSvmFaceDetector (int featureAmount):
    featureAmount(featureAmount)
{}

void HogSvmFaceDetector::readTrainingData(
        std::string datasetFilePath)
{
    std::vector<String> personFolder;
    glob(datasetFilePath + "*", personFolder);
    std::cout << personFolder.size() << std::endl;
    for (int i = 0; i < personFolder.size(); ++i)
    {
        std::cout << personFolder[i] << std::endl;
        std::vector<Mat> personImages;
        std::vector<String> fileNames;
        glob(datasetFilePath +
             personFolder[i] +
             "/*.jpg", fileNames); // get the filenames of a person's folder
        for (int j = 0; j < fileNames.size(); ++j)
        {
            std::cout << fileNames[j] << std::endl;
            personImages.push_back(
                        imread(
                            datasetFilePath +
                            personFolder[i] + "/" +
                            fileNames[j]
                            )
                        );
        }
        trainingData.push_back(personImages);
    }
}
