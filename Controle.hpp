#ifndef CONTROLE_HPP
#define CONTROLE_HPP

#define Title 0
#define Subtitle 1
#define Author 2
#define Body 3
#define Image 4
#define All 5

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include "Libs/curses.h" //Por o -> -L./PDCurses -l:pdcurses.a ao compilar
#include "Libs/json.hpp"

using json = nlohmann::json;
using namespace std;

class Controle {
private:
    // Atributos da classe
    char titulo[50];
    char subtitulo[100];
    char autor[50];
    char corpo[10000];
    char imagem[100];

    // Variáveis de estado da interface, também privadas
    int x, y, yMax, xMax, ch;

    // Métodos auxiliares privados
    void mover(int cx, int cy, char* buffer, int buffer_size);

public:
    // Declaração do Construtor
    Controle();

    // Declaração do método principal
    void executarEditor();
    void apagar(int t);
    vector<string> listar();
    void salvarDados(int i);
    void carregarDados(int i);
    void imprimir();
};

#endif // CONTROLE_HPP