
#include "reply.h"

Reply::Reply(QDateTime dor,string rcu,string rc)
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution <int> dis(1,1000000);
    do {
        idReply = dis(gen);
    } while (assignedIds.count(idPost) > 0);
    assignedIds.insert(idReply);
    dateOfReply=dor;
    replyCreatorUsernamne=rcu;
    replyContent = rc;
}
unordered_set<int> Reply::assignedIds;
