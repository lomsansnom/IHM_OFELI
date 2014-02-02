/********************************************************************************
** Form generated from reading UI file 'dialogaddnode.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDNODE_H
#define UI_DIALOGADDNODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAddNode
{
public:
    QLabel *label;
    QComboBox *parentList;
    QLabel *label_2;
    QComboBox *tagList;
    QPushButton *btnAddNode;
    QPushButton *btnCancel;
    QLabel *label_3;
    QLineEdit *textNode;

    void setupUi(QDialog *DialogAddNode)
    {
        if (DialogAddNode->objectName().isEmpty())
            DialogAddNode->setObjectName(QStringLiteral("DialogAddNode"));
        DialogAddNode->resize(332, 249);
        label = new QLabel(DialogAddNode);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 40, 50, 14));
        parentList = new QComboBox(DialogAddNode);
        parentList->setObjectName(QStringLiteral("parentList"));
        parentList->setGeometry(QRect(100, 40, 72, 31));
        label_2 = new QLabel(DialogAddNode);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 90, 50, 14));
        tagList = new QComboBox(DialogAddNode);
        tagList->setObjectName(QStringLiteral("tagList"));
        tagList->setGeometry(QRect(100, 90, 71, 31));
        tagList->setMaximumSize(QSize(72, 80));
        btnAddNode = new QPushButton(DialogAddNode);
        btnAddNode->setObjectName(QStringLiteral("btnAddNode"));
        btnAddNode->setGeometry(QRect(70, 200, 80, 31));
        btnCancel = new QPushButton(DialogAddNode);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(170, 200, 80, 31));
        label_3 = new QLabel(DialogAddNode);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 140, 50, 14));
        textNode = new QLineEdit(DialogAddNode);
        textNode->setObjectName(QStringLiteral("textNode"));
        textNode->setGeometry(QRect(100, 140, 171, 31));

        retranslateUi(DialogAddNode);

        QMetaObject::connectSlotsByName(DialogAddNode);
    } // setupUi

    void retranslateUi(QDialog *DialogAddNode)
    {
        DialogAddNode->setWindowTitle(QApplication::translate("DialogAddNode", "Dialog", 0));
        label->setText(QApplication::translate("DialogAddNode", "Parent", 0));
        label_2->setText(QApplication::translate("DialogAddNode", "Name", 0));
        btnAddNode->setText(QApplication::translate("DialogAddNode", "Add Node", 0));
        btnCancel->setText(QApplication::translate("DialogAddNode", "Cancel", 0));
        label_3->setText(QApplication::translate("DialogAddNode", "Text", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAddNode: public Ui_DialogAddNode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDNODE_H
