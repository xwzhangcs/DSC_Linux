#include "ParameterWidget.h"
#include <QFileDialog>

ParameterControlWidget::ParameterControlWidget(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

}

ParameterControlWidget::~ParameterControlWidget()
{

}

void ParameterControlWidget::onOK() {
	accept();
}

void ParameterControlWidget::onCancel() {
	reject();
}
