#include "postandrepliesdialog.h"
#include "ui_postandrepliesdialog.h"
#include "post.h"
#include "Globals.h"
#include "reply.h"
#include <QString>
#include <QVBoxLayout>
postandrepliesDialog::postandrepliesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postandrepliesDialog)
{
    ui->setupUi(this);
    Topic topic = globalForum.topicResearch(globalForum.getSelectedTopic());
    int k = topic.findPostIndex(globalForum.getSelectedPost());
    Post post = topic.getTopicPosts()[k];
    if(post.getIdPost()==globalForum.getSelectedPost())
    {

        qDebug()<<post.getPostTitle();
        qDebug()<<post.getPostContent();
        ui->label->setText(post.getPostTitle());
        ui->label_2->setText(post.getPostContent());
    }
    QDateTime date = QDateTime::currentDateTime();
    QString replyContent = ui->textEdit->toPlainText();
    QFile file2("replies.txt");
    QString replyContent1;
    QString replyCreatorUsername;
    QString dateOfReply;
    int idPost;
    int idReply;
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file2);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList list = line.split(": ");
            if (list[0] == "Reply Content") {
                replyContent1=list[1];
            }
            else if (list[0] == "Reply creator username "){
                replyCreatorUsername=list[1];
            }
            else if (list[0] == "Date of the creation of the Reply "){
                dateOfReply=list[1];
            }
            else if (list[0] == "Post id"){
                idPost=list[1].toInt();

            }
            else if(list[0] == "Reply id"){
                idReply=list[1].toInt();
                if(idPost==post.getIdPost()){
                    Reply reply;
                    reply.setIdPost(idPost);
                    reply.setIdReply(globalForum.getSelectedTopic());
                    reply.setReplyContent(replyContent1.toStdString());
                    reply.setReplyCreatorUsername(replyCreatorUsername.toStdString());
                    reply.setDateOfReply(QDateTime::fromString(dateOfReply));
                    // Create the QLabel to display the reply content
                    QLabel* replyLabel = new QLabel(QString::fromStdString(reply.getReplyContent()), this);

                    // Create the QLabel for username and date
                    QLabel* userInfoLabel = new QLabel(this);
                    QString userInfoText =QString::fromStdString(reply.getReplyCreatorUsernamme()) + " - " + reply.getDateOfReply().toString();
                    userInfoLabel->setText(userInfoText);

                    // Create the QHBoxLayout to hold the username and date QLabel
                    QHBoxLayout* userInfoLayout = new QHBoxLayout();
                    userInfoLayout->addWidget(userInfoLabel);
                    userInfoLayout->addStretch(); // Add space at the end

                    // Create the QVBoxLayout for the reply layout
                    QVBoxLayout* replyLayout = new QVBoxLayout();
                    replyLayout->addLayout(userInfoLayout);
                    replyLayout->addWidget(replyLabel);

                    // Add the reply layout to the main layout of your dialog (assuming it's called mainLayout)
                    ui->verticalLayout->addLayout(replyLayout);
                }
            }


            }



}
}


postandrepliesDialog::~postandrepliesDialog()
{
    delete ui;
}


void postandrepliesDialog::on_pushButton_clicked()
{
    QDateTime date = QDateTime::currentDateTime();
    QString replyContent = ui->textEdit->toPlainText();
    Topic topic = globalForum.topicResearch(globalForum.getSelectedTopic());
    Post post = topic.searchPost(globalForum.getSelectedPost());

    Reply reply(date, globalForum.getCurrentUsername(), replyContent.toStdString());
    reply.setIdPost(post.getIdPost());
    post.SaveRepliesFile(reply);

    // Create the QLabel to display the reply content
    QLabel* replyLabel = new QLabel(replyContent, this);

    // Create the QLabel for username and date
    QLabel* userInfoLabel = new QLabel(this);
    QString userInfoText =QString::fromStdString(globalForum.getCurrentUsername()) + " - " + date.toString();
    userInfoLabel->setText(userInfoText);

    // Create the QHBoxLayout to hold the username and date QLabel
    QHBoxLayout* userInfoLayout = new QHBoxLayout();
    userInfoLayout->addWidget(userInfoLabel);
    userInfoLayout->addStretch(); // Add space at the end

    // Create the QVBoxLayout for the reply layout
    QVBoxLayout* replyLayout = new QVBoxLayout();
    replyLayout->addLayout(userInfoLayout);
    replyLayout->addWidget(replyLabel);

    // Add the reply layout to the main layout of your dialog (assuming it's called mainLayout)
    ui->verticalLayout->addLayout(replyLayout);
}



