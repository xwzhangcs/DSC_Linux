/********************************************************************************
** Form generated from reading UI file 'BuildingMetrics.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDINGMETRICS_H
#define UI_BUILDINGMETRICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildingMetrics
{
public:

    void setupUi(QWidget *BuildingMetrics)
    {
        if (BuildingMetrics->objectName().isEmpty())
            BuildingMetrics->setObjectName(QStringLiteral("BuildingMetrics"));
        BuildingMetrics->resize(400, 300);

        retranslateUi(BuildingMetrics);

        QMetaObject::connectSlotsByName(BuildingMetrics);
    } // setupUi

    void retranslateUi(QWidget *BuildingMetrics)
    {
        BuildingMetrics->setWindowTitle(QApplication::translate("BuildingMetrics", "BuildingMetrics", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BuildingMetrics: public Ui_BuildingMetrics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDINGMETRICS_H
