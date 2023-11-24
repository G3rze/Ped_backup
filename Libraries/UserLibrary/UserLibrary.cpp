#include <iostream>
#include <fstream>

#include "UserLibrary.hpp"
#include "../DoctorLibrary/DoctorLibrary.hpp"
#include "../PatientLibrary/PatientLibrary.hpp"

using namespace std;

string username;

bool isLogged = false;

void SetIsLogged(bool _isLogged){
    isLogged = _isLogged;
}

bool GetIsLogged(){
    return isLogged;
}

void Login(string _username, string password){
    username = _username;
    if(username.find(ORGANIZATION_EMAIL)){
        DoctorLogin(_username);
    } else {
        PatientLogin(_username);
    }
}

void SignOut(){
    if(username.find(ORGANIZATION_EMAIL)){
        DoctorLogOut();
    } else {
        PatientLogOut();
    }
}

User *CreateAccount(bool isAdmin, string username, string password){
    ofstream credentialFile;
    User *newUser = new User();

    newUser->username = username;
    newUser->password = password;
    newUser->isAdmin = isAdmin;

    if(!isAdmin){
        credentialFile.open(PATIENT_CREDENTIAL_PATH, ios::app);
    } else {
        credentialFile.open(DOCTOR_CREDENTIAL_PATH, ios::app);
    }
    credentialFile << username <<","<< password;

    return newUser;
}

void DeleteAccount(string username){

}