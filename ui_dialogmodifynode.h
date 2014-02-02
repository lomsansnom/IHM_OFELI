/********************************************************************************
** Form generated from reading UI file 'dialogmodifynode.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMODIFYNODE_H
#define UI_DIALOGMODIFYNODE_H

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

class Ui_DialogModifyNode
{
public:
    QLineEdit *newName;
    QLabel *label;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *DialogModifyNode)
    {
        if (DialogModifyNode->objectName().isEmpty())
            DialogModifyNode->setObjectName(QStringLiteral("DialogModifyNode"));
        DialogModifyNode->resize(259, 139);
        newName = new QLineEdit(DialogModifyNode);
        newName->setObjectName(QStringLiteral("newName"));
        newName->setGeometry(QRect(110, 41, 113, 31));
        label = new QLabel(DialogModifyNode);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 40, 81, 16));
        btnOk = new QPushButton(DialogModifyNode);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        btnOk->setGeometry(QRect(40, 91, 80, 31));
        btnCancel = new QPushButton(DialogModifyNode);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(150, 90, 80, 31));

        retranslateUi(DialogModifyNode);

        QMetaObject::connectSlotsByName(DialogModifyNode);
    } // setupUi

    void retranslateUi(QDialog *DialogModifyNode)
    {
        DialogModifyNode->setWindowTitle(QApplication::translate("DialogModifyNode", "Dialog", 0));
        label->setText(QApplication::translate("DialogModifyNode", "New name", 0));
        btnOk->setText(QApplication::translate("DialogModifyNode", "Ok", 0));
        btnCancel->setText(QApplication::translate("DialogModifyNode", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogModifyNode: public Ui_DialogModifyNode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMODIFYNODE_H
