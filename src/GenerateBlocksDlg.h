#ifndef GENERATEBLOCKSDLG_H
#define GENERATEBLOCKSDLG_H

#include <QDialog>
#include "ui_GenerateBlocksDlg.h"

class GenerateBlocksDlg : public QDialog
{
	Q_OBJECT

public:
	GenerateBlocksDlg(QWidget *parent = 0);
	~GenerateBlocksDlg();

public:
	Ui::GenerateBlocksDlg ui;

public slots:

	void onOutputDirectory();
	void onOK();
	void onCancel();

};

#endif // GENERATEBLOCKSDLG_H


