/********************************************************************************
** Form generated from reading UI file 'ChangeFovDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEFOVDLG_H
#define UI_CHANGEFOVDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeFovDlg
{
public:
    QLabel *label;
    QLineEdit *lineEditFov;
    QSlider *horizontalSliderFov;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ChangeFovDlg)
    {
        if (ChangeFovDlg->objectName().isEmpty())
            ChangeFovDlg->setObjectName(QStringLiteral("ChangeFovDlg"));
        ChangeFovDlg->resize(400, 85);
        label = new QLabel(ChangeFovDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 47, 13));
        lineEditFov = new QLineEdit(ChangeFovDlg);
        lineEditFov->setObjectName(QStringLiteral("lineEditFov"));
        lineEditFov->setGeometry(QRect(50, 20, 113, 20));
        horizontalSliderFov = new QSlider(ChangeFovDlg);
        horizontalSliderFov->setObjectName(QStringLiteral("horizontalSliderFov"));
        horizontalSliderFov->setGeometry(QRect(200, 20, 160, 22));
        horizontalSliderFov->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(ChangeFovDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 20, 47, 13));
        label_3 = new QLabel(ChangeFovDlg);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 20, 47, 13));
        pushButton = new QPushButton(ChangeFovDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 60, 75, 23));
        pushButton_2 = new QPushButton(ChangeFovDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 60, 75, 23));

        retranslateUi(ChangeFovDlg);

        QMetaObject::connectSlotsByName(ChangeFovDlg);
    } // setupUi

    void retranslateUi(QWidget *ChangeFovDlg)
    {
        ChangeFovDlg->setWindowTitle(QApplication::translate("ChangeFovDlg", "ChangeFovDlg", Q_NULLPTR));
        label->setText(QApplication::translate("ChangeFovDlg", "Fov", Q_NULLPTR));
        label_2->setText(QApplication::translate("ChangeFovDlg", "0", Q_NULLPTR));
        label_3->setText(QApplication::translate("ChangeFovDlg", "90", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ChangeFovDlg", "Ok", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ChangeFovDlg", "Cancle", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChangeFovDlg: public Ui_ChangeFovDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEFOVDLG_H
