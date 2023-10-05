
#include "author.h"

author::author(string fn, string ln,int pn,string e,string ad,QDate bd, string us,string pa):user(fn, ln,pn,e,ad,bd,us,pa)
{
    dateOfFirstPost=QDate();
    numberOfPosts=0;
    dateOfFirstReply=QDate();
    dateOfLastReply=QDate();
    numberOfReplies=0;
}

