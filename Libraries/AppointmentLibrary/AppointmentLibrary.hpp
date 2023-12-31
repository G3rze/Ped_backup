#ifndef APPOINTMET_LIBRARY_HPP
#define APPOINTMET_LIBRARY_HPP

#include "../UtilsLibrary/UtilsLibrary.hpp"
#include "../PatientLibrary/PatientLibrary.hpp"
#include "../DoctorLibrary/DoctorLibrary.hpp"

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
    int priority;
    bool isAttended;
    PatientAppointment *patientAppointment;
    DoctorAppointment *doctorAppointment;
};

struct AppointmentNode{
    Appointment *appointment;
    AppointmentNode *next = nullptr, *prev = nullptr;
};

bool IsFull(string);

bool IsPending(Patient *);

void ShowCalendar();

AppointmentNode *GetAppointmentList();

Appointment *NewAppointment(Patient *, string, string, int);

void RegisterPatientAppointment(Appointment *);

void UpdateAppointment(Doctor *, int);

void DeletePatientAppointment(Patient *);

void ShowPatientAppointments(bool);

void ShowDoctorAppointments(bool);

void FillPendingAppointments();

void FillMedicalRecords(Patient *);

void FillAttendedAppointments(Doctor *);

#endif
