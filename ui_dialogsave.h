/********************************************************************************
** Form generated from reading UI file 'dialogsave.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSAVE_H
#define UI_DIALOGSAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogSave
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btnQuit;
    QPushButton *btnCancel;

    void setupUi(QDialog *DialogSave)
    {
        if (DialogSave->objectName().isEmpty())
            DialogSave->setObjectName(QStringLiteral("DialogSave"));
        DialogSave->resize(419, 178);
        label = new QLabel(DialogSave);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 211, 16));
        label_2 = new QLabel(DialogSave);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 371, 16));
        label_3 = new QLabel(DialogSave);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 90, 261, 16));
        btnQuit = new QPushButton(DialogSave);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));
        btnQuit->setGeometry(QRect(70, 130, 80, 31));
        btnCancel = new QPushButton(DialogSave);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(270, 130, 80, 31));

        retranslateUi(DialogSave);

        QMetaObject::connectSlotsByName(DialogSave);
    } // setupUi

    void retranslateUi(QDialog *DialogSave)
    {
        DialogSave->setWindowTitle(QApplication::translate("DialogSave", "Dialog", 0));
        label->setText(QApplication::translate("DialogSave", "You didn't save your XML file", 0));
        label_2->setText(QApplication::translate("DialogSave", "Click quit if you want to close the program and discard all changes", 0));
        label_3->setText(QApplication::translate("DialogSave", "or Cancel if you want to save your file.", 0));
        btnQuit->setText(QApplication::translate("DialogSave", "Quit", 0));
        btnCancel->setText(QApplication::translate("DialogSave", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSave: public Ui_DialogSave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSAVE_H
