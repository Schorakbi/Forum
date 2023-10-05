#include "addtopic.h"
#include "ui_addtopic.h"
#include <QDateTime>
#include "mainwindow.h"
#include <QFile>

AddTopic::AddTopic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTopic)
{
    ui->setupUi(this);
}

AddTopic::~AddTopic()
{
    delete ui;
}

void AddTopic::on_pushButton_clicked()
{
    QString topicCreatorUsername;
    QString topicTitle = ui->lineEdit->text();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QFile file("Current User.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList list = line.split(": ");
            if (list[0] == "Username") {
                topicCreatorUsername  = list[1];
                file.close();
            }
        }
    } else {
        qDebug() << "Failed to open file: Current User.txt";
    }
    QFile file1("topics.txt");
    if (file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file1);
        if(topicTitle.isEmpty()) {
            qDebug() << "Veuillez remplir tous les champs.";}
        else{
            out << "Topic Title: " << topicTitle << "\n";
            out << "Date of the creation of the Topic : "  << currentDateTime.toString() << "\n";
            out << "Topic creator username : " << topicCreatorUsername << "\n";
            out << "-----------------------------------------\n";
            file1.close();
            qDebug() << "Les informations ont été enregistrées dans le fichier.";
            close();
        }
    }
    else {
        qDebug() << "Impossible d'ouvrir le fichier.";
    }
}


