#include "signup.h"
#include "ui_signup.h"

bool SignUp::validateInputs(User newuser, QString confirmPassword, QMap<QString, QString>& ErrorMessages){
    bool isPass = true;
    ErrorMessages["EmptyFields"] = "false";
    QString firstName = newuser.getFirstName();
    QString lastName = newuser.getLastName();
    QString username = newuser.getUsername();
    QString email = newuser.getEmail();
    QString password = newuser.getPassword();


    if (firstName.isEmpty() || lastName.isEmpty() || username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        ErrorMessages["EmptyFields"] = "⚠️ All fields must be filled!\n";
        return false;
    }

    if (!Checkers::NameIsValid(firstName.toStdString())) {
        ErrorMessages["Name"] = "❌ First And Last Name Should only contain letters, hyphens, or apostrophes.\n";
        isPass = false;
    }else{
        ErrorMessages["Name"] = "false";
    }

    if (username.length() < 5) {
        ErrorMessages["username"]= "🔹 Username must be at least 5 characters long.\n";
        isPass = false;
    }else{
        if(User::isUsernameUsed(username)){
            ErrorMessages["username"] = "🔹This Username Already Used.\n";
            isPass = false;
        }else{
            ErrorMessages["username"] = "false";
        }
    }

    if (!Checkers::EmailIsValid(email.toStdString())) {
        ErrorMessages["email"] = "📧 Please enter a valid email (e.g., example@domain.com).\n";
        isPass = false;
    }else{
        if(User::isEmailUsed(email)){
            ErrorMessages["email"] = "📧 This Email Already In used.\n";
            isPass = false;
        }else{
            ErrorMessages["email"] = "false";
        }
    }

    if (!Checkers::PasswordIsValid(newuser, password.toStdString())) {
        ErrorMessages["password"] = "🔒 Password must be at least 8 characters, contain one uppercase letter and one number.\n";
        isPass = false;
    }else{
        ErrorMessages["password"] = "false";
        if(password != confirmPassword){
            ErrorMessages["confirmPassword"] = "🔄 Passwords do not match!\n";
            isPass = false;
        }else{
            ErrorMessages["confirmPassword"] = "false";
        }
    }

    return isPass;
}

SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);

    connect(ui->FinishSignupButton, &QPushButton::clicked, this, [=]() {
        QString firstName = ui->FirstNameEntry->text().trimmed();
        QString lastName = ui->LastNameEntry->text().trimmed();
        QString username = ui->UsernameEntry->text().trimmed();
        QString email = ui->EmailEntry->text().trimmed();
        QString password = ui->PasswordEntry->text();
        QString confirmPassword = ui->ConfirmPasswordEntry->text();

        User newUser(firstName, lastName, username, email, password, "Passenger");
        QMap<QString, QString> ErrorMessages;
        if (!validateInputs(newUser, confirmPassword, ErrorMessages)) {
            QString allErrors;
            for (const auto &error : ErrorMessages) {
                if (error != "false") {
                    allErrors += error;
                }
            }
            QMessageBox::warning(this, "Input Error", allErrors);
            return;
        }
        newUser.SaveStateTrue();
        if(newUser.saveUserToDb()){
            start *startWindow = new start();
            QMessageBox::information(this, "Success", "🎉 Sign-up Successful!");
            startWindow->show();
            this->hide();
        }else{
            QMessageBox::warning(this, "Input Error", "Ther's Problem In SignUp");
        }
    });

    connect(ui->SignInButton, &QPushButton::clicked, this, [=]() {
        LogIn *LogInWindow = new LogIn();
        LogInWindow->show();
        this->hide();
    });
}

SignUp::~SignUp()
{
    delete ui;
}
