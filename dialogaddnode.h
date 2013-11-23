#ifndef DIALOGADDNODE_H
#define DIALOGADDNODE_H

#include <QDialog>
#include <QtXml>
#include "mainwindow.h"

namespace Ui {
class DialogAddNode;
}

class DialogAddNode : public QDialog
{
    Q_OBJECT

    public:
        explicit DialogAddNode(QStringList* parentList, MainWindow *parent);
        ~DialogAddNode();

    public slots:
        void addNode();

    private:
        Ui::DialogAddNode *ui;
        QStringList* nodeNameList;
        MainWindow *parent;
};

#endif // DIALOGADDNODE_H
