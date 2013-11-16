#include "mainwindow.h"
#include "dialogexec.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QComboBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tagList = new QStringList();
    tagList->append("value");
    tagList->append("name");

    this->ui->formLayout->setMargin(20);
    this->ui->buttonAddParam->hide();
    this->ui->buttonValidate->hide();
    //openDatas("default.dat");
    QObject::connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(selectFile()));
    QObject::connect(this->ui->actionSave_File, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(this->ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(this->ui->buttonExec, SIGNAL(clicked()), this, SLOT(executable()));
    QObject::connect(this->ui->buttonAddParam, SIGNAL(clicked()), this, SLOT(addParam()));
    QObject::connect(this->ui->buttonValidate, SIGNAL(clicked()), this, SLOT(validate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::openDatas(QString filename)
{
    QStandardItemModel *model = new QStandardItemModel;

    QFile fichier(filename);
    QDomDocument *doc = new QDomDocument("docXml");
    QDomElement elem;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();

    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    doc->setContent(&fichier);
    this->currentDocument = doc;
    fichier.close();

    elem = doc->documentElement();

    for(int i = 0; i < 10; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }

    buildTree(elem, model, new QStandardItem(elem.tagName()), nodesLength, 0, currentChild, -1);

    this->model = model;
    this->ui->treeView->setModel(model);

    QObject::connect(this->ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));
    return 0;
}

void MainWindow::buildTree(QDomNode doc, QStandardItemModel* model, QStandardItem *item, QList<int> *nbChildren, int childNumber, QList<int> *currentChild, int currentLevel)
{
    //check if doc is not empty
    if(!doc.isNull())
    {
        QStandardItem *itemUpdated = item;
        //append root to model
        if(currentLevel == -1)
        {
            QList<QStandardItem*> list;
            list.append(item);
            list.append(new QStandardItem(""));
            model->appendRow(list);
        }
        //append everything but root to model
        else
        {
            //get the parent to the node we want to add to the model
            for(int i = 0; i < currentLevel; i++)
            {
                itemUpdated = itemUpdated->child(currentChild->at(i));
            }
            //append the node
            QList<QStandardItem*> list;
            cout << doc.attributes().length() << endl;
            if(doc.attributes().length()+2 > model->columnCount())
            {
                for(int i = 0; i <= doc.attributes().length()-model->columnCount(); i++)
                {
                    list.append(new QStandardItem(""));
                }
                model->appendColumn(list);
                list.clear();
            }

            list.append(new QStandardItem(doc.toElement().tagName()));
            if(!doc.childNodes().item(0).isElement() && doc.hasChildNodes())
            {
                list.append(new QStandardItem(doc.toElement().text()));
            }
            else
            {
                list.append(new QStandardItem(""));
            }
            for(int i = 0; i < doc.attributes().length(); i++)
            {
                list.append(new QStandardItem(doc.attributes().item(i).toAttr().name() + " : " + doc.attributes().item(i).toAttr().value()));
            }
            itemUpdated->appendRow(list);
        }
        //if the node has at least one child get all the children and add them to the model
        if(!doc.childNodes().isEmpty() && doc.firstChild().toElement().tagName() != "")
        {
            //get the children
            QDomNodeList nodeList = doc.childNodes();
            //update the level and store the number of children
            currentLevel++;
            (*nbChildren)[currentLevel] = nodeList.length();

            //for each child add the chils and its children to the model
            for(int i = 0; i < (*nbChildren)[currentLevel]; i++)
            {
                (*currentChild)[currentLevel] = i;
                buildTree(nodeList.at(i), model, item, nbChildren, i, currentChild, currentLevel);
            }
        }
        //if the current node doesn't have children the previous level need to be updated
        else
        {
            //the level which must be updated is the first one which is not equal to the
            //number of children of its level (if we start by the last level scanned)
            int ii = 1;
            if(currentLevel >= 1 && childNumber == (*nbChildren)[currentLevel] - 1)
            {
                while((*currentChild)[currentLevel-ii] == (*nbChildren)[currentLevel-ii] && ii <= currentLevel)
                {
                    ii++;
                }
                //if currentLevel-ii is < 0, it means that all the children of the previous levels have been scanned
                if(ii <= currentLevel)
                {
                    (*currentChild)[currentLevel-ii] += 1;
                }
            }
        }
    }
}

void MainWindow::buildTreeColumn(QStandardItem *item)
{
    QList<QStandardItem*> list;
    list.append(new QStandardItem("test"));
    item->appendColumn(list);
}

//Slots

void MainWindow::selectFile()
{
    QFileDialog *openWindow = new QFileDialog(this);
    QStringList filenameList;

    openWindow->setFileMode(QFileDialog::ExistingFiles);
    openWindow->show();

    if(openWindow->exec())
    {
        filenameList = openWindow->selectedFiles();
        cout << "ok" << endl;
        if(!filenameList.isEmpty())
        {
            filename = filenameList[0];
            openDatas(filename);
        }
    }
}

void MainWindow::showDetails(QModelIndex index)
{
    QDomNamedNodeMap listAttr = currentDocument->elementsByTagName(nodeName).item(0).attributes();

    nodeName = this->ui->treeView->model()->data(index).toString();

    this->ui->buttonAddParam->show();
    this->ui->buttonValidate->show();

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
        QComboBox *comboBoxTag = new QComboBox();
        comboBoxTag->addItem("Value");
        comboBoxTag->setDisabled(true);
        list.push_front(new QLineEdit(currentDocument->elementsByTagName(nodeName).item(0).toElement().text()));
        //list.push_front(new QLabel(QString("Value")));
        list.push_front(comboBoxTag);
        horizontalLayout->addWidget(list[0]);
        horizontalLayout->addWidget(list[1]);
        this->ui->formLayout->addRow(horizontalLayout);
    }

    QComboBox *comboBox;
    for(int i = 0; i < listAttr.length(); i++)
    {
        comboBox = new QComboBox();
        comboBox->addItems(*tagList);
        comboBox->setCurrentText(listAttr.item(i).toAttr().name());
        horizontalLayout = new QHBoxLayout();
        list.push_front(new QLineEdit(listAttr.item(i).toAttr().value()));
      //  list.push_front(new QLabel(listAttr.item(i).toAttr().name()));
        list.push_front(comboBox);
        horizontalLayout->addWidget(list[0]);
        horizontalLayout->addWidget(list[1]);
        this->ui->formLayout->addRow(horizontalLayout);
    }
}

void MainWindow::addParam()
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    list.push_front(new QLineEdit("Value"));
    list.push_front(new QLineEdit("Name")); //to replace by a dropdown list containing all possibles values
    horizontalLayout->addWidget(list[0]);
    horizontalLayout->addWidget(list[1]);
    this->ui->formLayout->addRow(horizontalLayout);
}

void MainWindow::validate()
{
    QString attrName, attrValue;
    //cout << list.length() << endl;
    for(int i = 0; i < list.length(); i += 2)
    {
        attrName = ((QComboBox*)list[i])->currentText();
        attrValue = ((QLineEdit*)list[i+1])->text();
        cout << "ook" << endl;
        currentDocument->elementsByTagName(nodeName).item(0).toElement().setAttribute(attrName, attrValue);
        cout << "bug" << endl;
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

void MainWindow::executable()
{
    DialogExec *windowExec = new DialogExec(this, filename);
    windowExec->show();
}
