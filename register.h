#ifndef REGISTER_H
#define REGISTER_H
#include <QDate>
#include <QDialog>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:




    void on_pushButton_submit_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
