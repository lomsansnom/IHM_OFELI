#ifndef RESULTS_H
#define RESULTS_H

#include "dialogexec.h"
#include <QDialog>

namespace Ui {
class Results;
}

class Results : public QDialog
{
    Q_OBJECT

    public:
    explicit Results(QWidget *parent = 0, QString res = "");
        ~Results();
        void closeExec(DialogExec *execWindow);

    private:
        Ui::Results *ui;
};

#endif // RESULTS_H
