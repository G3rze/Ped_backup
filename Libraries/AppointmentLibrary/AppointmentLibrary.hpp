#ifndef APPOINTMET_LIBRARY_HPP
#define APPOINTMET_LIBRARY_HPP

#include "../UtilsLibrary/UtilsLibrary.hpp"

using namespace std;

struct PatientAppointment{
    string date;
    string suffering;
    string medicalPrescription;
    string doctorName;
};

struct DoctorAppointment{
    string date;
    int patientAge;
    string patientName;
    string medicalPrescription;
    string suffering;
};

struct Appointment{
    int id;
    bool isAttended;
    PatientAppointment *patientAppointment;
    DoctorAppointment *doctorAppointment;
};

struct AppointmentNode{
    Appointment *appointment;
    AppointmentNode *next = nullptr, *prev = nullptr;
};

AppointmentNode *GetAppointmentList();

Appointment *NewAppointment(string, string, string, int);

void RegisterPatientAppointment(Appointment *);

void UpdateAppointment(string, int);

void DeletePatientAppointment(string);

void ShowPatientAppointments(bool);

void ShowDoctorAppointments(bool);

#endif
