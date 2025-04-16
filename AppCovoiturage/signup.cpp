#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);

    // Ajouter dynamiquement les rôles
    ui->RoleComboBox->addItem("Driver");
    ui->RoleComboBox->addItem("Passenger");
    ui->RoleComboBox->setCurrentIndex(-1); // Aucun rôle sélectionné par défaut

    // Masquer les boutons d’erreur au démarrage
    ui->btnFirstNameError->hide();
    ui->btnLastNameError->hide();
    ui->btnUsernameError->hide();
    ui->btnEmailError->hide();
    ui->btnPasswordError->hide();
    ui->btnConfirmPasswordError->hide();

    // Style des boutons d'erreur
    QList<QPushButton*> errorButtons = {
        ui->btnFirstNameError, ui->btnLastNameError, ui->btnUsernameError,
        ui->btnEmailError, ui->btnPasswordError, ui->btnConfirmPasswordError
    };

    for (auto btn : errorButtons) {
        btn->setFlat(true);
        btn->setStyleSheet("QPushButton { border: none; padding: 0px; }");
    }

    connect(ui->FinishSignupButton, &QPushButton::clicked, this, [=]() {
        QString firstName = ui->FirstNameEntry->text().trimmed();
        QString lastName = ui->LastNameEntry->text().trimmed();
        QString username = ui->UsernameEntry->text().trimmed();
        QString email = ui->EmailEntry->text().trimmed();
        QString password = ui->PasswordEntry->text();
        QString confirmPassword = ui->ConfirmPasswordEntry->text();
        QString selectedRole = ui->RoleComboBox->currentText();

        if (selectedRole.isEmpty()) {
            QMessageBox::warning(this, "Role Error", "❗ Please select a role.");
            return;
        }

        User newUser(firstName, lastName, username, email, password, selectedRole);
        QMap<QString, QString> ErrorMessages;

        for (auto btn : errorButtons) btn->hide();

        if (!validateInputs(newUser, confirmPassword, ErrorMessages)) {
            if (!ErrorMessages["Name"].isEmpty()) {
                ui->btnFirstNameError->show();
                ui->btnLastNameError->show();
            }
            if (!ErrorMessages["username"].isEmpty())
                ui->btnUsernameError->show();
            if (!ErrorMessages["email"].isEmpty())
                ui->btnEmailError->show();
            if (!ErrorMessages["password"].isEmpty())
                ui->btnPasswordError->show();
            if (!ErrorMessages["confirmPassword"].isEmpty())
                ui->btnConfirmPasswordError->show();
            if (ErrorMessages["EmptyFields"] != "false")
                QMessageBox::warning(this, "Input Error", ErrorMessages["EmptyFields"]);
            return;
        }

        newUser.SaveStateTrue();
        if (newUser.saveUserToDb()) {
            QMessageBox::information(this, "Success", "🎉 Sign-up Successful!");

            if (selectedRole == "Driver") {
                DriverHomePage* homePage = new DriverHomePage(&newUser);
                homePage->show();
            } else if (selectedRole == "Passenger") {
                PassengerHomePage* homePage = new PassengerHomePage(&newUser);
                homePage->show();
            }

            this->hide();
        } else {
            QMessageBox::warning(this, "Input Error", "There's a problem in SignUp.");
        }
    });

    // Redirection vers login
    connect(ui->SignInButton, &QPushButton::clicked, this, [=]() {
        LogIn *LogInWindow = new LogIn();
        LogInWindow->show();
        this->hide();
    });

    // Connexions pour les messages d’erreur au clic
    connect(ui->btnFirstNameError, &QPushButton::clicked, this, [=]() {
        QMessageBox::warning(this, "First Name Error", "❌ First and Last Name should only contain letters, hyphens, or apostrophes.");
    });
    connect(ui->btnLastNameError, &QPushButton::clicked, this, [=]() {
        QMessageBox::warning(this, "Last Name Error", "❌ First and Last Name should only contain letters, hyphens, or apostrophes.");
    });
    connect(ui->btnUsernameError, &QPushButton::clicked, this, [=]() {
        QMessageBox::warning(this, "Username Error", "🔹 Username must be at least 5 characters long or already used.");
    });
    connect(ui->btnEmailError, &QPushButton::clicked, this, [=]() {
        QMessageBox::warning(this, "Email Error", "📧 Please enter a valid email or use another one.");
    });
    connect(ui->btnPasswordError, &QPushButton::clicked, this, [=]() {
        QMessageBox::warning(this, "Password Error", "🔒 Password must be at least 8 characters, contain one uppercase letter and one number.");
    });
    connect(ui->btnConfirmPasswordError, &QPushButton::clicked, this, [=]() {
        QMessageBox::warning(this, "Confirm Password Error", "🔄 Passwords do not match!");
    });
}

SignUp::~SignUp()
{
    delete ui;
}

bool SignUp::validateInputs(User newuser, QString confirmPassword, QMap<QString, QString>& ErrorMessages){
    bool isPass = true;
    ErrorMessages["EmptyFields"] = "false";
    QString firstName = newuser.getFirstName();
    QString lastName = newuser.getLastName();
    QString username = newuser.getUsername();
    QString email = newuser.getEmail();
    QString password = newuser.getPassword();

    if (firstName.isEmpty() || lastName.isEmpty() || username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        ErrorMessages["EmptyFields"] = "⚠️ All fields must be filled!";
        return false;
    }

    if (!Checkers::NameIsValid(firstName.toStdString())) {
        ErrorMessages["Name"] = "❌ First and Last Name should only contain letters, hyphens, or apostrophes.";
        isPass = false;
    } else {
        ErrorMessages["Name"] = "";
    }

    if (username.length() < 5) {
        ErrorMessages["username"] = "🔹 Username must be at least 5 characters long.";
        isPass = false;
    } else {
        if (User::isUsernameUsed(username)) {
            ErrorMessages["username"] = "🔹 This Username is already used.";
            isPass = false;
        } else {
            ErrorMessages["username"] = "";
        }
    }

    if (!Checkers::EmailIsValid(email.toStdString())) {
        ErrorMessages["email"] = "📧 Please enter a valid email (e.g., example@domain.com).";
        isPass = false;
    } else {
        if (User::isEmailUsed(email)) {
            ErrorMessages["email"] = "📧 This Email is already used.";
            isPass = false;
        } else {
            ErrorMessages["email"] = "";
        }
    }

    if (!Checkers::PasswordIsValid(newuser, password.toStdString())) {
        ErrorMessages["password"] = "🔒 Password must be at least 8 characters, contain one uppercase letter and one number.";
        isPass = false;
    } else {
        ErrorMessages["password"] = "";
        if (password != confirmPassword) {
            ErrorMessages["confirmPassword"] = "🔄 Passwords do not match!";
            isPass = false;
        } else {
            ErrorMessages["confirmPassword"] = "";
        }
    }

    return isPass;
}
