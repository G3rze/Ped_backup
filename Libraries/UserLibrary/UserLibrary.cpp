#include <iostream>
#include <fstream>

#include "UserLibrary.hpp"
#include "../DoctorLibrary/DoctorLibrary.hpp"
#include "../PatientLibrary/PatientLibrary.hpp"

using namespace std;

UserNode *userList = nullptr;

bool isLogged = false;

bool UserExist(string username){
    UserNode *aux = userList;

    while (aux){

        if(aux->user->username == username){
            break;
        }

        aux = aux->next;
    }

    if(aux){
        return true;
    } else {
        return false;
    }
}

bool CredentialCheck(string username, string password){
    UserNode *aux = userList;
    while (aux){
        if(aux->user->username == username && aux->user->password == password){
            break;
        }
        aux = aux->next;
    }

    if(aux){
        return true;
    } else {
        return false;
    }
}

UserNode *GetUserList(){
    return  userList;
}

void SetIsLogged(bool _isLogged){
    isLogged = _isLogged;
}

bool GetIsLogged(){
    return isLogged;
}

void Login(string username, string password){
    if(CredentialCheck(username, password)){
        if (username.find(ORGANIZATION_EMAIL) != string::npos) {
            DoctorMenu(GetDoctorByUsername(username));
        } else {
            PatientMenu(GetPatientByUsername(username));
        }
        SetIsLogged(true);
    } else {
        cout<<Red("ERROR: INICIO DE SESI")<<Red(GetLatinChar().O)<<Red("N FALLIDO REVISE SUS CREDENCIALES \n");
    }
}


User *CreateAccount(bool isAdmin, string username, string password){
    ofstream credentialFile;
    User *newUser = new User();

    newUser->username = username;
    newUser->password = password;
    newUser->isAdmin = isAdmin;

    UserNode *newUserNode = new UserNode;
    UserNode *aux = GetUserList();

    newUserNode->user = newUser;

    if(aux){
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = newUserNode;
    } else {
        userList = newUserNode;
    }

    if(!isAdmin){
        credentialFile.open(PATIENT_CREDENTIAL_PATH, ios::app);
    } else {
        credentialFile.open(DOCTOR_CREDENTIAL_PATH, ios::app);
    }
    credentialFile << username <<","<< password <<"\n";

    return newUser;
}

void DeleteAccount(string username) {
    while (userList != nullptr && userList->user->username == username) {
        UserNode *aux= userList;
        userList = userList->next;
        delete aux;
    }

    UserNode *aux = userList;

    while (aux != nullptr && aux->next != nullptr) {
        if (aux->next->user->username == username) {
            UserNode *aux1 = aux->next;
            aux->next = aux->next->next;
            delete aux1;
        } else {
            aux = aux->next;
        }
    }


}
