
#ifndef TOPIC_H
#define TOPIC_H
#include <QDate>
#include <string>
using namespace std;
#include <vector>
#include "post.h"
#include <random>
#include <set>
#include <unordered_set>
#include <iostream>
class Topic
{
    int idTopic;
    QDateTime topicDateTime;
    QString topicTitle;
    QString topicCreatorUsername;
    vector <Post> posts;
    static unordered_set <int> assignedIds;
    int currentPostId;


public:
    int getIdTopic(){return idTopic;}
    QDateTime getTopicDateTime(){return topicDateTime;}
    QString getTopicTitle(){return topicTitle;}
    QString getTopicCreatorUsername(){return topicCreatorUsername;}
    vector <Post> getTopicPosts(){return posts;}
    void setTopicTitle(QString title){topicTitle=title;}
    void setTopicDateTime(QDateTime date){topicDateTime=date;}
    void setTopicId(int id){idTopic=id;}
    void setTopicCreatorUsername(QString username){topicCreatorUsername=username;}
    void setTopicPosts(vector <Post> vector){posts=vector;}
    int getCurrentPostId(){return currentPostId;}
    void setCurrentPostId(int id){currentPostId=id;}
    Topic(QDateTime td,QString tt,QString tcu);
    Topic();
    void addPost(QString title,QString content);
    int findPostIndex(int id);
    void deletePost(int index);
    void savePostFile(Post post);
    void postUpdate(Post * post,QString title,QString content);
    void displayAttributesOfPosts()
    {
        cout << "Id: " << idTopic << endl;
        cout << "Date: " << topicDateTime.toString().toStdString() << endl;
        cout << "Title: " << topicTitle.toStdString() << endl;
        cout << "Topic creator username: " << topicCreatorUsername.toStdString() << endl;

        cout << "Posts:" << endl;
        for (int i = 0; i < posts.size(); i++) {
            cout << "  " << i+1 << ". " << idTopic << ", "
                 << posts[i].getIdPost() << " "
                 << posts[i].getPostTitle().toStdString() << ", "
                 << posts[i].getPostDate().toString().toStdString() << endl
                 << "   Creator: " << posts[i].getPostCreatorUsername() << endl
                 << "   Content: " << posts[i].getPostContent().toStdString() << endl;
        }
    }
    void addPostEasy(Post post)
    {
        posts.push_back(post);

    }
    Post searchPost(int id){
        return(posts[(*this).findPostIndex(id)]);

    }


};

#endif // TOPIC_H
