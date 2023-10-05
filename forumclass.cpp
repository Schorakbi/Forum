
#include "forumclass.h"
#include <QDate>
#include <QFile>
#include <QString>
#include "Globals.h"
using namespace std;
ForumClass::ForumClass(string ia,string e)
{
    internetAdress = ia;
    email=e;    
    topics={};
    users={};
    authors={};
    idSelectedTopic=-1;
}
string ForumClass::getCurrentUsername()
{
    string currentUsername;
    QFile file("Current User.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList list = line.split(": ");
            if (list[0] == "Username") {
                currentUsername = list[1].toStdString();
                file.close();
            }
        }
    }
    return currentUsername;
}
void ForumClass::topicAdd(QString topicTitle){
    Topic topic(QDateTime::currentDateTime(),topicTitle,QString::fromStdString(globalForum.getCurrentUsername()));
    topics.push_back(topic);

}
void ForumClass::topicDelete(int id){
    // Find the user with the given ID
    for (auto it = topics.begin(); it != topics.end(); ++it) {
        if (it->getIdTopic() == id) {
            // Remove the user from the vector
            topics.erase(it);
            return;
        }
    }
    cout << "Error: user with ID " << id << " not found!" << endl;
}
Topic ForumClass::topicResearch(int id){
    Topic topic;
    for (int i=0;i<topics.size();i++)
    {
        if(topics[i].getIdTopic()==id)
        {
            topic.setTopicCreatorUsername(topics[i].getTopicCreatorUsername());
            topic.setTopicDateTime(topics[i].getTopicDateTime());
            topic.setTopicId(topics[i].getIdTopic());
            topic.setTopicPosts(topics[i].getTopicPosts());
            topic.setTopicTitle(topics[i].getTopicTitle());
        }
    }
    return topic;

}
Topic ForumClass::researchTopicByTitle(QString title){
    Topic topic;
    for (int i=0;i<topics.size();i++)
    {
        if(topics[i].getTopicTitle()==title)
        {
            topic.setTopicCreatorUsername(topics[i].getTopicCreatorUsername());
            topic.setTopicDateTime(topics[i].getTopicDateTime());
            topic.setTopicId(topics[i].getIdTopic());
            topic.setTopicPosts(topics[i].getTopicPosts());
            topic.setTopicTitle(topics[i].getTopicTitle());
        }
    }
    return topic;
}


