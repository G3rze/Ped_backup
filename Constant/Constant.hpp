#ifndef PROYECTOFINAL_GRUPOAB_PROYECTOFINAL_CONSTANT_HPP
#define PROYECTOFINAL_GRUPOAB_PROYECTOFINAL_CONSTANT_HPP
#include <iostream>

using namespace std;

static const string ORGANIZATION_EMAIL = "@hospital.com";
static const string ORGANIZATION_CODE = "ABCD";
static const string ROOT_PATH = "Hospital";
static const string DATACENTER_DIRECTORY_PATH = ROOT_PATH + "/DataCenter";
static const string CREDENTIALS_PATH = DATACENTER_DIRECTORY_PATH + "/Credentials";
static const string DOCTOR_DATA_PATH = ROOT_PATH + "/Doctor";
static const string PATIENT_DATA_PATH = ROOT_PATH + "/Patient";
static const string SUFFERING_DATABASE_PATH = DATACENTER_DIRECTORY_PATH + "/SufferingDatabase.txt";
static const string PENDING_APPOINTMENTS_PATH = DATACENTER_DIRECTORY_PATH + "/PendingAppointments.txt";
static const string PATIENT_CREDENTIAL_PATH = CREDENTIALS_PATH + "/PatientCredentials.txt";
static const string DOCTOR_CREDENTIAL_PATH = CREDENTIALS_PATH + "/DoctorCredentials.txt";

#endif