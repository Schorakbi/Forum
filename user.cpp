#include <set>
#include <random>
#include "user.h"
user::user() : id(0), firstName(""), lastName(""), phoneNumber(0), email(""), adress(""), birthDate(QDate()), username(""), password("")
{
    // Constructor body
}

user::user(string fn, string ln,int pn,string e,string ad,QDate bd, string us,string pa)
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution <int> dis(1,1000000);
    do {
        id = dis(gen);
    } while (assignedIds.count(id) > 0);
    assignedIds.insert(id);
    firstName=fn;
    lastName=ln;
    phoneNumber=pn;
    email=e;
    adress = ad;
    birthDate=bd;
    username = us;
    password = pa;

}
unordered_set<int> user::assignedIds;
