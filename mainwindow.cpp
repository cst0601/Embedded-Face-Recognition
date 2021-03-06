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

void MainWindow::updateFaceNumberLabel ()
{
    QString str = QString::fromUtf8(model.getNumberOfFaces().c_str());
    ui->face_counter_label->setText(str);
}

void MainWindow::updatePeopleNumberLabel ()
{
    QString str = QString::fromUtf8(model.getNumberOfPeople().c_str());
    ui->people_counter_label->setText(str);
}

void MainWindow::on_close_app_button_clicked()
{
    this->close();
    model.release();
}

void MainWindow::on_open_camera_button_clicked()
{
    while(true)
    {
        QPixmap image = model.getInputFrame();
        ui->input_image_label->setPixmap(image.scaled(
                                              ui->detect_image_label->width(),
                                              ui->detect_image_label->height(),
                                              Qt::KeepAspectRatio));
        updateDetectLabel();
        updateFaceNumberLabel();
        updatePeopleNumberLabel();
        qApp->processEvents();
    }
}

void MainWindow::on_face_recog_button_clicked()
{
    std::cout << "predict" << std::endl;
    QString str = QString::fromUtf8(model.predictFace().c_str());
    ui->face_index_label->setText(str);
}

void MainWindow::updateDetectLabel()
{
    QPixmap image = model.getDetectFrame();
    ui->detect_image_label->setPixmap(image.scaled(
                                          ui->detect_image_label->width(),
                                          ui->detect_image_label->height(),
                                          Qt::KeepAspectRatio));
}

void MainWindow::on_face_add_button_clicked()
{
    FaceCapture faceCaptureDialog;
    faceCaptureDialog.setModal(true);
    faceCaptureDialog.exec();
}
