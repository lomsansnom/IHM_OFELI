#ifndef DIALOGMODIFYNODE_H
#define DIALOGMODIFYNODE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogModifyNode;
}

/*!
 * \brief The DialogModifyNode class manages the modification of a node in the TreeView
 */
class DialogModifyNode : public QDialog
{
    Q_OBJECT

    public:
        /*!
         * \brief Constructor
         * \param parent
         * \param selectedNode The name of the selected node
         */
        explicit DialogModifyNode(MainWindow *parent, QString selectedNode);
        ~DialogModifyNode();

    public slots:
        /*!
         * \brief Modifes the node selected with the new name
         */
        void modifyNode();

    private:
        Ui::DialogModifyNode *ui;
        MainWindow *parent;
        QString selectedNode;
};

#endif // DIALOGMODIFYNODE_H
