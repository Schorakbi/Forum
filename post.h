
#ifndef POST_H
#define POST_H
#include <QDate>
#include <string>
using namespace std;
#include <vector>
#include <random>
#include <set>
#include <unordered_set>
#include "reply.h"


class Post
{
    int idPost;
    int idTopic;
    QString postTitle;
    string postCreatorUsername;
    QDateTime postDate;
    QString postContent;
    vector <Reply> replies;
    static unordered_set <int> assignedIds;
public:
    Post(string pcu,QDateTime pd,QString pc,QString pt);
    int getIdPost(){return idPost;}
    QString getPostTitle(){return postTitle;}
    string getPostCreatorUsername(){return postCreatorUsername;}
    QDateTime getPostDate(){return postDate;}
    QString getPostContent(){return postContent;}
    vector <Reply> getReplies(){return replies;}
    Post(){
        idPost = 0;
        idTopic = 0;
        postTitle="";
        postCreatorUsername="";
        postDate=QDateTime::currentDateTime();
        postContent="";
        replies = {};
    }
    void setIdTopic(int id){idTopic=id;}
    void setPostTitle(QString title){postTitle=title;}
    void setPostContent(QString content){postContent=content;}
    void setIdPost(int id){idPost=id;}
    void setPostUsernameCreator(string pcu){postCreatorUsername=pcu;}
    void setPostDate(QDateTime pd){postDate=pd;}
    int getIdTopic(){return idTopic;}
    void replyAdd(Reply reply);
    void replyDelete(int id);
    Reply replySearch(int id);
    void updateReply(string content,Reply reply);
    void SaveRepliesFile(Reply reply);
    int findReplyIndex(int id);
};

#endif // POST_H
