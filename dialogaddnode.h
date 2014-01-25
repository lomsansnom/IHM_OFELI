#ifndef DIALOGADDNODE_H
#define DIALOGADDNODE_H

#include <QDialog>
#include <QtXml>
#include "mainwindow.h"

namespace Ui {
class DialogAddNode;
}

/*!
 * \brief The DialogAddNode class manages the addition of a node.
 */
class DialogAddNode : public QDialog
{
    Q_OBJECT

    public:
        /*!
         * \brief Constructor
         * \param parentList The list of possibles parent to the new node.
         * \param parent
         */
        explicit DialogAddNode(QStringList* parentList, MainWindow *parent);
        ~DialogAddNode();

    public slots:
        /*!
         * \brief Add the node to the TreeView (and to the document) by calling tha addNode function of the MainWindow
         */
        void addNode();

    private:
        Ui::DialogAddNode *ui;
        QStringList* nodeNameList;
        MainWindow *parent;
};

#endif // DIALOGADDNODE_H
