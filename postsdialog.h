#ifndef POSTSDIALOG_H
#define POSTSDIALOG_H

#include <QDialog>

namespace Ui {
class PostsDialog;
}

class PostsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PostsDialog(QWidget *parent = nullptr);
    ~PostsDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_4_clicked();

private:
    Ui::PostsDialog *ui;
    int itemSelected=-1;
};

#endif // POSTSDIALOG_H
