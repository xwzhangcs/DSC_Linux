/********************************************************************************
** Form generated from reading UI file 'ImageOBBDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEOBBDLG_H
#define UI_IMAGEOBBDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageOBBDlg
{
public:
    QPushButton *pushButtonOBBOK;
    QPushButton *pushButtonPathOBBSrc;
    QLineEdit *lineEditImageOBBDes;
    QPushButton *pushButtonPathOBBDes;
    QLineEdit *lineEditImageOBBSrc;

    void setupUi(QWidget *ImageOBBDlg)
    {
        if (ImageOBBDlg->objectName().isEmpty())
            ImageOBBDlg->setObjectName(QStringLiteral("ImageOBBDlg"));
        ImageOBBDlg->resize(289, 120);
        pushButtonOBBOK = new QPushButton(ImageOBBDlg);
        pushButtonOBBOK->setObjectName(QStringLiteral("pushButtonOBBOK"));
        pushButtonOBBOK->setGeometry(QRect(210, 60, 61, 31));
        pushButtonPathOBBSrc = new QPushButton(ImageOBBDlg);
        pushButtonPathOBBSrc->setObjectName(QStringLiteral("pushButtonPathOBBSrc"));
        pushButtonPathOBBSrc->setGeometry(QRect(30, 30, 31, 28));
        lineEditImageOBBDes = new QLineEdit(ImageOBBDlg);
        lineEditImageOBBDes->setObjectName(QStringLiteral("lineEditImageOBBDes"));
        lineEditImageOBBDes->setGeometry(QRect(80, 70, 113, 22));
        pushButtonPathOBBDes = new QPushButton(ImageOBBDlg);
        pushButtonPathOBBDes->setObjectName(QStringLiteral("pushButtonPathOBBDes"));
        pushButtonPathOBBDes->setGeometry(QRect(30, 70, 31, 28));
        lineEditImageOBBSrc = new QLineEdit(ImageOBBDlg);
        lineEditImageOBBSrc->setObjectName(QStringLiteral("lineEditImageOBBSrc"));
        lineEditImageOBBSrc->setGeometry(QRect(80, 30, 113, 22));

        retranslateUi(ImageOBBDlg);

        QMetaObject::connectSlotsByName(ImageOBBDlg);
    } // setupUi

    void retranslateUi(QWidget *ImageOBBDlg)
    {
        ImageOBBDlg->setWindowTitle(QApplication::translate("ImageOBBDlg", "ImageOBBDlg", Q_NULLPTR));
        pushButtonOBBOK->setText(QApplication::translate("ImageOBBDlg", "OK", Q_NULLPTR));
        pushButtonPathOBBSrc->setText(QApplication::translate("ImageOBBDlg", "src", Q_NULLPTR));
        pushButtonPathOBBDes->setText(QApplication::translate("ImageOBBDlg", "des", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageOBBDlg: public Ui_ImageOBBDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEOBBDLG_H
