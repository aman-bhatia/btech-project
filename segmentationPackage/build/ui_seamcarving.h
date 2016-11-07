/********************************************************************************
** Form generated from reading UI file 'seamcarving.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEAMCARVING_H
#define UI_SEAMCARVING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SeamCarving
{
public:
    QLineEdit *lineEdit_num_cols_del;
    QLabel *label_num_cols_del;
    QLabel *label_num_cols;
    QLabel *label_num_cols_insert;
    QLabel *label2;
    QPushButton *pushButton_save_rem;
    QLabel *label1;
    QLabel *label_num_rows_del;
    QLabel *label_num_rows;
    QLineEdit *lineEdit_num_rows_insert;
    QLineEdit *lineEdit_num_rows_del;
    QLabel *label_num_rows_insert;
    QLineEdit *lineEdit_num_cols_insert;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;

    void setupUi(QDialog *SeamCarving)
    {
        if (SeamCarving->objectName().isEmpty())
            SeamCarving->setObjectName(QStringLiteral("SeamCarving"));
        SeamCarving->resize(369, 415);
        SeamCarving->setFocusPolicy(Qt::ClickFocus);
        lineEdit_num_cols_del = new QLineEdit(SeamCarving);
        lineEdit_num_cols_del->setObjectName(QStringLiteral("lineEdit_num_cols_del"));
        lineEdit_num_cols_del->setGeometry(QRect(240, 210, 81, 21));
        lineEdit_num_cols_del->setFocusPolicy(Qt::ClickFocus);
        label_num_cols_del = new QLabel(SeamCarving);
        label_num_cols_del->setObjectName(QStringLiteral("label_num_cols_del"));
        label_num_cols_del->setGeometry(QRect(40, 210, 201, 20));
        label_num_cols = new QLabel(SeamCarving);
        label_num_cols->setObjectName(QStringLiteral("label_num_cols"));
        label_num_cols->setGeometry(QRect(240, 80, 91, 17));
        label_num_cols_insert = new QLabel(SeamCarving);
        label_num_cols_insert->setObjectName(QStringLiteral("label_num_cols_insert"));
        label_num_cols_insert->setGeometry(QRect(40, 270, 201, 20));
        label2 = new QLabel(SeamCarving);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(40, 81, 161, 17));
        pushButton_save_rem = new QPushButton(SeamCarving);
        pushButton_save_rem->setObjectName(QStringLiteral("pushButton_save_rem"));
        pushButton_save_rem->setGeometry(QRect(70, 330, 221, 21));
        label1 = new QLabel(SeamCarving);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(40, 51, 161, 17));
        label_num_rows_del = new QLabel(SeamCarving);
        label_num_rows_del->setObjectName(QStringLiteral("label_num_rows_del"));
        label_num_rows_del->setGeometry(QRect(40, 180, 201, 17));
        label_num_rows = new QLabel(SeamCarving);
        label_num_rows->setObjectName(QStringLiteral("label_num_rows"));
        label_num_rows->setGeometry(QRect(240, 50, 91, 17));
        lineEdit_num_rows_insert = new QLineEdit(SeamCarving);
        lineEdit_num_rows_insert->setObjectName(QStringLiteral("lineEdit_num_rows_insert"));
        lineEdit_num_rows_insert->setGeometry(QRect(240, 239, 81, 20));
        lineEdit_num_rows_del = new QLineEdit(SeamCarving);
        lineEdit_num_rows_del->setObjectName(QStringLiteral("lineEdit_num_rows_del"));
        lineEdit_num_rows_del->setGeometry(QRect(240, 178, 81, 21));
        label_num_rows_insert = new QLabel(SeamCarving);
        label_num_rows_insert->setObjectName(QStringLiteral("label_num_rows_insert"));
        label_num_rows_insert->setGeometry(QRect(40, 240, 201, 17));
        lineEdit_num_cols_insert = new QLineEdit(SeamCarving);
        lineEdit_num_cols_insert->setObjectName(QStringLiteral("lineEdit_num_cols_insert"));
        lineEdit_num_cols_insert->setGeometry(QRect(240, 270, 81, 21));
        buttonBox = new QDialogButtonBox(SeamCarving);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(100, 360, 165, 20));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_2 = new QGroupBox(SeamCarving);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 20, 311, 101));

        retranslateUi(SeamCarving);
        QObject::connect(buttonBox, SIGNAL(accepted()), SeamCarving, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SeamCarving, SLOT(reject()));

        QMetaObject::connectSlotsByName(SeamCarving);
    } // setupUi

    void retranslateUi(QDialog *SeamCarving)
    {
        SeamCarving->setWindowTitle(QApplication::translate("SeamCarving", "Dialog", 0));
        lineEdit_num_cols_del->setText(QApplication::translate("SeamCarving", "0", 0));
        label_num_cols_del->setText(QApplication::translate("SeamCarving", "Number of Cols to delete     : ", 0));
        label_num_cols->setText(QString());
        label_num_cols_insert->setText(QApplication::translate("SeamCarving", "Number of Cols to insert     : ", 0));
        label2->setText(QApplication::translate("SeamCarving", "Number of Cols in Image   : ", 0));
        pushButton_save_rem->setText(QApplication::translate("SeamCarving", "Draw to Save or Remove Objects", 0));
        label1->setText(QApplication::translate("SeamCarving", "Number of Rows in Image : ", 0));
        label_num_rows_del->setText(QApplication::translate("SeamCarving", "Number of Rows to delete   : ", 0));
        label_num_rows->setText(QString());
        lineEdit_num_rows_insert->setText(QApplication::translate("SeamCarving", "0", 0));
        lineEdit_num_rows_del->setText(QApplication::translate("SeamCarving", "0", 0));
        label_num_rows_insert->setText(QApplication::translate("SeamCarving", "Number of Rows to insert   : ", 0));
        lineEdit_num_cols_insert->setText(QApplication::translate("SeamCarving", "0", 0));
        groupBox_2->setTitle(QApplication::translate("SeamCarving", "Image Info", 0));
    } // retranslateUi

};

namespace Ui {
    class SeamCarving: public Ui_SeamCarving {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEAMCARVING_H
