/********************************************************************************
** Form generated from reading UI file 'ParcelMetrics.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARCELMETRICS_H
#define UI_PARCELMETRICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParcelMetrics
{
public:
    QLineEdit *lineEditGtDir;
    QPushButton *pushButtonGtDir;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonPreDir;
    QLabel *label_3;
    QLineEdit *lineEditPreDir;
    QGroupBox *groupBox;
    QCheckBox *checkBoxParcelNum;
    QCheckBox *checkBoxParcelAvg;
    QCheckBox *checkBoxParcelCom;

    void setupUi(QWidget *ParcelMetrics)
    {
        if (ParcelMetrics->objectName().isEmpty())
            ParcelMetrics->setObjectName(QStringLiteral("ParcelMetrics"));
        ParcelMetrics->resize(442, 340);
        lineEditGtDir = new QLineEdit(ParcelMetrics);
        lineEditGtDir->setObjectName(QStringLiteral("lineEditGtDir"));
        lineEditGtDir->setGeometry(QRect(130, 40, 241, 20));
        pushButtonGtDir = new QPushButton(ParcelMetrics);
        pushButtonGtDir->setObjectName(QStringLiteral("pushButtonGtDir"));
        pushButtonGtDir->setGeometry(QRect(390, 40, 31, 23));
        label_2 = new QLabel(ParcelMetrics);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 40, 121, 21));
        pushButtonOK = new QPushButton(ParcelMetrics);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(210, 280, 91, 31));
        pushButtonCancel = new QPushButton(ParcelMetrics);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(320, 280, 91, 31));
        pushButtonPreDir = new QPushButton(ParcelMetrics);
        pushButtonPreDir->setObjectName(QStringLiteral("pushButtonPreDir"));
        pushButtonPreDir->setGeometry(QRect(390, 80, 31, 23));
        label_3 = new QLabel(ParcelMetrics);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 121, 21));
        lineEditPreDir = new QLineEdit(ParcelMetrics);
        lineEditPreDir->setObjectName(QStringLiteral("lineEditPreDir"));
        lineEditPreDir->setGeometry(QRect(130, 80, 241, 20));
        groupBox = new QGroupBox(ParcelMetrics);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 120, 411, 141));
        checkBoxParcelNum = new QCheckBox(groupBox);
        checkBoxParcelNum->setObjectName(QStringLiteral("checkBoxParcelNum"));
        checkBoxParcelNum->setGeometry(QRect(30, 30, 121, 20));
        checkBoxParcelAvg = new QCheckBox(groupBox);
        checkBoxParcelAvg->setObjectName(QStringLiteral("checkBoxParcelAvg"));
        checkBoxParcelAvg->setGeometry(QRect(30, 60, 121, 20));
        checkBoxParcelCom = new QCheckBox(groupBox);
        checkBoxParcelCom->setObjectName(QStringLiteral("checkBoxParcelCom"));
        checkBoxParcelCom->setGeometry(QRect(30, 90, 211, 20));

        retranslateUi(ParcelMetrics);

        QMetaObject::connectSlotsByName(ParcelMetrics);
    } // setupUi

    void retranslateUi(QWidget *ParcelMetrics)
    {
        ParcelMetrics->setWindowTitle(QApplication::translate("ParcelMetrics", "ParcelMetrics", Q_NULLPTR));
        pushButtonGtDir->setText(QApplication::translate("ParcelMetrics", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("ParcelMetrics", "Gt directory:", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("ParcelMetrics", "OK", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("ParcelMetrics", "Cancel", Q_NULLPTR));
        pushButtonPreDir->setText(QApplication::translate("ParcelMetrics", "...", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParcelMetrics", "Pre directory:", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ParcelMetrics", "Metrics Options", Q_NULLPTR));
        checkBoxParcelNum->setText(QApplication::translate("ParcelMetrics", "Parcel Number", Q_NULLPTR));
        checkBoxParcelAvg->setText(QApplication::translate("ParcelMetrics", "Parcel Avg Area", Q_NULLPTR));
        checkBoxParcelCom->setText(QApplication::translate("ParcelMetrics", "Parcel Comprehensive Analysis", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParcelMetrics: public Ui_ParcelMetrics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARCELMETRICS_H
