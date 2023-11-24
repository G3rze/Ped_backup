#include <iostream>

#include "AppointmentLibrary.hpp"

using namespace std;

AppointmentNode *appointmentList = nullptr;

AppointmentNode *GetAppointmentList() {
    return appointmentList;
}

Appointment *NewAppointment(string patientName, string date, string suffering, int age){
    Appointment *newAppointment = new Appointment;

    newAppointment->isAttended = false;
    newAppointment->doctorAppointment->patientName = patientName;
    newAppointment->doctorAppointment->date = date;
    newAppointment->doctorAppointment->suffering = suffering;
    newAppointment->doctorAppointment->patientAge = age;

    newAppointment->patientAppointment->suffering = suffering;
    newAppointment->patientAppointment->date = date;

    return newAppointment;
}

void RegisterPatientAppointment(Appointment *newApointment){
    AppointmentNode *newNode = new AppointmentNode;
    newNode->appointment = newApointment;

    int id;

    if(!appointmentList){
        newNode->appointment->id = 1;
        appointmentList = newNode;
    } else {
        AppointmentNode *aux = GetAppointmentList();
        id = 1;
        while(aux){
            id++;
            aux = aux->next;
        }
        newNode->appointment->id = id;
        newNode->prev = aux;
        aux->next = newNode;
    }
}

void UpdateAppointment(string doctorName, int id){
    AppointmentNode *aux = GetAppointmentList();

    while (aux && aux->appointment->id != id){
        aux = aux->next;
    }

    if (aux->appointment->id == id){
        aux->appointment->patientAppointment->doctorName = doctorName;
        cout<<"Escriba el proceso medico: ";
        cin.get();
        getline(cin, aux->appointment->doctorAppointment->medicalPrescription);
        aux->appointment->patientAppointment->medicalPrescription = aux->appointment->doctorAppointment->medicalPrescription;
        aux->appointment->isAttended = true;
    } else {
        cout<<Red("ERROR: ID de la cita no encontrado \n");
    }
}

void DeletePatientAppointment(string username){

}

void ShowPatientAppointments(bool isAttended){

}

void ShowDoctorAppointments(bool isAttended){

}


