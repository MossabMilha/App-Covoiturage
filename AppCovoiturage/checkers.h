#ifndef CHECKERS_H
#define CHECKERS_H
#include <string>
#include <QRegularExpression>
#include <regex>

#include "user.h"

class Checkers
{
public:
    Checkers();
    static bool NameIsValid(const std::string& name);
    static bool EmailIsValid(const std::string& email);
    static bool UserNameIsValid(const std::string& username);
    static bool PasswordIsValid(const User& newUser,const std::string& Password);
};

#endif // CHECKERS_H
