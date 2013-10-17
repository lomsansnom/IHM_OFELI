#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::openDatas(QString filename)
{
    QStandardItemModel *model = new QStandardItemModel;

    QList<QStandardItem*> tagList;
    QList<QStandardItem*> subTagList;
    QList< QList<QStandardItem*> > subSubTagList;
    QList<QStandardItem*> list;

    QFile fichier(filename);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    QDomDocument *doc = new QDomDocument("docXml");
    doc->setContent(&fichier);
    this->currentDocument = doc;
    fichier.close();
    QDomElement elem = doc->documentElement();
    QDomNode noeud = elem.firstChild();

    int i = 0;
    while(!elem.isNull())
    {
        tagList.append(new QStandardItem(elem.tagName()));
        while(!noeud.isNull())
        {
            subTagList.append(new QStandardItem(noeud.toElement().tagName()));
            QDomNode noeudd = noeud.firstChild();
            list.clear();
            while(!noeudd.isNull())
            {
                list.append(new QStandardItem(noeudd.toElement().tagName())); //+ " : " + noeudd.toElement().text();
                noeudd = noeudd.nextSibling();
            }
            subSubTagList.append(list);
            noeud = noeud.nextSibling();
        }
        elem = elem.nextSiblingElement();
        noeud = elem.firstChild();
        i++;
    }
    cout << "length : " << subSubTagList.length() << " => " << subSubTagList[1][2]->text().toStdString() << endl;
    model->appendRow(tagList);
    for(int i = 0; i < tagList.length(); i++)
    {
        for(int ii = 0; ii < subTagList.length(); ii++)
        {
            tagList[i]->appendRow(subTagList[ii]);
        }
    }
    for(int i = 0; i < subTagList.length(); i++)
    {
        for(int ii = 0; ii < subSubTagList[i].length(); ii++)
        {
            subTagList[i]->appendRow(subSubTagList[i][ii]);
        }
    }

    this->ui->treeView->setModel(model);
    QObject::connect(this->ui->treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(showDetails(QModelIndex)));
    return 0;
}

//Slots
//Works for a document with 3 level(or less)
void MainWindow::showDetails(QModelIndex index)
{
    //if the selection is the root(the first level)
    if(index.parent().column() == -1 && index.parent().row() == -1)
    {
        this->ui->verticalLayout_2->addWidget(new QPushButton(this->currentDocument->documentElement().toElement().tagName()));
    }
    //else if the selection is in the second level
    else if(index.parent().column() == 0 && index.parent().parent().column() == -1)
    {
        QDomNode noeud = this->currentDocument->documentElement().firstChild();
        int i = index.row();
        //go to the next row while this is not the good row
        while(i != 0)
        {
            noeud = noeud.nextSibling();
            i--;
        }
        this->ui->verticalLayout_2->addWidget(new QPushButton(noeud.toElement().tagName()));
    }
    //else if the selection is in the third level
    else if(index.parent().column() == 0 && index.parent().parent().column() == 0)
    {
        QDomNode noeud = this->currentDocument->documentElement().firstChild();
        int i = index.parent().row();
        //go to the next row while this is not the good row(in the second level)
        while(i != 0)
        {
            noeud = noeud.nextSiblingElement();
            i--;
        }
        noeud = noeud.firstChild();
        i = index.row();
        //go to the next row while this is not the good row(in the third level)
        while(i != 0)
        {
            noeud = noeud.nextSibling();
            i--;
        }
        this->ui->verticalLayout_2->addWidget(new QPushButton(noeud.toElement().tagName()));
    }
}
