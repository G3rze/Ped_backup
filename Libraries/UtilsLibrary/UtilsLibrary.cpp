#include "UtilsLibrary.hpp"
#include "../UserLibrary/UserLibrary.hpp"
#include "../DoctorLibrary/DoctorLibrary.hpp"
#include "../PatientLibrary/PatientLibrary.hpp"
#include "../../Constant/Constant.hpp"

LatinChar latinChar;

void MainMenu(){
    bool userExist;
    int option = 0;
    while(option != 3){
        ClearConsole();

        cout << Blue("Bienvenido a Hospital El Salvador") << "\n"
             << "1- Iniciar Sesi" << GetLatinChar().o << "n" << "\n"
             << "2- Registrarse" << "\n"
             << "3- Salir" << "\n";

        cin >> option;

        string username, password, passwordConfirmation, organizationCode;

        switch (option) {
            case 1:
                ClearConsole();
                cout << Yellow("Usuario: ");
                cin >> username;

                cout << Yellow("Contrase") << Yellow(GetLatinChar().n) << Yellow("a: ");
                cin >> password;

                Login(username, password);
                break;
            case 2:
                ClearConsole();
                do {
                    cout << Yellow("Nuevo Usuario: ");
                    cin >> username;

                    cout << Yellow("Nueva Contrase") << Yellow(GetLatinChar().n) << Yellow("a: ");
                    cin >> password;

                    cout << Yellow("Confirmar Contrase") << Yellow(GetLatinChar().n) << Yellow("a: ");
                    cin >> passwordConfirmation;

                    userExist = UserExist(username);

                    if (password != passwordConfirmation) {
                        ClearConsole();
                        cout << Red("ERROR: Contrase") << Red(GetLatinChar().n) << Red("as distintas") << "\n";
                    }
                    if (UserExist(username)){
                        ClearConsole();
                        cout << Red("ERROR: Usuario ya existente \n");
                    }
                } while (password != passwordConfirmation || UserExist(username));

                if (username.find(ORGANIZATION_EMAIL) != string::npos) {
                    cout << Yellow("Ingrese el codigo de su organizaci") << Yellow(GetLatinChar().o) << Yellow("n")
                         << "\n";
                    cin >> organizationCode;

                    if (organizationCode == ORGANIZATION_CODE) {
                        NewDoctorRegistration(NewDoctor(CreateAccount(true,username,password)));
                    } else {
                        cout << Red("ERROR: Codigo de acceso invalido, contacte a su organizaci")
                             << Red(GetLatinChar().o) << Red("n para m") << Red(GetLatinChar().a) << Red("s informaci")
                             << Red(GetLatinChar().o) << Red("n")
                             << "\n";
                    }
                } else {
                    NewPatientRegistration(NewPatient(CreateAccount(false, username, password)));
                }
                break;
            case 3:
                cout << Green("Muchas gracias por usar nuestro sistema en l") << Green(GetLatinChar().i)
                     << Green("nea, feliz d") << Green(GetLatinChar().i) << Green("a") << "\n";
                break;
            default:
                cout << Red("ERROR: Opción invalida") << "\n";
                break;
        }
    }
}

LatinChar GetLatinChar(){
    return latinChar;
}

string Red(string text){
    string coloredText;
    coloredText = "\033[1;31m" + text + "\033[0m";
    return coloredText;
}

string Green(string text){
    string coloredText;
    coloredText = "\033[1;32m" + text + "\033[0m";
    return coloredText;
}

string Yellow(string text){
    string coloredText;
    coloredText = "\033[1;33m" + text + "\033[0m";
    return coloredText;
}

string Blue(string text){
    string coloredText;
    coloredText = "\033[1;34m" + text + "\033[0m";
    return coloredText;
}

void ClearConsole(){
    cout<<"\033[H\033[J";
}
