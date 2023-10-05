
#include "post.h"
#include <QFile>
Post::Post(string pcu,QDateTime pd,QString pc,QString pt)
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution <int> dis(1,1000000);
    do {
        idPost = dis(gen);
    } while (assignedIds.count(idPost) > 0);
    assignedIds.insert(idPost);
    postCreatorUsername=pcu;
    postDate=pd;
    postContent = pc;
    postTitle=pt;
    replies={};
}
unordered_set<int> Post::assignedIds;
void Post::replyAdd(Reply reply){
        replies.push_back(reply);
}
void Post::replyDelete(int id){
        int i = (*this).findReplyIndex(id);
        if(i!=-1){
        replies.erase(replies.begin()+i);
        }
}
int Post::findReplyIndex(int id)
{
        int j=-1;
        for(int i=0;i<replies.size();i++)
        {
        if (replies[i].getIdReply()==id)
            j=i;
        }
        return j;
}
Reply Post::replySearch(int id){
        int j = (*this).findReplyIndex(id);
        return (replies[j]);
}
void Post::updateReply(string content,Reply reply){
        reply.setReplyContent(content);
}
void Post::SaveRepliesFile(Reply reply){
        QFile file1("replies.txt");
        if (file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file1);



                out << "Reply Content: " << QString::fromStdString(reply.getReplyContent()) << "\n";
                out << "Reply creator username : " << QString::fromStdString(reply.getReplyCreatorUsernamme()) << "\n";
                out << "Date of the creation of the Reply : "  << reply.getDateOfReply().toString() << "\n";
                out << "Post id: " << reply.getIdPost() << "\n";
                out << "Reply id: " << reply.getIdReply() << "\n";
                out << "---------------------------------------------------------------------------------\n";
                file1.close();
                qDebug() << "Les informations ont été enregistrées dans le fichier.";

        }
        else {
        qDebug() << "Impossible d'ouvrir le fichier.";
        }

}
