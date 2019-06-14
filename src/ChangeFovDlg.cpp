#include "ChangeFovDlg.h"

ChangeFovDlg::ChangeFovDlg(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEditFov->setText(QString::number(45));
	ui.horizontalSliderFov->setMinimum(0);
	ui.horizontalSliderFov->setMaximum(180);
	ui.horizontalSliderFov->setValue(45);

	connect(ui.lineEditFov, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditFovChanged()));
	connect(ui.horizontalSliderFov, SIGNAL(valueChanged(int)), this, SLOT(onSliderFovChanged(int)));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(onCancel()));
}

ChangeFovDlg::~ChangeFovDlg()
{
}

void ChangeFovDlg::onLineEditFovChanged() {
	ui.horizontalSliderFov->setValue(ui.lineEditFov->text().toFloat());
}

void ChangeFovDlg::onSliderFovChanged(int value) {
	ui.lineEditFov->setText(QString::number(ui.horizontalSliderFov->value()));
}

void ChangeFovDlg::onOK() {
	accept();
}

void ChangeFovDlg::onCancel() {
	reject();
}