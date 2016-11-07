/********************************************************************************
** Form generated from reading UI file 'graphcut.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHCUT_H
#define UI_GRAPHCUT_H

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

class Ui_graphCut
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *graphCut)
    {
        if (graphCut->objectName().isEmpty())
            graphCut->setObjectName(QStringLiteral("graphCut"));
        graphCut->resize(216, 152);
        buttonBox = new QDialogButtonBox(graphCut);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 100, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(graphCut);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 50, 113, 21));
        label = new QLabel(graphCut);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 121, 16));

        retranslateUi(graphCut);
        QObject::connect(buttonBox, SIGNAL(accepted()), graphCut, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), graphCut, SLOT(reject()));

        QMetaObject::connectSlotsByName(graphCut);
    } // setupUi

    void retranslateUi(QDialog *graphCut)
    {
        graphCut->setWindowTitle(QApplication::translate("graphCut", "Dialog", 0));
        label->setText(QApplication::translate("graphCut", "Number of Clusters :", 0));
    } // retranslateUi

};

namespace Ui {
    class graphCut: public Ui_graphCut {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHCUT_H
