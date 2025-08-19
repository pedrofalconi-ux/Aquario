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
#include <ctime>
#ifdef _WIN32
    #include "Libs/curses.h" //Por o -> -L./Libs -l:pdcurses.a ao compilar
    #include "Libs/json.hpp"
#else
    #include <ncurses.h>
    #include <nlohmann/json.hpp>
#endif

using json = nlohmann::json;
using namespace std;

class Controle {
private:
    // Variáveis de estado da interface
    int x, y, yMax, xMax, ch;

    // Métodos auxiliares privados
    void mover(int cx, int cy, char* buffer, int buffer_size);

public:
    // Declaração do Construtor
    Controle();

    // Declaração do método principal
    void executarEditor(int tipoNoticia);
    void executarCRUD();
    void adicionarNoticia();
    void listarNoticias();
    void deletarNoticia();
    void editarNoticiaExistente();
    void apagar(int t);
    vector<string> listar();
    void salvarDados(int i);
    void carregarDados(int i);
    void carregarDadosArquivo(const string& nomeArquivo);
    vector<string> obterArquivosJSON();
};

#endif // CONTROLE_HPP