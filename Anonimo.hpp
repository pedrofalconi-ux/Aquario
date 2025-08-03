#ifndef ANONIMO_HPP
#define ANONIMO_HPP

#include "Noticia.hpp"

class Anonimo : public Noticia {
public:
    Anonimo();
    void formatar() override;
    void exibir() override;
};

#endif
