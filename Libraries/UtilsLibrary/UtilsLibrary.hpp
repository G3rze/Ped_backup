#ifndef UTILS_LIBRARY_HPP
#define UTILS_LIBRARY_HPP

#include <iostream>

using namespace std;

struct LatinChar{
    string A = "\xC1";
    string a = "\xE1";

    string E = "\xC9";
    string e = "\xE9";

    string I = "\xCD";
    string i = "\xED";

    string O = "\xD3";
    string o = "\xF3";

    string U = "\xDA";
    string u = "\xFA";

    string N = "\xD1";
    string n = "\xF1";
};

string Red(string);
string Green(string);
string Yellow(string);
string Blue(string);

void ClearConsole();


#endif
