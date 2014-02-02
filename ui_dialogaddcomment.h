/********************************************************************************
** Form generated from reading UI file 'dialogaddcomment.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDCOMMENT_H
#define UI_DIALOGADDCOMMENT_H

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

class Ui_DialogAddComment
{
public:
    QLabel *label;
    QLineEdit *commentText;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *DialogAddComment)
    {
        if (DialogAddComment->objectName().isEmpty())
            DialogAddComment->setObjectName(QStringLiteral("DialogAddComment"));
        DialogAddComment->resize(400, 193);
        label = new QLabel(DialogAddComment);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 50, 101, 21));
        commentText = new QLineEdit(DialogAddComment);
        commentText->setObjectName(QStringLiteral("commentText"));
        commentText->setGeometry(QRect(150, 50, 201, 22));
        btnOk = new QPushButton(DialogAddComment);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        btnOk->setGeometry(QRect(70, 130, 80, 31));
        btnCancel = new QPushButton(DialogAddComment);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(240, 130, 80, 31));

        retranslateUi(DialogAddComment);

        QMetaObject::connectSlotsByName(DialogAddComment);
    } // setupUi

    void retranslateUi(QDialog *DialogAddComment)
    {
        DialogAddComment->setWindowTitle(QApplication::translate("DialogAddComment", "Dialog", 0));
        label->setText(QApplication::translate("DialogAddComment", "Your comment : ", 0));
        btnOk->setText(QApplication::translate("DialogAddComment", "Ok", 0));
        btnCancel->setText(QApplication::translate("DialogAddComment", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAddComment: public Ui_DialogAddComment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDCOMMENT_H
