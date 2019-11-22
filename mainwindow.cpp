#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_close_app_button_clicked()
{
    this->close();
}

void MainWindow::on_open_camera_button_clicked()
{
    std::cout << "mumi" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        cv::VideoCapture video(i);
        //開攝影機
        if (!video.isOpened())
        {
            std::cout << "cyka blyat" << i << std::endl;
        }
        video.release();
    }/*
    cv::Mat videoFrame;
    while(true)
    {
        video >> videoFrame;
        //讀Frame
        if(videoFrame.empty()){break;}
        cv::cvtColor(videoFrame, videoFrame, CV_BGR2RGB);
        QPixmap image = QPixmap::fromImage(QImage((unsigned char*) videoFrame.data, videoFrame.cols, videoFrame.rows, QImage::Format_RGB888));
        ui->input_image_label->setPixmap(image);
        qApp->processEvents();
    }*/
}
