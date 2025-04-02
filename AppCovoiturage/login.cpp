#include "login.h"
#include "ui_login.h"


bool CheckSignIn(QString username, QString password, User &user) {
    if (User::isUsernameUsed(username)) {
        user = User::getUserByUsername(username);
        if (user.getPassword() == encryption::encrypt(password)) {
            return true;
        }
    }
    return false;
}

LogIn::LogIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    connect(ui->LoginButton, &QPushButton::clicked, this, [=]() {
        QString Username = ui->UsernameEntry->text().trimmed();
        QString Password = ui->PasswordEntry->text().trimmed();
        User user("", "", "", "", "", "",false);
        if(CheckSignIn(Username,Password,user)){
            if(user.getRole() == "Passenger"){
                PassengerHomePage* homePage = new PassengerHomePage();
                homePage->show();
                this->hide();
            }else if(user.getRole() == "Driver"){
                DriverHomePage* homePage = new DriverHomePage(&user);
                homePage->show();
                this->hide();

            }

        }else{

            QMessageBox::warning(this, "Input Error", "Username Or The Password  Are Incorrect");
            return;
        }
    });
}

LogIn::~LogIn()
{
    delete ui;
}
