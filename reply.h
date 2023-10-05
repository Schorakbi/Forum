
#ifndef REPLY_H
#define REPLY_H
#include <QDate>
#include <string>
#include <vector>
#include <random>
#include <set>
#include <unordered_set>
using namespace std;

class Reply
{
    int idReply;
    int idPost;
    QDateTime dateOfReply;
    string replyCreatorUsernamne;
    string replyContent;
    static unordered_set <int> assignedIds;
public:
    Reply(QDateTime dor,string rcu,string rc);
    int getIdReply(){return idReply;}
    int getIdPost(){return idPost;}
    QDateTime getDateOfReply(){return dateOfReply;}
    string getReplyCreatorUsernamme(){return replyCreatorUsernamne;}
    string getReplyContent(){return replyContent;}
    void setIdReply(int id){idReply=id;}
    void setIdPost(int id){idPost=id;}
    void setDateOfReply(QDateTime id){dateOfReply=id;}
    void setReplyCreatorUsername(string id){replyCreatorUsernamne=id;}
    void setReplyContent(string id){replyContent=id;}
    Reply(){
        idReply=0;
        idPost=0;
        dateOfReply=QDateTime::currentDateTime();
        replyCreatorUsernamne="";
        replyContent="";
    }
};

#endif // REPLY_H
