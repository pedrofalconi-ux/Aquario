#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include "Data.hpp"

using namespace std;

class Data {
private:
    int dia, mes, ano, hora, minuto;
    SYSTEMTIME systemInfo;

public:

    Data() {
    GetLocalTime(&systemInfo);
    dia = systemInfo.wDay;
    mes = systemInfo.wMonth;
    ano = systemInfo.wYear;
    hora = systemInfo.wHour;
    minuto = systemInfo.wMinute;
    }

    string getData();
    string getHora();

    void setData(int d, int m, int a);
    void setHora(int h, int m);
};

#endif
