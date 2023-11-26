#include <iostream>
#include <filesystem>
#include <fstream>

#include "PatientLibrary.hpp"
#include "../UtilsLibrary/UtilsLibrary.hpp"
#include "../AppointmentLibrary/AppointmentLibrary.hpp"
#include "../../Constant/Constant.hpp"

PatientNode *patientList = nullptr;

PatientNode *GetPatientList(){
    return patientList;
}


void PatientMenu(Patient *patient){
    int option = 0;
    while (option != 5) {
        cout << "Que acci" << GetLatinChar().o << "n desea realizar: \n"
             << "1- Agendar una cita \n"
             << "2- Cancelar una cita \n"
             << "3- Mostrar historial medico \n"
             << "4- Borrar mi cuenta \n"
             << "5- Cerrar Sesi" << GetLatinChar().o << "n \n";
        cin >> option;

        switch (option) {
            case 1:
                CreateAppointment(patient);
                break;
            case 2:
                CancelAppointment(patient);
                break;
            case 3:
                ShowMedicalRecords(patient);
                break;
            case 4:
                DeletePatientByUsername(patient->user->username);
                patient = nullptr;
                option = 5;
                break;
            case 5:
                patient = nullptr;
                break;
            default:
                cout << Red("ERROR: Opci") << Red(GetLatinChar().o) << Red("n desconocida \n");
                break;
        }
    }
}

Patient *GetPatientByUsername(string username){

    Patient *patient = nullptr;
    PatientNode *aux = GetPatientList();
    while (aux) {
        if (aux->patient->user->username == username) {
            patient = aux->patient;
            SetIsLogged(true);
            break;
        }
        aux = aux->next;
    }

    return patient;
}

void CreateAppointment(Patient * patient){
    string date, suffering;
    int priority;

    if(GetIsLogged()) {
        if(!IsPending(patient)){
            bool isFull;
            ClearConsole();
            ShowCalendar();
            do{
                cout << "Ingresar la fecha de la cita en el formato dd/mm/yy: ";
                cin >> date;

                cout << "Raz"<<GetLatinChar().o<<"n de la cita (Consulta 1), (Ex"<<GetLatinChar().a<<"menes m"<<GetLatinChar().e<<"dicos 2), (Cirug"<<GetLatinChar().i<<"a 3): ";
                cin >> priority;

                cout << "Ingrese los s"<<GetLatinChar().i<<"ntomas: ";
                cin.get();
                getline(cin, suffering);

                isFull = IsFull(date);

                if(!isFull) {
                    RegisterPatientAppointment(NewAppointment(patient, date, suffering, priority));
                } else {
                    cout<<Red("ERROR: NO HAY CITAS DISPONIBLES PARA ESA FECHA \n");
                }
            }while(isFull);
        } else {
            cout<<Red("ERROR: USTED YA TIENE AGENDADA UNA CITA PENDIENTE \n");
        }
    }
}

void CancelAppointment(Patient *patient){
    if(GetIsLogged()) {
        ClearConsole();
        DeletePatientAppointment(patient);
    }
}

void ShowMedicalRecords(Patient *patient){
    if(GetIsLogged()) {
        ClearConsole();
        ShowPatientAppointments(true);
    }
}

void DeletePatientByUsername(string username){
    if(GetIsLogged()) {
        ClearConsole();
        PatientNode* aux = patientList;

        while (aux != nullptr) {
            if (aux->patient->user->username == username) {
                break;
            }

            aux = aux->next;
        }
        if (aux->prev) {
            aux->prev->next = aux->next;
        } else {
            patientList = aux->next;
        }

        if (aux->next) {
            aux->next->prev = aux->prev;
        }

        delete aux;
        DeleteAccount(username);
    }
}


void NewPatientRegistration(Patient *patient){
    string newPatientPath = PATIENT_DATA_PATH + "/" + patient->user->username;
    string newPatientInfoPath = newPatientPath + "/" + "Info.txt";
    string newPatientMedicalRecordPath = newPatientPath + "/" + "HistorialMedico.txt";


    PatientNode *newPatientNode = new PatientNode;
    PatientNode *aux = GetPatientList();

    newPatientNode->patient = patient;

    if(aux){
        while (aux->next) {
            aux = aux->next;
        }
        newPatientNode->prev = aux;
        aux->next = newPatientNode;
    } else {
        patientList = newPatientNode;
    }


    if(!filesystem::exists(newPatientPath)){
        filesystem::create_directory(newPatientPath);
        ofstream outfile(newPatientInfoPath);
        ofstream file(newPatientMedicalRecordPath);
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

Patient *NewPatient (User *user){
    Patient *newPatient = new Patient;
    cout<<"Ingrese el nombre del nuevo paciente"<<"\n";
    cout<<"Nombre: ";
    cin.get();
    getline(cin,newPatient->name);

    cout<<"Ingrese el la edad del nuevo paciente"<<"\n";
    cout<<"Edad: ";
    cin>>newPatient->age;

    newPatient->user = user;
    return newPatient;
}
