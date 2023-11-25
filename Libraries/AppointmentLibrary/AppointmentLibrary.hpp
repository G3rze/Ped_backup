#ifndef APPOINTMET_LIBRARY_HPP
#define APPOINTMET_LIBRARY_HPP

#include "../UtilsLibrary/UtilsLibrary.hpp"
#include "../PatientLibrary/PatientLibrary.hpp"

using namespace std;

struct PatientAppointment{
    string date;
    string suffering;
    string medicalPrescription;
    string doctorName;
};

struct DoctorAppointment{
    string date;
    Patient *patient;
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

bool IsPending(Patient *);

void ShowCalendar();

AppointmentNode *GetAppointmentList();

Appointment *NewAppointment(Patient *, string, string);

void RegisterPatientAppointment(Appointment *);

void UpdateAppointment(string, int);

void DeletePatientAppointment(string);

void ShowPatientAppointments(bool);

void ShowDoctorAppointments(bool);

#endif
