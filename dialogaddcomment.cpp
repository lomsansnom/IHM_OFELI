#include "dialogaddcomment.h"
#include "ui_dialogaddcomment.h"

DialogAddComment::DialogAddComment(QString parentNode, int selectedRow, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddComment)
{
    ui->setupUi(this);
    this->parentNode = parentNode;
    this->selectedRow = selectedRow;
    this->parent = parent;
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(addComment()));
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

DialogAddComment::~DialogAddComment()
{
    delete ui;
}

void DialogAddComment::addComment()
{
    parent->addComment(parentNode, ui->commentText->text(), selectedRow);
}
