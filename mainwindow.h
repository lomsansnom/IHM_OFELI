#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QtXml>
#include <QTreeView>

#include "qtreeviewofeli.h"

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
        //void buildTree(QDomNode doc, QStandardItemModel* model);

    public slots:
        void showDetails(QModelIndex index);

    private:
        Ui::MainWindow *ui;
        QDomDocument *currentDocument;
        QList<QWidget*> list;
};

#endif // MAINWINDOW_H
