#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Data.hpp"
#ifdef _WIN64
    #include <windows.h> // Para Windows
#else
    #include <ctime>     // Para Linux e outros sistemas POSIX
#endif

using namespace std;

class Data {
private:
    int dia, mes, ano, hora, minuto;
    int day, month, year, hour, minute;
    void atualizarData();

public:

    Data() {
        void atualizarData();
    }

    string getData();
    string getHora();
    string getDataDeHoje();
    string getHoraDeHoje();

    void setData(int d, int m, int a);
    void setHora(int h, int m);

};

#endif
