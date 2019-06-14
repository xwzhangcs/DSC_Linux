#include "ParameterControlDlg.h"
#include <QFileDialog>

ParameterControlDlg::ParameterControlDlg(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEditSmMid->setText("300.0");
	ui.parcelBoundarySmallMidSlider->setMinimum(100);
	ui.parcelBoundarySmallMidSlider->setMaximum(400);
	ui.parcelBoundarySmallMidSlider->setValue(300);

	ui.lineEditMidLg->setText("570.0");
	ui.parcelBoundaryMidLargeSlider->setMinimum(400);
	ui.parcelBoundaryMidLargeSlider->setMaximum(800);
	ui.parcelBoundaryMidLargeSlider->setValue(570);

	ui.lineEditSetback->setText("1.0");
	ui.correctionFactorSlider->setMinimum(10);
	ui.correctionFactorSlider->setMaximum(200);
	ui.correctionFactorSlider->setSingleStep(1);
	ui.correctionFactorSlider->setValue(100);

	connect(ui.parcelBoundarySmallMidSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderParcelSmallMidChanged(int)));
	//connect(ui.lineEditSmMid, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditParcelSmMidChanged()));

	connect(ui.parcelBoundaryMidLargeSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderParcelMidLargeChanged(int)));
	//connect(ui.lineEditMidLg, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditParcelMidLargeChanged()));

	connect(ui.correctionFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderCorrectionChanged(int)));
	//connect(ui.lineEditSetback, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditCorrectionChanged()));

	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

}

ParameterControlDlg::~ParameterControlDlg()
{

}

void ParameterControlDlg::onSliderParcelSmallMidChanged(int value) {
	ui.lineEditSmMid->setText(QString::number(ui.parcelBoundarySmallMidSlider->value()));
}

void ParameterControlDlg::onLineEditParcelSmMidChanged(){
	ui.parcelBoundarySmallMidSlider->setValue(ui.lineEditSmMid->text().toInt());
}

void ParameterControlDlg::onSliderParcelMidLargeChanged(int value) {
	ui.lineEditMidLg->setText(QString::number(ui.parcelBoundaryMidLargeSlider->value()));
}

void ParameterControlDlg::onLineEditParcelMidLargeChanged(){
	ui.parcelBoundaryMidLargeSlider->setValue(ui.lineEditMidLg->text().toInt());
}

void ParameterControlDlg::onSliderCorrectionChanged(int value) {
	ui.lineEditSetback->setText(QString::number(ui.correctionFactorSlider->value() / 100.0));
}

void ParameterControlDlg::onLineEditCorrectionChanged(){
	ui.correctionFactorSlider->setValue(ui.lineEditSetback->text().toFloat() * 100.0);
}


void ParameterControlDlg::onOK() {
	accept();
}

void ParameterControlDlg::onCancel() {
	reject();
}
