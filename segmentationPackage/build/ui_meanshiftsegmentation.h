/********************************************************************************
** Form generated from reading UI file 'meanshiftsegmentation.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEANSHIFTSEGMENTATION_H
#define UI_MEANSHIFTSEGMENTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_meanShiftSegmentation
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_spatial_rad;
    QLineEdit *lineEdit_range_rad;

    void setupUi(QDialog *meanShiftSegmentation)
    {
        if (meanShiftSegmentation->objectName().isEmpty())
            meanShiftSegmentation->setObjectName(QStringLiteral("meanShiftSegmentation"));
        meanShiftSegmentation->resize(387, 215);
        buttonBox = new QDialogButtonBox(meanShiftSegmentation);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 140, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(meanShiftSegmentation);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 50, 151, 16));
        label_2 = new QLabel(meanShiftSegmentation);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 111, 16));
        lineEdit_spatial_rad = new QLineEdit(meanShiftSegmentation);
        lineEdit_spatial_rad->setObjectName(QStringLiteral("lineEdit_spatial_rad"));
        lineEdit_spatial_rad->setGeometry(QRect(180, 50, 113, 22));
        lineEdit_range_rad = new QLineEdit(meanShiftSegmentation);
        lineEdit_range_rad->setObjectName(QStringLiteral("lineEdit_range_rad"));
        lineEdit_range_rad->setGeometry(QRect(180, 80, 113, 22));

        retranslateUi(meanShiftSegmentation);
        QObject::connect(buttonBox, SIGNAL(accepted()), meanShiftSegmentation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), meanShiftSegmentation, SLOT(reject()));

        QMetaObject::connectSlotsByName(meanShiftSegmentation);
    } // setupUi

    void retranslateUi(QDialog *meanShiftSegmentation)
    {
        meanShiftSegmentation->setWindowTitle(QApplication::translate("meanShiftSegmentation", "Dialog", 0));
        label->setText(QApplication::translate("meanShiftSegmentation", "Spatial Radius", 0));
        label_2->setText(QApplication::translate("meanShiftSegmentation", "Range Radius", 0));
    } // retranslateUi

};

namespace Ui {
    class meanShiftSegmentation: public Ui_meanShiftSegmentation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEANSHIFTSEGMENTATION_H
