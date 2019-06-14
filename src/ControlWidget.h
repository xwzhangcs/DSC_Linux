#pragma once

#include <QtWidgets/QDockWidget>
#include "ui_ControlWidget.h"

class MainWindow;

class ControlWidget : public QDockWidget {
	Q_OBJECT

public:
	MainWindow* mainWin;
	Ui::ControlWidget ui;

public:
	ControlWidget(MainWindow* mainWin);

public slots:
	void onCityChanged(int index);
	void onLineEditAvenueSegmentLengthChanged();
	void onSliderAvenueSegmentLengthChanged(int value);
	void onLineEditRoadBaseOrientationChanged();
	void onSliderRoadBaseOrientationChanged(int value);
	void onLineEditRoadCurvatureChanged();
	void onSliderRoadCurvatureChanged(int value);
	void onLineEditMajorRoadWidthChanged();
	void onSliderMajorRoadWidthChanged(int value);
	void onLineEditMinorRoadWidthChanged();
	void onSliderMinorRoadWidthChanged(int value);
	void onLineEditParkRatioChanged();
	void onSliderParkRatioChanged(int value);
	void onLineEditParcelAreaChanged();
	void onSliderParcelAreaChanged(int value);
	void onLineEditParcelAreaDevChanged();
	void onSliderParcelAreaDevChanged(int value);
	void onLineEditSetbackFrontChanged();
	void onSliderSetbackFrontChanged(int value);
	void onLineEditSetbackRearChanged();
	void onSliderSetbackRearChanged(int value);
	void onLineEditSetbackSideChanged();
	void onSliderSetbackSideChanged(int value);
	void onLineEditNumStoriesMinChanged();
	void onSliderNumStoriesMinChanged(int value);
	void onLineEditNumStoriesMaxChanged();
	void onSliderNumStoriesMaxChanged(int value);
	void onLineEditMinBuildingDimChanged();
	void onSliderMinBuildingDimChanged(int value);
};

