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
        void heightXML(QDomNode doc, int *height);
        void nbAttributesMax(QDomNode doc, int *nbAttributes);
        void getTagList(QDomNode doc, QStringList *tagList);
        void addNode(QString nameParent, QString nameNode, QString textNode);
        void modifyNode(QString nodeSelected, QString newName);
        void clearFormLayout();

    public slots:
        void selectFile();
        void showDetails(QModelIndex index);
        void saveFile();
        void executable();
        void addParam();
        void validate();
        void openWindowAddNode();
        void deleteSelectedNode();
        void openWindowModifyNode();

    private:
        Ui::MainWindow *ui;
        QString filename;
        QString nodeName;
        QString root;
        QModelIndex currentIndex;
        QDomDocument *currentDocument;
        QStandardItemModel *model;
        QList<QWidget*> list;
        QList<QLayout*> listLayout;
};

#endif // MAINWINDOW_H
