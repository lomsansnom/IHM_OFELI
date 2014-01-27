#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <iostream>
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
#include <QFormLayout>
#include <QTextEdit>
#include <QClipboard>
#include <QScrollArea>
#include <QGridLayout>
#include <QSplitter>
#include <QComboBox>
#include <QMap>
#include <QKeyEvent>
#include <QSettings>

namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class manages all the user interface.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /*!
         * \brief MainWindow
         * \param parent
         */
        explicit MainWindow(QWidget *parent = 0);
        //! Destructor
        ~MainWindow();
        /*!
         * \brief Opens the XML file containing the datas needed to execute the OFELI program and generate the tree associated
         * \param fileName A QString containing the path to the XML file
         */
        void openDatas(QString fileName);
        /*!
         * \brief Generates a QStandardItemModel recursively from a QDomDocument. This model can be used by a TreeView
         * \param doc A QDomNode containing the root of your QDomDocument
         * \param model An empty QStandardItemModel
         * \param item A QStandardItem containing a QString which is the tag name of the root
         * \param nbChildren A list containing only zeros. Its length must be equals to the maximum height of the QDomDocument
         * \param childNumber Must be 0 for the first call.
         * \param currentChild A list containing only zeros. Its length must be equals to the maximum height of the QDomDocument
         * \param currentLevel Must be -1 for the first call.
         */
        void buildTree(QDomNode doc, QStandardItemModel* model, QStandardItem *item, QList<int> *nbChildren, int childNumber, QList<int> *currentChild, int currentLevel);
        /*!
         * \brief Gets the list of parameters from a specific tag
         * \param list Contains the outpout
         * \param doc The node from which you want to get the list of attributes
         */
        void getTagAttributes(QList<QStandardItem*> *list, QDomNode doc);
        /*!
         * \brief Adds an empty column to a QStandardItemModel for each attribute contained in the given node
         * \param model The model on which you want to add a column
         * \param doc A node
         */
        void addColumnModel(QStandardItemModel *model, QDomNode doc);
        /*!
         * \brief Gets the maximum height in the QDomDocument recursively
         * \param doc The root of the document
         * \param height Must be 0 for the first call. Contains the output
         */
        void heightXML(QDomNode doc, int *height);
        /*!
         * \brief Gets the number of attributes maximum for a tag in the QDomDocument recursively
         * \param doc The root of the document
         * \param nbAttributes Must be 0 for the first call. Contains the output
         */
        void nbAttributesMax(QDomNode doc, int *nbAttributes);
        /*!
         * \brief Gets the list of tags in the QDomDocument recursively
         * \param doc The root of the document
         * \param tagList An empty QStringList. Contains the output
         */
        void getTagList(QDomNode doc, QStringList *tagList);
        /*!
         * \brief Adds a node to the given parent
         * \param nameParent The tag name of the parent
         * \param nameNode The tag name of the node to add
         * \param textNode The text to insert in the node
         */
        void addNode(QString nameParent, QString nameNode, QString textNode);
        /*!
         * \brief Modifies the node currently selected in the tree
         * \param nodeSelected The name of the node selected
         * \param newName The new name of the node
         */
        void modifyNode(QString nodeSelected, QString newName);
        /*!
         * \brief Removes all items from the formLayout
         */
        void clearFormLayout();
        /*!
         * \brief Modifies the names of the columns by an empty String
         * \param model
         */
        void setColumnLabels(QStandardItemModel *model);
        /*!
         * \brief Specifies that the user can press the key return to insert new parameters if a text edit is focused.
         * \param event
         */
        void keyPressEvent(QKeyEvent *event);
        /*!
         * \brief Checks if the user saved his files, if not, shows a dialog to notify the user that he didn't save the file. Also saves the window geometry using QSettings object.
         * \param event
         */
        void closeEvent(QCloseEvent *event);
        /*!
         * \brief For now saves the recent files opened by the user using QSettings object. Can be used for save more settings.
         * \param filename
         */
        void setSettings(QString filename);
        /*!
         * \brief Updates the recent files menu.
         */
        void updateMenuRecentFiles();
        /*!
         * \brief Adds a comment after the selected node.
         * \param nameParent The name of the parent of the node selected
         * \param comment The comment to add
         * \param selectedRow The row number of the slected node
         */
        void addComment(QString nameParent, QString comment, int selectedRow);
        /*!
         * \brief Return the name of the settings file associated to the application
         * \return
         */
        QString getSettingsFile();
        /*!
         * \brief Updates the tree. This function needs to be called if the user adds a parameter, delete a node, add a node, modify a node...
         */
        void updateTree();

    public slots:
        /*!
         * \brief Opens a dialog to select an XML file and store the file slected in filename.
         */
        void selectFile();
        /*!
         * \brief Shows the list of editables elements for the node slected. Informations are shown in the right part of the window.
         * \param index Index of the node selected in the tree
         */
        void showDetails(QModelIndex index);
        /*!
         * \brief Save the XML file by replacing the file selected before
         */
        void saveFileAs();
        /*!
         * \brief Opens a dialog to save the XML file.
         */
        void saveFile();
        /*!
         * \brief Opens a dialog to execute the OFELI program.
         */
        void executable();
        /*!
         * \brief Updates the right part of the window and add two fields editables so the user can set the name and the value of a new attribute.
         */
        void addParam();
        /*!
         * \brief Updates the tree (and the document) with the attributes modified or added by the user.
         */
        void insert();
        /*!
         * \brief Opens a dialog to add a new node to the tree (and the document).
         */
        void openWindowAddNode();
        /*!
         * \brief Deletes the selected node in the tree.
         */
        void deleteSelectedNode();
        /*!
         * \brief Opens a dialog to modify the name of the selected node in the tree.
         */
        void openWindowModifyNode();
        /*!
         * \brief Delete a given attribute from a node.
         * \param nameAttribute The name of the attribute to delete.
         */
        void deleteAttribute(QString nameAttribute);
        /*!
         * \brief Clears the text area where the results are shown.
         */
        void clearResult();
        /*!
         * \brief Copies the contents of the text area to the clipboard.
         */
        void copyToClipboard();
        /*!
         * \brief Opens the file on which the user clicked in the Recent files menu.
         */
        void openRecent();
        /*!
         * \brief Opens a dialog to add a new comment to the tree (and the document).
         */
        void openWindowAddComment();
        /*!
         * \brief Opens the dialog "about".
         */
        void openWindowAbout();

    private:
        Ui::MainWindow *ui;
        QString filename;
        QString nodeName;
        QString root;
        QModelIndex currentIndex;
        QDomDocument *currentDocument;
        QStandardItemModel *model;
        QList<QWidget*> list;
        QList<QPushButton*> listButton;
        QList<QLayout*> listLayout;
        QSignalMapper *signalMapper;
        QClipboard *clipboard;
        QStringList listExpanded;
        bool fileSaved;
        QSettings settings;
        QMenu *menuRecentFiles;
        bool modelIsSet;

        //CentralWidget elements
        QGridLayout *gridLayout;
        QTreeView *treeView;
        QTextEdit *textResult;
        QPushButton *buttonSave;
        QPushButton *buttonExec;
        QPushButton *buttonAddParam;
        QPushButton *buttonInsert;
        QFormLayout *formLayout;
        QLabel *label;
        QPushButton *buttonClear;
        QPushButton *buttonCopy;
        QScrollArea *scrollContainer;
        QWidget *scrollableWidget;
        QSplitter *splitter;
};

#endif // MAINWINDOW_H
