
#include "mainwindow.h"
#include "Globals.h"
#include <QApplication>
#include "forumclass.h"
using namespace std;
ForumClass globalForum("example.com", "example@example.com");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
