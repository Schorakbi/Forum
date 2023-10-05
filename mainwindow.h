
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"register.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MainWindow returnMainWindow();

private slots:
    void on_pushButton_register_clicked();
    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    Register *reg;
};

#endif // MAINWINDOW_H
