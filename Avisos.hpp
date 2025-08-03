#ifndef AVISOS_HPP
#define AVISOS_HPP

#include "Noticia.hpp"
#include <string>

class Avisos : public Noticia {
private:
    std::string achadosPerdido;

public:
    void formatar() override;
    void exibir() override;
};

#endif
