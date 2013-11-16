#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QtXml>
#include <QTreeView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        int openDatas(QString fileName);
        void buildTree(QDomNode doc, QStandardItemModel* model, QStandardItem *item, QList<int> *nbChildren, int childNumber, QList<int> *currentChild, int currentLevel);

    public slots:
        void selectFile();
        void showDetails(QModelIndex index);
        void saveFile();
        void executable();
        void addParam();
        void validate();

    private:
        Ui::MainWindow *ui;
        QString filename;
        QString nodeName;
        QStringList* tagList;
        QDomDocument *currentDocument;
        QStandardItemModel *model;
        QList<QWidget*> list;
};

#endif // MAINWINDOW_H
