#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->verticalLayout->setMargin(20);
    QObject::connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(selectFile()));
    QObject::connect(this->ui->actionSave_File, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
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


    /*cout << elem.tagName().toStdString() << endl;
    model->appendRow(new QStandardItem(elem.tagName()));
    buildTree(noeud, model);*/


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
    }

    //add all tags to the tree as rows
    model->appendRow(tagList);
    for(int i = 0; i < tagList.length(); i++)
    {
        tagList[i]->appendRows(subTagList);
    }
    for(int i = 0; i < subTagList.length(); i++)
    {
        subTagList[i]->appendRows(subSubTagList[i]);
    }
    this->model = model;
    this->ui->treeView->setModel(model);
    QObject::connect(this->ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));

    return 0;
}

/*void MainWindow::buildTree(QDomNode doc, QStandardItemModel* model)
{
    if(!doc.isNull())
    {
        if(doc.toElement().tagName() != QString(""))
        {
            model->appendRow(new QStandardItem(doc.toElement().tagName()));
        }
        buildTree(doc.firstChild(), model);
        buildTree(doc.nextSibling(), model);
    }
}*/

//Slots

void MainWindow::selectFile()
{
    QFileDialog *openWindow = new QFileDialog(this);

    openWindow->setFileMode(QFileDialog::ExistingFiles);
    openWindow->show();

    if(openWindow->exec())
    {
        filename = openWindow->selectedFiles();
        cout << "ok" << endl;
        if(!filename.isEmpty())
        {
            openDatas(filename[0]);
        }
    }
}

void MainWindow::showDetails(QModelIndex index)
{
    QString nodeName = this->ui->treeView->model()->data(index).toString();
    QDomNamedNodeMap listAttr = currentDocument->elementsByTagName(nodeName).item(0).attributes();

    this->ui->label->setText(QString("Edit ") + nodeName);

    if(!list.empty())
    {
        for(int i = 0; i < list.length(); i++)
        {
            delete list[i];
        }
        list.clear();
    }

    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    if(!currentDocument->elementsByTagName(nodeName).item(0).childNodes().item(0).isElement() && currentDocument->elementsByTagName(nodeName).item(0).hasChildNodes())
    {
        horizontalLayout = new QHBoxLayout();
        list.push_front(new QLineEdit(currentDocument->elementsByTagName(nodeName).item(0).toElement().text()));
        list.push_front(new QLabel(QString("Value")));
        horizontalLayout->addWidget(list[0]);
        horizontalLayout->addWidget(list[1]);
        this->ui->verticalLayout->addLayout(horizontalLayout);
    }

    for(int i = 0; i < listAttr.length(); i++)
    {
        horizontalLayout = new QHBoxLayout();
        list.push_front(new QLineEdit(listAttr.item(i).toAttr().value()));
        list.push_front(new QLabel(listAttr.item(i).toAttr().name()));
        horizontalLayout->addWidget(list[0]);
        horizontalLayout->addWidget(list[1]);
        this->ui->verticalLayout->addLayout(horizontalLayout);
        this->ui->verticalLayout->setAlignment(horizontalLayout, Qt::AlignTop);
    }

    if(listAttr.isEmpty() && !currentDocument->elementsByTagName(nodeName).item(0).childNodes().item(0).isElement())
    {
       this->ui->verticalLayout->setAlignment(horizontalLayout, Qt::AlignTop);
    }
}

void MainWindow::saveFile()
{
    QFileDialog *saveWindow = new QFileDialog(this);
    FILE *saveFile;
    QTextStream *fileStream;
    QByteArray filenameFopen;

    saveWindow->setAcceptMode(QFileDialog::AcceptSave);
    saveWindow->setFileMode(QFileDialog::AnyFile);
    saveWindow->show();

    if(saveWindow->exec())
    {
        //convert Qstring to char* for the fopen function
        filenameFopen = saveWindow->selectedFiles()[0].toLocal8Bit();
        saveFile = fopen(filenameFopen.data(), "w");

        if(saveFile == NULL)
        {
            cout << "Erreur" << endl;
        }
        else
        {
            fileStream = new QTextStream(saveFile,QIODevice::ReadWrite);
            currentDocument->save(*fileStream, 4);
            fclose(saveFile);
        }
    }

}
