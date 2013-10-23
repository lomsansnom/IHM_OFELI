#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
   /* QString filename = "/home/alex/Téléchargements/ofeli-2.3.0/tutorial/lesson4/test.dat";
    w.openDatas(filename);*/

    return a.exec();
}
