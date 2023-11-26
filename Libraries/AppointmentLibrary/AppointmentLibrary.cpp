#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <filesystem>

#include "AppointmentLibrary.hpp"
#include "../../Constant/Constant.hpp"

using namespace std;

const int numCitas = 28; // 4 semanas * 7 días

AppointmentNode *appointmentList = nullptr;

bool IsFull(string date){

    int count = 0;

    AppointmentNode *aux = appointmentList;

    while(aux){

        if(date == aux->appointment->patientAppointment->date){
            count++;
        }

        aux = aux->next;
    }

    if (count == 3) {
        return true;
    } else {
        return false;
    }
}

bool IsPending(Patient *patient){
    AppointmentNode *aux = appointmentList;

    while (aux){
        if(aux->appointment->doctorAppointment->patient->user->username == patient->user->username && !aux->appointment->isAttended){
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

    int today = now->tm_mday;

    int weekDay = now->tm_wday;

    if(weekDay == 0){
        weekDay = 6;
    } else {
        weekDay--;
    }

// Ajustar para iniciar desde el primer día de la semana
    t -= weekDay * 24 * 60 * 60; // Restar días para llegar al primer día de la semana
    now = localtime(&t);

    // Imprimir encabezado con nombres de los días
    cout << setw(4) << "Lun" << setw(4) << "Mar" << setw(4) << "Mie" << setw(4) << "Jue"
         << setw(4) << "Vie" << setw(4) << "Sab" << setw(4) << "Dom" << endl;

    // Imprimir números de los días y nombres de los días para las próximas 3 semanas
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 7; ++j) {
            int count = 0;

            int day = now->tm_mday;

            if(day != today){
                AppointmentNode *aux = appointmentList;

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

Appointment *NewAppointment(Patient *patient, string date, string suffering, int priority){
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
    newAppointment->priority = priority;

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
        while(aux->next){
            id++;
            aux = aux->next;
        }
        newNode->appointment->id = aux->appointment->id + 1;
        newNode->prev = aux;
        aux->next = newNode;
    }

    FillPendingAppointments();
}

void UpdateAppointment(Doctor *doctor, int id){
    AppointmentNode *aux = appointmentList;

    while (aux && aux->appointment->id != id){
        aux = aux->next;
    }

    if (aux->appointment->id == id){
        aux->appointment->patientAppointment->doctorName = doctor->name;
        cout<<"Escriba el proceso medico: ";
        cin.get();
        getline(cin, aux->appointment->doctorAppointment->medicalPrescription);
        aux->appointment->patientAppointment->medicalPrescription = aux->appointment->doctorAppointment->medicalPrescription;
        aux->appointment->isAttended = true;
    } else {
        cout<<Red("ERROR: ID de la cita no encontrado \n");
    }
    FillPendingAppointments();
    FillAttendedAppointments(doctor);
    FillMedicalRecords(aux->appointment->doctorAppointment->patient);
}

void DeletePatientAppointment(Patient *patient){
    AppointmentNode *aux = appointmentList;

    while(aux){

        if(aux->appointment->doctorAppointment->patient->user->username == patient->user->username && !aux->appointment->isAttended){
            break;
        }

        aux = aux->next;
    }
    if(aux){
        if (aux->prev) {
            appointmentList->prev->next = aux->next;

        } else {
            appointmentList = aux->next;
        }
        if (aux->next){
            aux->next->prev = aux->prev;
        } else {
            appointmentList = nullptr;
        }

        delete aux;
    } else {
        cout<<Red("ERROR: NO HAY CITAS PARA ELIMINAR \n");
    }



}

void ShowPatientAppointments(bool isAttended){
    AppointmentNode *aux = appointmentList;
    int count = 0;
    while(aux){
        if(isAttended){
            count++;
            cout << Green("Cita ") << Green(to_string(count)) << "\n";
            cout << aux->appointment->patientAppointment->date << ", "
                 << aux->appointment->patientAppointment->suffering << ", "
                 << aux->appointment->patientAppointment->medicalPrescription << ", "
                 << aux->appointment->patientAppointment->doctorName << ". \n";
        }

        aux = aux->next;
    }
}

void ShowDoctorAppointments(bool isAttended){
    int count = 1;
    AppointmentNode *aux = appointmentList;
    if (!isAttended){
        while (count < 4) {
            aux = appointmentList;
            while (aux) {
                    if (aux->appointment->priority == count && !aux->appointment->isAttended) {
                        cout << Green("ID: ") << Green(to_string(aux->appointment->id)) << "\n";
                        cout << aux->appointment->doctorAppointment->date << ", "
                             << aux->appointment->doctorAppointment->patient->age << ", "
                             << aux->appointment->doctorAppointment->patient->name << ", "
                             << aux->appointment->doctorAppointment->suffering << ".\n";
                    }
                aux = aux->next;
            }
            count++;
        }
    } else {
        while(aux){
            if(aux->appointment->isAttended){
                cout << Green("ID: ") << Green(to_string(aux->appointment->id)) << "\n";
                cout << aux->appointment->doctorAppointment->date << ", "
                     << aux->appointment->doctorAppointment->patient->age << ", "
                     << aux->appointment->doctorAppointment->patient->name << ", "
                     << aux->appointment->doctorAppointment->medicalPrescription << ", "
                     << aux->appointment->doctorAppointment->suffering << ".\n";
            }
            aux = aux->next;
        }
    }
}

void FillPendingAppointments(){
    ofstream file;

    int count = 0;

    file.open(PENDING_APPOINTMENTS_PATH, ::ios::out);

    AppointmentNode *aux = appointmentList;

    while(aux){

        if(!aux->appointment->isAttended){
            file << "ID: " << aux->appointment->id <<"\n";
            file << aux->appointment->doctorAppointment->date << ", "
            << aux->appointment->doctorAppointment->patient->age << ", "
            << aux->appointment->doctorAppointment->patient->name << ", "
            << aux->appointment->doctorAppointment->suffering << ".\n";
        }

        aux = aux->next;
    }

    file.close();
}

void FillMedicalRecords(Patient *patient){
    string PatientPath = PATIENT_DATA_PATH + "/" + patient->user->username;
    string newPatientMedicalRecordPath = PatientPath + "/" + "HistorialMedico.txt";

    ofstream file;

    file.open(newPatientMedicalRecordPath, ::ios::out);

    AppointmentNode *aux = appointmentList;

    while(aux){

        if(aux->appointment->isAttended){
            file << "ID: " << aux->appointment->id << "\n";
            file << aux->appointment->patientAppointment->date << ", "
            << aux->appointment->patientAppointment->suffering << ", "
            << aux->appointment->patientAppointment->medicalPrescription << ", "
            << aux->appointment->patientAppointment->doctorName << ".\n";
        }

        aux = aux->next;
    }

    file.close();

}

void FillAttendedAppointments(Doctor *doctor){
    string doctorPath = DOCTOR_DATA_PATH + "/" + doctor->user->username;
    string doctorAttendedAppointmentPath = doctorPath + "/" + "CitasAtendidas.txt";

    ofstream file;

    file.open(doctorAttendedAppointmentPath, ::ios::out);

    if(file.is_open()){
        AppointmentNode *aux = appointmentList;

        while (aux) {

            if (aux->appointment->isAttended) {
                file << "ID: " << aux->appointment->id << "\n";
                file << aux->appointment->doctorAppointment->date << ", "
                     << aux->appointment->doctorAppointment->patient->age << ", "
                     << aux->appointment->doctorAppointment->patient->name << ", "
                     << aux->appointment->doctorAppointment->medicalPrescription << ", "
                     << aux->appointment->doctorAppointment->suffering << ".\n";
            }

            aux = aux->next;
        }
    }

    file.close();
}
