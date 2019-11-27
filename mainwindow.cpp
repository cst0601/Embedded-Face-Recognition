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
    model.release();
}

void MainWindow::on_open_camera_button_clicked()
{
    while(true)
    {
        QPixmap image = model.getInputFrame();
        ui->input_image_label->setPixmap(image);
        qApp->processEvents();
    }
}
