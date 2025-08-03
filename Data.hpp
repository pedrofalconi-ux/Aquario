#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class Data {
private:
    int dia, mes, ano, hora, min;

public:
    std::string getData();
    std::string getHora();

    void setData(int d, int m, int a);
    void setHora(int h, int m);
};

#endif
