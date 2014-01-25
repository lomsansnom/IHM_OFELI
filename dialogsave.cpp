#include "dialogsave.h"
#include "ui_dialogsave.h"

DialogSave::DialogSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSave)
{
    ui->setupUi(this);
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    QObject::connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(quitClicked()));
}

DialogSave::~DialogSave()
{
    delete ui;
}

void DialogSave::cancelClicked()
{
    done(QDialog::Rejected);
}

void DialogSave::quitClicked()
{
    done(QDialog::Accepted);
}

