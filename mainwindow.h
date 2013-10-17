#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QtXml>

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

    public slots:
        void showDetails(QModelIndex index);

    private:
        Ui::MainWindow *ui;
        QDomDocument *currentDocument;
};

#endif // MAINWINDOW_H
