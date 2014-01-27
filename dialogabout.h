#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>
#include <QImage>
#include <QFile>

namespace Ui {
class DialogAbout;
}

/*!
 * \brief The DialogAbout class manages the dialog about
 */
class DialogAbout : public QDialog
{
    Q_OBJECT

    public:
        /*!
         * \brief DialogAbout
         * \param parent
         */
        explicit DialogAbout(QWidget *parent = 0);
        ~DialogAbout();

    private:
        Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
