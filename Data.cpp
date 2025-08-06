#include "Data.hpp"

int dia, mes, ano, hora, minuto;
int day, month, year, hour, minute;

void Data::atualizarData() {
    #ifdef _WIN64
        // --- CÓDIGO PARA WINDOWS ---
        SYSTEMTIME st;
        GetLocalTime(&st);
        day = st.wDay;
        month = st.wMonth;
        year = st.wYear;
        hour = st.wHour;
        minute = st.wMinute;
    #else
        // --- CÓDIGO PARA LINUX ---
        time_t tempo_bruto = time(NULL);
        tm* tm_info = localtime(&tempo_bruto);
        day = tm_info->tm_mday;
        month = tm_info->tm_mon + 1;      // tm_mon é 0-11, então somamos 1
        year = tm_info->tm_year + 1900;  // tm_year são os anos desde 1900
        hour = tm_info->tm_hour;
        minute = tm_info->tm_min;
    #endif
}

void Data::setData(int d, int m, int a) {

    atualizarData();

    //Ano
    if (a < 0) {
        ano = year;
    }
    else if (a > year) {
        ano = year;
    }
    else if (a >= 0 && a <= year % 100) {
        ano = year - (year % 100) + a; // Ex: se botar 24 ele joga a data para 2024
    }
    else if (a > year % 100 && a < 100) {
        ano = year - (year % 100) + (a-100); // Ex: se botar 95 ele joga a data para 1995
    }
    else {
        ano = a;
    }

    //Mês
    if (m < 1 || m > 12) {
        mes = month;
    }
    else {
        mes = m;
    }

    //Dia
    if (d < 1 || d > 31) {
        dia = day;
    } 
    else if (mes >= 1 && mes <= 7) {
        if (mes == 2) {
            if ((d == 29) && (/*Verifica se é bissexto */(ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) {
                dia = d;
            }
            else if (d > 28) {
                dia = day;
            }
            else {
                dia = d;
            }
        }
        else if (mes % 2 == 0) {
            if (d > 30) {
                dia = day;
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
                dia = day;
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
    atualizarData();
    //Hora
    if (h < 0 || h > 24) {
        hora = hour;
    }
    else {
        hora = h;
    }

    //Min
    if (mi < 0 || mi > 59) {
        minuto = minute;
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

string Data::getDataDeHoje() {
    atualizarData();
    stringstream data;
    // Formatação
    data << setw(2) << setfill('0') << day << "/"
         << setw(2) << setfill('0') << month << "/"
         << setw(4) << setfill('0') << year;
    
    return data.str();
}

string Data::getHoraDeHoje() {
    atualizarData();
    stringstream tempo;
    // Formatação
    tempo << setw(2) << setfill('0') << hour << ":"
          << setw(2) << setfill('0') << minute;

    return tempo.str();
}