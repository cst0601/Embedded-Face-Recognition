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
    //model.saveTrainingData();
    model.pushFrameToData();
}

void FaceCapture::on_buttonBox_clicked(QAbstractButton *button)
{
    continueCapture = false;
    if (button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        std::string faceName = ui->name_line_edit->text().toStdString();
        if (faceName != "") {
            model.setFaceName (faceName);
        }
        model.saveTrainingData();
    }
}


void FaceCapture::on_capture_button_pressed()
{
    while (continueCapture)
    {
        ui->capture_label->setPixmap(model.captureFace());
        qApp->processEvents();
    }
}
