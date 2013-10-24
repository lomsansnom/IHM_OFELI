#include "dialogexec.h"
#include "ui_dialogexec.h"
#include "results.h"

#include <iostream>
using namespace std;

DialogExec::DialogExec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExec)
{
    ui->setupUi(this);
    this->parent = parent;

    QObject::connect(this->ui->buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->ui->buttonBrowse, SIGNAL(clicked()), this, SLOT(selectExec()));
    QObject::connect(this->ui->buttonBrowseDat, SIGNAL(clicked()), this, SLOT(selectDat()));
    QObject::connect(this->ui->buttonExecute, SIGNAL(clicked()), this, SLOT(execute()));
}

DialogExec::~DialogExec()
{
    delete ui;
}

//Slots

void DialogExec::selectExec()
{
    QFileDialog *openWindow = new QFileDialog(this);
    openWindow->setFileMode(QFileDialog::Directory);
    openWindow->show();
    if(openWindow->exec())
    {
        this->ui->pathExec->setText(openWindow->selectedFiles()[0]);
    }
}

void DialogExec::selectDat()
{
    QFileDialog *openWindow = new QFileDialog(this);
    openWindow->setFileMode(QFileDialog::ExistingFile);
    openWindow->show();
    if(openWindow->exec())
    {
        this->ui->pathDat->setText(openWindow->selectedFiles()[0]);
    }
}

void DialogExec::execute()
{
    QProcess *proc = new QProcess();
    proc->setProcessChannelMode(QProcess::MergedChannels);
    proc->start("sh", QStringList() << "-c" << "cd " + this->ui->pathExec->text() + " && " + this->ui->nameExec->text() + " " + this->ui->pathDat->text());
    proc->waitForFinished(-1);

    QString p_stdout = proc->readAll();
    proc->close();
    cout << p_stdout.toStdString() << endl;
    Results *resWindow = new Results(parent, p_stdout);
    resWindow->show();
    resWindow->closeExec(this);
}





