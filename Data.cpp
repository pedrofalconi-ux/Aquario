#include <iostream>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include "Data.hpp"

using namespace std;

int dia, mes, ano, hora, minuto;
SYSTEMTIME systemInfo;

void Data::setData(int d, int m, int a) {
    GetLocalTime(&systemInfo);

    //Ano
    if (a < 0) {
        ano = systemInfo.wYear;
    }
    else if (a > systemInfo.wYear) {
        ano = systemInfo.wYear;
    }
    else if (a >= 0 && a <= systemInfo.wYear % 100) {
        ano = systemInfo.wYear - (systemInfo.wYear % 100) + a; // Ex: se botar 24 ele joga a data para 2024
    }
    else if (a > systemInfo.wYear % 100 && a < 100) {
        ano = systemInfo.wYear - (systemInfo.wYear % 100) + (a-100); // Ex: se botar 95 ele joga a data para 1995
    }
    else {
        ano = a;
    }

    //Mês
    if (m < 1 || m > 12) {
        mes = systemInfo.wMonth;
    }
    else {
        mes = m;
    }

    //Dia
    if (d < 1 || d > 31) {
        dia = systemInfo.wDay;
    } 
    else if (mes >= 1 && mes <= 7) {
        if (mes == 2) {
            if ((d == 29) && (/*Verifica se é bissexto */(ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) {
                dia = d;
            }
            else if (d > 28) {
                dia = systemInfo.wDay;
            }
            else {
                dia = d;
            }
        }
        else if (mes % 2 == 0) {
            if (d > 30) {
                dia = systemInfo.wDay;
            }
            else {
                dia = d;
            }
        }
        else {
            dia = d;
        }
    }
    else {
        if (mes % 2 != 0) {
            if (d > 30) {
                dia = systemInfo.wDay;
            }
            else {
                dia = d;
            }
        }
        else {
            dia = d;
        }
    }
}

void Data::setHora(int h, int mi) {
    //Hora
    if (h < 0 || h > 24) {
        hora = systemInfo.wHour;
    }
    else {
        hora = h;
    }

    //Min
    if (mi < 0 || mi > 59) {
        minuto = systemInfo.wMinute;
    }
    else {
        minuto = mi;
    }
}

string Data::getData() {
    stringstream data;
    // Formatação
    data << setw(2) << setfill('0') << dia << "/"
         << setw(2) << setfill('0') << mes << "/"
         << setw(4) << setfill('0') << ano;
    
    return data.str();
}

string Data::getHora() {
    stringstream tempo;
    // Formatação
    tempo << setw(2) << setfill('0') << hora << ":"
          << setw(2) << setfill('0') << minuto;

    return tempo.str();
}