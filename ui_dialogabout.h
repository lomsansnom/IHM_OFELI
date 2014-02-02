/********************************************************************************
** Form generated from reading UI file 'dialogabout.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGABOUT_H
#define UI_DIALOGABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogAbout
{
public:
    QTextEdit *textAbout;
    QLabel *logo;
    QPushButton *btnClose;

    void setupUi(QDialog *DialogAbout)
    {
        if (DialogAbout->objectName().isEmpty())
            DialogAbout->setObjectName(QStringLiteral("DialogAbout"));
        DialogAbout->resize(456, 469);
        textAbout = new QTextEdit(DialogAbout);
        textAbout->setObjectName(QStringLiteral("textAbout"));
        textAbout->setGeometry(QRect(20, 150, 411, 271));
        logo = new QLabel(DialogAbout);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(60, 20, 50, 14));
        btnClose = new QPushButton(DialogAbout);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(180, 430, 80, 31));

        retranslateUi(DialogAbout);

        QMetaObject::connectSlotsByName(DialogAbout);
    } // setupUi

    void retranslateUi(QDialog *DialogAbout)
    {
        DialogAbout->setWindowTitle(QApplication::translate("DialogAbout", "Dialog", 0));
        logo->setText(QApplication::translate("DialogAbout", "TextLabel", 0));
        btnClose->setText(QApplication::translate("DialogAbout", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAbout: public Ui_DialogAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGABOUT_H
