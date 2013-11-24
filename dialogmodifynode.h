#ifndef DIALOGMODIFYNODE_H
#define DIALOGMODIFYNODE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogModifyNode;
}

class DialogModifyNode : public QDialog
{
    Q_OBJECT

    public:
        explicit DialogModifyNode(MainWindow *parent, QString selectedNode);
        ~DialogModifyNode();

    public slots:
        void modifyNode();

    private:
        Ui::DialogModifyNode *ui;
        MainWindow *parent;
        QString selectedNode;
};

#endif // DIALOGMODIFYNODE_H
