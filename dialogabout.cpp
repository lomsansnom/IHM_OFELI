#include "dialogabout.h"
#include "ui_dialogabout.h"
#include <iostream>

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    QImage picture;
    picture.load("logo.png");
    ui->logo->setPixmap(QPixmap::fromImage(picture));
    ui->logo->adjustSize();
    ui->logo->setAlignment(Qt::AlignHCenter);

    QFile file("textAbout.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    ui->textAbout->setReadOnly(true);
    ui->textAbout->setText(QString(file.readAll()));


    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
