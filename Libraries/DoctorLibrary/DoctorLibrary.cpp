#include <iostream>
#include <filesystem>
#include <fstream>

#include "DoctorLibrary.hpp"
#include "../UtilsLibrary/UtilsLibrary.hpp"

using namespace std;

DoctorNode* doctorList = nullptr;


DoctorNode*GetDoctorList(){

    return doctorList;
}

void DoctorMenu(Doctor*doctor){
    int option;
    while (option != 5) {
        cout << "Que acci" << GetLatinChar().o << "n desea realizar: \n"
             << "1- Crear Paciente \n"
             << "2- Atender Paciente \n"
             << "3- Eliminar paciente \n"
             << "4- Mostrar lista citas atendidas \n"
             << "5- Cerrar Sesi" << GetLatinChar().o << "n \n";
        cin >> option;

        switch (option) {
            case 1:
                CreateNewPatient(doctor);
                break;
            case 2:
                AttendPatient(doctor);
                break;
            case 3:
                DeletePatient(doctor);
                break;
            case 4:
                ShowAttendedAppointments(doctor);
                break;
            case 5:
                doctor = nullptr;
                break;
            default:
                cout << Red("ERROR: Opci") << Red(GetLatinChar().o) << Red("n desconocida \n");
                break;
        }
    }
}


Doctor *GetDoctorByUsername(string username){

    Doctor *doctor = nullptr;
    DoctorNode *aux = GetDoctorList();
    while (aux) {
        if (aux->doctor->user->username == username) {
            doctor = aux->doctor;
            SetIsLogged(true);
            break;
        }
        aux = aux->next;
    }

    return doctor;
}



void CreateNewPatient(Doctor *doctor){
    if(GetIsLogged()){
        string patientUsername, patientPassword;

        cout<<"Ingrese el usuario del nuevo paciente: ";
        cin.get();
        cin>>patientUsername;

        cout<<"Ingrese la contrase"<<GetLatinChar().n<<"a del nuevo paciente: ";
        cin>>patientPassword;

        NewPatientRegistration(NewPatient(CreateAccount(false, patientUsername, patientPassword)));
    }
}

void DeletePatient(Doctor *doctor){
    if(GetIsLogged()){
        string patientUsername;

        cout<<"Ingrese el usuario del paciente a eliminar: ";
        cin>>patientUsername;

        DeleteAccount(patientUsername);
    }
}

void AttendPatient(Doctor *doctor){
    if(GetIsLogged()){
        ShowDoctorAppointments(false);
    }
}

void ShowAttendedAppointments(Doctor *doctor){
    if(GetIsLogged()){
        ShowDoctorAppointments(true);
    }
}

void NewDoctorRegistration(Doctor *doctor){

    string newDoctorPath = DOCTOR_DATA_PATH + "/" + doctor->user->username;
    string newDoctorInfoPath = newDoctorPath + "/" + doctor->user->username + "Info.txt";

    DoctorNode *newDoctorNode = new DoctorNode;
    DoctorNode *aux = GetDoctorList();

    newDoctorNode->doctor = doctor;

    if(aux){
        while (aux->next) {
            aux = aux->next;
        }
        newDoctorNode->prev = aux;
        aux->next = newDoctorNode;
    } else {
        doctorList = newDoctorNode;
    }

    if(!filesystem::exists(newDoctorPath)){
        filesystem::create_directory(newDoctorPath);


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

Doctor *NewDoctor(User*user){
    Doctor *newDoctor = new Doctor;
    cout<<"Ingrese el nombre del nuevo doctor \n";
    cout<<"Nombre: ";
    cin.get();
    getline(cin, newDoctor->name);

    cout<<"Ingrese la especialidad del nuevo doctor \n";
    cout<<"Especialidad: ";
    cin.get();
    getline(cin, newDoctor->specialty);

    newDoctor->user = user;

    return newDoctor;
}