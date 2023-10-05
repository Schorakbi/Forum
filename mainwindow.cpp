
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register.h"
#include <string>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include "forum.h"
#include <QMessageBox>
#include <algorithm>
#include <QStackedWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_register_clicked()
{
    reg = new Register(this);
    reg->show();
}



void MainWindow::on_pushButton_login_clicked()
{
    QString currentID;
    QString currentFirstName;
    QString currentLastName;
    QString currentPhoneNumber;
    QString currentEmail;
    QString currentAdress;
    QString currentBirth;
    QString usernameWritten,passwordWritten;
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QFile file("user.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Le fichier est vide.(Aucun utilisateur enregistré)";
    }
    QTextStream in(&file);
    QString line;
    bool userFound = false;
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList list = line.split(": ");
        if (list[0] == "ID") {
            currentID = list[1];
        }
        else if (list[0] == "First name") {
            currentFirstName = list[1];
        }
        else if (list[0] == "Last name") {
            currentLastName = list[1];
        }
        else if (list[0] == "Phone number") {
            currentPhoneNumber = list[1];
        }
        else if (list[0] == "Email") {
            currentEmail = list[1];
        }
        else if (list[0] == "Adress") {
            currentAdress = list[1];
        }
        else if (list[0] == "Birth Date") {
            currentBirth = list[1];
        }
        else if (list[0] == "Username") {
            usernameWritten = list[1];
        }
        else if (list[0] == "Password") {
            passwordWritten = list[1];
        }
        if (!usernameWritten.isEmpty() && !passwordWritten.isEmpty() && username.toLower() == usernameWritten.toLower() && password == passwordWritten){
            userFound=true;
            break;

        }

    }

    file.close();
    QFile file1("Current User.txt");
    if (file1.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file1);
        if (userFound) {
            out << "ID: " << currentID << "\n";
            out << "First name: " << currentFirstName << "\n";
            out << "Last name: " << currentLastName << "\n";
            out << "Phone number: " << currentPhoneNumber << "\n";
            out << "Email: " << currentEmail << "\n";
            out << "Adress: " << currentAdress << "\n";
            out << "Birth Date: " << currentBirth << "\n";
            out << "Username: " << usernameWritten << "\n";
            out << "Password: " << passwordWritten << "\n";
            file1.close();
            Forum *f = new Forum(this);
            close();
            f->show();

    }
    else {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Warning"));
        msgBox.setText(tr("Invalid username or password."));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("");
        msgBox.exec();

    }

}
}
