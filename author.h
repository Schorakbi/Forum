
#ifndef AUTHOR_H
#define AUTHOR_H

#include "user.h"



class author : public user
{
    int numberOfPosts;
    QDate dateOfFirstPost;
    QDate dateOfLastPost;
    int numberOfReplies;
    QDate dateOfFirstReply;
    QDate dateOfLastReply;
public:
    author(string fn, string ln,int pn,string e,string ad,QDate bd, string us,string pa);
};

#endif // AUTHOR_H
