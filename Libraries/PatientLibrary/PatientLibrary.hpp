#ifndef PATIENT_LIBRARY_HPP
#define PATIENT_LIBRARY_HPP

#include "../UserLibrary/UserLibrary.hpp"
#include "../../Constant/Constant.hpp"
#include "../UtilsLibrary/UtilsLibrary.hpp"
#include "../AppointmentLibrary/AppointmentLibrary.hpp"

using namespace std;

struct Patient{
    User *user;
    string name;
    int age;
};

void PatientLogin(string);

void CreateAppointment();

void CancelAppointment();

void ShowMedicalRecords();

void DeleteMyAccount();

void PatientLogOut();

void NewPatientRegistrarion(string username, string password);

Patient *NewPatient(string, string);

#endif