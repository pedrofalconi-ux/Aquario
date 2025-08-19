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
#include <memory>
#include "Libs/curses.h" //Por o -> -L./Libs -l:pdcurses.a ao compilar
#include "Libs/json.hpp"

// Incluindo suas classes de notícia
#include "Noticia.hpp"
#include "Avisos.hpp"
#include "fofoca.hpp"
#include "Humor.hpp" 
#include "StackOverflow.hpp"
#include "Anonimo.hpp"
#include "Data.hpp"

using json = nlohmann::json;
using namespace std;

class Controle {
private:
    // Atributos antigos (manter compatibilidade)
    char titulo[50];
    char subtitulo[100];
    char autor[50];
    char corpo[10000];
    char imagem[100];

    // Novos atributos para suas classes
    vector<unique_ptr<Noticia>> noticias;
    int tipoNoticiaAtual;

    // Variáveis de estado da interface, também privadas
    int x, y, yMax, xMax, ch;

    // Métodos auxiliares privados
    void mover(int cx, int cy, char* buffer, int buffer_size);

public:
    // Declaração do Construtor
    Controle();

    // Métodos antigos (manter compatibilidade)
    void executarEditor();
    void apagar(int t);
    vector<string> listar();
    void salvarDados(int i);
    void carregarDados(int i);
    void imprimir();

    // Novos métodos para suas classes
    void criarNoticia(int tipo);
    void editarNoticiaAtual();
    void selecionarTipoNoticia();
    void exibirNoticias();
    void gerarHTML();
    string getTipoNoticiaString(int tipo);
};

#endif // CONTROLE_HPP