#include <iostream>
#include <clocale>
#include <filesystem>
#include <fstream>


#include "Libraries/DoctorLibrary/DoctorLibrary.hpp"
#include "Libraries/PatientLibrary/PatientLibrary.hpp"
#include "Libraries/UtilsLibrary/UtilsLibrary.hpp"
#include "Constant/Constant.hpp"

using namespace std;

void LoadDirectories();
void LoadDataFiles();
void OnStart();
void MainMenu(int);
void DoctorMenu();
void PatientMenu();

LatinChar latinChar;

int main(){
    setlocale(LC_CTYPE, "spanish");
    LoadDirectories();
    LoadDataFiles();
    OnStart();
    return 0;
}

void LoadDirectories(){
    if (!filesystem::exists(ROOT_PATH)) {
        filesystem::create_directory(ROOT_PATH);
    }
    if (!filesystem::exists(DATACENTER_DIRECTORY_PATH)) {
        filesystem::create_directory(DATACENTER_DIRECTORY_PATH);
    }
    if (!filesystem::exists(DOCTOR_DATA_PATH)) {
        filesystem::create_directory(DOCTOR_DATA_PATH);
    }
    if (!filesystem::exists(PATIENT_DATA_PATH)) {
        filesystem::create_directory(PATIENT_DATA_PATH);
    }
    if (!filesystem::exists(CREDENTIALS_PATH)) {
        filesystem::create_directory(CREDENTIALS_PATH);
    }
}

void LoadDataFiles(){
    if(!filesystem::exists(SUFFERING_DATABASE_PATH)){
        ofstream sufferingDatabaseFile(SUFFERING_DATABASE_PATH);
    }
    if(!filesystem::exists(PENDING_APPOINTMENTS_PATH)){
        ofstream pendingAppointmentsFile(PENDING_APPOINTMENTS_PATH);
    }
    if(!filesystem::exists(DOCTOR_CREDENTIAL_PATH)){
        ofstream doctorDataFile(DOCTOR_CREDENTIAL_PATH);
    }
    if(!filesystem::exists(PATIENT_CREDENTIAL_PATH)){
        ofstream patientDataFile(PATIENT_CREDENTIAL_PATH);
    }
}

void OnStart(){
    int option;

    do {
        ClearConsole();

        cout << Blue("Bienvenido a Hospital El Salvador") << "\n"
             << "\n"
             << "1- Iniciar Sesi"<<latinChar.o<<"n" << "\n"
             << "2- Registrarse" << "\n"
             << "3- Salir"<<"\n";

        cin >> option;

        MainMenu(option);

    } while (option != 3);
}

void MainMenu(int option){

    string username, password, passwordConfirmation, organizationCode;


    switch (option) {
        case 1:
            ClearConsole();
            cout<<Yellow("Usuario: ");
            cin>>username;

            cout<<Yellow("Contrase")<<Yellow(latinChar.n)<<Yellow("a: ");
            cin>>password;

            Login(username, password);
            break;
        case 2:
            ClearConsole();
            do{
                cout<<Yellow("Nuevo Usuario: ");
                cin>>username;

                cout<<Yellow("Nueva Contrase")<<Yellow(latinChar.n)<<Yellow("a: ");
                cin>>password;

                cout<<Yellow("Confirmar Contrase")<<Yellow(latinChar.n)<<Yellow("a: ");
                cin>>passwordConfirmation;

                if(password != passwordConfirmation){
                    ClearConsole();
                    cout<<Red("ERROR: Contrase")<<Red(latinChar.n)<<Red("as distintas")<<"\n";
                }
            } while (password != passwordConfirmation);

            if(username.find(ORGANIZATION_EMAIL) != string::npos) {
                cout<<Yellow("Ingrese el codigo de su organizaci")<<Yellow(latinChar.o)<<Yellow("n")<<"\n";
                cin >> organizationCode;

                if (organizationCode == ORGANIZATION_CODE) {
                    NewDoctorRegistration(username, password);
                } else {
                    cout << Red("ERROR: Codigo de acceso invalido, contacte a su organizaci")<<Red(latinChar.o)<<Red("n para m")<<Red(latinChar.a)<<Red("s informaci")<<Red(latinChar.o)<<Red("n")
                         << "\n";
                    MainMenu(2);
                }
            } else {
                NewPatientRegistrarion(username, password);
            }
            break;
        case 3:
            cout<<Green("Muchas gracias por usar nuestro sistema en l")<<Green(latinChar.i)<<Green("nea, feliz d")<<Green(latinChar.i)<<Green("a")<<"\n";
            break;
        default:
            cout<<Red("ERROR: Opción invalida")<<"\n";
            break;
    }
}

void DoctorMenu(){

}

void PatientMenu(){

}