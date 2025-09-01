#ifndef HUMOR_HPP
#define HUMOR_HPP

#include "Noticia.hpp"

class Humor : public Noticia {
public:
    void exibir() override;
    void setPiada(const string pia);
    string exibirMais();
private:
    string piada;
};
    
#endif
