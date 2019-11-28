#include "facecapture.h"
#include "ui_facecapture.h"

FaceCapture::FaceCapture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceCapture)
{
    ui->setupUi(this);
}

FaceCapture::~FaceCapture()
{
    delete ui;
}

void FaceCapture::on_capture_button_clicked()
{
    QPixmap image = model.captureFace();
    ui->capture_label->setPixmap(image);
    model.release();
}
