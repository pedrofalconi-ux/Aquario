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
    // Métodos para definir dados da notícia
    void setTitulo(const std::string& t) { titulo = t; }
    void setSubtitulo(const std::string& s) { subtitulo = s; }
    void setCorpo(const std::string& c) { corpo = c; }
    void setAutor(const std::string& a) { autor = a; }
    void setImagem(const std::string& i) { imagem = i; }
    void setData(int d, int m, int a) { data.setData(d, m, a); }
    void setHora(int h, int mi) { data.setHora(h, mi); }
    
    // Métodos para obter dados da notícia
    std::string getTitulo() const { return titulo; }
    std::string getSubtitulo() const { return subtitulo; }
    std::string getCorpo() const { return corpo; }
    std::string getAutor() const { return autor; }
    std::string getImagem() const { return imagem; }
    std::string getDataFormatada() const { return data.getData(); }
    std::string getHoraFormatada() const { return data.getHora(); }

    virtual void formatar() = 0;
    virtual void exibir() = 0;
    virtual ~Noticia() {}
};

#endif
