#ifndef DIALOGEXEC_H
#define DIALOGEXEC_H

#include <QDialog>
#include <QFileDialog>
#include <QProcess>

namespace Ui {
class DialogExec;
}

class DialogExec : public QDialog
{
    Q_OBJECT

    public:
        explicit DialogExec(QWidget *parent = 0);
        ~DialogExec();

    public slots:
        void selectExec();
        void selectDat();
        void execute();

    private:
        Ui::DialogExec *ui;
        QWidget *parent;
};

#endif // DIALOGEXEC_H
