#ifndef SEAMCARVING_H
#define SEAMCARVING_H

#include <QDialog>
#include <QMessageBox>
#include <set>
#include "opencv2/opencv.hpp"

#define HOR 1
#define VER 2
#define coord pair<int,int>		// order is (row,col)
#define RED Scalar(0,0,255)
#define GREEN Scalar(0,255,0)

extern cv::Mat obj_img;
extern cv::Mat bin_img;
extern std::string draw_winname;

struct node{
    int path;	// left is -1, middle is 0, right is 1
    long long int energy;
};


namespace Ui {
class SeamCarving;
}

class SeamCarving : public QDialog
{
    Q_OBJECT

public:
    explicit SeamCarving(std::string src_image, QWidget *parent = 0);
    ~SeamCarving();

private slots:
    cv::Mat seamNormal(cv::Mat img, int cols_to_delete, int mode);

    void on_pushButton_save_rem_clicked();

    void on_buttonBox_accepted();

private:
    Ui::SeamCarving *ui;
    std::string img_name = "";
    bool obj = false;
};

#endif // SEAMCARVING_H
