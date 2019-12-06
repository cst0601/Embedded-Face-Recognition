#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "facecapture.h"
#include "recognition_model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateFaceNumberLabel ();
    void updatePeopleNumberLabel ();
    void updateDetectLabel();

private slots:
    void on_close_app_button_clicked();

    void on_open_camera_button_clicked();

    void on_face_recog_button_clicked();

    void on_face_add_button_clicked();

private:
    Ui::MainWindow *ui;
    RecognitionModel model;
};

#endif // MAINWINDOW_H
