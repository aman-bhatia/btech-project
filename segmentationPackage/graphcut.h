#ifndef GRAPHCUT_H
#define GRAPHCUT_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include "gco/GCoptimization.h"

namespace Ui {
class graphCut;
}

class graphCut : public QDialog
{
    Q_OBJECT

public:
    explicit graphCut(std::string src_image, QWidget *parent = 0);
    ~graphCut();

private slots:

    void increase_smoothness();

    void decrease_smoothness();

    void on_buttonBox_accepted();

private:
    Ui::graphCut *ui;
    std::string src_image;
    int num_labels = 5;
    int smoothness = 5;
    GCoptimizationGridGraph *graph;
};

#endif // GRAPHCUT_H
