#ifndef FOVDLG_H
#define FOVDLG_H

#include <QDialog>
#include "ui_ChangeFovDlg.h"

class ChangeFovDlg : public QDialog
{
	Q_OBJECT

public:
	ChangeFovDlg(QWidget *parent = 0);
	~ChangeFovDlg();

public:
	Ui::ChangeFovDlg ui;

	public slots:

	void onLineEditFovChanged();
	void onSliderFovChanged(int value);
	void onOK();
	void onCancel();
};
#endif // GENERATEBLOCKSDLG_H