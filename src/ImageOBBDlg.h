#ifndef IMAGEOBBDLG_H
#define IMAGEOBBDLG_H

#include <QDialog>
#include "ui_ImageOBBDlg.h"

class ImageOBBDlg : public QDialog
{
	Q_OBJECT

public:
	ImageOBBDlg(QWidget *parent = 0);
	~ImageOBBDlg();

public:
	Ui::ImageOBBDlg ui;

public slots:
	void onGetSrcPath();
	void onGetDesPath();
	void onOK();
};

#endif // IMAGEOBBDLG_H
