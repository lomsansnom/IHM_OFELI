#include "mainwindow.h"
#include "dialogexec.h"
#include "dialogaddnode.h"
#include "dialogmodifynode.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QComboBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->formLayout->setContentsMargins(5,30,5,10);
    ui->buttonAddParam->hide();
    ui->buttonValidate->hide();

    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(selectFile()));
    QObject::connect(ui->actionSave_File, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(ui->buttonExec, SIGNAL(clicked()), this, SLOT(executable()));
    QObject::connect(ui->buttonAddParam, SIGNAL(clicked()), this, SLOT(addParam()));
    QObject::connect(ui->buttonValidate, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(ui->actionAdd_node, SIGNAL(triggered()), this, SLOT(openWindowAddNode()));
    QObject::connect(ui->actionDelete_selected_node, SIGNAL(triggered()), this, SLOT(deleteSelectedNode()));
    QObject::connect(ui->actionModifySelectedNode, SIGNAL(triggered()), this, SLOT(openWindowModifyNode()));
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
    int height = 0;

    //open the selected file and get the xml document in doc
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    doc->setContent(&fichier);
    currentDocument = doc;
    fichier.close();

    //get the first element of the document
    elem = doc->documentElement();
    root = elem.tagName();
    //get the height for the document and prepare the parameters to build the tree
    heightXML(elem, &height);
    for(int i = 0; i < height-1; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }

    //build the model and use it to be displayed using a QTreeView
    buildTree(elem, model, new QStandardItem(elem.tagName()), nodesLength, 0, currentChild, -1);

    this->model = model;
    ui->treeView->setModel(model);

    QObject::connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));
    return 0;
}

void MainWindow::buildTree(QDomNode doc, QStandardItemModel* model, QStandardItem *item, QList<int> *nbChildren, int childNumber, QList<int> *currentChild, int currentLevel)
{
    //check if doc is not empty
    if(!doc.isNull())
    {
        QStandardItem *itemUpdated = item;
        int nbAttributes = 0;
        nbAttributesMax(doc, &nbAttributes);
        //append root to model
        if(currentLevel == -1)
        {
            QList<QStandardItem*> list;
            list.append(item);
            for(int i = 0; i < nbAttributes; i++)
            {
                list.append(new QStandardItem(""));
            }
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

            QList<QStandardItem*> list;
            //add the number of column needed to the model so we are able to add new column to the children
            if(doc.attributes().length()+2 > model->columnCount())
            {
                for(int i = 0; i <= doc.attributes().length()-model->columnCount(); i++)
                {
                    list.append(new QStandardItem(""));
                }
                model->appendColumn(list);
                list.clear();
            }

            //add the tag's name in the list
            list.append(new QStandardItem(doc.toElement().tagName()));

            //if the node doesn't have any children, it means there is a value inside the node, we had this value in the list here
            if(!doc.childNodes().item(0).isElement() && doc.hasChildNodes())
            {
                list.append(new QStandardItem(doc.toElement().text()));
            }
            //if the node have at least one child, there is no value inside the node so we just had an empty string to the list
            else
            {
                list.append(new QStandardItem(""));
            }
            //add all the attributes to the list
            for(int i = 0; i < doc.attributes().length(); i++)
            {
                list.append(new QStandardItem(doc.attributes().item(i).toAttr().name() + " : " + doc.attributes().item(i).toAttr().value()));
            }

            //append the list
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

void MainWindow::heightXML(QDomNode doc, int *height)
{
    if(!doc.isNull())
    {
        int heightCurrentNode = 0;
        QDomNode docParent = doc;
        while(!docParent.parentNode().isNull())
        {
            docParent = docParent.parentNode();
            heightCurrentNode++;
        }
        if(heightCurrentNode > *height)
        {
            *height = heightCurrentNode;
        }
        if(!doc.childNodes().isEmpty() && doc.firstChild().toElement().tagName() != "")
        {
            QDomNodeList nodeList = doc.childNodes();

            for(int i = 0; i < nodeList.length(); i++)
            {
                heightXML(nodeList.at(i), height);
            }
        }
    }
}

void MainWindow::nbAttributesMax(QDomNode doc, int *nbAttributes)
{
    if(!doc.isNull())
    {
        if(doc.attributes().length() > *nbAttributes)
        {
            *nbAttributes = doc.attributes().length();
        }

        if(!doc.childNodes().isEmpty() && doc.firstChild().toElement().tagName() != "")
        {
            QDomNodeList nodeList = doc.childNodes();

            for(int i = 0; i < nodeList.length(); i++)
            {
                nbAttributesMax(nodeList.at(i), nbAttributes);
            }
        }
    }
}

void MainWindow::getTagList(QDomNode doc, QStringList *tagList)
{
    if(!doc.isNull())
    {
        tagList->append(doc.toElement().tagName());

        if(!doc.childNodes().isEmpty() && doc.firstChild().toElement().tagName() != "")
        {
            QDomNodeList nodeList = doc.childNodes();

            for(int i = 0; i < nodeList.length(); i++)
            {
                getTagList(nodeList.at(i), tagList);
            }
        }
    }
}

void MainWindow::addNode(QString nameParent, QString nameNode, QString textNode)
{
    QStandardItemModel *modelUpdated = new QStandardItemModel();
    int height = 0;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();

    currentDocument->elementsByTagName(nameParent).item(0).appendChild((new QDomDocument())->createElement(nameNode));
    currentDocument->elementsByTagName(nameParent).item(0).lastChild().appendChild((new QDomDocument())->createTextNode(textNode));

    heightXML(currentDocument->documentElement(), &height);
    for(int i = 0; i < height-1; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }

    buildTree(currentDocument->documentElement(), modelUpdated, new QStandardItem(currentDocument->documentElement().tagName()), nodesLength, 0, currentChild, -1);
    model = modelUpdated;
    ui->treeView->setModel(model);
}

void MainWindow::modifyNode(QString nodeSelected, QString newName)
{
    QStandardItemModel *modelUpdated = new QStandardItemModel();
    int height = 0;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();

    currentDocument->elementsByTagName(nodeSelected).item(0).toElement().setTagName(newName);

    heightXML(currentDocument->documentElement(), &height);
    for(int i = 0; i < height-1; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }

    buildTree(currentDocument->documentElement(), modelUpdated, new QStandardItem(currentDocument->documentElement().tagName()), nodesLength, 0, currentChild, -1);
    model = modelUpdated;
    ui->treeView->setModel(model);
}

void MainWindow:: clearFormLayout()
{
    if(!list.empty())
    {
        for(int i = 0; i < list.length(); i++)
        {
            delete list[i];
        }
        list.clear();
        if(!listLayout.isEmpty())
        {
            for(int i = 0; i < listLayout.length(); i++)
            {
                delete listLayout[i];
            }
            listLayout.clear();
        }
    }
    ui->label->setText("");
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
        if(!filenameList.isEmpty())
        {
            filename = filenameList[0];
            openDatas(filename);
        }
    }
}

void MainWindow::showDetails(QModelIndex index)
{
    QStringList listAttr;
    index = index.sibling(index.row(), 0);

    nodeName = model->itemFromIndex(index)->text();
    currentIndex = index;
    ui->buttonAddParam->show();
    ui->buttonValidate->show();

    //Clear formLayout to remove the parameter related to the last element selected
    clearFormLayout();

    ui->label->setText("Edit " + nodeName);

    if(nodeName.compare(root) != 0)
    {
        //Store the list of attribute for the selected element
        for(int i = 1; i < model->itemFromIndex(index)->parent()->columnCount(); i++)
        {
            index = index.sibling(index.row(), i);
            if(i == 1)
            {
                listAttr.append("TextNode");
                listAttr.append(model->itemFromIndex(index)->text());
            }
            else
            {
                if(model->itemFromIndex(index)->text() != "")
                {
                    listAttr.append(model->itemFromIndex(index)->text().section(":",0,0));
                    listAttr.append(model->itemFromIndex(index)->text().section(":",1));
                }
            }
        }

        //Add all attributes in formLayout to display them and store them so we'll be able to remove them from formLayout later
        //The QHBoxLayout is used to display the name and the value of the attribute on the same line
        QHBoxLayout *horizontalLayout;
        //if(!currentDocument->elementsByTagName(nodeName).item(0).childNodes().item(0).isElement() && currentDocument->elementsByTagName(nodeName).item(0).hasChildNodes())
        if(listAttr[1] != "")
        {
            horizontalLayout = new QHBoxLayout();
            list.push_front(new QLineEdit(listAttr[1]));
            list.push_front(new QLineEdit(listAttr[0]));
            horizontalLayout->addWidget(list[0]);
            horizontalLayout->addWidget(list[1]);
            listLayout.push_front(horizontalLayout);
            ui->formLayout->addRow(horizontalLayout);
        }


        for(int i = 2; i < listAttr.length(); i+=2)
        {
            horizontalLayout = new QHBoxLayout();
            list.push_front(new QLineEdit(listAttr[i+1]));
            list.push_front(new QLineEdit(listAttr[i]));
            horizontalLayout->addWidget(list[0]);
            horizontalLayout->addWidget(list[1]);
            listLayout.push_front(horizontalLayout);
            ui->formLayout->addRow(horizontalLayout);
        }
    }
}

void MainWindow::addParam()
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    list.push_front(new QLineEdit("Value"));
    list.push_front(new QLineEdit("Name"));
    horizontalLayout->addWidget(list[0]);
    horizontalLayout->addWidget(list[1]);
    ui->formLayout->addRow(horizontalLayout);
}

void MainWindow::validate()
{
    QString attrName, attrValue;
    QStandardItemModel *modelUpdated = new QStandardItemModel;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();
    QStringList *listAttr = new QStringList();
    int height = 0;
    int ii = 0;
    QList<int> *indexToDelete = new QList<int>();
    bool indexToDeleteFound = false;

    for(int i = 0; i < currentDocument->elementsByTagName(nodeName).item(0).attributes().length(); i++)
    {
        listAttr->append(currentDocument->elementsByTagName(nodeName).item(0).attributes().item(i).toAttr().name().trimmed());
    }

    //If the name of existing attributes are modified, first we need to delete them from the document and add them with their new name
    //The firsts elements in list are the ones which were added so we need to start at the first "old attribute"
    ii = (list.length()/2-listAttr->length())*2;

    //get the index of existing attributes if their name is modified
    for(int i = 0; i < listAttr->length(); i++)
    {
        while(ii < list.length() && !indexToDeleteFound)
        {
            if(((QLineEdit*)list[ii])->text().trimmed() == listAttr->at(i))
            {
                indexToDeleteFound = true;
            }
            ii += 2;
        }
        if(!indexToDeleteFound)
        {
            indexToDelete->append(i);
        }
        ii = (list.length()/2-listAttr->length())*2;;
        indexToDeleteFound = false;
    }
    //delete the attributes if their name is modified
    for(int i = 0; i < indexToDelete->length(); i++)
    {
        currentDocument->elementsByTagName(nodeName).item(0).toElement().removeAttribute(listAttr->at(indexToDelete->at(i)));
    }

    //add the attributes to the document
    for(int i = 0; i < list.length(); i += 2)
    {
        attrName = ((QLineEdit*)list[i])->text().trimmed();
        attrValue = ((QLineEdit*)list[i+1])->text().trimmed();

        currentDocument->elementsByTagName(nodeName).item(0).toElement().setAttribute(attrName, attrValue);
    }

    //update the tree
    heightXML(currentDocument->documentElement(), &height);
    for(int i = 0; i < height-1; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }
    buildTree(currentDocument->documentElement(), modelUpdated, new QStandardItem(currentDocument->documentElement().tagName()), nodesLength, 0, currentChild, -1);
    model = modelUpdated;
    ui->treeView->setModel(model);
    clearFormLayout();
}

void MainWindow::openWindowAddNode()
{
    DialogAddNode *addNodeWindow;
    QStringList *tagList = new QStringList;

    if(!currentDocument->isNull())
    {
        if(!currentDocument->documentElement().isNull())
        {
            getTagList(currentDocument->documentElement(), tagList);
        }
    }
    addNodeWindow = new DialogAddNode(tagList, this);
    addNodeWindow->show();
}

void MainWindow::openWindowModifyNode()
{
    DialogModifyNode *modifyNodeWindow = new DialogModifyNode(this, model->itemFromIndex(ui->treeView->currentIndex())->text());
    cout << model->itemFromIndex(ui->treeView->currentIndex())->text().toStdString() << endl;
    modifyNodeWindow->show();
}

void MainWindow::deleteSelectedNode()
{
    QDomNode parent = currentDocument->elementsByTagName(model->itemFromIndex(ui->treeView->currentIndex().sibling(ui->treeView->currentIndex().row(), 0))->text()).item(0).parentNode();
    QStandardItemModel *modelUpdated = new QStandardItemModel();
    int height = 0;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();

    parent.removeChild(currentDocument->elementsByTagName(model->itemFromIndex(ui->treeView->currentIndex().sibling(ui->treeView->currentIndex().row(), 0))->text()).item(0));

    heightXML(currentDocument->documentElement(), &height);
    for(int i = 0; i < height-1; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }

    buildTree(currentDocument->documentElement(), modelUpdated, new QStandardItem(currentDocument->documentElement().tagName()), nodesLength, 0, currentChild, -1);
    model = modelUpdated;
    ui->treeView->setModel(model);
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

