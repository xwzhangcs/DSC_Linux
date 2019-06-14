#include "ImageOBBDlg.h"
#include <QFileDialog>

ImageOBBDlg::ImageOBBDlg(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonPathOBBSrc, SIGNAL(clicked()), this, SLOT(onGetSrcPath()));
	connect(ui.pushButtonPathOBBDes, SIGNAL(clicked()), this, SLOT(onGetDesPath()));
	connect(ui.pushButtonOBBOK, SIGNAL(clicked()), this, SLOT(onOK()));
}

ImageOBBDlg::~ImageOBBDlg()
{

}

void ImageOBBDlg::onGetDesPath() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditImageOBBDes->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditImageOBBDes->setText(dir);
	}
}

void ImageOBBDlg::onGetSrcPath(){
	// load the image
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.png)"));
	if (filename.isEmpty()) return;
	ui.lineEditImageOBBSrc->setText(filename);
}


void ImageOBBDlg::onOK() {
	accept();
}
