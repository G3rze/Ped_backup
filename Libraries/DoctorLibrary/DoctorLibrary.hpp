#ifndef DOCTOR_LIBRARY_HPP
#define DOCTOR_LIBRARY_HPP

#include "../UserLibrary/UserLibrary.hpp"
#include "../../Constant/Constant.hpp"
#include "../UtilsLibrary/UtilsLibrary.hpp"
#include "../AppointmentLibrary/AppointmentLibrary.hpp"
#include "../PatientLibrary/PatientLibrary.hpp"

using namespace std;

struct Doctor{
    User *user;
    string name;
    string specialty;
};
struct DoctorNode{
    Doctor*doctor;
    DoctorNode *next = nullptr, *prev = nullptr;
};


void DoctorMenu(Doctor *);

DoctorNode *GetDoctorList();

Doctor *GetDoctorByUsername(string);

void CreateNewPatient(Doctor *);

void DeletePatient(Doctor *);

void AttendPatient(Doctor *);

void ShowAttendedAppointments(Doctor *);

void NewDoctorRegistration(Doctor *);

Doctor *NewDoctor(User*);



#endif