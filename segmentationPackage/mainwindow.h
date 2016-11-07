#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "meanshiftsegmentation.h"
#include "egbis.h"
#include "graphcut.h"
#include "seamcarving.h"
#include "bg_sub.h"
#include "motion_seg.h"

extern std::string img_to_segment;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    meanShiftSegmentation *mss;
    graphCut *gc;
    SeamCarving *sc;
};

#endif // MAINWINDOW_H
