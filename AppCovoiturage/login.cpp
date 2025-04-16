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

    // 🔒 Masquer le mot de passe au démarrage
    ui->PasswordEntry->setEchoMode(QLineEdit::Password);

    // Affichage/Masquage du mot de passe
    connect(ui->showpass, &QPushButton::clicked, this, [=]() {
        if (ui->PasswordEntry->echoMode() == QLineEdit::Password) {
            ui->PasswordEntry->setEchoMode(QLineEdit::Normal);
        } else {
            ui->PasswordEntry->setEchoMode(QLineEdit::Password);
        }
    });

    // Connexion bouton Login
    connect(ui->LoginButton, &QPushButton::clicked, this, [=]() {
        QString Username = ui->UsernameEntry->text().trimmed();
        QString Password = ui->PasswordEntry->text().trimmed();

        // Vérification des champs vides
        if (Username.isEmpty() || Password.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in both username and password.");
            return;
        }

        User user("", "", "", "", "", "", false);
        if (CheckSignIn(Username, Password, user)) {
            if (user.getRole() == "Passenger") {
                PassengerHomePage* homePage = new PassengerHomePage(&user);
                homePage->show();
                this->hide();
            } else if (user.getRole() == "Driver") {
                DriverHomePage* homePage = new DriverHomePage(&user);
                homePage->show();
                this->hide();
            }
        } else {
            QMessageBox::warning(this, "Login Failed", "Username or password is incorrect.");
        }
    });

    // Connexion bouton Sign Up
    connect(ui->SignUpButton, &QPushButton::clicked, this, [=]() {
        SignUp* SignUpPage = new SignUp();
        SignUpPage->show();
        this->hide();
    });
}


LogIn::~LogIn() {
    delete ui;
}
