/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionSave_File;
    QAction *actionAdd_node;
    QAction *actionDelete_selected_node;
    QAction *actionModifySelectedNode;
    QAction *actionSave;
    QAction *actionRecent_files;
    QAction *actionAdd_Comment;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAide;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen->setEnabled(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave_File = new QAction(MainWindow);
        actionSave_File->setObjectName(QStringLiteral("actionSave_File"));
        actionAdd_node = new QAction(MainWindow);
        actionAdd_node->setObjectName(QStringLiteral("actionAdd_node"));
        actionDelete_selected_node = new QAction(MainWindow);
        actionDelete_selected_node->setObjectName(QStringLiteral("actionDelete_selected_node"));
        actionModifySelectedNode = new QAction(MainWindow);
        actionModifySelectedNode->setObjectName(QStringLiteral("actionModifySelectedNode"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionRecent_files = new QAction(MainWindow);
        actionRecent_files->setObjectName(QStringLiteral("actionRecent_files"));
        actionAdd_Comment = new QAction(MainWindow);
        actionAdd_Comment->setObjectName(QStringLiteral("actionAdd_Comment"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 19));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QStringLiteral("menuEdition"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionOpen);
        menuFichier->addAction(actionRecent_files);
        menuFichier->addAction(actionSave);
        menuFichier->addAction(actionSave_File);
        menuFichier->addSeparator();
        menuFichier->addAction(actionExit);
        menuAide->addAction(actionAbout);
        mainToolBar->addAction(actionAdd_node);
        mainToolBar->addAction(actionAdd_Comment);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionModifySelectedNode);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDelete_selected_node);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionSave_File->setText(QApplication::translate("MainWindow", "Save As", 0));
#ifndef QT_NO_TOOLTIP
        actionSave_File->setToolTip(QApplication::translate("MainWindow", "Save As", 0));
#endif // QT_NO_TOOLTIP
        actionAdd_node->setText(QApplication::translate("MainWindow", "Add node", 0));
        actionDelete_selected_node->setText(QApplication::translate("MainWindow", "Delete selected node", 0));
        actionModifySelectedNode->setText(QApplication::translate("MainWindow", "Modify selected node", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionRecent_files->setText(QApplication::translate("MainWindow", "Recent files", 0));
        actionAdd_Comment->setText(QApplication::translate("MainWindow", "Add Comment after selection", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdition->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuAide->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
