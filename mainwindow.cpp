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
        ui->input_image_label->setPixmap(image);
        on_face_recog_button_clicked();
        updateFaceNumberLabel();
        qApp->processEvents();
    }
}

void MainWindow::on_face_recog_button_clicked()
{

    QPixmap image = model.getDetectFrame();
    ui->detect_image_label->setPixmap(image);
    qApp->processEvents();

}

void MainWindow::on_face_add_button_clicked()
{
    FaceCapture faceCaptureDialog;
    faceCaptureDialog.setModal(true);
    faceCaptureDialog.exec();
}
