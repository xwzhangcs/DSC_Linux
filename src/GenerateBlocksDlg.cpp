#include "GenerateBlocksDlg.h"
#include <QFileDialog>

GenerateBlocksDlg::GenerateBlocksDlg(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEditNumScenarios->setText("1");
	ui.lineEditOutputDirectory->setText("scenarios");
	ui.lineEditBatchNum->setText("1");
	ui.lineEditBlocksWidthMin->setText("227");
	ui.lineEditBlocksWidthMax->setText("227");
	ui.lineEditBlocksHeightMin->setText("150");
	ui.lineEditBlocksHeightMax->setText("200");
	ui.lineEditParcelAreaMin->setText("1");
	ui.lineEditParcelAreaMax->setText("5");
	ui.lineEditParcelAreaDev->setText("0");
	ui.lineEditSetbackFrontMin->setText("1.0");
	ui.lineEditSetbackFrontMax->setText("3.0");
	ui.lineEditSetbackRearMin->setText("1.0");
	ui.lineEditSetbackRearMax->setText("3.0");
	ui.lineEditSetbackSideMin->setText("1.0");
	ui.lineEditSetbackSideMax->setText("3.0");
	ui.lineEditBuildingFootprintsImageSize->setText("227");

	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

}

GenerateBlocksDlg::~GenerateBlocksDlg()
{

}

void GenerateBlocksDlg::onOutputDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutputDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutputDirectory->setText(dir);
	}
}

void GenerateBlocksDlg::onOK() {
	accept();
}

void GenerateBlocksDlg::onCancel() {
	reject();
}
