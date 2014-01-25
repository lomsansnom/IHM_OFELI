#ifndef DIALOGEXEC_H
#define DIALOGEXEC_H

#include <QDialog>
#include <QFileDialog>
#include <QProcess>
#include <QTextEdit>

namespace Ui {
class DialogExec;
}

/*!
 * \brief The DialogExec class manages the execution of the OFELI program.
 */
class DialogExec : public QDialog
{
    Q_OBJECT

    public:
        /*!
         * \brief Constructor
         * \param parent
         * \param filenameDat The path to the data file
         */
        explicit DialogExec(QTextEdit *parent = 0, QString filenameDat = "");
        ~DialogExec();

    public slots:
        /*!
         * \brief Opens a dialog to select the executable for the OFELI program.
         */
        void selectExec();
        /*!
         * \brief Opens a dialog to select the data file for the OFELI program.
         */
        void selectDat();
        /*!
         * \brief Executes the OFELI program and show the result in the MainWindow.
         */
        void execute();

    private:
        Ui::DialogExec *ui;
        QTextEdit *parent;
};

#endif // DIALOGEXEC_H
