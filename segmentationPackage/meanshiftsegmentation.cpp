#include "meanshiftsegmentation.h"
#include "ui_meanshiftsegmentation.h"

meanShiftSegmentation::meanShiftSegmentation(std::string src_image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::meanShiftSegmentation)
{
    ui->setupUi(this);
    this->src_image = src_image;
}

meanShiftSegmentation::~meanShiftSegmentation()
{
    delete ui;
}


using namespace cv;

void meanShiftSegmentation::on_buttonBox_accepted()
{
    TermCriteria criteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 100, 0.001);
    int spatial_radius = ui->lineEdit_spatial_rad->text().toInt();
    int range_radius = ui->lineEdit_range_rad->text().toInt();

    Mat src = imread(this->src_image);
    Mat dst;
    pyrMeanShiftFiltering(src, dst, spatial_radius, range_radius, 0, criteria);

    imshow("input", src);
    imshow("output", dst);
    imwrite("../../Mean-Shift.jpg", dst);
    waitKey();
    destroyAllWindows();
}
