#ifndef FACECAPTURE_H
#define FACECAPTURE_H

#include <QDialog>
#include "facecapturemodel.h"

namespace Ui {
class FaceCapture;
}

class FaceCapture : public QDialog
{
    Q_OBJECT

public:
    explicit FaceCapture(QWidget *parent = 0);
    ~FaceCapture();

private slots:
    void on_capture_button_clicked();

private:
    Ui::FaceCapture *ui;
    FaceCaptureModel model;
};

#endif // FACECAPTURE_H
