
#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
#include <QDate>
#include <unordered_set>

class user
{
    int id ;
    string firstName;
    string lastName;
    int phoneNumber;
    string email;
    string adress;
    QDate birthDate;
    string username;
    string password;

    static unordered_set <int> assignedIds;
public:
    user();
    user(string fn, string ln,int pn,string e,string ad,QDate bd, string us,string pa);
    int getId(){return id;}
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    int getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    string getAdress() const { return adress; }
    QDate getBirthDate() const { return birthDate; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    void setPhoneNumber(int newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }
    void setEmail(string newEmail) {
        email = newEmail;
    }

    void setAdress(string newAdress) {
        adress = newAdress;
    }

    void setBirthDate(QDate newBirthDate) {
        birthDate = newBirthDate;
    }

    void setUsername(string newUsername) {
        username = newUsername;
    }

    void setPassword(string newPassword) {
        password = newPassword;
    }
};

#endif // USER_H
