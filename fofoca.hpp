#ifndef FOFOCA_HPP
#define FOFOCA_HPP

#include "Noticia.hpp"

class Fofoca : public Noticia {
public:
    void formatar() override;
    void exibir() override;
};

#endif
