#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget *desktop = a.desktop();
    QSettings settings(w.getSettingsFile(), QSettings::NativeFormat);

    if(settings.contains("userGeometry"))
    {
        w.restoreGeometry(settings.value("userGeometry").toByteArray());
    }
    else
    {
        w.setGeometry((desktop->width()-1000)/2, (desktop->height()-750)/2, 1000, 750);
    }
    w.show();

    return a.exec();
}
