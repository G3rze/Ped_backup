#ifndef USER_LIBRARY_HPP
#define USER_LIBRARY_HPP

#include <iostream>

#include "../../Constant/Constant.hpp"

using namespace std;

struct User{
    string username;
    string password;
    bool isAdmin;
};

struct UserNode{
    User *user;
    UserNode *next = nullptr;
};

bool CredentialCheck(string, string);

UserNode *GetUserList();

void SetIsLogged(bool);

bool GetIsLogged();

void Login(string username, string password);


User *CreateAccount(bool ,string ,string);

void DeleteAccount(string username);

#endif