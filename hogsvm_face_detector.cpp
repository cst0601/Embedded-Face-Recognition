#include "hogsvm_face_detector.h"

HogSvmFaceDetector::HogSvmFaceDetector (int featureAmount):
    featureAmount(featureAmount)
{
    std::cout << "132" << std::endl;
    svm = SVM::create();
    // set svm params
    svm->setKernel(SVM::LINEAR);
    svm->setType(SVM::C_SVC);
    svm->setC(1);
    svm->setTermCriteria(cv::TermCriteria(CV_TERMCRIT_ITER, 100, 0.000001));
}

void HogSvmFaceDetector::readTrainingData(
        std::string datasetFilePath)
{
    std::vector<String> personFolder;
    std::cout << datasetFilePath << std::endl;
    readAllPersonDir(datasetFilePath, personFolder);
    std::cout << "folders= " << personFolder.size() << std::endl;
    for (int i = 0; i < personFolder.size(); ++i)
    {
        if (personFolder[i] == "." || personFolder[i] == "..")
            continue;
        std::cout << "folder name: " << personFolder[i] << std::endl;
        std::vector<Mat> personImages;
        std::vector<String> fileNames;
        glob(datasetFilePath +
             personFolder[i] +
             "/*.jpg", fileNames); // get the filenames of a person's folder
        for (int j = 0; j < fileNames.size(); ++j)
        {
            std::cout << "[read]: filename " << fileNames[j] << std::endl;
            personImages.push_back(imread(fileNames[j]));
        }
        trainingData.push_back(personImages);
    }
}

void HogSvmFaceDetector::readAllPersonDir (std::string path, std::vector<String> & folder)
{
    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir(path.c_str());
    if (dpdf != NULL){
       while (epdf = readdir(dpdf)){
            folder.push_back(epdf->d_name);
       }
    }
    closedir(dpdf);
}
/*12996*/
void HogSvmFaceDetector::hogsvm()
{
    int trainingDataAmount = 0;
    for (int personIndex = 0; personIndex < trainingData.size(); ++personIndex)
        trainingDataAmount += trainingData[personIndex].size();

    std::vector<float> feature;
    cv::Mat sampleFeatures = cv::Mat(cv::Size(featureAmount, trainingDataAmount), CV_32FC1);
    cv::Mat sampleLabels = cv::Mat(cv::Size(1, trainingDataAmount), CV_32SC1);
    std::cout << "trainingData.size() = " << trainingData.size() << std::endl;
    for (int personIndex = 0; personIndex < trainingData.size(); personIndex++)
    {
        std::cout << "Person " << personIndex << " hog" << std::endl;
        for (int i = 0; i < trainingData[personIndex].size(); ++i)
        {
            //imshow("training image", trainingData[personIndex][i]);
            //waitKey(1);
            hogDescriptor.compute(trainingData[personIndex][i], feature);       // in sample, reads image in gray scale
            for (int featureIndex = 0; featureIndex < featureAmount; ++featureIndex)
            {
                sampleFeatures.ptr<float>(i)[featureIndex] = feature[featureIndex];
            }
            feature.clear();
        }
        sampleLabels.ptr<float>(personIndex)[0] = personIndex;
    }
    trainSvm(sampleFeatures, sampleLabels);
}

void HogSvmFaceDetector::trainSvm (cv::Mat sampleFeatures, cv::Mat sampleLabel)
{
    svm->train(sampleFeatures, ROW_SAMPLE, sampleLabel);
    svm->save("/home/nvidia/Desktop/model/face.xml");
}

int HogSvmFaceDetector::test(Mat testData)
{
    std::cout << "testData size: " << testData.cols << " " << testData.rows << std::endl;
    svm = SVM::load("/home/nvidia/Desktop/model/face.xml");
    cv::Mat testFeatures = cv::Mat(cv::Size(featureAmount, 1), CV_32FC1);
    std::vector<float> feature;
    hogDescriptor.compute(testData, feature);
    for (int featureIndex = 0; featureIndex < featureAmount; ++featureIndex)
    {
        testFeatures.ptr<float>(0)[featureIndex] = feature[featureIndex];
    }
    return svm->predict(testFeatures);

}

