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

void DoctorLogin(string);

void DoctorLogOut();

void CreateNewPatient();

void DeletePatient();

void AttendPatient();

void ShowAttendedAppointments();

void NewDoctorRegistration(string username, string password);

Doctor *NewDoctor(string, string);

#endif