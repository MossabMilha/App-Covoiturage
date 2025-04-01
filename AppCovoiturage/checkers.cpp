#include "checkers.h"

bool Checkers::NameIsValid(const std::string& name){
    // Convert std::string to QString
    QString qName = QString::fromStdString(name);

    // Create QRegularExpression instance
    QRegularExpression nameRegex("^[A-Za-z'-]+$");

    // Perform regex match
    if (nameRegex.match(qName).hasMatch()) {
        return true;
    }

    return false;
}


bool Checkers::EmailIsValid(const std::string& email) {

    std::regex emailRegex("^[A-Za-z0-9_.+-]+@[A-Za-z]+\\.[A-Za-z-.]+$");


    if (std::regex_match(email, emailRegex)) {

        size_t atPos = email.find('@');
        size_t dotPos = email.find('.', atPos);


        if (atPos == 0 || atPos == email.length() - 1 || dotPos == email.length() - 1) {
            return false;
        }


        std::string domain = email.substr(atPos + 1);
        for (char ch : domain) {
            if (ch == ' ' || (!isalnum(ch) && ch != '-' && ch != '.')) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool Checkers::PasswordIsValid(const User& newUser,const std::string& Password){

    QRegularExpression upperCaseRegex("[A-Z]");
    QRegularExpression lowerCaseRegex("[a-z]");
    QRegularExpression specialCharRegex("[^A-Za-z0-9]");
    QRegularExpression numberRegex("[0-9]");


    QString password = QString::fromStdString(Password);


    if (password.length() <= 8) {
        return false;
    }

    // Check for at least one uppercase letter
    if (!upperCaseRegex.match(password).hasMatch()) {
        return false;
    }

    // Check for at least one lowercase letter
    if (!lowerCaseRegex.match(password).hasMatch()) {
        return false;
    }

    // Check for at least one special character
    if (!specialCharRegex.match(password).hasMatch()) {
        return false;
    }

    // Check for at least one number
    if (!numberRegex.match(password).hasMatch()) {
        return false;
    }

    // Check if password contains first name or last name
    if (password.contains(newUser.getFirstName(), Qt::CaseInsensitive) ||
        password.contains(newUser.getLastName(), Qt::CaseInsensitive)) {
        return false;
    }

    return true;
}


Checkers::Checkers() {}
