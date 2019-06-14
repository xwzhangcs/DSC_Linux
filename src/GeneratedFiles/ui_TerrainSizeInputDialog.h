/********************************************************************************
** Form generated from reading UI file 'TerrainSizeInputDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERRAINSIZEINPUTDIALOG_H
#define UI_TERRAINSIZEINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TerrainSizeInputDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label;
    QLineEdit *lineEditSide;
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *lineEditCellResolution;

    void setupUi(QDialog *TerrainSizeInputDialog)
    {
        if (TerrainSizeInputDialog->objectName().isEmpty())
            TerrainSizeInputDialog->setObjectName(QStringLiteral("TerrainSizeInputDialog"));
        TerrainSizeInputDialog->resize(220, 126);
        layoutWidget = new QWidget(TerrainSizeInputDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 80, 201, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(31, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        label = new QLabel(TerrainSizeInputDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 41, 16));
        lineEditSide = new QLineEdit(TerrainSizeInputDialog);
        lineEditSide->setObjectName(QStringLiteral("lineEditSide"));
        lineEditSide->setGeometry(QRect(110, 16, 51, 20));
        label_2 = new QLabel(TerrainSizeInputDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 16, 21, 16));
        label_5 = new QLabel(TerrainSizeInputDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 54, 71, 16));
        lineEditCellResolution = new QLineEdit(TerrainSizeInputDialog);
        lineEditCellResolution->setObjectName(QStringLiteral("lineEditCellResolution"));
        lineEditCellResolution->setGeometry(QRect(110, 50, 51, 20));

        retranslateUi(TerrainSizeInputDialog);

        QMetaObject::connectSlotsByName(TerrainSizeInputDialog);
    } // setupUi

    void retranslateUi(QDialog *TerrainSizeInputDialog)
    {
        TerrainSizeInputDialog->setWindowTitle(QApplication::translate("TerrainSizeInputDialog", "Dialog", Q_NULLPTR));
        okButton->setText(QApplication::translate("TerrainSizeInputDialog", "OK", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("TerrainSizeInputDialog", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("TerrainSizeInputDialog", "Side:", Q_NULLPTR));
        label_2->setText(QApplication::translate("TerrainSizeInputDialog", "[m]", Q_NULLPTR));
        label_5->setText(QApplication::translate("TerrainSizeInputDialog", "Cell Resolution:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TerrainSizeInputDialog: public Ui_TerrainSizeInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERRAINSIZEINPUTDIALOG_H
