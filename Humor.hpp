#ifndef HUMOR_HPP
#define HUMOR_HPP

#include "Noticia.hpp"

class Humor : public Noticia {
public:
    void formatar() override;
    void exibir() override;
};

#endif
