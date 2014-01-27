#include "mainwindow.h"
#include "dialogexec.h"
#include "dialogaddnode.h"
#include "dialogmodifynode.h"
#include "dialogsave.h"
#include "ui_mainwindow.h"
#include "dialogaddcomment.h"
#include "dialogabout.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCoreApplication::setOrganizationName("OFELI");
    QCoreApplication::setApplicationName("GUI_OFELI");

    modelIsSet = false;
    menuRecentFiles = new QMenu();
    updateMenuRecentFiles();

    gridLayout = new QGridLayout(ui->centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);

    treeView = new QTreeView(ui->centralWidget);

    textResult = new QTextEdit(ui->centralWidget);
    textResult->setReadOnly(true);

    buttonSave = new QPushButton(ui->centralWidget);
    buttonSave->setText("Save");

    buttonExec = new QPushButton(ui->centralWidget);
    buttonExec->setText("Execute");

    buttonAddParam = new QPushButton(ui->centralWidget);
    buttonAddParam->setText("Add parameter");
    buttonAddParam->hide();

    buttonInsert = new QPushButton(ui->centralWidget);
    buttonInsert->setText("Insert");
    buttonInsert->hide();

    formLayout = new QFormLayout();
    formLayout->setContentsMargins(5,30,5,10);

    scrollContainer = new QScrollArea();
    scrollableWidget = new QWidget();
    scrollableWidget->setLayout(formLayout);
    scrollContainer->setWidget(scrollableWidget);
    scrollContainer->setWidgetResizable(true);

    label = new QLabel(ui->centralWidget);
    formLayout->addWidget(label);

    buttonClear = new QPushButton(ui->centralWidget);
    buttonClear->setText("Clear");

    buttonCopy = new QPushButton(ui->centralWidget);
    buttonCopy->setText("Copy to clipboard");

    splitter = new QSplitter(ui->centralWidget);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(treeView);
    splitter->addWidget(textResult);

    gridLayout->addWidget(splitter, 0, 0, 3, 4);
    gridLayout->addWidget(scrollContainer, 0, 4, 2, 2);
    gridLayout->addWidget(buttonAddParam, 2, 4);
    gridLayout->addWidget(buttonInsert, 2, 5);
    gridLayout->addWidget(buttonSave, 6, 4);
    gridLayout->addWidget(buttonExec, 6, 5);
    gridLayout->addWidget(buttonClear, 6, 0);
    gridLayout->addWidget(buttonCopy, 6, 1);

    signalMapper = new QSignalMapper(this);

    clipboard = QApplication::clipboard();

    fileSaved = true;

    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(selectFile()));
    QObject::connect(ui->actionSave_File, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(buttonExec, SIGNAL(clicked()), this, SLOT(executable()));
    QObject::connect(buttonAddParam, SIGNAL(clicked()), this, SLOT(addParam()));
    QObject::connect(buttonInsert, SIGNAL(clicked()), this, SLOT(insert()));
    QObject::connect(ui->actionAdd_node, SIGNAL(triggered()), this, SLOT(openWindowAddNode()));
    QObject::connect(ui->actionDelete_selected_node, SIGNAL(triggered()), this, SLOT(deleteSelectedNode()));
    QObject::connect(ui->actionModifySelectedNode, SIGNAL(triggered()), this, SLOT(openWindowModifyNode()));
    QObject::connect(buttonClear, SIGNAL(clicked()), this, SLOT(clearResult()));
    QObject::connect(buttonCopy, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
    QObject::connect(ui->actionAdd_Comment, SIGNAL(triggered()), this, SLOT(openWindowAddComment()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openWindowAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDatas(QString filename)
{
    QStandardItemModel *model = new QStandardItemModel;

    QFile fichier(filename);
    QDomDocument *doc = new QDomDocument("docXml");
    QDomElement elem;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();
    int height = 0;

    //open the selected file and get the xml document in doc
    fichier.open(QIODevice::ReadWrite | QIODevice::Text);

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

    //Modify the columns' headers
    //setColumnLabels(model);

    this->model = model;
    this->modelIsSet = true;

    //set the to the tree
    /*treeView->setModel(model);
    treeView->expandAll();
    for(int i = 0; i < model->columnCount(); i++)
    {
        treeView->resizeColumnToContents(i);
    }*/

    //Store the filename for the menu "Recent files"
    /*setSettings(filename);
    updateMenuRecentFiles();*/
    QObject::connect(treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));
}

void MainWindow::buildTree(QDomNode doc, QStandardItemModel* model, QStandardItem *item, QList<int> *nbChildren, int childNumber, QList<int> *currentChild, int currentLevel)
{
    //check if doc is not empty
    if(!doc.isNull())
    {
        cout << doc.toElement().tagName().toStdString() << endl;
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
            if(!doc.isComment())
            {
                //get the parent to the node we want to add to the model
                QList<QStandardItem*> list;
                for(int i = 0; i < currentLevel; i++)
                {
                    itemUpdated = itemUpdated->child(currentChild->at(i));
                }
                addColumnModel(model, doc);
                getTagAttributes(&list, doc);

                //append the list
                itemUpdated->appendRow(list);
            }
            else
            {
                for(int i = 0; i < currentLevel; i++)
                {
                    itemUpdated = itemUpdated->child(currentChild->at(i));
                }
                itemUpdated->appendRow(new QStandardItem("(Comment) " + doc.nodeValue()));
            }
        }
        //if the node has at least one child get all the children and add them to the model
        if(!doc.childNodes().isEmpty() && (doc.firstChild().toElement().tagName() != "" || doc.firstChild().isComment()))
        {
            //get the children
            QDomNodeList nodeList = doc.childNodes();
            //update the level and store the number of children
            currentLevel++;
            (*nbChildren)[currentLevel] = nodeList.length();

            //for each child add the child and its children to the model
            for(int i = 0; i < (*nbChildren)[currentLevel]; i++)
            {
                (*currentChild)[currentLevel] = i;
                buildTree(nodeList.at(i), model, item, nbChildren, i, currentChild, currentLevel);
            }
        }
        //if the current node doesn't have any children the previous level need to be updated
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

void MainWindow::getTagAttributes(QList<QStandardItem*> *list, QDomNode doc)
{
    //add the tag's name in the list
    list->append(new QStandardItem(doc.toElement().tagName()));

    //if the node doesn't have any children, it means there is a value inside the node, we add this value in the list here
    if((!doc.childNodes().item(0).isElement() && doc.hasChildNodes()) && !doc.childNodes().item(0).isComment())
    {
        list->append(new QStandardItem(doc.toElement().text()));
    }
    //if the node have at least one child, there is no value inside the node so we just had an empty string to the list
    else
    {
        list->append(new QStandardItem(""));
    }
    //add all the attributes to the list
    for(int i = 0; i < doc.attributes().length(); i++)
    {
        list->append(new QStandardItem(doc.attributes().item(i).toAttr().name() + " : " + doc.attributes().item(i).toAttr().value()));
    }
}

void MainWindow::addColumnModel(QStandardItemModel *model, QDomNode doc)
{
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
        if(!doc.childNodes().isEmpty() && (doc.firstChild().toElement().tagName() != "" || doc.firstChild().isComment()))
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

        if(!doc.childNodes().isEmpty() && (doc.firstChild().toElement().tagName() != "" || doc.firstChild().isComment()))
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

        if(!doc.childNodes().isEmpty() && (doc.firstChild().toElement().tagName() != "" || doc.firstChild().isComment()))
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
    QDomElement newNode = (new QDomDocument())->createElement(nameNode);
    newNode.setTagName(nameNode);
    currentDocument->elementsByTagName(nameParent).item(0).appendChild(newNode);
    if(textNode.trimmed() != "")
    {
        currentDocument->elementsByTagName(nameParent).item(0).lastChild().appendChild((new QDomDocument())->createTextNode(textNode));
    }

    updateTree();
}

void MainWindow::addComment(QString nameParent, QString comment, int selectedRow)
{
    currentDocument->elementsByTagName(nameParent).item(0).insertAfter((new QDomDocument())->createComment(comment), currentDocument->elementsByTagName(nameParent).item(0).childNodes().item(selectedRow));

    updateTree();
}

void MainWindow::modifyNode(QString nodeSelected, QString newName)
{
    if(modelIsSet && currentIndex.isValid())
    {
        //the function elementsByTagName returns a list, so to get the good index in this list we need to count how many nodes
        //have a tag different from the one which is selected
        int countDiff = 0;

        for(int i = 1; i <= treeView->currentIndex().row(); i++)
        {
            if(model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row()-i,0))->text() != model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row(),0))->text())
            {
                countDiff++;
            }
        }
        if(root == nodeSelected)
        {
            root = newName;
        }
        currentDocument->elementsByTagName(nodeSelected).item(treeView->currentIndex().row() - countDiff).toElement().setTagName(newName);

        updateTree();
    }
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
    }
    if(!listLayout.isEmpty())
    {
        for(int i = 0; i < listLayout.length(); i++)
        {
            delete listLayout[i];
        }
        listLayout.clear();
    }
    if(!listButton.empty())
    {
        for(int i = 0; i < listButton.length(); i++)
        {
            delete listButton[i];
        }
        listButton.clear();
    }
    label->setText("");
}

void MainWindow::setColumnLabels(QStandardItemModel *model)
{
    QStringList columnLabels;
    for(int i = 0; i < model->columnCount(); i++)
    {
        columnLabels.append("");
    }
    model->setHorizontalHeaderLabels(columnLabels);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!list.isEmpty())
    {
        //call the function insert() when the key Return is pressed and a text edit is focused
        if(event->key() == Qt::Key_Return)
        {
            bool listFocused = false;
            int i = 0;
            while(i != list.length() && !listFocused)
            {
                if(list[i]->hasFocus())
                {
                   listFocused = true;
                   insert();
                }
                i++;
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //Open a dialog to notify the user that he didn't save the file
    if(!fileSaved)
    {
        DialogSave *windowSave = new DialogSave(this);
        int ret = windowSave->exec();
        if(ret == QDialog::Rejected)
        {
            event->ignore();
        }
    }
    settings.setValue("userGeometry", this->saveGeometry());
}

void MainWindow::setSettings(QString fileName)
{
    //Save a list the five last documents opened on this computer
    QStringList recentFiles = QStringList();
    if(settings.contains("recentFiles"))
    {
        recentFiles = settings.value("recentFiles").toStringList();
        if(recentFiles.length() == 5)
        {
            recentFiles.pop_back();
        }
    }
    recentFiles.push_front(fileName);
    settings.setValue("recentFiles", recentFiles);

}

void MainWindow::updateMenuRecentFiles()
{
    if(settings.contains("recentFiles"))
    {
        menuRecentFiles->clear();
        QList<QAction*>recentFiles = QList<QAction*>();
        for(int i = 0; i < settings.value("recentFiles").toStringList().length(); i++)
        {
            QAction* a = new QAction(this);
            a->setText(settings.value("recentFiles").toStringList().at(i));
            QObject::connect(a, SIGNAL(triggered()), this, SLOT(openRecent()));
            recentFiles.append(a);
        }
        menuRecentFiles->addActions(recentFiles);
        ui->actionRecent_files->setMenu(menuRecentFiles);
    }
}

QString MainWindow::getSettingsFile()
{
    return settings.fileName();
}

void MainWindow::updateTree()
{
    QStandardItemModel *modelUpdated = new QStandardItemModel();
    int height = 0;
    QList<int> *currentChild = new QList<int>();
    QList<int> *nodesLength = new QList<int>();

    heightXML(currentDocument->documentElement(), &height);
    for(int i = 0; i < height-1; i++)
    {
        currentChild->append(0);
        nodesLength->append(0);
    }
    cout << currentDocument->elementsByTagName("Project").at(0).childNodes().at(0).toElement().tagName().toStdString() << endl;
    buildTree(currentDocument->documentElement(), modelUpdated, new QStandardItem(currentDocument->documentElement().tagName()), nodesLength, 0, currentChild, -1);
    setColumnLabels(modelUpdated);
    model = modelUpdated;
    treeView->setModel(model);
    treeView->expandAll();
    clearFormLayout();
    fileSaved = false;
    currentIndex = QModelIndex();
    for(int i = 0; i < model->columnCount(); i++)
    {
        treeView->resizeColumnToContents(i);
    }
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
    buttonAddParam->show();
    buttonInsert->show();

    signalMapper = new QSignalMapper(this);

    //Clear formLayout to remove the parameter related to the last element selected
    clearFormLayout();

    label->setText("Edit " + nodeName);
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
            formLayout->addRow(horizontalLayout);
        }


        for(int i = 2; i < listAttr.length(); i+=2)
        {
            horizontalLayout = new QHBoxLayout();
            list.push_front(new QLineEdit(listAttr[i+1]));
            list.push_front(new QLineEdit(listAttr[i]));
            listButton.push_front(new QPushButton("-"));
            horizontalLayout->addWidget(list[0]);
            horizontalLayout->addWidget(list[1]);
            QObject::connect(listButton[0], SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(listButton[0], listAttr[i]);
            horizontalLayout->addWidget(listButton[0]);
            listLayout.push_front(horizontalLayout);
            formLayout->addRow(horizontalLayout);
        }
        QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(deleteAttribute(QString)));
    }
}

void MainWindow::deleteAttribute(QString nameAttribute)
{
    //the function elementsByTagName returns a list, so to get the good index in this list we need to count how many nodes
    //have a tag different from the one which is selected
    int countDiff = 0;
    for(int i = 1; i <= treeView->currentIndex().row(); i++)
    {
        if(model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row()-i,0))->text() != model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row(),0))->text())
        {
            countDiff++;
        }
    }

    currentDocument->elementsByTagName(model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row(),0))->text()).item(treeView->currentIndex().row() - countDiff).toElement().removeAttribute(nameAttribute.trimmed());

    updateTree();
}

void MainWindow::addParam()
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    list.push_front(new QLineEdit("Value"));
    list.push_front(new QLineEdit("Name"));
    horizontalLayout->addWidget(list[0]);
    horizontalLayout->addWidget(list[1]);
    formLayout->addRow(horizontalLayout);
}

void MainWindow::insert()
{
    QString attrName, attrValue;
    QStringList *listAttr = new QStringList();
    int ii = 0;
    QList<int> *indexToDelete = new QList<int>();
    bool indexToDeleteFound = false;

    //the function elementsByTagName returns a list, so to get the good index in this list we need to count how many nodes
    //have a tag different from the one which is selected
    int countDiff = 0;
    for(int i = 1; i <= treeView->currentIndex().row(); i++)
    {
        if(model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row()-i,0))->text() != model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row(),0))->text())
        {
            countDiff++;
        }
    }

    for(int i = 0; i < currentDocument->elementsByTagName(nodeName).item(treeView->currentIndex().row() - countDiff).attributes().length(); i++)
    {
        listAttr->append(currentDocument->elementsByTagName(nodeName).item(treeView->currentIndex().row() - countDiff).attributes().item(i).toAttr().name().trimmed());
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
        currentDocument->elementsByTagName(nodeName).item(treeView->currentIndex().row() - countDiff).toElement().removeAttribute(listAttr->at(indexToDelete->at(i)));
    }

    //add the attributes to the document
    for(int i = 0; i < list.length(); i += 2)
    {
        attrName = ((QLineEdit*)list[i])->text().trimmed();
        attrValue = ((QLineEdit*)list[i+1])->text().trimmed();

        currentDocument->elementsByTagName(nodeName).item(treeView->currentIndex().row() - countDiff).toElement().setAttribute(attrName, attrValue);
    }

    updateTree();
}

void MainWindow::openWindowAddNode()
{
    if(modelIsSet)
    {
        DialogAddNode *addNodeWindow;
        QStringList *tagList = new QStringList;

        if(!currentDocument->documentElement().isNull())
        {
            getTagList(currentDocument->documentElement(), tagList);
        }

        addNodeWindow = new DialogAddNode(tagList, this);
        addNodeWindow->show();
    }
}

void MainWindow::openWindowModifyNode()
{
    if(modelIsSet && currentIndex.isValid())
    {
        DialogModifyNode *modifyNodeWindow = new DialogModifyNode(this, model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row(), 0))->text());
        modifyNodeWindow->show();
    }
}

void MainWindow::deleteSelectedNode()
{
    if(modelIsSet && currentIndex.isValid())
    {
        QDomNode parent = currentDocument->elementsByTagName(model->itemFromIndex(treeView->currentIndex().sibling(treeView->currentIndex().row(), 0))->parent()->text()).at(0);
        parent.removeChild(parent.childNodes().item(treeView->currentIndex().row()));        
        updateTree();
    }
}

void MainWindow::saveFile()
{
    FILE *saveFile;
    QTextStream *fileStream;
    QByteArray filenameFopen;

    //convert Qstring to char* for the fopen function
    filenameFopen = this->filename.toLocal8Bit();
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
        fileSaved = true;
    }
}

void MainWindow::saveFileAs()
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
            fileSaved = true;
        }
    }

}

void MainWindow::executable()
{
    DialogExec *windowExec = new DialogExec(textResult, filename);
    windowExec->show();
}

void MainWindow::clearResult()
{
    textResult->clear();
}

void MainWindow::copyToClipboard()
{
    clipboard->setText(textResult->toPlainText());
}

void MainWindow::openRecent()
{
    openDatas(((QAction*)QObject::sender())->text());
}

void MainWindow::openWindowAddComment()
{
    if(modelIsSet && currentIndex.isValid())
    {
        DialogAddComment *windowAddComment = new DialogAddComment(model->itemFromIndex(treeView->currentIndex())->parent()->text(), treeView->currentIndex().row(), this);
        windowAddComment->show();
    }

}

void MainWindow::openWindowAbout()
{
    DialogAbout *windowAbout = new DialogAbout();
    windowAbout->show();
}
