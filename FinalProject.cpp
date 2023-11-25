#include <iostream>
#include <clocale>
#include <filesystem>
#include <fstream>


#include "Libraries/DoctorLibrary/DoctorLibrary.hpp"
#include "Libraries/PatientLibrary/PatientLibrary.hpp"
#include "Libraries/UtilsLibrary/UtilsLibrary.hpp"
#include "Libraries/AppointmentLibrary/AppointmentLibrary.hpp"
#include "Constant/Constant.hpp"

using namespace std;

void LoadDirectories();
void LoadDataFiles();

int main(){
    setlocale(LC_CTYPE, "spanish");
    LoadDataFiles();
    LoadDirectories();
    MainMenu();
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


