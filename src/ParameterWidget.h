#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QDialog>
#include "ui_ParameterControlWidget.h"

class ParameterControlWidget : public QDialog
{
	Q_OBJECT

public:
	ParameterControlWidget(QWidget *parent = 0);
	~ParameterControlWidget();

public:
	Ui::ParameterControlWidget ui;

	public slots:

	void onOK();
	void onCancel();

};

#endif // GENERATEBLOCKSDLG_H


