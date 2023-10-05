#ifndef FORUM_H
#define FORUM_H
#include <QListWidgetItem>
#include <QDialog>

namespace Ui {
class Forum;
}

class Forum : public QDialog
{
    Q_OBJECT

public:
    explicit Forum(QWidget *parent = nullptr);
    ~Forum();

private slots:

    void on_pushButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_2_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_edit_phone_number_clicked();

    void on_pushButton_edit_email_clicked();

    void on_pushButton_edit_adress_clicked();

    void on_pushButton_edit_username_clicked();

    void on_pushButton_edit_password_clicked();

    void on_pushButton_delete_profile_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Forum *ui;
    bool isTab1Initialized;
    int itemSelected=-1;
};

#endif // FORUM_H
