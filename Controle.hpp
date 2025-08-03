#ifndef CONTROLE_HPP
#define CONTROLE_HPP

#include <vector>
#include <string>
#include "Noticia.hpp"

class Controle {
private:
    std::vector<Noticia*> mural;

public:
    void editar();
    void apagar();
    void listarTodos();
    void salvarDados();
    void carregarDados();
    void imprimir();

    ~Controle();
};

#endif
