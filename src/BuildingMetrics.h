#ifndef BUILDINGMETRICS_H
#define BUILDINGMETRICS_H

#include <QWidget>
#include "ui_BuildingMetrics.h"

class BuildingMetrics : public QWidget
{
	Q_OBJECT

public:
	BuildingMetrics(QWidget *parent = 0);
	~BuildingMetrics();

private:
	Ui::BuildingMetrics ui;
};

#endif // BUILDINGMETRICS_H
