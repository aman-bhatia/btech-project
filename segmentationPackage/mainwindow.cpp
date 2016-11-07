#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cstdlib>
#include <QDebug>

std::string img_to_segment;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mss = new meanShiftSegmentation(img_to_segment, this);
    mss->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    egbis eg(img_to_segment);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fname = QFileDialog::getOpenFileName(this,"Choose Image to Segment","",tr("Image Files (*.png *.jpg *.bmp)"));
    if (fname == ""){
        QMessageBox::information(this, tr("Usage Information"),tr("Please choose an image file to continue."));
    } else {
        img_to_segment = fname.toStdString();
        ui->groupBox->setEnabled(true);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    std::string command = "python ../../plot_ncut.py \"" + img_to_segment + "\"";
    system(command.c_str());
}

void MainWindow::on_pushButton_5_clicked()
{
    gc = new graphCut(img_to_segment,this);
    gc->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    sc = new SeamCarving(img_to_segment,this);
    sc->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    std::string command = "wine ../../photomontage/fuse.exe";
    system(command.c_str());
}

void MainWindow::on_pushButton_8_clicked()
{
    QString video_path = QFileDialog::getOpenFileName(this,"Choose Video for Backgroung Subtraction","",tr("Video Files (*.avi *.3gp *.mov *.mp4)"));
    if (video_path == ""){
        QMessageBox::information(this, tr("Usage Information"),tr("Please choose a video file to continue."));
    } else {
        std::string vpath = video_path.toStdString();
        bg_sub bgs(vpath);
        bgs.processVideo();
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    QString video_path = QFileDialog::getOpenFileName(this,"Choose Video for MOtion Segmentation","",tr("Video Files (*.avi *.3gp *.mov *.mp4)"));
    if (video_path == ""){
        QMessageBox::information(this, tr("Usage Information"),tr("Please choose a video file to continue."));
    } else {
        QMessageBox::information(this, tr("Usage Information"),tr("Press 'i' to increase threashold, 'd' to decrease it. Press 1/2/3/4/5 to set no. of moving objects."));
        std::string vpath = video_path.toStdString();
        motion_seg mseg(vpath);
    }
}
