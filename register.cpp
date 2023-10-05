#include "register.h"
#include"Globals.h"
#include "ui_register.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include "user.h"
#include <QDate>
#include <string>
vector <user> allUsers;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_submit_clicked()
{
    QString firstname = ui->lineEdit_firstname->text();
    QString lastname = ui->lineEdit_lastname->text();
    QString phonenumber = ui->lineEdit_phonenumber->text();
    QString email = ui->lineEdit_email->text();
    QString adress = ui->lineEdit_adress->text();
    QString birthdate = ui->lineEdit_birthdate->text();
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QDate date = QDate::fromString(birthdate, "dd.MM.yyyy");
    string firstname_string = firstname.toStdString();
    string lastname_string = lastname.toStdString();
    string email_string = email.toStdString();
    string adress_string = adress.toStdString();
    string username_string = username.toStdString();
    string password_string = password.toStdString();
    int phonenumber_int = phonenumber.toInt();
    user temp(firstname_string,lastname_string,phonenumber_int,email_string,adress_string,date,username_string,password_string);
    QFile file("user.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        if(firstname.isEmpty() || lastname.isEmpty() || phonenumber.isEmpty() || email.isEmpty() || username.isEmpty() || password.isEmpty()) {
            qDebug() << "Veuillez remplir tous les champs.";
        }
        else{
            out << "ID: " << temp.getId() << "\n";
            out << "First name: " << firstname << "\n";
            out << "Last name: " << lastname << "\n";
            out << "Phone number: " << phonenumber << "\n";
            out << "Email: " << email << "\n";
            out << "Adress: " << adress << "\n";
            out << "Birth Date: " << birthdate << "\n";
            out << "Username: " << username << "\n";
            out << "Password: " << password << "\n";
            out << "-----------------------------------------\n";
            file.close();
            allUsers.push_back(temp);
            globalForum.useradd(allUsers);
            qDebug() << "Les informations ont été enregistrées dans le fichier.";
            close();
            globalForum.displayAttributes();
            qDebug() <<globalForum.getUsers().size();
        }
    }
    else {
        qDebug() << "Impossible d'ouvrir le fichier.";
    }
}
