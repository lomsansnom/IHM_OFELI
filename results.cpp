#include "results.h"
#include "ui_results.h"

Results::Results(QWidget *parent, QString res) :
    QDialog(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
    this->ui->textEdit->setText(res);
    QObject::connect(this->ui->buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

Results::~Results()
{
    delete ui;
}

void Results::closeExec(DialogExec *execWindow)
{
    execWindow->close();
}
