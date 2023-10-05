#include <QStringList>
#include "forum.h"
#include "ui_forum.h"
#include <QStackedWidget>
#include <QFile>
#include <QList>
#include <QDate>
#include <vector>
#include "topic.h"
#include"user.h"
#include <QRandomGenerator>
#include <QSet>
#include <QStringList>
#include "postsdialog.h"
#include "forumclass.h"
#include "Globals.h"
#include"mainwindow.h"
ForumClass forum("forum-enit.tn","forum@enit.tn");


Forum::Forum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Forum)
{
    ui->setupUi(this);
    isTab1Initialized = false;
}

Forum::~Forum()
{
    delete ui;
}


void Forum::on_pushButton_clicked()

{
    QSet<int> uniqueNumbers;
    int randomNumber;
    QRandomGenerator randomGenerator;
    while (uniqueNumbers.size() < 20) {
        randomNumber = randomGenerator.bounded(1, 100 + 1);
        uniqueNumbers.insert(randomNumber);
    }
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
    globalForum.topicAdd(topicTitle);
    QFile file1("topics.txt");
    if (file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file1);
        if(topicTitle.isEmpty()) {
            qDebug() << "Veuillez remplir tous les champs.";}
        else{
            out << "Topic Title: " << topicTitle << "\n";
            out << "Date of the creation of the Topic : "  << currentDateTime.toString() << "\n";
            out << "Topic creator username : " << topicCreatorUsername << "\n";
            out << "Topic Id: "<< globalForum.getTopics().back().getIdTopic()<<"\n";
            out << "-----------------------------------------\n";
            file1.close();
            qDebug() << "Les informations ont été enregistrées dans le fichier.";
        }
    }
    else {
        qDebug() << "Impossible d'ouvrir le fichier.";
    }
    ui->listWidget->addItem(topicTitle+"\n"+"Created by "+topicCreatorUsername+" on "+currentDateTime.toString());
}


void Forum::on_tabWidget_currentChanged(int index)
{
    if(index==1 && !isTab1Initialized){
        QString topicTitle;
        QString date;
        QString username;
        int id;
        QFile file2("topics.txt");
        if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file2);
            QString line;
            while (!in.atEnd()) {
                line = in.readLine();
                QStringList list = line.split(": ");
                if (list[0] == "Topic Title") {
                    topicTitle  = list[1];                                       
                }
                else if (list[0] == "Date of the creation of the Topic "){
                    date=list[1];
                }
                else if (list[0] == "Topic creator username "){
                    username=list[1];                   
                    ui->listWidget->addItem(topicTitle+"\n"+"Created by "+username+" on "+date);

                }
                else if (list[0] == "Topic Id"){
                    id=(list[1]).toInt();
                    Topic topic;
                    topic.setTopicTitle(topicTitle);
                    topic.setTopicDateTime(QDateTime::fromString(date));
                    topic.setTopicCreatorUsername(username);
                    topic.setTopicId(id);
                    globalForum.addTopic(topic);


                }


            }

            file2.close();

        }

        else {
            qDebug() << "Failed to open file: Current User.txt";
        }

        globalForum.displayAttributesOfTopic();

        isTab1Initialized = true;

    }
}


void Forum::on_pushButton_2_clicked()
{
    int index = ui->listWidget->currentRow();

    if (index < 0) {
        return;
    }


    QFile file("topics.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line;
    QVector<QString> lines;
    while (!in.atEnd()) {
        line = in.readLine();
        lines.append(line);
    }
    file.close();


    QString itemName = ui->listWidget->currentItem()->text();
    QStringList list = itemName.split("\n");
    QString title =list[0];


    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].startsWith("Topic Title: " + title)) {
            lines.remove(i, 5);
            break;
        }
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (int i = 0; i < lines.size(); i++) {
        out << lines[i] << "\n";
    }
    file.close();

    delete ui->listWidget->takeItem(index);

    if (index == ui->listWidget->count()) {
        itemSelected = -1;
    }
    Topic topic = globalForum.researchTopicByTitle(title);
    globalForum.topicDelete(topic.getIdTopic());
}



void Forum::on_listWidget_currentRowChanged(int currentRow)
{
    itemSelected=currentRow;
}


void Forum::on_pushButton_3_clicked()
{

    QString itemName = ui->listWidget->currentItem()->text();
    QStringList list = itemName.split("\n");
    QString title =list[0];
    globalForum.setIdSelectedTopic(globalForum.researchTopicByTitle(title).getIdTopic());
    PostsDialog *p = new PostsDialog(this);
    p->show();

}


void Forum::on_pushButton_4_clicked()
{
    QFile file("Current User.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString profileDetails = QString::fromUtf8(file.readAll());
        ui->textEdit->setText(profileDetails);
        file.close();
    } else {
        qDebug() << "Failed to open file: Current User.txt";
    }
}

void Forum::on_pushButton_edit_phone_number_clicked()
{
    // Get the new phone number from the line edit
    QString new_phone_number = ui->lineEdit__edit_phone_number->text();

    // Open the current user file
    QFile file("Current User.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contents = file.readAll();

    // Find the line with the phone number and update it
    QRegularExpression regex("Phone number: \\d+");
    QRegularExpressionMatch match = regex.match(contents);
    if (match.hasMatch()) {
        int start = match.capturedStart();
        int length = match.capturedLength();
        contents.replace(start, length, "Phone number: " + new_phone_number);
    }

    // Write the updated contents back to the file
    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << contents;
    file.close();





    // Open the current user file
    QFile file1("Current User.txt");
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contentss = file1.readAll();

    // Get the user ID from the current user file
    QRegularExpression id_regex("ID: (\\d+)");
    QRegularExpressionMatch id_match = id_regex.match(contentss);
    if (!id_match.hasMatch()) {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
        return;
    }
    int user_id = id_match.captured(1).toInt();

    // Close the current user file
    file1.close();

    // Open the users file
    QFile users_file("user.txt");
    if (!users_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Read the contents of the users file into a QString
    QString users_contents = users_file.readAll();

    // Find the user with the given ID in the users file and update their phone number
    QRegularExpression user_regex("ID: "+QString::number(user_id)+"\nFirst name: (.+)\nLast name: (.+)\nPhone number: (.+)\nEmail: (.+)\nAdress: (.+)\nBirth Date: (.+)\nUsername: (.+)\nPassword: (.+)\n-----------------------------------------\\n"  );
    QRegularExpressionMatch user_match = user_regex.match(users_contents);
    qDebug() << "Failed to find user with ID " << users_contents << " in file: " << "user.txt";


    if (!user_match.hasMatch()) {
        qDebug() << "Failed to find user with ID " << user_id << " in file: " << "user.txt";
        return;
    }
    int user_start = user_match.capturedStart();
    qDebug() << "Failed to find user with ID " << user_start << " in file: " << "user.txt";
    int user_length = user_match.capturedLength();
    qDebug() << "Failed to find user with ID " << user_length << " in file: " << "user.txt";
    QString user_string = user_match.captured(0);
    QRegularExpression phone_regex("Phone number: \\d+");
    qDebug() << "Failed to find user with ID " << user_string << " in file: " << "user.txt";

    QRegularExpressionMatch phone_match = phone_regex.match(user_string);
    if (!phone_match.hasMatch()) {
        qDebug() << "Failed to find phone number in user string: " << user_string;
        return;
    }
    int phone_start = phone_match.capturedStart();
    int phone_length = phone_match.capturedLength();
    users_contents.replace(user_start + phone_start, phone_length, "Phone number: " + new_phone_number);

    // Write the updated contents back to the users file
    users_file.resize(0); // Clear the file before writing
    QTextStream users_out(&users_file);
    users_out << users_contents;
    users_file.close();

    // Update the user in the globalForum object
    user updated_user = globalForum.userSearch(user_id);
    if (updated_user.getId() == -1) {
        qDebug() << "Failed to find user with ID " << user_id << " in globalForum object";
        return;
    }
    updated_user.setPhoneNumber(std::stoi(new_phone_number.toStdString()));
    globalForum.displayAttributes();
    qDebug() <<globalForum.getUsers().size();
}

void Forum::on_pushButton_edit_email_clicked()
{
    // Get the new phone number from the line edit
    QString new_email = ui->lineEdit__edit_email->text();

    // Open the current user file
    QFile file("Current User.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contents = file.readAll();

    // Find the line with the phone number and update it
    QRegularExpression regex("Email: (.+)");
    QRegularExpressionMatch match = regex.match(contents);
    if (match.hasMatch()) {
        int start = match.capturedStart();
        int length = match.capturedLength();
        contents.replace(start, length, "Email: " + new_email);
    }

    // Write the updated contents back to the file
    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << contents;
    file.close();





    // Open the current user file
    QFile file1("Current User.txt");
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contentss = file1.readAll();

    // Get the user ID from the current user file
    QRegularExpression id_regex("ID: (\\d+)");
    QRegularExpressionMatch id_match = id_regex.match(contentss);
    if (!id_match.hasMatch()) {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
        return;
    }
    int user_id = id_match.captured(1).toInt();

    // Close the current user file
    file1.close();

    // Open the users file
    QFile users_file("user.txt");
    if (!users_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Read the contents of the users file into a QString
    QString users_contents = users_file.readAll();

    // Find the user with the given ID in the users file and update their phone number
    QRegularExpression user_regex("ID: "+QString::number(user_id)+"\nFirst name: (.+)\nLast name: (.+)\nPhone number: (.+)\nEmail: (.+)\nAdress: (.+)\nBirth Date: (.+)\nUsername: (.+)\nPassword: (.+)\n-----------------------------------------\\n"  );
    QRegularExpressionMatch user_match = user_regex.match(users_contents);
    qDebug() << "Failed to find user with ID " << users_contents << " in file: " << "user.txt";


    if (!user_match.hasMatch()) {
        qDebug() << "Failed to find user with ID " << user_id << " in file: " << "user.txt";
        return;
    }
    int user_start = user_match.capturedStart();
    qDebug() << "Failed to find user with ID " << user_start << " in file: " << "user.txt";
    int user_length = user_match.capturedLength();
    qDebug() << "Failed to find user with ID " << user_length << " in file: " << "user.txt";
    QString user_string = user_match.captured(0);
    QRegularExpression phone_regex("Email: (.+)");
    qDebug() << "Failed to find user with ID " << user_string << " in file: " << "user.txt";

    QRegularExpressionMatch phone_match = phone_regex.match(user_string);
    if (!phone_match.hasMatch()) {
        qDebug() << "Failed to find Email in user string: " << user_string;
        return;
    }
    int phone_start = phone_match.capturedStart();
    int phone_length = phone_match.capturedLength();
    users_contents.replace(user_start + phone_start, phone_length, "Email: " + new_email);

    // Write the updated contents back to the users file
    users_file.resize(0); // Clear the file before writing
    QTextStream users_out(&users_file);
    users_out << users_contents;
    users_file.close();

    // Update the user in the globalForum object
    user updated_user = globalForum.userSearch(user_id);
    if (updated_user.getId() == -1) {
        qDebug() << "Failed to find user with ID " << user_id << " in globalForum object";
        return;
    }
    updated_user.setEmail(new_email.toStdString());
    globalForum.displayAttributes();
    qDebug() <<globalForum.getUsers().size();
}


void Forum::on_pushButton_edit_adress_clicked()
{

    // Get the new phone number from the line edit
    QString edit_adress = ui->lineEdit__edit_adress->text();

    // Open the current user file
    QFile file("Current User.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contents = file.readAll();

    // Find the line with the phone number and update it
    QRegularExpression regex("Adress: (.+)");
    QRegularExpressionMatch match = regex.match(contents);
    if (match.hasMatch()) {
        int start = match.capturedStart();
        int length = match.capturedLength();
        contents.replace(start, length, "Adress: " + edit_adress);
    }

    // Write the updated contents back to the file
    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << contents;
    file.close();





    // Open the current user file
    QFile file1("Current User.txt");
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contentss = file1.readAll();

    // Get the user ID from the current user file
    QRegularExpression id_regex("ID: (\\d+)");
    QRegularExpressionMatch id_match = id_regex.match(contentss);
    if (!id_match.hasMatch()) {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
        return;
    }
    int user_id = id_match.captured(1).toInt();

    // Close the current user file
    file1.close();

    // Open the users file
    QFile users_file("user.txt");
    if (!users_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Read the contents of the users file into a QString
    QString users_contents = users_file.readAll();

    // Find the user with the given ID in the users file and update their phone number
    QRegularExpression user_regex("ID: "+QString::number(user_id)+"\nFirst name: (.+)\nLast name: (.+)\nPhone number: (.+)\nEmail: (.+)\nAdress: (.+)\nBirth Date: (.+)\nUsername: (.+)\nPassword: (.+)\n-----------------------------------------\\n"  );
    QRegularExpressionMatch user_match = user_regex.match(users_contents);
    qDebug() << "Failed to find user with ID " << users_contents << " in file: " << "user.txt";


    if (!user_match.hasMatch()) {
        qDebug() << "Failed to find user with ID " << user_id << " in file: " << "user.txt";
        return;
    }
    int user_start = user_match.capturedStart();
    qDebug() << "Failed to find user with ID " << user_start << " in file: " << "user.txt";
    int user_length = user_match.capturedLength();
    qDebug() << "Failed to find user with ID " << user_length << " in file: " << "user.txt";
    QString user_string = user_match.captured(0);
    QRegularExpression phone_regex("Adress: (.+)");
    qDebug() << "Failed to find user with ID " << user_string << " in file: " << "user.txt";

    QRegularExpressionMatch phone_match = phone_regex.match(user_string);
    if (!phone_match.hasMatch()) {
        qDebug() << "Failed to find Adress in user string: " << user_string;
        return;
    }
    int phone_start = phone_match.capturedStart();
    int phone_length = phone_match.capturedLength();
    users_contents.replace(user_start + phone_start, phone_length, "Adress: " + edit_adress);

    // Write the updated contents back to the users file
    users_file.resize(0); // Clear the file before writing
    QTextStream users_out(&users_file);
    users_out << users_contents;
    users_file.close();

    // Update the user in the globalForum object
    user updated_user = globalForum.userSearch(user_id);
    if (updated_user.getId() == -1) {
        qDebug() << "Failed to find user with ID " << user_id << " in globalForum object";
        return;
    }
    updated_user.setAdress(edit_adress.toStdString());
    globalForum.displayAttributes();
    qDebug() <<globalForum.getUsers().size();
}


void Forum::on_pushButton_edit_username_clicked()
{
    // Get the new phone number from the line edit
    QString username = ui->lineEdit_edit_username->text();

    // Open the current user file
    QFile file("Current User.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contents = file.readAll();

    // Find the line with the phone number and update it
    QRegularExpression regex("Username: (.+)");
    QRegularExpressionMatch match = regex.match(contents);
    if (match.hasMatch()) {
        int start = match.capturedStart();
        int length = match.capturedLength();
        contents.replace(start, length, "Username: " + username);
    }

    // Write the updated contents back to the file
    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << contents;
    file.close();





    // Open the current user file
    QFile file1("Current User.txt");
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contentss = file1.readAll();

    // Get the user ID from the current user file
    QRegularExpression id_regex("ID: (\\d+)");
    QRegularExpressionMatch id_match = id_regex.match(contentss);
    if (!id_match.hasMatch()) {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
        return;
    }
    int user_id = id_match.captured(1).toInt();

    // Close the current user file
    file1.close();

    // Open the users file
    QFile users_file("user.txt");
    if (!users_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Read the contents of the users file into a QString
    QString users_contents = users_file.readAll();

    // Find the user with the given ID in the users file and update their phone number
    QRegularExpression user_regex("ID: "+QString::number(user_id)+"\nFirst name: (.+)\nLast name: (.+)\nPhone number: (.+)\nEmail: (.+)\nAdress: (.+)\nBirth Date: (.+)\nUsername: (.+)\nPassword: (.+)\n-----------------------------------------\\n"  );
    QRegularExpressionMatch user_match = user_regex.match(users_contents);
    qDebug() << "Failed to find user with ID " << users_contents << " in file: " << "user.txt";


    if (!user_match.hasMatch()) {
        qDebug() << "Failed to find user with ID " << user_id << " in file: " << "user.txt";
        return;
    }
    int user_start = user_match.capturedStart();
    qDebug() << "Failed to find user with ID " << user_start << " in file: " << "user.txt";
    int user_length = user_match.capturedLength();
    qDebug() << "Failed to find user with ID " << user_length << " in file: " << "user.txt";
    QString user_string = user_match.captured(0);
    QRegularExpression phone_regex("Username: (.+)");
    qDebug() << "Failed to find user with ID " << user_string << " in file: " << "user.txt";

    QRegularExpressionMatch phone_match = phone_regex.match(user_string);
    if (!phone_match.hasMatch()) {
        qDebug() << "Failed to find Adress in user string: " << user_string;
        return;
    }
    int phone_start = phone_match.capturedStart();
    int phone_length = phone_match.capturedLength();
    users_contents.replace(user_start + phone_start, phone_length, "Username: " + username);

    // Write the updated contents back to the users file
    users_file.resize(0); // Clear the file before writing
    QTextStream users_out(&users_file);
    users_out << users_contents;
    users_file.close();

    // Update the user in the globalForum object
    user updated_user = globalForum.userSearch(user_id);
    if (updated_user.getId() == -1) {
        qDebug() << "Failed to find user with ID " << user_id << " in globalForum object";
        return;
    }
    updated_user.setUsername(username.toStdString());
    globalForum.displayAttributes();
    qDebug() <<globalForum.getUsers().size();
}


void Forum::on_pushButton_edit_password_clicked()
{
    // Get the new phone number from the line edit
    QString password = ui->lineEdit_edit_password->text();

    // Open the current user file
    QFile file("Current User.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contents = file.readAll();

    // Find the line with the phone number and update it
    QRegularExpression regex("Password: (.+)");
    QRegularExpressionMatch match = regex.match(contents);
    if (match.hasMatch()) {
        int start = match.capturedStart();
        int length = match.capturedLength();
        contents.replace(start, length, "Password: " + password);
    }

    // Write the updated contents back to the file
    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << contents;
    file.close();

    // Open the current user file
    QFile file1("Current User.txt");
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contentss = file1.readAll();

    // Get the user ID from the current user file
    QRegularExpression id_regex("ID: (\\d+)");
    QRegularExpressionMatch id_match = id_regex.match(contentss);
    if (!id_match.hasMatch()) {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
        return;
    }
    int user_id = id_match.captured(1).toInt();

    // Close the current user file
    file1.close();

    // Open the users file
    QFile users_file("user.txt");
    if (!users_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Read the contents of the users file into a QString
    QString users_contents = users_file.readAll();

    // Find the user with the given ID in the users file and update their phone number
    QRegularExpression user_regex("ID: "+QString::number(user_id)+"\nFirst name: (.+)\nLast name: (.+)\nPhone number: (.+)\nEmail: (.+)\nAdress: (.+)\nBirth Date: (.+)\nUsername: (.+)\nPassword: (.+)\n-----------------------------------------\\n"  );
    QRegularExpressionMatch user_match = user_regex.match(users_contents);
    qDebug() << "Failed to find user with ID " << users_contents << " in file: " << "user.txt";


    if (!user_match.hasMatch()) {
        qDebug() << "Failed to find user with ID " << user_id << " in file: " << "user.txt";
        return;
    }
    int user_start = user_match.capturedStart();
    qDebug() << "Failed to find user with ID " << user_start << " in file: " << "user.txt";
    int user_length = user_match.capturedLength();
    qDebug() << "Failed to find user with ID " << user_length << " in file: " << "user.txt";
    QString user_string = user_match.captured(0);
    QRegularExpression phone_regex("Password: (.+)");
    qDebug() << "Failed to find user with ID " << user_string << " in file: " << "user.txt";

    QRegularExpressionMatch phone_match = phone_regex.match(user_string);
    if (!phone_match.hasMatch()) {
        qDebug() << "Failed to find Adress in user string: " << user_string;
        return;
    }
    int phone_start = phone_match.capturedStart();
    int phone_length = phone_match.capturedLength();
    users_contents.replace(user_start + phone_start, phone_length, "Password: " + password);

    // Write the updated contents back to the users file
    users_file.resize(0); // Clear the file before writing
    QTextStream users_out(&users_file);
    users_out << users_contents;
    users_file.close();

    // Update the user in the globalForum object
    user updated_user = globalForum.userSearch(user_id);
    if (updated_user.getId() == -1) {
        qDebug() << "Failed to find user with ID " << user_id << " in globalForum object";
        return;
    }
    updated_user.setPassword(password.toStdString());
    globalForum.displayAttributes();
    qDebug() <<globalForum.getUsers().size();
}


void Forum::on_pushButton_delete_profile_clicked()
{

    // Open the current user file
    QFile file1("Current User.txt");
    if (!file1.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contentss = file1.readAll();

    // Get the user ID from the current user file
    QRegularExpression id_regex("ID: (\\d+)");
    QRegularExpressionMatch id_match = id_regex.match(contentss);
    if (!id_match.hasMatch()) {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
        return;
    }
    int user_id = id_match.captured(1).toInt();

    // Close the current user file
    file1.close();

    // Open the users file
    QFile users_file("user.txt");
    if (!users_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Read the contents of the users file into a QString
    QString users_contents = users_file.readAll();

    // Find the user with the given ID in the users file and update their phone number
    QRegularExpression user_regex("ID: "+QString::number(user_id)+"\nFirst name: (.+)\nLast name: (.+)\nPhone number: (.+)\nEmail: (.+)\nAdress: (.+)\nBirth Date: (.+)\nUsername: (.+)\nPassword: (.+)\n-----------------------------------------\\n"  );
    QRegularExpressionMatch user_match = user_regex.match(users_contents);
    qDebug() << "Failed to find user with ID " << users_contents << " in file: " << "user.txt";


    if (!user_match.hasMatch()) {
        qDebug() << "Failed to find user with ID " << user_id << " in file: " << "user.txt";
        return;
    }
    int user_start = user_match.capturedStart();

    int user_length = user_match.capturedLength();
    // Remove the matched user entry from the string
    users_contents.remove(user_start, user_length);

    // Close the users file
    users_file.close();

    // Reopen the users file in write mode and truncate it to clear its contents
    if (!users_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "user.txt";
        return;
    }

    // Write the updated string back to the file
    QTextStream out(&users_file);
    out << users_contents;

    // Close the users file
    users_file.close();

    // TODO: Delete the user's posts, replies, and topics from their respective files
    // Open the current user file
    QFile file("Current User.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << "Current User.txt";
        return;
    }

    // Read the contents of the file into a QString
    QString contents = file.readAll();

    // Get the user ID from the file using a regular expression
    QRegularExpression regex("ID: (\\d+)");
    QRegularExpressionMatch match = regex.match(contents);
    if (match.hasMatch()) {
        int user_id = match.captured(1).toInt();
        qDebug() << "User ID is " << user_id;
    } else {
        qDebug() << "Failed to find user ID in file: " << "Current User.txt";
    }

    // Close the file
    file.close();

    user updated_user = globalForum.userSearch(user_id);
    if (updated_user.getId() == -1) {
        qDebug() << "Failed to find user with ID " << user_id << " in globalForum object";
        return;
    }
    globalForum.userDelete(user_id);

    MainWindow *f = new MainWindow(this);
    close();
    f->show();
}


void Forum::on_pushButton_5_clicked()
{
    MainWindow *f = new MainWindow(this);
    close();
    f->show();
}

