/********************************************************************************
** Form generated from reading UI file 'ControlWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLWIDGET_H
#define UI_CONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlWidget
{
public:
    QWidget *dockWidgetContents;
    QGroupBox *groupBox;
    QLabel *label_3;
    QLineEdit *lineEditAvenueSegmentLength;
    QLabel *label_6;
    QLabel *label_9;
    QLineEdit *lineEditRoadBaseOrientation;
    QLineEdit *lineEditRoadCurvature;
    QLabel *label_20;
    QLineEdit *lineEditMajorRoadWidth;
    QLabel *label_23;
    QLineEdit *lineEditMinorRoadWidth;
    QLabel *label_25;
    QCheckBox *checkBoxUseElevation;
    QSlider *horizontalSliderAvenueSegmentLength;
    QLabel *labelAvenueSegmentLengthMin;
    QLabel *labelAvenueSegmentLengthMax;
    QSlider *horizontalSliderRoadBaseOrientation;
    QLabel *labelRoadBaseOrientationMin;
    QLabel *labelRoadBaseOrientationMax;
    QSlider *horizontalSliderRoadCurvature;
    QLabel *labelRoadCurvatureMin;
    QLabel *labelRoadCurvatureMax;
    QSlider *horizontalSliderMajorRoadWidth;
    QLabel *labelMajorRoadWidthMin;
    QLabel *labelMajorRoadWidthMax;
    QSlider *horizontalSliderMinorRoadWidth;
    QLabel *labelMinorRoadWidthMin;
    QLabel *labelMinorRoadWidthMax;
    QGroupBox *groupBox_2;
    QLabel *label_11;
    QLineEdit *lineEditParkRatio;
    QLabel *label_15;
    QLabel *label_21;
    QLabel *label_17;
    QLabel *label_19;
    QLineEdit *lineEditSetbackRear;
    QLineEdit *lineEditParcelArea;
    QLineEdit *lineEditSetbackFront;
    QLineEdit *lineEditSetbackSide;
    QLineEdit *lineEditParcelAreaDev;
    QLabel *label_16;
    QSlider *horizontalSliderParkRatio;
    QLabel *labelParkRatioMin;
    QLabel *labelParkRatioMax;
    QSlider *horizontalSliderParcelArea;
    QLabel *labelParcelAreaMin;
    QLabel *labelParcelAreaMax;
    QSlider *horizontalSliderParcelAreaDev;
    QLabel *labelParcelAreaDevMin;
    QLabel *labelParcelAreaDevMax;
    QSlider *horizontalSliderSetbackFront;
    QSlider *horizontalSliderSetbackRear;
    QSlider *horizontalSliderSetbackSide;
    QLabel *labelSetbackFrontMin;
    QLabel *labelSetbackFrontMax;
    QLabel *labelSetbackRearMin;
    QLabel *labelSetbackRearMax;
    QLabel *labelSetbackSideMin;
    QLabel *labelSetbackSideMax;
    QGroupBox *groupBox_3;
    QLineEdit *lineEditNumStoriesMin;
    QLabel *label_33;
    QLineEdit *lineEditNumStoriesMax;
    QLabel *label_35;
    QLabel *label_34;
    QLineEdit *lineEditMinBuildingDim;
    QSlider *horizontalSliderNumStoriesMin;
    QSlider *horizontalSliderNumStoriesMax;
    QSlider *horizontalSliderMinBuildingDim;
    QLabel *labelNumStoriesMinMin;
    QLabel *labelNumStoriesMaxMin;
    QLabel *labelMinBuildingDimMin;
    QLabel *labelNumStoriesMinMax;
    QLabel *labelNumStoriesMaxMax;
    QLabel *labelMinBuildingDimMax;
    QPushButton *pushButtonGenerateAll;
    QComboBox *comboBoxCity;
    QLabel *label;

    void setupUi(QDockWidget *ControlWidget)
    {
        if (ControlWidget->objectName().isEmpty())
            ControlWidget->setObjectName(QStringLiteral("ControlWidget"));
        ControlWidget->resize(422, 679);
        ControlWidget->setMinimumSize(QSize(422, 474));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 401, 201));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 141, 21));
        lineEditAvenueSegmentLength = new QLineEdit(groupBox);
        lineEditAvenueSegmentLength->setObjectName(QStringLiteral("lineEditAvenueSegmentLength"));
        lineEditAvenueSegmentLength->setGeometry(QRect(160, 20, 41, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 50, 141, 21));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 80, 121, 21));
        lineEditRoadBaseOrientation = new QLineEdit(groupBox);
        lineEditRoadBaseOrientation->setObjectName(QStringLiteral("lineEditRoadBaseOrientation"));
        lineEditRoadBaseOrientation->setGeometry(QRect(160, 50, 41, 20));
        lineEditRoadCurvature = new QLineEdit(groupBox);
        lineEditRoadCurvature->setObjectName(QStringLiteral("lineEditRoadCurvature"));
        lineEditRoadCurvature->setGeometry(QRect(160, 80, 41, 20));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 110, 121, 21));
        lineEditMajorRoadWidth = new QLineEdit(groupBox);
        lineEditMajorRoadWidth->setObjectName(QStringLiteral("lineEditMajorRoadWidth"));
        lineEditMajorRoadWidth->setGeometry(QRect(160, 110, 41, 20));
        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 140, 121, 21));
        lineEditMinorRoadWidth = new QLineEdit(groupBox);
        lineEditMinorRoadWidth->setObjectName(QStringLiteral("lineEditMinorRoadWidth"));
        lineEditMinorRoadWidth->setGeometry(QRect(160, 140, 41, 20));
        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 170, 121, 21));
        checkBoxUseElevation = new QCheckBox(groupBox);
        checkBoxUseElevation->setObjectName(QStringLiteral("checkBoxUseElevation"));
        checkBoxUseElevation->setGeometry(QRect(159, 170, 51, 21));
        horizontalSliderAvenueSegmentLength = new QSlider(groupBox);
        horizontalSliderAvenueSegmentLength->setObjectName(QStringLiteral("horizontalSliderAvenueSegmentLength"));
        horizontalSliderAvenueSegmentLength->setGeometry(QRect(250, 20, 111, 22));
        horizontalSliderAvenueSegmentLength->setOrientation(Qt::Horizontal);
        horizontalSliderAvenueSegmentLength->setInvertedControls(false);
        horizontalSliderAvenueSegmentLength->setTickPosition(QSlider::NoTicks);
        labelAvenueSegmentLengthMin = new QLabel(groupBox);
        labelAvenueSegmentLengthMin->setObjectName(QStringLiteral("labelAvenueSegmentLengthMin"));
        labelAvenueSegmentLengthMin->setGeometry(QRect(210, 20, 31, 21));
        labelAvenueSegmentLengthMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelAvenueSegmentLengthMax = new QLabel(groupBox);
        labelAvenueSegmentLengthMax->setObjectName(QStringLiteral("labelAvenueSegmentLengthMax"));
        labelAvenueSegmentLengthMax->setGeometry(QRect(370, 20, 31, 21));
        labelAvenueSegmentLengthMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderRoadBaseOrientation = new QSlider(groupBox);
        horizontalSliderRoadBaseOrientation->setObjectName(QStringLiteral("horizontalSliderRoadBaseOrientation"));
        horizontalSliderRoadBaseOrientation->setGeometry(QRect(250, 50, 111, 22));
        horizontalSliderRoadBaseOrientation->setOrientation(Qt::Horizontal);
        labelRoadBaseOrientationMin = new QLabel(groupBox);
        labelRoadBaseOrientationMin->setObjectName(QStringLiteral("labelRoadBaseOrientationMin"));
        labelRoadBaseOrientationMin->setGeometry(QRect(210, 50, 31, 21));
        labelRoadBaseOrientationMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelRoadBaseOrientationMax = new QLabel(groupBox);
        labelRoadBaseOrientationMax->setObjectName(QStringLiteral("labelRoadBaseOrientationMax"));
        labelRoadBaseOrientationMax->setGeometry(QRect(370, 50, 31, 21));
        labelRoadBaseOrientationMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderRoadCurvature = new QSlider(groupBox);
        horizontalSliderRoadCurvature->setObjectName(QStringLiteral("horizontalSliderRoadCurvature"));
        horizontalSliderRoadCurvature->setGeometry(QRect(250, 80, 111, 22));
        horizontalSliderRoadCurvature->setOrientation(Qt::Horizontal);
        labelRoadCurvatureMin = new QLabel(groupBox);
        labelRoadCurvatureMin->setObjectName(QStringLiteral("labelRoadCurvatureMin"));
        labelRoadCurvatureMin->setGeometry(QRect(210, 80, 31, 21));
        labelRoadCurvatureMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelRoadCurvatureMax = new QLabel(groupBox);
        labelRoadCurvatureMax->setObjectName(QStringLiteral("labelRoadCurvatureMax"));
        labelRoadCurvatureMax->setGeometry(QRect(370, 80, 31, 21));
        labelRoadCurvatureMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderMajorRoadWidth = new QSlider(groupBox);
        horizontalSliderMajorRoadWidth->setObjectName(QStringLiteral("horizontalSliderMajorRoadWidth"));
        horizontalSliderMajorRoadWidth->setGeometry(QRect(250, 110, 111, 22));
        horizontalSliderMajorRoadWidth->setOrientation(Qt::Horizontal);
        labelMajorRoadWidthMin = new QLabel(groupBox);
        labelMajorRoadWidthMin->setObjectName(QStringLiteral("labelMajorRoadWidthMin"));
        labelMajorRoadWidthMin->setGeometry(QRect(210, 110, 31, 21));
        labelMajorRoadWidthMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMajorRoadWidthMax = new QLabel(groupBox);
        labelMajorRoadWidthMax->setObjectName(QStringLiteral("labelMajorRoadWidthMax"));
        labelMajorRoadWidthMax->setGeometry(QRect(370, 110, 31, 21));
        labelMajorRoadWidthMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderMinorRoadWidth = new QSlider(groupBox);
        horizontalSliderMinorRoadWidth->setObjectName(QStringLiteral("horizontalSliderMinorRoadWidth"));
        horizontalSliderMinorRoadWidth->setGeometry(QRect(250, 140, 111, 22));
        horizontalSliderMinorRoadWidth->setOrientation(Qt::Horizontal);
        labelMinorRoadWidthMin = new QLabel(groupBox);
        labelMinorRoadWidthMin->setObjectName(QStringLiteral("labelMinorRoadWidthMin"));
        labelMinorRoadWidthMin->setGeometry(QRect(210, 140, 31, 21));
        labelMinorRoadWidthMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMinorRoadWidthMax = new QLabel(groupBox);
        labelMinorRoadWidthMax->setObjectName(QStringLiteral("labelMinorRoadWidthMax"));
        labelMinorRoadWidthMax->setGeometry(QRect(370, 140, 31, 21));
        labelMinorRoadWidthMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 250, 401, 201));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 20, 121, 21));
        lineEditParkRatio = new QLineEdit(groupBox_2);
        lineEditParkRatio->setObjectName(QStringLiteral("lineEditParkRatio"));
        lineEditParkRatio->setGeometry(QRect(160, 20, 41, 20));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 50, 121, 21));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 170, 121, 21));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 110, 121, 21));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 140, 121, 21));
        lineEditSetbackRear = new QLineEdit(groupBox_2);
        lineEditSetbackRear->setObjectName(QStringLiteral("lineEditSetbackRear"));
        lineEditSetbackRear->setGeometry(QRect(160, 140, 41, 20));
        lineEditParcelArea = new QLineEdit(groupBox_2);
        lineEditParcelArea->setObjectName(QStringLiteral("lineEditParcelArea"));
        lineEditParcelArea->setGeometry(QRect(160, 50, 41, 20));
        lineEditSetbackFront = new QLineEdit(groupBox_2);
        lineEditSetbackFront->setObjectName(QStringLiteral("lineEditSetbackFront"));
        lineEditSetbackFront->setGeometry(QRect(160, 110, 41, 20));
        lineEditSetbackSide = new QLineEdit(groupBox_2);
        lineEditSetbackSide->setObjectName(QStringLiteral("lineEditSetbackSide"));
        lineEditSetbackSide->setGeometry(QRect(160, 170, 41, 20));
        lineEditParcelAreaDev = new QLineEdit(groupBox_2);
        lineEditParcelAreaDev->setObjectName(QStringLiteral("lineEditParcelAreaDev"));
        lineEditParcelAreaDev->setGeometry(QRect(160, 80, 41, 20));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 80, 151, 21));
        horizontalSliderParkRatio = new QSlider(groupBox_2);
        horizontalSliderParkRatio->setObjectName(QStringLiteral("horizontalSliderParkRatio"));
        horizontalSliderParkRatio->setGeometry(QRect(250, 20, 111, 22));
        horizontalSliderParkRatio->setOrientation(Qt::Horizontal);
        labelParkRatioMin = new QLabel(groupBox_2);
        labelParkRatioMin->setObjectName(QStringLiteral("labelParkRatioMin"));
        labelParkRatioMin->setGeometry(QRect(210, 20, 31, 21));
        labelParkRatioMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelParkRatioMax = new QLabel(groupBox_2);
        labelParkRatioMax->setObjectName(QStringLiteral("labelParkRatioMax"));
        labelParkRatioMax->setGeometry(QRect(370, 20, 31, 21));
        labelParkRatioMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderParcelArea = new QSlider(groupBox_2);
        horizontalSliderParcelArea->setObjectName(QStringLiteral("horizontalSliderParcelArea"));
        horizontalSliderParcelArea->setGeometry(QRect(250, 50, 111, 22));
        horizontalSliderParcelArea->setOrientation(Qt::Horizontal);
        labelParcelAreaMin = new QLabel(groupBox_2);
        labelParcelAreaMin->setObjectName(QStringLiteral("labelParcelAreaMin"));
        labelParcelAreaMin->setGeometry(QRect(210, 50, 31, 21));
        labelParcelAreaMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelParcelAreaMax = new QLabel(groupBox_2);
        labelParcelAreaMax->setObjectName(QStringLiteral("labelParcelAreaMax"));
        labelParcelAreaMax->setGeometry(QRect(370, 50, 31, 21));
        labelParcelAreaMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderParcelAreaDev = new QSlider(groupBox_2);
        horizontalSliderParcelAreaDev->setObjectName(QStringLiteral("horizontalSliderParcelAreaDev"));
        horizontalSliderParcelAreaDev->setGeometry(QRect(250, 80, 111, 22));
        horizontalSliderParcelAreaDev->setOrientation(Qt::Horizontal);
        labelParcelAreaDevMin = new QLabel(groupBox_2);
        labelParcelAreaDevMin->setObjectName(QStringLiteral("labelParcelAreaDevMin"));
        labelParcelAreaDevMin->setGeometry(QRect(210, 80, 31, 21));
        labelParcelAreaDevMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelParcelAreaDevMax = new QLabel(groupBox_2);
        labelParcelAreaDevMax->setObjectName(QStringLiteral("labelParcelAreaDevMax"));
        labelParcelAreaDevMax->setGeometry(QRect(370, 80, 31, 21));
        labelParcelAreaDevMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderSetbackFront = new QSlider(groupBox_2);
        horizontalSliderSetbackFront->setObjectName(QStringLiteral("horizontalSliderSetbackFront"));
        horizontalSliderSetbackFront->setGeometry(QRect(250, 110, 111, 22));
        horizontalSliderSetbackFront->setOrientation(Qt::Horizontal);
        horizontalSliderSetbackRear = new QSlider(groupBox_2);
        horizontalSliderSetbackRear->setObjectName(QStringLiteral("horizontalSliderSetbackRear"));
        horizontalSliderSetbackRear->setGeometry(QRect(250, 140, 111, 22));
        horizontalSliderSetbackRear->setOrientation(Qt::Horizontal);
        horizontalSliderSetbackSide = new QSlider(groupBox_2);
        horizontalSliderSetbackSide->setObjectName(QStringLiteral("horizontalSliderSetbackSide"));
        horizontalSliderSetbackSide->setGeometry(QRect(250, 170, 111, 22));
        horizontalSliderSetbackSide->setOrientation(Qt::Horizontal);
        labelSetbackFrontMin = new QLabel(groupBox_2);
        labelSetbackFrontMin->setObjectName(QStringLiteral("labelSetbackFrontMin"));
        labelSetbackFrontMin->setGeometry(QRect(210, 110, 31, 21));
        labelSetbackFrontMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelSetbackFrontMax = new QLabel(groupBox_2);
        labelSetbackFrontMax->setObjectName(QStringLiteral("labelSetbackFrontMax"));
        labelSetbackFrontMax->setGeometry(QRect(370, 110, 31, 21));
        labelSetbackFrontMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelSetbackRearMin = new QLabel(groupBox_2);
        labelSetbackRearMin->setObjectName(QStringLiteral("labelSetbackRearMin"));
        labelSetbackRearMin->setGeometry(QRect(210, 140, 31, 21));
        labelSetbackRearMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelSetbackRearMax = new QLabel(groupBox_2);
        labelSetbackRearMax->setObjectName(QStringLiteral("labelSetbackRearMax"));
        labelSetbackRearMax->setGeometry(QRect(370, 140, 31, 21));
        labelSetbackRearMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelSetbackSideMin = new QLabel(groupBox_2);
        labelSetbackSideMin->setObjectName(QStringLiteral("labelSetbackSideMin"));
        labelSetbackSideMin->setGeometry(QRect(210, 170, 31, 21));
        labelSetbackSideMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelSetbackSideMax = new QLabel(groupBox_2);
        labelSetbackSideMax->setObjectName(QStringLiteral("labelSetbackSideMax"));
        labelSetbackSideMax->setGeometry(QRect(370, 170, 31, 21));
        labelSetbackSideMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_3 = new QGroupBox(dockWidgetContents);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 460, 401, 111));
        lineEditNumStoriesMin = new QLineEdit(groupBox_3);
        lineEditNumStoriesMin->setObjectName(QStringLiteral("lineEditNumStoriesMin"));
        lineEditNumStoriesMin->setGeometry(QRect(160, 20, 41, 20));
        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(10, 20, 121, 21));
        lineEditNumStoriesMax = new QLineEdit(groupBox_3);
        lineEditNumStoriesMax->setObjectName(QStringLiteral("lineEditNumStoriesMax"));
        lineEditNumStoriesMax->setGeometry(QRect(160, 50, 41, 20));
        label_35 = new QLabel(groupBox_3);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(10, 50, 121, 21));
        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(10, 80, 121, 21));
        lineEditMinBuildingDim = new QLineEdit(groupBox_3);
        lineEditMinBuildingDim->setObjectName(QStringLiteral("lineEditMinBuildingDim"));
        lineEditMinBuildingDim->setGeometry(QRect(160, 80, 41, 20));
        horizontalSliderNumStoriesMin = new QSlider(groupBox_3);
        horizontalSliderNumStoriesMin->setObjectName(QStringLiteral("horizontalSliderNumStoriesMin"));
        horizontalSliderNumStoriesMin->setGeometry(QRect(250, 20, 111, 22));
        horizontalSliderNumStoriesMin->setOrientation(Qt::Horizontal);
        horizontalSliderNumStoriesMax = new QSlider(groupBox_3);
        horizontalSliderNumStoriesMax->setObjectName(QStringLiteral("horizontalSliderNumStoriesMax"));
        horizontalSliderNumStoriesMax->setGeometry(QRect(250, 50, 111, 22));
        horizontalSliderNumStoriesMax->setOrientation(Qt::Horizontal);
        horizontalSliderMinBuildingDim = new QSlider(groupBox_3);
        horizontalSliderMinBuildingDim->setObjectName(QStringLiteral("horizontalSliderMinBuildingDim"));
        horizontalSliderMinBuildingDim->setGeometry(QRect(250, 80, 111, 22));
        horizontalSliderMinBuildingDim->setOrientation(Qt::Horizontal);
        labelNumStoriesMinMin = new QLabel(groupBox_3);
        labelNumStoriesMinMin->setObjectName(QStringLiteral("labelNumStoriesMinMin"));
        labelNumStoriesMinMin->setGeometry(QRect(210, 20, 31, 21));
        labelNumStoriesMinMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelNumStoriesMaxMin = new QLabel(groupBox_3);
        labelNumStoriesMaxMin->setObjectName(QStringLiteral("labelNumStoriesMaxMin"));
        labelNumStoriesMaxMin->setGeometry(QRect(210, 50, 31, 21));
        labelNumStoriesMaxMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMinBuildingDimMin = new QLabel(groupBox_3);
        labelMinBuildingDimMin->setObjectName(QStringLiteral("labelMinBuildingDimMin"));
        labelMinBuildingDimMin->setGeometry(QRect(210, 80, 31, 21));
        labelMinBuildingDimMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelNumStoriesMinMax = new QLabel(groupBox_3);
        labelNumStoriesMinMax->setObjectName(QStringLiteral("labelNumStoriesMinMax"));
        labelNumStoriesMinMax->setGeometry(QRect(370, 20, 31, 21));
        labelNumStoriesMinMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelNumStoriesMaxMax = new QLabel(groupBox_3);
        labelNumStoriesMaxMax->setObjectName(QStringLiteral("labelNumStoriesMaxMax"));
        labelNumStoriesMaxMax->setGeometry(QRect(370, 50, 31, 21));
        labelNumStoriesMaxMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelMinBuildingDimMax = new QLabel(groupBox_3);
        labelMinBuildingDimMax->setObjectName(QStringLiteral("labelMinBuildingDimMax"));
        labelMinBuildingDimMax->setGeometry(QRect(370, 80, 31, 21));
        labelMinBuildingDimMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGenerateAll = new QPushButton(dockWidgetContents);
        pushButtonGenerateAll->setObjectName(QStringLiteral("pushButtonGenerateAll"));
        pushButtonGenerateAll->setGeometry(QRect(30, 600, 361, 31));
        comboBoxCity = new QComboBox(dockWidgetContents);
        comboBoxCity->setObjectName(QStringLiteral("comboBoxCity"));
        comboBoxCity->setGeometry(QRect(130, 10, 231, 22));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 10, 81, 21));
        ControlWidget->setWidget(dockWidgetContents);
        QWidget::setTabOrder(lineEditAvenueSegmentLength, lineEditRoadBaseOrientation);
        QWidget::setTabOrder(lineEditRoadBaseOrientation, lineEditRoadCurvature);
        QWidget::setTabOrder(lineEditRoadCurvature, lineEditMajorRoadWidth);
        QWidget::setTabOrder(lineEditMajorRoadWidth, lineEditParkRatio);
        QWidget::setTabOrder(lineEditParkRatio, lineEditParcelArea);
        QWidget::setTabOrder(lineEditParcelArea, lineEditParcelAreaDev);
        QWidget::setTabOrder(lineEditParcelAreaDev, lineEditSetbackFront);
        QWidget::setTabOrder(lineEditSetbackFront, lineEditSetbackRear);
        QWidget::setTabOrder(lineEditSetbackRear, lineEditSetbackSide);
        QWidget::setTabOrder(lineEditSetbackSide, lineEditNumStoriesMin);
        QWidget::setTabOrder(lineEditNumStoriesMin, lineEditNumStoriesMax);
        QWidget::setTabOrder(lineEditNumStoriesMax, lineEditMinBuildingDim);
        QWidget::setTabOrder(lineEditMinBuildingDim, pushButtonGenerateAll);

        retranslateUi(ControlWidget);

        QMetaObject::connectSlotsByName(ControlWidget);
    } // setupUi

    void retranslateUi(QDockWidget *ControlWidget)
    {
        groupBox->setTitle(QApplication::translate("ControlWidget", "Roads", Q_NULLPTR));
        label_3->setText(QApplication::translate("ControlWidget", "Avenue segment length [m]:", Q_NULLPTR));
        label_6->setText(QApplication::translate("ControlWidget", "Road base orientation [deg]:", Q_NULLPTR));
        label_9->setText(QApplication::translate("ControlWidget", "Road curvature:", Q_NULLPTR));
        label_20->setText(QApplication::translate("ControlWidget", "Major road width [m]:", Q_NULLPTR));
        label_23->setText(QApplication::translate("ControlWidget", "Minor road width [m]:", Q_NULLPTR));
        label_25->setText(QApplication::translate("ControlWidget", "Use elevation:", Q_NULLPTR));
        checkBoxUseElevation->setText(QString());
        labelAvenueSegmentLengthMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelAvenueSegmentLengthMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelRoadBaseOrientationMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelRoadBaseOrientationMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelRoadCurvatureMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelRoadCurvatureMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelMajorRoadWidthMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelMajorRoadWidthMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelMinorRoadWidthMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelMinorRoadWidthMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("ControlWidget", "Parcels", Q_NULLPTR));
        label_11->setText(QApplication::translate("ControlWidget", "Park ratio:", Q_NULLPTR));
        label_15->setText(QApplication::translate("ControlWidget", "Parcel area [m^2]:", Q_NULLPTR));
        label_21->setText(QApplication::translate("ControlWidget", "Setback side [m]:", Q_NULLPTR));
        label_17->setText(QApplication::translate("ControlWidget", "Setback front [m]:", Q_NULLPTR));
        label_19->setText(QApplication::translate("ControlWidget", "Setback rear [m]:", Q_NULLPTR));
        label_16->setText(QApplication::translate("ControlWidget", "Deviation of parcel area [m^2]:", Q_NULLPTR));
        labelParkRatioMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelParkRatioMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelParcelAreaMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelParcelAreaMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelParcelAreaDevMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelParcelAreaDevMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelSetbackFrontMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelSetbackFrontMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelSetbackRearMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelSetbackRearMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelSetbackSideMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelSetbackSideMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("ControlWidget", "Buildings", Q_NULLPTR));
        label_33->setText(QApplication::translate("ControlWidget", "# Min stories", Q_NULLPTR));
        label_35->setText(QApplication::translate("ControlWidget", "# Max stories", Q_NULLPTR));
        label_34->setText(QApplication::translate("ControlWidget", "Min dimension [m]:", Q_NULLPTR));
        labelNumStoriesMinMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelNumStoriesMaxMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelMinBuildingDimMin->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelNumStoriesMinMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelNumStoriesMaxMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        labelMinBuildingDimMax->setText(QApplication::translate("ControlWidget", "0", Q_NULLPTR));
        pushButtonGenerateAll->setText(QApplication::translate("ControlWidget", "Generate City", Q_NULLPTR));
        label->setText(QApplication::translate("ControlWidget", "Select a city:", Q_NULLPTR));
        Q_UNUSED(ControlWidget);
    } // retranslateUi

};

namespace Ui {
    class ControlWidget: public Ui_ControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLWIDGET_H
