/********************************************************************************
** Form generated from reading UI file 'GenerateBlocksDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEBLOCKSDLG_H
#define UI_GENERATEBLOCKSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateBlocksDlg
{
public:
    QLineEdit *lineEditOutputDirectory;
    QLabel *label_2;
    QLineEdit *lineEditNumScenarios;
    QLabel *label;
    QPushButton *pushButtonOutputDirectory;
    QLineEdit *lineEditBuildingFootprintsImageSize;
    QPushButton *pushButtonCancel;
    QGroupBox *groupBox_2;
    QLabel *label_15;
    QLineEdit *lineEditParcelAreaMin;
    QLineEdit *lineEditParcelAreaMax;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *lineEditSetbackFrontMin;
    QLineEdit *lineEditSetbackFrontMax;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lineEditSetbackRearMin;
    QLineEdit *lineEditSetbackRearMax;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *lineEditSetbackSideMin;
    QLineEdit *lineEditSetbackSideMax;
    QLabel *label_22;
    QLabel *label_38;
    QLineEdit *lineEditParcelAreaDev;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_40;
    QPushButton *pushButtonOK;
    QGroupBox *groupBox_4;
    QLabel *label_35;
    QLineEdit *lineEditBlocksWidthMin;
    QLineEdit *lineEditBlocksWidthMax;
    QLabel *label_39;
    QLabel *label_41;
    QLineEdit *lineEditBlocksHeightMin;
    QLineEdit *lineEditBlocksHeightMax;
    QLabel *label_42;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *lineEditBatchNum;
    QLabel *label_43;

    void setupUi(QWidget *GenerateBlocksDlg)
    {
        if (GenerateBlocksDlg->objectName().isEmpty())
            GenerateBlocksDlg->setObjectName(QStringLiteral("GenerateBlocksDlg"));
        GenerateBlocksDlg->resize(557, 502);
        lineEditOutputDirectory = new QLineEdit(GenerateBlocksDlg);
        lineEditOutputDirectory->setObjectName(QStringLiteral("lineEditOutputDirectory"));
        lineEditOutputDirectory->setGeometry(QRect(130, 50, 361, 20));
        label_2 = new QLabel(GenerateBlocksDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 121, 21));
        lineEditNumScenarios = new QLineEdit(GenerateBlocksDlg);
        lineEditNumScenarios->setObjectName(QStringLiteral("lineEditNumScenarios"));
        lineEditNumScenarios->setGeometry(QRect(130, 20, 71, 20));
        label = new QLabel(GenerateBlocksDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 61, 21));
        pushButtonOutputDirectory = new QPushButton(GenerateBlocksDlg);
        pushButtonOutputDirectory->setObjectName(QStringLiteral("pushButtonOutputDirectory"));
        pushButtonOutputDirectory->setGeometry(QRect(500, 50, 31, 23));
        lineEditBuildingFootprintsImageSize = new QLineEdit(GenerateBlocksDlg);
        lineEditBuildingFootprintsImageSize->setObjectName(QStringLiteral("lineEditBuildingFootprintsImageSize"));
        lineEditBuildingFootprintsImageSize->setGeometry(QRect(180, 410, 71, 20));
        pushButtonCancel = new QPushButton(GenerateBlocksDlg);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(430, 450, 91, 31));
        groupBox_2 = new QGroupBox(GenerateBlocksDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 230, 521, 161));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(20, 30, 121, 21));
        lineEditParcelAreaMin = new QLineEdit(groupBox_2);
        lineEditParcelAreaMin->setObjectName(QStringLiteral("lineEditParcelAreaMin"));
        lineEditParcelAreaMin->setGeometry(QRect(150, 30, 71, 20));
        lineEditParcelAreaMax = new QLineEdit(groupBox_2);
        lineEditParcelAreaMax->setObjectName(QStringLiteral("lineEditParcelAreaMax"));
        lineEditParcelAreaMax->setGeometry(QRect(240, 30, 71, 20));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(226, 30, 16, 21));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(20, 60, 121, 21));
        lineEditSetbackFrontMin = new QLineEdit(groupBox_2);
        lineEditSetbackFrontMin->setObjectName(QStringLiteral("lineEditSetbackFrontMin"));
        lineEditSetbackFrontMin->setGeometry(QRect(150, 60, 71, 20));
        lineEditSetbackFrontMax = new QLineEdit(groupBox_2);
        lineEditSetbackFrontMax->setObjectName(QStringLiteral("lineEditSetbackFrontMax"));
        lineEditSetbackFrontMax->setGeometry(QRect(240, 60, 71, 20));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(226, 60, 16, 21));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(20, 90, 121, 21));
        lineEditSetbackRearMin = new QLineEdit(groupBox_2);
        lineEditSetbackRearMin->setObjectName(QStringLiteral("lineEditSetbackRearMin"));
        lineEditSetbackRearMin->setGeometry(QRect(150, 90, 71, 20));
        lineEditSetbackRearMax = new QLineEdit(groupBox_2);
        lineEditSetbackRearMax->setObjectName(QStringLiteral("lineEditSetbackRearMax"));
        lineEditSetbackRearMax->setGeometry(QRect(240, 90, 71, 20));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(226, 90, 16, 21));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 120, 121, 21));
        lineEditSetbackSideMin = new QLineEdit(groupBox_2);
        lineEditSetbackSideMin->setObjectName(QStringLiteral("lineEditSetbackSideMin"));
        lineEditSetbackSideMin->setGeometry(QRect(150, 120, 71, 20));
        lineEditSetbackSideMax = new QLineEdit(groupBox_2);
        lineEditSetbackSideMax->setObjectName(QStringLiteral("lineEditSetbackSideMax"));
        lineEditSetbackSideMax->setGeometry(QRect(240, 120, 71, 20));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(226, 120, 16, 21));
        label_38 = new QLabel(groupBox_2);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(370, 30, 51, 21));
        lineEditParcelAreaDev = new QLineEdit(groupBox_2);
        lineEditParcelAreaDev->setObjectName(QStringLiteral("lineEditParcelAreaDev"));
        lineEditParcelAreaDev->setGeometry(QRect(430, 30, 71, 20));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(320, 60, 31, 21));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(320, 90, 31, 21));
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(320, 120, 31, 21));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(320, 30, 41, 21));
        label_40 = new QLabel(GenerateBlocksDlg);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(10, 410, 161, 21));
        pushButtonOK = new QPushButton(GenerateBlocksDlg);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(320, 450, 91, 31));
        groupBox_4 = new QGroupBox(GenerateBlocksDlg);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 140, 521, 81));
        label_35 = new QLabel(groupBox_4);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(20, 20, 121, 21));
        lineEditBlocksWidthMin = new QLineEdit(groupBox_4);
        lineEditBlocksWidthMin->setObjectName(QStringLiteral("lineEditBlocksWidthMin"));
        lineEditBlocksWidthMin->setGeometry(QRect(150, 20, 71, 20));
        lineEditBlocksWidthMax = new QLineEdit(groupBox_4);
        lineEditBlocksWidthMax->setObjectName(QStringLiteral("lineEditBlocksWidthMax"));
        lineEditBlocksWidthMax->setGeometry(QRect(240, 20, 71, 20));
        label_39 = new QLabel(groupBox_4);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(226, 20, 16, 21));
        label_41 = new QLabel(groupBox_4);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(20, 50, 121, 21));
        lineEditBlocksHeightMin = new QLineEdit(groupBox_4);
        lineEditBlocksHeightMin->setObjectName(QStringLiteral("lineEditBlocksHeightMin"));
        lineEditBlocksHeightMin->setGeometry(QRect(150, 50, 71, 20));
        lineEditBlocksHeightMax = new QLineEdit(groupBox_4);
        lineEditBlocksHeightMax->setObjectName(QStringLiteral("lineEditBlocksHeightMax"));
        lineEditBlocksHeightMax->setGeometry(QRect(240, 50, 71, 20));
        label_42 = new QLabel(groupBox_4);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(226, 50, 16, 21));
        label_28 = new QLabel(groupBox_4);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(320, 50, 31, 21));
        label_29 = new QLabel(groupBox_4);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(320, 20, 31, 21));
        lineEditBatchNum = new QLineEdit(GenerateBlocksDlg);
        lineEditBatchNum->setObjectName(QStringLiteral("lineEditBatchNum"));
        lineEditBatchNum->setGeometry(QRect(130, 90, 71, 20));
        label_43 = new QLabel(GenerateBlocksDlg);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(20, 90, 101, 21));

        retranslateUi(GenerateBlocksDlg);

        QMetaObject::connectSlotsByName(GenerateBlocksDlg);
    } // setupUi

    void retranslateUi(QWidget *GenerateBlocksDlg)
    {
        GenerateBlocksDlg->setWindowTitle(QApplication::translate("GenerateBlocksDlg", "GenerateBlocksDlg", Q_NULLPTR));
        label_2->setText(QApplication::translate("GenerateBlocksDlg", "Output directory:", Q_NULLPTR));
        label->setText(QApplication::translate("GenerateBlocksDlg", "# Scenarios:", Q_NULLPTR));
        pushButtonOutputDirectory->setText(QApplication::translate("GenerateBlocksDlg", "...", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("GenerateBlocksDlg", "Cancel", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("GenerateBlocksDlg", "Parcels", Q_NULLPTR));
        label_15->setText(QApplication::translate("GenerateBlocksDlg", "Parcel area:", Q_NULLPTR));
        label_16->setText(QApplication::translate("GenerateBlocksDlg", "~", Q_NULLPTR));
        label_17->setText(QApplication::translate("GenerateBlocksDlg", "Setback front:", Q_NULLPTR));
        label_18->setText(QApplication::translate("GenerateBlocksDlg", "~", Q_NULLPTR));
        label_19->setText(QApplication::translate("GenerateBlocksDlg", "Setback rear:", Q_NULLPTR));
        label_20->setText(QApplication::translate("GenerateBlocksDlg", "~", Q_NULLPTR));
        label_21->setText(QApplication::translate("GenerateBlocksDlg", "Setback side:", Q_NULLPTR));
        label_22->setText(QApplication::translate("GenerateBlocksDlg", "~", Q_NULLPTR));
        label_38->setText(QApplication::translate("GenerateBlocksDlg", "Std Dev:", Q_NULLPTR));
        label_23->setText(QApplication::translate("GenerateBlocksDlg", "[m]", Q_NULLPTR));
        label_24->setText(QApplication::translate("GenerateBlocksDlg", "[m]", Q_NULLPTR));
        label_25->setText(QApplication::translate("GenerateBlocksDlg", "[m]", Q_NULLPTR));
        label_26->setText(QApplication::translate("GenerateBlocksDlg", "[m^2]", Q_NULLPTR));
        label_40->setText(QApplication::translate("GenerateBlocksDlg", "Block footprints image size", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("GenerateBlocksDlg", "OK", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("GenerateBlocksDlg", "Blocks", Q_NULLPTR));
        label_35->setText(QApplication::translate("GenerateBlocksDlg", "Block width:", Q_NULLPTR));
        label_39->setText(QApplication::translate("GenerateBlocksDlg", "~", Q_NULLPTR));
        label_41->setText(QApplication::translate("GenerateBlocksDlg", "Block height:", Q_NULLPTR));
        label_42->setText(QApplication::translate("GenerateBlocksDlg", "~", Q_NULLPTR));
        label_28->setText(QApplication::translate("GenerateBlocksDlg", "[m]", Q_NULLPTR));
        label_29->setText(QApplication::translate("GenerateBlocksDlg", "[m]", Q_NULLPTR));
        label_43->setText(QApplication::translate("GenerateBlocksDlg", "Batch number:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GenerateBlocksDlg: public Ui_GenerateBlocksDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEBLOCKSDLG_H
