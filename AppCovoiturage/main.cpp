#include "start.h"
#include "login.h"
#include "signup.h"
#include "databasemanager.h"
#include <QApplication>{
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
DataBaseManager::openDatabase();
    start w;
    w.show();
    return a.exec();
}
