#ifndef NOTICIA_HPP
#define NOTICIA_HPP

#include <string>
#include "Data.hpp"

class Noticia {
protected:
    std::string titulo;
    std::string subtitulo;
    std::string corpo;
    std::string autor;
    std::string imagem;
    Data data;

public:
    virtual void formatar() = 0;
    virtual void exibir() = 0;
    virtual ~Noticia() {}
};

#endif
