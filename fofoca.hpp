#ifndef FOFOCA_HPP
#define FOFOCA_HPP

#include "Noticia.hpp"

class Fofoca : public Noticia {
public:
    void exibir() override;
    void setAssunto(const string ass);
    string exibirMais();
private:
    string assunto;
};

#endif
