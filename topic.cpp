
#include "topic.h"
#include "Globals.h"
#include <QDate>
#include <QFile>
#include <QString>
Topic::Topic()
{
    idTopic=0;
    topicCreatorUsername="";
    topicDateTime = QDateTime::currentDateTime();
    topicTitle="";

}
Topic::Topic(QDateTime td,QString tt,QString tcu)
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution <int> dis(1,1000000);
    do {
        idTopic = dis(gen);
    } while (assignedIds.count(idTopic) > 0);
    assignedIds.insert(idTopic);
    topicDateTime=td;
    topicTitle=tt;
    topicCreatorUsername=tcu;
}
unordered_set<int> Topic::assignedIds;
void Topic::addPost(QString title,QString content){
    string currentUsername=globalForum.getCurrentUsername();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    Post p(currentUsername,currentDateTime,content,title);
    posts.push_back(p);
}
int Topic::findPostIndex(int id)
{
    int j=-1;
    for(int i=0;i<posts.size();i++)
    {
        if (posts[i].getIdPost()==id)
            j=i;
    }
    return j;
}
void Topic::deletePost(int id){
    int i = (*this).findPostIndex(id);
    if(i!=-1){
        posts.erase(posts.begin()+i);
    }
}
void Topic::savePostFile(Post post){
    QFile file1("posts.txt");
    if (file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file1);
        if(posts.size()==0) {
            qDebug() << "Veuillez remplir tous les champs.";}
        else{


                out << "Post Title: " << post.getPostTitle() << "\n";
                out << "Post creator username : " << QString::fromStdString(post.getPostCreatorUsername()) << "\n";
                out << "Date of the creation of the Topic : "  << post.getPostDate().toString() << "\n";
                out << "Post Content: " << post.getPostContent() << "\n";
                out << "Post id: " << post.getIdPost() << "\n";
                out << "Topic id: "<<globalForum.getSelectedTopic()<<"\n";
                out << "---------------------------------------------------------------------------------\n";
                file1.close();
                qDebug() << "Les informations ont été enregistrées dans le fichier.";


        }
    }
    else {
        qDebug() << "Impossible d'ouvrir le fichier.";
    }
}
void Topic::postUpdate(Post * post,QString title,QString content){
    post->setPostContent(content);
    post->setPostTitle(title);
}
