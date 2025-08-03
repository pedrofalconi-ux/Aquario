#ifndef STACKOVERFLOW_HPP
#define STACKOVERFLOW_HPP

#include "Noticia.hpp"

class StackOverflow : public Noticia {
public:
    void formatar() override;
    void exibir() override;
};

#endif
