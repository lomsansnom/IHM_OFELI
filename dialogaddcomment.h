#ifndef DIALOGADDCOMMENT_H
#define DIALOGADDCOMMENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogAddComment;
}

/*!
 * \brief The DialogAddComment class manages the addition of a comment
 */
class DialogAddComment : public QDialog
{
    Q_OBJECT

    public:
        /*!
         * \brief DialogAddComment
         * \param parentNode The name of the parent node
         * \param selectedRow The row number of the selected node
         * \param parent
         */
        explicit DialogAddComment(QString parentNode, int selectedRow, MainWindow *parent = 0);
        ~DialogAddComment();

    public slots:
        /*!
         * \brief Add the comment to the TreeView (and to the document) by calling tha addComment function of the MainWindow
         */
        void addComment();

    private:
        Ui::DialogAddComment *ui;
        QString parentNode;
        int selectedRow;
        MainWindow *parent;
};

#endif // DIALOGADDCOMMENT_H
