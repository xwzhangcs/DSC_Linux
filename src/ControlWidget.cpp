#include "ControlWidget.h"
#include "MainWindow.h"
#include "UrbanGeometry.h"
#include "GLWidget3D.h"
#include "global.h"

ControlWidget::ControlWidget(MainWindow* mainWin) : QDockWidget("Control Widget", (QWidget*)mainWin) {
	std::cout << "Going to ControlWidget" << std::endl;
	this->mainWin = mainWin;

	// set up the UI
	ui.setupUi(this);

	ui.comboBoxCity->addItem("Default");
	ui.comboBoxCity->addItem("San Francisco");
	ui.comboBoxCity->addItem("New York");
	ui.comboBoxCity->addItem("Chicago");

	ui.lineEditAvenueSegmentLength->setText(QString::number(G::getFloat("avenueAvgSegmentLength")));
	ui.labelAvenueSegmentLengthMin->setText("20");
	ui.labelAvenueSegmentLengthMax->setText("200");
	ui.horizontalSliderAvenueSegmentLength->setMinimum(20);
	ui.horizontalSliderAvenueSegmentLength->setMaximum(200);
	ui.horizontalSliderAvenueSegmentLength->setValue(G::getFloat("avenueAvgSegmentLength"));

	ui.lineEditRoadBaseOrientation->setText(QString::number(G::getFloat("road_base_orientation")));
	ui.labelRoadBaseOrientationMin->setText("0");
	ui.labelRoadBaseOrientationMax->setText("360");
	ui.horizontalSliderRoadBaseOrientation->setMinimum(0);
	ui.horizontalSliderRoadBaseOrientation->setMaximum(360);
	ui.horizontalSliderRoadBaseOrientation->setValue(G::getFloat("road_base_orientation"));

	ui.lineEditRoadCurvature->setText(QString::number(G::getFloat("road_curvature")));
	ui.labelRoadCurvatureMin->setText("0");
	ui.labelRoadCurvatureMax->setText("0.8");
	ui.horizontalSliderRoadCurvature->setMinimum(0);
	ui.horizontalSliderRoadCurvature->setMaximum(80);
	ui.horizontalSliderRoadCurvature->setValue(G::getFloat("road_curvature") * 100);

	ui.lineEditMajorRoadWidth->setText(QString::number(G::getFloat("major_road_width")));
	ui.labelMajorRoadWidthMin->setText("3");
	ui.labelMajorRoadWidthMax->setText("30");
	ui.horizontalSliderMajorRoadWidth->setMinimum(3);
	ui.horizontalSliderMajorRoadWidth->setMaximum(30);
	ui.horizontalSliderMajorRoadWidth->setValue(G::getFloat("major_road_width"));

	ui.lineEditMinorRoadWidth->setText(QString::number(G::getFloat("minor_road_width")));
	ui.labelMinorRoadWidthMin->setText("3");
	ui.labelMinorRoadWidthMax->setText("15");
	ui.horizontalSliderMinorRoadWidth->setMinimum(3);
	ui.horizontalSliderMinorRoadWidth->setMaximum(15);
	ui.horizontalSliderMinorRoadWidth->setValue(G::getFloat("minor_road_width"));

	ui.checkBoxUseElevation->setChecked(true);

	ui.lineEditParkRatio->setText(QString::number(G::getFloat("parksRatio")));
	ui.labelParkRatioMin->setText("0");
	ui.labelParkRatioMax->setText("0.5");
	ui.horizontalSliderParkRatio->setMinimum(0);
	ui.horizontalSliderParkRatio->setMaximum(50);
	ui.horizontalSliderParkRatio->setValue(G::getFloat("parksRatio") * 100);

	ui.lineEditParcelArea->setText(QString::number(G::getFloat("parcel_area_mean")));
	ui.labelParcelAreaMin->setText("300");
	ui.labelParcelAreaMax->setText("2000");
	ui.horizontalSliderParcelArea->setMinimum(300);
	ui.horizontalSliderParcelArea->setMaximum(2000);
	ui.horizontalSliderParcelArea->setValue(G::getFloat("parcel_area_mean"));
	
	ui.lineEditParcelAreaDev->setText(QString::number(G::getFloat("parcel_area_deviation")));
	ui.labelParcelAreaDevMin->setText("0");
	ui.labelParcelAreaDevMax->setText("500");
	ui.horizontalSliderParcelAreaDev->setMinimum(0);
	ui.horizontalSliderParcelAreaDev->setMaximum(500);
	ui.horizontalSliderParcelAreaDev->setValue(G::getFloat("parcel_area_deviation"));

	ui.lineEditSetbackFront->setText(QString::number(G::getFloat("parcel_setback_front")));
	ui.labelSetbackFrontMin->setText("0");
	ui.labelSetbackFrontMax->setText("10");
	ui.horizontalSliderSetbackFront->setMinimum(0);
	ui.horizontalSliderSetbackFront->setMaximum(10);
	ui.horizontalSliderSetbackFront->setValue(G::getFloat("parcel_setback_front"));
	
	ui.lineEditSetbackRear->setText(QString::number(G::getFloat("parcel_setback_rear")));
	ui.labelSetbackRearMin->setText("0");
	ui.labelSetbackRearMax->setText("10");
	ui.horizontalSliderSetbackRear->setMinimum(0);
	ui.horizontalSliderSetbackRear->setMaximum(10);
	ui.horizontalSliderSetbackRear->setValue(G::getFloat("parcel_setback_rear"));

	ui.lineEditSetbackSide->setText(QString::number(G::getFloat("parcel_setback_sides")));
	ui.labelSetbackSideMin->setText("0");
	ui.labelSetbackSideMax->setText("10");
	ui.horizontalSliderSetbackSide->setMinimum(0);
	ui.horizontalSliderSetbackSide->setMaximum(10);
	ui.horizontalSliderSetbackSide->setValue(G::getFloat("parcel_setback_sides"));

	ui.lineEditNumStoriesMin->setText(QString::number(G::getFloat("building_stories_min")));
	ui.labelNumStoriesMinMin->setText("1");
	ui.labelNumStoriesMinMax->setText("10");
	ui.horizontalSliderNumStoriesMin->setMinimum(1);
	ui.horizontalSliderNumStoriesMin->setMaximum(10);
	ui.horizontalSliderNumStoriesMin->setValue(G::getFloat("building_stories_min"));

	ui.lineEditNumStoriesMax->setText(QString::number(G::getFloat("building_stories_max")));
	ui.labelNumStoriesMaxMin->setText("2");
	ui.labelNumStoriesMaxMax->setText("50");
	ui.horizontalSliderNumStoriesMax->setMinimum(2);
	ui.horizontalSliderNumStoriesMax->setMaximum(50);
	ui.horizontalSliderNumStoriesMax->setValue(G::getFloat("building_stories_max"));

	ui.lineEditMinBuildingDim->setText(QString::number(G::getFloat("building_min_dimension")));
	ui.labelMinBuildingDimMin->setText("1");
	ui.labelMinBuildingDimMax->setText("20");
	ui.horizontalSliderMinBuildingDim->setMinimum(1);
	ui.horizontalSliderMinBuildingDim->setMaximum(20);
	ui.horizontalSliderMinBuildingDim->setValue(G::getFloat("building_min_dimension"));

	connect(ui.comboBoxCity, SIGNAL(currentIndexChanged(int)), this, SLOT(onCityChanged(int)));
	connect(ui.lineEditAvenueSegmentLength, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditAvenueSegmentLengthChanged()));
	connect(ui.horizontalSliderAvenueSegmentLength, SIGNAL(valueChanged(int)), this, SLOT(onSliderAvenueSegmentLengthChanged(int)));
	connect(ui.lineEditRoadBaseOrientation, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditRoadBaseOrientationChanged()));
	connect(ui.horizontalSliderRoadBaseOrientation, SIGNAL(valueChanged(int)), this, SLOT(onSliderRoadBaseOrientationChanged(int)));
	connect(ui.lineEditRoadCurvature, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditRoadCurvatureChanged()));
	connect(ui.horizontalSliderRoadCurvature, SIGNAL(valueChanged(int)), this, SLOT(onSliderRoadCurvatureChanged(int)));
	connect(ui.lineEditMajorRoadWidth, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditMajorRoadWidthChanged()));
	connect(ui.horizontalSliderMajorRoadWidth, SIGNAL(valueChanged(int)), this, SLOT(onSliderMajorRoadWidthChanged(int)));
	connect(ui.lineEditMinorRoadWidth, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditMinorRoadWidthChanged()));
	connect(ui.horizontalSliderMinorRoadWidth, SIGNAL(valueChanged(int)), this, SLOT(onSliderMinorRoadWidthChanged(int)));
	connect(ui.lineEditParkRatio, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditParkRatioChanged()));
	connect(ui.horizontalSliderParkRatio, SIGNAL(valueChanged(int)), this, SLOT(onSliderParkRatioChanged(int)));
	connect(ui.lineEditParcelArea, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditParcelAreaChanged()));
	connect(ui.horizontalSliderParcelArea, SIGNAL(valueChanged(int)), this, SLOT(onSliderParcelAreaChanged(int)));
	connect(ui.lineEditParcelAreaDev, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditParcelAreaDevChanged()));
	connect(ui.horizontalSliderParcelAreaDev, SIGNAL(valueChanged(int)), this, SLOT(onSliderParcelAreaDevChanged(int)));
	connect(ui.lineEditSetbackFront, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditSetbackFrontChanged()));
	connect(ui.horizontalSliderSetbackFront, SIGNAL(valueChanged(int)), this, SLOT(onSliderSetbackFrontChanged(int)));
	connect(ui.lineEditSetbackRear, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditSetbackRearChanged()));
	connect(ui.horizontalSliderSetbackRear, SIGNAL(valueChanged(int)), this, SLOT(onSliderSetbackRearChanged(int)));
	connect(ui.lineEditSetbackSide, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditSetbackSideChanged()));
	connect(ui.horizontalSliderSetbackSide, SIGNAL(valueChanged(int)), this, SLOT(onSliderSetbackSideChanged(int)));
	connect(ui.lineEditNumStoriesMin, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditNumStoriesMinChanged()));
	connect(ui.horizontalSliderNumStoriesMin, SIGNAL(valueChanged(int)), this, SLOT(onSliderNumStoriesMinChanged(int)));
	connect(ui.lineEditNumStoriesMax, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditNumStoriesMaxChanged()));
	connect(ui.horizontalSliderNumStoriesMax, SIGNAL(valueChanged(int)), this, SLOT(onSliderNumStoriesMaxChanged(int)));
	connect(ui.lineEditMinBuildingDim, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditMinBuildingDimChanged()));
	connect(ui.horizontalSliderMinBuildingDim, SIGNAL(valueChanged(int)), this, SLOT(onSliderMinBuildingDimChanged(int)));
	connect(ui.pushButtonGenerateAll, SIGNAL(clicked()), mainWin, SLOT(onGenerateCity()));
	
	hide();	
}

void ControlWidget::onCityChanged(int index) {
	// not implemented yet
}

void ControlWidget::onLineEditAvenueSegmentLengthChanged() {
	ui.horizontalSliderAvenueSegmentLength->setValue(ui.lineEditAvenueSegmentLength->text().toFloat());
}

void ControlWidget::onSliderAvenueSegmentLengthChanged(int value) {
	ui.lineEditAvenueSegmentLength->setText(QString::number(ui.horizontalSliderAvenueSegmentLength->value()));
}

void ControlWidget::onLineEditRoadBaseOrientationChanged() {
	ui.horizontalSliderRoadBaseOrientation->setValue(ui.lineEditRoadBaseOrientation->text().toFloat());
}

void ControlWidget::onSliderRoadBaseOrientationChanged(int value) {
	ui.lineEditRoadBaseOrientation->setText(QString::number(ui.horizontalSliderRoadBaseOrientation->value()));
}

void ControlWidget::onLineEditRoadCurvatureChanged() {
	ui.horizontalSliderRoadCurvature->setValue(ui.lineEditRoadCurvature->text().toFloat() * 100);
}

void ControlWidget::onSliderRoadCurvatureChanged(int value) {
	ui.lineEditRoadCurvature->setText(QString::number(ui.horizontalSliderRoadCurvature->value() * 0.01));
}

void ControlWidget::onLineEditMajorRoadWidthChanged() {
	ui.horizontalSliderMajorRoadWidth->setValue(ui.lineEditMajorRoadWidth->text().toFloat());
}

void ControlWidget::onSliderMajorRoadWidthChanged(int value) {
	ui.lineEditMajorRoadWidth->setText(QString::number(ui.horizontalSliderMajorRoadWidth->value()));
}

void ControlWidget::onLineEditMinorRoadWidthChanged() {
	ui.horizontalSliderMinorRoadWidth->setValue(ui.lineEditMinorRoadWidth->text().toFloat());
}

void ControlWidget::onSliderMinorRoadWidthChanged(int value) {
	ui.lineEditMinorRoadWidth->setText(QString::number(ui.horizontalSliderMinorRoadWidth->value()));
}

void ControlWidget::onLineEditParkRatioChanged() {
	ui.horizontalSliderParkRatio->setValue(ui.lineEditParkRatio->text().toFloat() * 100);
}

void ControlWidget::onSliderParkRatioChanged(int value) {
	ui.lineEditParkRatio->setText(QString::number(ui.horizontalSliderParkRatio->value() * 0.01));
}

void ControlWidget::onLineEditParcelAreaChanged() {
	ui.horizontalSliderParcelArea->setValue(ui.lineEditParcelArea->text().toFloat());
}

void ControlWidget::onSliderParcelAreaChanged(int value) {
	ui.lineEditParcelArea->setText(QString::number(ui.horizontalSliderParcelArea->value()));
}

void ControlWidget::onLineEditParcelAreaDevChanged() {
	ui.horizontalSliderParcelAreaDev->setValue(ui.lineEditParcelAreaDev->text().toFloat());
}

void ControlWidget::onSliderParcelAreaDevChanged(int value) {
	ui.lineEditParcelAreaDev->setText(QString::number(ui.horizontalSliderParcelAreaDev->value()));
}

void ControlWidget::onLineEditSetbackFrontChanged() {
	ui.horizontalSliderSetbackFront->setValue(ui.lineEditSetbackFront->text().toFloat());
}

void ControlWidget::onSliderSetbackFrontChanged(int value) {
	ui.lineEditSetbackFront->setText(QString::number(ui.horizontalSliderSetbackFront->value()));
}

void ControlWidget::onLineEditSetbackRearChanged() {
	ui.horizontalSliderSetbackRear->setValue(ui.lineEditSetbackRear->text().toFloat());
}

void ControlWidget::onSliderSetbackRearChanged(int value) {
	ui.lineEditSetbackRear->setText(QString::number(ui.horizontalSliderSetbackRear->value()));
}

void ControlWidget::onLineEditSetbackSideChanged() {
	ui.horizontalSliderSetbackSide->setValue(ui.lineEditSetbackSide->text().toFloat());
}

void ControlWidget::onSliderSetbackSideChanged(int value) {
	ui.lineEditSetbackSide->setText(QString::number(ui.horizontalSliderSetbackSide->value()));
}

void ControlWidget::onLineEditNumStoriesMinChanged() {
	ui.horizontalSliderNumStoriesMin->setValue(ui.lineEditNumStoriesMin->text().toFloat());
}

void ControlWidget::onSliderNumStoriesMinChanged(int value) {
	ui.lineEditNumStoriesMin->setText(QString::number(ui.horizontalSliderNumStoriesMin->value()));
}

void ControlWidget::onLineEditNumStoriesMaxChanged() {
	ui.horizontalSliderNumStoriesMax->setValue(ui.lineEditNumStoriesMax->text().toFloat());
}

void ControlWidget::onSliderNumStoriesMaxChanged(int value) {
	ui.lineEditNumStoriesMax->setText(QString::number(ui.horizontalSliderNumStoriesMax->value()));
}

void ControlWidget::onLineEditMinBuildingDimChanged() {
	ui.horizontalSliderMinBuildingDim->setValue(ui.lineEditMinBuildingDim->text().toFloat());
}

void ControlWidget::onSliderMinBuildingDimChanged(int value) {
	ui.lineEditMinBuildingDim->setText(QString::number(ui.horizontalSliderMinBuildingDim->value()));
}
