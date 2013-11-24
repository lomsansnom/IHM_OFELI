#include "dialogmodifynode.h"
#include "ui_dialogmodifynode.h"

DialogModifyNode::DialogModifyNode(MainWindow *parent, QString selectedNode) :
    QDialog(parent),
    ui(new Ui::DialogModifyNode)
{
    ui->setupUi(this);

    this->parent = parent;
    this->selectedNode = selectedNode;

    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(modifyNode()));
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

DialogModifyNode::~DialogModifyNode()
{
    delete ui;
}

//SLOTS

void DialogModifyNode::modifyNode()
{
    parent->modifyNode(selectedNode, ui->newName->text());
}
