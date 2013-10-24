/********************************************************************************
** Form generated from reading UI file 'dialogexec.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGEXEC_H
#define UI_DIALOGEXEC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogExec
{
public:
    QPushButton *buttonExecute;
    QPushButton *buttonCancel;
    QLabel *label;
    QLineEdit *pathExec;
    QPushButton *buttonBrowse;
    QLabel *label_2;
    QLineEdit *nameExec;
    QLineEdit *pathDat;
    QLabel *label_3;
    QPushButton *buttonBrowseDat;

    void setupUi(QDialog *DialogExec)
    {
        if (DialogExec->objectName().isEmpty())
            DialogExec->setObjectName(QStringLiteral("DialogExec"));
        DialogExec->resize(400, 288);
        buttonExecute = new QPushButton(DialogExec);
        buttonExecute->setObjectName(QStringLiteral("buttonExecute"));
        buttonExecute->setGeometry(QRect(60, 250, 80, 31));
        buttonCancel = new QPushButton(DialogExec);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setGeometry(QRect(210, 250, 80, 31));
        label = new QLabel(DialogExec);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 321, 31));
        pathExec = new QLineEdit(DialogExec);
        pathExec->setObjectName(QStringLiteral("pathExec"));
        pathExec->setEnabled(false);
        pathExec->setGeometry(QRect(10, 51, 261, 31));
        buttonBrowse = new QPushButton(DialogExec);
        buttonBrowse->setObjectName(QStringLiteral("buttonBrowse"));
        buttonBrowse->setGeometry(QRect(300, 51, 80, 31));
        label_2 = new QLabel(DialogExec);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 281, 31));
        nameExec = new QLineEdit(DialogExec);
        nameExec->setObjectName(QStringLiteral("nameExec"));
        nameExec->setEnabled(true);
        nameExec->setGeometry(QRect(10, 120, 261, 31));
        pathDat = new QLineEdit(DialogExec);
        pathDat->setObjectName(QStringLiteral("pathDat"));
        pathDat->setEnabled(false);
        pathDat->setGeometry(QRect(10, 190, 261, 31));
        label_3 = new QLabel(DialogExec);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(10, 160, 281, 31));
        buttonBrowseDat = new QPushButton(DialogExec);
        buttonBrowseDat->setObjectName(QStringLiteral("buttonBrowseDat"));
        buttonBrowseDat->setGeometry(QRect(300, 190, 80, 31));

        retranslateUi(DialogExec);

        QMetaObject::connectSlotsByName(DialogExec);
    } // setupUi

    void retranslateUi(QDialog *DialogExec)
    {
        DialogExec->setWindowTitle(QApplication::translate("DialogExec", "Dialog", 0));
        buttonExecute->setText(QApplication::translate("DialogExec", "Execute", 0));
        buttonCancel->setText(QApplication::translate("DialogExec", "Cancel", 0));
        label->setText(QApplication::translate("DialogExec", "Select the folder of the executable :", 0));
        buttonBrowse->setText(QApplication::translate("DialogExec", "Browse...", 0));
        label_2->setText(QApplication::translate("DialogExec", "Name of the executable :", 0));
        pathDat->setText(QString());
        label_3->setText(QApplication::translate("DialogExec", "Select the path to the .dat file : ", 0));
        buttonBrowseDat->setText(QApplication::translate("DialogExec", "Browse...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogExec: public Ui_DialogExec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGEXEC_H
