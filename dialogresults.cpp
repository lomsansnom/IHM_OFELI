#include "dialogresults.h"
#include "ui_dialogresults.h"

DialogResults::DialogResults(QWidget *parent, QString res) :
    QDialog(parent),
    ui(new Ui::DialogResults)
{
    ui->setupUi(this);
    this->ui->textEdit->setText(res);
    QObject::connect(this->ui->buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

DialogResults::~DialogResults()
{
    delete ui;
}

void DialogResults::closeExec(DialogExec *execWindow)
{
    execWindow->close();
}
