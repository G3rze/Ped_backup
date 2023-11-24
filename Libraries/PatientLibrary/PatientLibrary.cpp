#include <iostream>
#include <filesystem>
#include <fstream>

#include "PatientLibrary.hpp"
Patient *patient = new Patient;

void PatientLogin(string username){
    if(GetIsLogged()) {
        patient->name = username;
        patient->user->username = username;
        SetIsLogged(true);
    }
}

void CreateAppointment(){
    string date, suffering;

    if(GetIsLogged()) {
        NewAppointment(patient->name, date, suffering, patient->age);
    }
}

void CancelAppointment(){
    if(GetIsLogged()) {
        DeletePatientAppointment(patient->user->username);
    }
}

void ShowMedicalRecords(){
    if(GetIsLogged()) {
        ShowPatientAppointments(true);
    }
}

void DeleteMyAccount(){
    if(GetIsLogged()) {
        DeleteAccount(patient->user->username);
    }
}

void PatientLogOut(){
    if(GetIsLogged()){
        SetIsLogged(false);
    }
}

void NewPatientRegistrarion(string username, string password){
    string newPatientPath = PATIENT_DATA_PATH + "/" + username;
    string newPatientInfoPath = newPatientPath + "/" + username + "Info.txt";
    Patient *patient = nullptr;

    if(!filesystem::exists(newPatientPath)){
        filesystem::create_directory(newPatientPath);
        patient = NewPatient(username, password);

        ofstream outfile(newPatientInfoPath);
        if(outfile.is_open()){
            outfile<<"Nombre: "<<patient->name<<"\n"
            <<"Edad: "<<patient->age<<"\n";
            outfile.close();
        }
    } else {
        cout<<Red("ERROR: ESTE USUARIO YA EXISTE");
        return;
    }
}

Patient *NewPatient (string username, string password){
    Patient *newPatient = new Patient;
    cout<<"Ingrese el nombre del nuevo paciente"<<"\n";
    cout<<"Nombre: ";
    cin.get();
    getline(cin,newPatient->name);

    cout<<"Ingrese el la edad del nuevo paciente"<<"\n";
    cout<<"Edad: ";
    cin>>newPatient->age;

    newPatient->user = CreateAccount(false, username, password);
    return newPatient;
}