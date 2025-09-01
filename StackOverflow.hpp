#ifndef STACKOVERFLOW_HPP
#define STACKOVERFLOW_HPP

#include "Noticia.hpp"

class StackOverflow : public Noticia {
public:
    void exibir() override;
    void setTudo(const string top, const string prob);
    string exibirMais();
private:
    string topico;
    string problema;
};

#endif
