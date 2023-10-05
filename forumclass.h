
#ifndef FORUMCLASS_H
#define FORUMCLASS_H
#include <string>
#include <vector>
#include "post.h"
#include "reply.h"
#include "topic.h"
#include "user.h"
#include "author.h"
#include <iostream>
#include <QFile>

using namespace std;


class ForumClass
{
private :
    string internetAdress;
    string email;
    vector <Topic> topics;
    vector <user> users;
    vector <author> authors;
    int idSelectedTopic;
    int idSelectedPost;

public:
    ForumClass(string ia,string e);
    vector <Topic> getTopics(){return topics;}
    void setIdSelectedTopic(int id){idSelectedTopic=id;}
    int getSelectedTopic(){return idSelectedTopic;}
    void setIdSelectedPost(int id){idSelectedPost=id;}
    int getSelectedPost(){return idSelectedPost;}
    string getCurrentUsername();
    void topicAdd(QString topicTitle);
    void topicDelete(int id);
    Topic topicResearch(int id);
    Topic researchTopicByTitle(QString title);
    void useradd(vector<user> updatedUsers)
    {
        users = updatedUsers;
    }
    vector<user> getUsers() const {
        return users;
    }

    void userDelete(int id) {
        // Find the user with the given ID
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->getId() == id) {
                // Remove the user from the vector
                users.erase(it);
                return;
            }
        }
        cout << "Error: user with ID " << id << " not found!" << endl;
    }


    user userSearch(int id) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getId() == id) {
                return users[i];
            }
        }
        return user();

    }

    void authorAdd();
    void authorDelete();
    author authorSearch();
    void displayAttributes() {
        cout << "Internet Address: " << internetAdress << endl;
        cout << "Email: " << email << endl;



        cout << "Users:" << endl;
        for (int i = 0; i < users.size(); i++) {
            cout << "  " << i+1 << ". " << users[i].getId() << ", " << users[i].getFirstName() << " " << users[i].getLastName() << ", " << users[i].getEmail() << endl;
        }


    }
    void addTopic(Topic topic){
        topics.push_back(topic);
    }
    void displayAttributesOfTopic() {
        cout << "Internet Address: " << internetAdress << endl;
        cout << "Email: " << email << endl;



        cout << "Topics:" << endl;
        for (int i = 0; i < topics.size(); i++) {
            cout << "  " << i+1 << ". " << topics[i].getIdTopic() << ", "
                 << topics[i].getTopicCreatorUsername().toStdString() << " "
                 << topics[i].getTopicDateTime().toString().toStdString() << ", "
                 << topics[i].getTopicTitle().toStdString() << endl;

        }


    }
    void addPostForum(Post post,int i)
    {
        topics[i].addPostEasy(post);

    }
    Post serachPostByTitle(QString title)
    {
        for(int i=0;i<topics.size();i++)
        {
            for(int j;j<topics[i].getTopicPosts().size();j++){
                if (topics[i].getTopicPosts()[j].getPostTitle()==title)
                {
                    return topics[i].getTopicPosts()[j];
                }
            }
        }

    }
    void savePostFilePost(Post post){
        QFile file1("posts.txt");
        if (file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file1);

            out << "Post Title: " << post.getPostTitle() << "\n";
            out << "Post creator username : " << QString::fromStdString(post.getPostCreatorUsername()) << "\n";
            out << "Date of the creation of the Topic : "  << post.getPostDate().toString() << "\n";
            out << "Post Content: " << post.getPostContent() << "\n";
            out << "Post id: " << post.getIdPost() << "\n";
            out << "Topic id: "<<post.getIdTopic()<<"\n";
            out << "---------------------------------------------------------------------------------\n";
            file1.close();
            qDebug() << "Les informations ont été enregistrées dans le fichier.";

            }

        else {
            qDebug() << "Impossible d'ouvrir le fichier.";
        }
    }



};

#endif // FORUMCLASS_H

