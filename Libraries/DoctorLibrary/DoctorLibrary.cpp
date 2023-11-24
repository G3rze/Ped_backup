#include <iostream>
#include <filesystem>
#include <fstream>

#include "DoctorLibrary.hpp"

using namespace std;

Doctor *doctor = new Doctor;

void DoctorLogin(string username){
    if(!GetIsLogged()){
        doctor->name = username;
        doctor->user->username = username;
        SetIsLogged(true);
    }
}

void DoctorLogOut(){
    if(GetIsLogged()){
        SetIsLogged(false);
    }
}

void CreateNewPatient(){
    if(GetIsLogged()){
        string patientUsername, patientPassword;

        cout<<"Ingrese el usuario del nuevo paciente: ";
        cin.get();
        cin>>patientUsername;

        cout<<"Ingrese la contraseña del nuevo paciente: ";
        cin>>patientPassword;

        NewPatientRegistrarion(patientUsername, patientPassword);
    }
}

void DeletePatient(){
    if(GetIsLogged()){
        string patientUsername;

        cout<<"Ingrese el usuario del paciente a eliminar: ";
        cin>>patientUsername;

        DeleteAccount(patientUsername);
    }
}

void AttendPatient(){
    if(GetIsLogged()){
        ShowDoctorAppointments(false);
    }
}

void ShowAttendedAppointments(){
    if(GetIsLogged()){
        ShowDoctorAppointments(true);
    }
}

void NewDoctorRegistration(string username, string password){

    string newDoctorPath = DOCTOR_DATA_PATH + "/" + username;
    string newDoctorInfoPath = newDoctorPath + "/" + username + "Info.txt";
    Doctor *doctor = nullptr;

    if(!filesystem::exists(newDoctorPath)){
        filesystem::create_directory(newDoctorPath);
        doctor = NewDoctor(username, password);

        ofstream outfile(newDoctorInfoPath);
        if(outfile.is_open()){
            outfile<<"Nombre: "<<doctor->name<<"\n"
                   <<"Especialidad: "<<doctor->specialty<<"\n";
            outfile.close();
        }
    } else {
        cout<<Red("ERROR: ESTE USUARIO YA EXISTE");
        return;
    }
}

Doctor *NewDoctor(string username, string password){
    Doctor *newDoctor = new Doctor;
    cout<<"Ingrese el nombre del nuevo doctor \n";
    cout<<"Nombre: ";
    cin.get();
    getline(cin, newDoctor->name);

    cout<<"Ingrese la especialidad del nuevo doctor \n";
    cout<<"Especialidad: ";
    cin.get();
    getline(cin, newDoctor->specialty);

    newDoctor->user = CreateAccount(true, username, password);
    return newDoctor;
}