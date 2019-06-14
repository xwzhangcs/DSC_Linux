/********************************************************************************
** Form generated from reading UI file 'ParameterControlDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERCONTROLDLG_H
#define UI_PARAMETERCONTROLDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterControlDlg
{
public:
    QGroupBox *groupBox;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_9;
    QSlider *parcelBoundarySmallMidSlider;
    QLabel *labelAvenueSegmentLengthMin;
    QLabel *labelAvenueSegmentLengthMax;
    QSlider *parcelBoundaryMidLargeSlider;
    QLabel *labelRoadBaseOrientationMin;
    QLabel *labelRoadBaseOrientationMax;
    QSlider *correctionFactorSlider;
    QLabel *labelRoadCurvatureMin;
    QLabel *labelRoadCurvatureMax;
    QLineEdit *lineEditSmMid;
    QLineEdit *lineEditSetback;
    QLineEdit *lineEditMidLg;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QWidget *ParameterControlDlg)
    {
        if (ParameterControlDlg->objectName().isEmpty())
            ParameterControlDlg->setObjectName(QStringLiteral("ParameterControlDlg"));
        ParameterControlDlg->resize(439, 227);
        groupBox = new QGroupBox(ParameterControlDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 401, 121));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 141, 21));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 50, 141, 21));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 80, 141, 21));
        parcelBoundarySmallMidSlider = new QSlider(groupBox);
        parcelBoundarySmallMidSlider->setObjectName(QStringLiteral("parcelBoundarySmallMidSlider"));
        parcelBoundarySmallMidSlider->setEnabled(false);
        parcelBoundarySmallMidSlider->setGeometry(QRect(250, 20, 111, 22));
        parcelBoundarySmallMidSlider->setMaximum(100);
        parcelBoundarySmallMidSlider->setValue(50);
        parcelBoundarySmallMidSlider->setOrientation(Qt::Horizontal);
        parcelBoundarySmallMidSlider->setInvertedControls(false);
        parcelBoundarySmallMidSlider->setTickPosition(QSlider::NoTicks);
        labelAvenueSegmentLengthMin = new QLabel(groupBox);
        labelAvenueSegmentLengthMin->setObjectName(QStringLiteral("labelAvenueSegmentLengthMin"));
        labelAvenueSegmentLengthMin->setEnabled(false);
        labelAvenueSegmentLengthMin->setGeometry(QRect(210, 20, 31, 21));
        labelAvenueSegmentLengthMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelAvenueSegmentLengthMax = new QLabel(groupBox);
        labelAvenueSegmentLengthMax->setObjectName(QStringLiteral("labelAvenueSegmentLengthMax"));
        labelAvenueSegmentLengthMax->setEnabled(false);
        labelAvenueSegmentLengthMax->setGeometry(QRect(370, 20, 31, 21));
        labelAvenueSegmentLengthMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        parcelBoundaryMidLargeSlider = new QSlider(groupBox);
        parcelBoundaryMidLargeSlider->setObjectName(QStringLiteral("parcelBoundaryMidLargeSlider"));
        parcelBoundaryMidLargeSlider->setEnabled(false);
        parcelBoundaryMidLargeSlider->setGeometry(QRect(250, 50, 111, 22));
        parcelBoundaryMidLargeSlider->setMaximum(100);
        parcelBoundaryMidLargeSlider->setValue(50);
        parcelBoundaryMidLargeSlider->setOrientation(Qt::Horizontal);
        parcelBoundaryMidLargeSlider->setTickInterval(1);
        labelRoadBaseOrientationMin = new QLabel(groupBox);
        labelRoadBaseOrientationMin->setObjectName(QStringLiteral("labelRoadBaseOrientationMin"));
        labelRoadBaseOrientationMin->setEnabled(false);
        labelRoadBaseOrientationMin->setGeometry(QRect(210, 50, 31, 21));
        labelRoadBaseOrientationMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelRoadBaseOrientationMax = new QLabel(groupBox);
        labelRoadBaseOrientationMax->setObjectName(QStringLiteral("labelRoadBaseOrientationMax"));
        labelRoadBaseOrientationMax->setEnabled(false);
        labelRoadBaseOrientationMax->setGeometry(QRect(370, 50, 31, 21));
        labelRoadBaseOrientationMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        correctionFactorSlider = new QSlider(groupBox);
        correctionFactorSlider->setObjectName(QStringLiteral("correctionFactorSlider"));
        correctionFactorSlider->setEnabled(false);
        correctionFactorSlider->setGeometry(QRect(250, 80, 111, 22));
        correctionFactorSlider->setMaximum(200);
        correctionFactorSlider->setValue(100);
        correctionFactorSlider->setOrientation(Qt::Horizontal);
        labelRoadCurvatureMin = new QLabel(groupBox);
        labelRoadCurvatureMin->setObjectName(QStringLiteral("labelRoadCurvatureMin"));
        labelRoadCurvatureMin->setEnabled(false);
        labelRoadCurvatureMin->setGeometry(QRect(210, 80, 31, 21));
        labelRoadCurvatureMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelRoadCurvatureMax = new QLabel(groupBox);
        labelRoadCurvatureMax->setObjectName(QStringLiteral("labelRoadCurvatureMax"));
        labelRoadCurvatureMax->setEnabled(false);
        labelRoadCurvatureMax->setGeometry(QRect(370, 80, 31, 21));
        labelRoadCurvatureMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditSmMid = new QLineEdit(groupBox);
        lineEditSmMid->setObjectName(QStringLiteral("lineEditSmMid"));
        lineEditSmMid->setGeometry(QRect(160, 20, 51, 20));
        lineEditSetback = new QLineEdit(groupBox);
        lineEditSetback->setObjectName(QStringLiteral("lineEditSetback"));
        lineEditSetback->setGeometry(QRect(160, 80, 51, 20));
        lineEditMidLg = new QLineEdit(groupBox);
        lineEditMidLg->setObjectName(QStringLiteral("lineEditMidLg"));
        lineEditMidLg->setGeometry(QRect(160, 50, 51, 20));
        pushButtonCancel = new QPushButton(ParameterControlDlg);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(320, 170, 91, 31));
        pushButtonOK = new QPushButton(ParameterControlDlg);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(210, 170, 91, 31));

        retranslateUi(ParameterControlDlg);

        QMetaObject::connectSlotsByName(ParameterControlDlg);
    } // setupUi

    void retranslateUi(QWidget *ParameterControlDlg)
    {
        ParameterControlDlg->setWindowTitle(QApplication::translate("ParameterControlDlg", "ParameterControlDlg", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ParameterControlDlg", "Parameters", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParameterControlDlg", "Parcel Boundary (Sm - Mid)", Q_NULLPTR));
        label_6->setText(QApplication::translate("ParameterControlDlg", "Parcel Boundary (Mid - Lg)", Q_NULLPTR));
        label_9->setText(QApplication::translate("ParameterControlDlg", "Correction Factor (Setbacks)", Q_NULLPTR));
        labelAvenueSegmentLengthMin->setText(QApplication::translate("ParameterControlDlg", "100", Q_NULLPTR));
        labelAvenueSegmentLengthMax->setText(QApplication::translate("ParameterControlDlg", "400", Q_NULLPTR));
        labelRoadBaseOrientationMin->setText(QApplication::translate("ParameterControlDlg", "400", Q_NULLPTR));
        labelRoadBaseOrientationMax->setText(QApplication::translate("ParameterControlDlg", "800", Q_NULLPTR));
        labelRoadCurvatureMin->setText(QApplication::translate("ParameterControlDlg", "0.1", Q_NULLPTR));
        labelRoadCurvatureMax->setText(QApplication::translate("ParameterControlDlg", "2.0", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("ParameterControlDlg", "Cancel", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("ParameterControlDlg", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParameterControlDlg: public Ui_ParameterControlDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERCONTROLDLG_H
