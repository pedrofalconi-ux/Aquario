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
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#include "Libs/curses.h" //Por o -> -L./Libs -l:pdcurses.a ao compilar
#endif

#ifdef __linux__
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <boost/locale.hpp>
#endif

// Incluindo suas classes de notícia
#include "Noticia.hpp"
#include "Avisos.hpp"
#include "fofoca.hpp"
#include "Humor.hpp" 
#include "StackOverflow.hpp"
#include "Anonimo.hpp"
#include "Data.hpp"

#include "Libs/json.hpp"

using json = nlohmann::json;
using namespace std;
namespace fs = std::filesystem;

class Controle {
private:
    // Variáveis de estado da interface, também privadas
    int x, y, yMax, xMax, ch;
    
    #if defined(_WIN32) || defined(_WIN64)
    // Atributos da classe
    char titulo[50];
    char subtitulo[100];
    char autor[50];
    char corpo[10000];
    char imagem[100];

    vector<char*> textos;

    // Métodos auxiliares privados
    void mover(int cx, int cy, char* buffer, int buffer_size);
    void salvarDadoIndice(int contador);
    void carregarDadoIndice(int indice);
    #endif

    #ifdef __linux__
    // Atributos da classe
    vector<wstring> textos;
    vector<wstring> rotulos = {L"Titulo:    ", L"Subtitulo: ", L"Autor:     ", L"Corpo:     ", L"Imagem:    "};

    wint_t wch;

    json js;

    // Métodos auxiliares privados
    void mover(int cx, int cy, wstring &buffer);
    void salvarDadoIndice(int contador);
    void carregarDadoIndice(int indice);
    string wstringToUtf8(const std::wstring &wstr);
    wstring utf8ToWstring(const std::string &str);

    #endif

    // Novos atributos para suas classes
    vector<unique_ptr<Noticia>> noticias;
    int tipoNoticiaAtual;

public:
    // Declaração do Construtor
    Controle();
    Controle(int tipoNoticia);

    // Declaração do método principal
    int pesquisar();

    void animation();
    void executarEditor();
    void apagar(int t);
    void editarNoticia(int indice);
    void salvarDados();
    void carregarDados();
    void iniciar_a_Porra_Toda();
    void imprimir();

     // Novos métodos para suas classes
    void criarNoticia(int tipo);
    void editarNoticiaAtual();
    void selecionarTipoNoticia();
    string exibirNoticias(int escolha);
    void gerarHTML();
    string getTipoNoticiaString(int tipo);
};

#endif // CONTROLE_HPP