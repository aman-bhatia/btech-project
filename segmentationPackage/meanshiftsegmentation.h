#ifndef MEANSHIFTSEGMENTATION_H
#define MEANSHIFTSEGMENTATION_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class meanShiftSegmentation;
}

class meanShiftSegmentation : public QDialog
{
    Q_OBJECT

public:
    explicit meanShiftSegmentation(std::string src_image, QWidget *parent = 0);
    ~meanShiftSegmentation();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::meanShiftSegmentation *ui;
    std::string src_image;
};

#endif // MEANSHIFTSEGMENTATION_H
