#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H

#include <QDialog>

namespace Ui {
class DialogSave;
}

/*!
 * \brief The DialogSave class manages the dialog shown when the user close the program but didn't save his file
 */
class DialogSave : public QDialog
{
    Q_OBJECT

    public:
        /*!
         * \brief DialogSave
         * \param parent
         */
        explicit DialogSave(QWidget *parent = 0);
        ~DialogSave();

    public slots:
        /*!
         * \brief Closes the dialog and returns Rejected (this value is used by the exec function of the QDialog class)
         */
        void cancelClicked();
        /*!
         * \brief Closes the dialog and returns Accepted (this value is used by the exec function of the QDialog class)
         */
        void quitClicked();

    private:
        Ui::DialogSave *ui;
};

#endif // DIALOGSAVE_H
