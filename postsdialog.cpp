#include "postsdialog.h"
#include "ui_postsdialog.h"
#include "Globals.h"
#include <QFile>
#include "postandrepliesdialog.h"
PostsDialog::PostsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostsDialog)
{
    ui->setupUi(this);
    ui->label_3->setText(globalForum.topicResearch(globalForum.getSelectedTopic()).getTopicTitle());
    QString postTitle;
    QString postContent;
    QString date;
    QString username;
    int postId;
    QFile file2("posts.txt");
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file2);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList list = line.split(": ");
            if (list[0] == "Post Title") {
                postTitle  = list[1];
            }
            else if (list[0] == "Post creator username "){
                username=list[1];
            }
            else if (list[0] == "Date of the creation of the Topic "){
                date=list[1];
            }
            else if (list[0] == "Post Content"){
                postContent=list[1];

            }
            else if(list[0] == "Post id"){
                postId=list[1].toInt();
            }
            else if (list[0]=="Topic id"){
                if(list[1].toInt()==(globalForum.topicResearch(globalForum.getSelectedTopic()).getIdTopic())){
                    Post post;
                    post.setIdPost(postId);
                    post.setIdTopic(globalForum.getSelectedTopic());
                    post.setPostContent(postContent);
                    post.setPostTitle(postTitle);
                    post.setPostUsernameCreator(username.toStdString());
                    for(int i=0;i<globalForum.getTopics().size();i++)
                    {
                        if(globalForum.getTopics()[i].getIdTopic()==globalForum.getSelectedTopic())
                        {
                            globalForum.addPostForum(post,i);
                            globalForum.getTopics()[i].displayAttributesOfPosts();
                        }
                    }
                    ui->listWidget->addItem(postTitle+"\n"+postContent+"\n"+"Posted by "+username+" on "+date);
                }
            }





        }
        file2.close();


    }

    else {
        qDebug() << "Failed to open file: posts.txt";
    }
}

PostsDialog::~PostsDialog()
{
    delete ui;
}

void PostsDialog::on_pushButton_clicked()
{
    int j = globalForum.getSelectedTopic();
    Topic topic = globalForum.topicResearch(j);
    QString postTitle = ui->lineEdit->text();
    QString postContent=ui->textEdit->toPlainText();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    Post post(globalForum.getCurrentUsername(),currentDateTime,postContent,postTitle);
    qDebug()<<postTitle;
    qDebug()<<postContent;
    int k;
    post.setIdTopic(topic.getIdTopic());
    for(int i=0;i<globalForum.getTopics().size();i++){
        if(topic.getTopicTitle()==globalForum.getTopics()[i].getTopicTitle())
        {
            k=i;
            qDebug()<<post.getPostTitle();
            qDebug()<<post.getPostContent();
            globalForum.addPostForum(post,i);


        }
    }
    ui->listWidget->addItem(postTitle + "\n" + postContent + "\n" + "Posted by " + QString::fromStdString(globalForum.getCurrentUsername()) + " on " + currentDateTime.toString());
    globalForum.getTopics()[k].savePostFile(post);
}


void PostsDialog::on_pushButton_3_clicked()
{
    int index = ui->listWidget->currentRow();

    if (index < 0) {
        return;
    }


    QFile file("posts.txt");
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
        if (lines[i].startsWith("Post Title: " + title)) {
            lines.remove(i, 7);
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
    int j = globalForum.getSelectedTopic();
    Topic topic = globalForum.topicResearch(j);
    for(int i=0;i<globalForum.getTopics().size();i++){
        if(topic.getTopicTitle()==globalForum.getTopics()[i].getTopicTitle())
        {
            globalForum.getTopics()[i].deletePost(i);
        }
    }
}

void PostsDialog::on_listWidget_currentRowChanged(int currentRow)
{
    itemSelected=currentRow;
}


void PostsDialog::on_pushButton_4_clicked()
{
    QString itemName = ui->listWidget->currentItem()->text();
    QStringList list = itemName.split("\n");
    QString title =list[0];
    globalForum.setIdSelectedPost(globalForum.serachPostByTitle(title).getIdPost());
    postandrepliesDialog *par = new postandrepliesDialog(this);
    par->show();
}

