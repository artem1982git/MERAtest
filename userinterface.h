#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include<string>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
class UserInterface
{
private:
    std::string id;
    std::string user;
    std::string password;
public:
    UserInterface();
    int mainMenu();
    int registration(std::string& user,std::string& password);
    int  authentification(std::string& user,std::string& password);
    int actions();
    int createOrder(std::string& client,std::string& price,std::string& msg);
 };

#endif // USERINTERFACE_H
