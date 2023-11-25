#include <iostream>
#include <iomanip>
#include <ctime>

#include "AppointmentLibrary.hpp"

using namespace std;

const int numCitas = 28; // 4 semanas * 7 días

AppointmentNode *appointmentList = nullptr;

bool IsPending(Patient *patient){
    AppointmentNode *aux = GetAppointmentList();

    while (aux){
        if(aux->appointment->doctorAppointment->patient->name == patient->name && !aux->appointment->isAttended){
            break;
        }
        aux = aux->next;
    }
    if(aux){
        return true;
    } else {
        return false;
    }
}

void ShowCalendar() {
    // Obtener la fecha actual
    time_t t = time(0);
    tm* now = localtime(&t);

    // Obtener el día de hoy
    int today = now->tm_mday;

    //int thisMonth = now->tm_mon + 1;

// Calcular el día de la semana del primer día del mes actual
    int primerDiaMes = (now->tm_wday - now->tm_mday % 7 + 7) % 7;

// Ajustar para iniciar desde el primer día de la semana
    t -= primerDiaMes * 24 * 60 * 60; // Restar días para llegar al primer día de la semana
    now = localtime(&t);

    // Imprimir encabezado con nombres de los días
    cout << setw(4) << "Lun" << setw(4) << "Mar" << setw(4) << "Mie" << setw(4) << "Jue"
         << setw(4) << "Vie" << setw(4) << "Sab" << setw(4) << "Dom" << endl;

    // Imprimir números de los días y nombres de los días para las próximas 3 semanas
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 7; ++j) {
            int count = 0;
            // Obtener el número del día del mes
            int day = now->tm_mday;

            // Imprimir 'H' si el día es el día de hoy, de lo contrario, imprimir el número del día
            if(day != today){
                AppointmentNode *aux = GetAppointmentList();

                while (aux){
                    size_t found = aux->appointment->patientAppointment->date.find("/");
                    if(found != string::npos){
                        int dayOfAppointment = stoi(aux->appointment->patientAppointment->date.substr(0, found));
                        int monthOfAppointment = stoi(aux->appointment->patientAppointment->date.substr(found + 1, 2));

                        if(day == dayOfAppointment ){
                            count++;
                        }
                    }
                    aux = aux->next;
                }

                if(count == 0){
                    cout << setw(4) << day;
                } else if (count > 0 && count < 3){
                    cout << setw(2) << "" << Yellow(to_string(day));
                } else {
                    cout << setw(2) << "" << Red(to_string(day));
                }

            } else {
                cout << setw(2) <<""<< Blue(to_string(day));
            }

            // Mover a la siguiente fecha
            t += 24 * 60 * 60; // agregar 24 horas en segundos
            now = localtime(&t);
        }
        cout << endl;
    }
}

AppointmentNode *GetAppointmentList() {
    return appointmentList;
}

Appointment *NewAppointment(Patient *patient, string date, string suffering){
    Appointment *newAppointment = new Appointment;
    DoctorAppointment *newDoctorAppointment = new DoctorAppointment;
    PatientAppointment *newPatientAppointment = new PatientAppointment;

    newDoctorAppointment->patient = patient;
    newDoctorAppointment->date = date;
    newDoctorAppointment->suffering = suffering;

    newPatientAppointment->suffering = suffering;
    newPatientAppointment->date = date;

    newAppointment->isAttended = false;

    newAppointment->patientAppointment = newPatientAppointment;
    newAppointment->doctorAppointment = newDoctorAppointment;

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
        AppointmentNode *aux = appointmentList;
        id = 1;
        while(aux->next){
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


