#ifndef PATIENT_LIBRARY_HPP
#define PATIENT_LIBRARY_HPP

#include "../UserLibrary/UserLibrary.hpp"

using namespace std;

struct Patient{
    User *user;
    string name;
    int age;
};

struct PatientNode{
    Patient *patient;
    PatientNode *next = nullptr, *prev = nullptr;
};

PatientNode *GetPatientList();

Patient *GetPatientByUsername(string);

void PatientMenu(Patient *);

void CreateAppointment(Patient *);

void CancelAppointment(Patient *);

void ShowMedicalRecords(Patient *);

void DeleteMyAccount(Patient *);

void NewPatientRegistration(Patient *);

Patient *NewPatient(User *);

void DeletePatientByUsername(string);

#endif