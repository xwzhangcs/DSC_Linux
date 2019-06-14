
#ifndef PARAMETERDLG_H
#define PARAMETERDLG_H

#include <QDialog>
#include "ui_ParameterControlDlg.h"

class ParameterControlDlg : public QDialog
{
	Q_OBJECT

public:
	ParameterControlDlg(QWidget *parent = 0);
	~ParameterControlDlg();

public:
	Ui::ParameterControlDlg ui;

	public slots:

	void onOK();
	void onCancel();
	void onSliderParcelSmallMidChanged(int);
	void onLineEditParcelSmMidChanged();
	void onSliderParcelMidLargeChanged(int);
	void onLineEditParcelMidLargeChanged();
	void onSliderCorrectionChanged(int);
	void onLineEditCorrectionChanged();

};

#endif // GENERATEBLOCKSDLG_H