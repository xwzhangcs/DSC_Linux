#ifndef PARCELMETRICS_H
#define PARCELMETRICS_H

#include <QWidget>
#include "ui_ParcelMetrics.h"

class ParcelMetrics : public QWidget
{
	Q_OBJECT

public:
	ParcelMetrics(QWidget *parent = 0);
	~ParcelMetrics();

private:
	Ui::ParcelMetrics ui;
};

#endif // PARCELMETRICS_H
