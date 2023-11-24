#include "UtilsLibrary.hpp"

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
