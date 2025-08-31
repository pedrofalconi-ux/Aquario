#ifndef NOTICIA_HPP
#define NOTICIA_HPP

#include <string>
#include "Data.hpp"

class Noticia : public Data {
protected:
    std::string titulo;
    std::string subtitulo;
    std::string corpo;
    std::string autor;
    std::string imagem;
    Data data;
    int tipo; // ADICIONADO: Variável para guardar o tipo da notícia

public:
    // Métodos para definir dados da notícia
    void setTitulo( std::string t) { titulo = t; }
    void setSubtitulo( std::string s) { subtitulo = s; }
    void setCorpo( std::string c) { corpo = c; }
    void setAutor( std::string a) { autor = a; }
    void setImagem( std::string i) { imagem = i; }
    void setData(int d, int m, int a) { data.setData(d, m, a); }
    void setHora(int h, int mi) { data.setHora(h, mi); }
    void setTipo(int t) { tipo = t; } 
    
    // Métodos para obter dados da notícia
    std::string getTitulo()  { return titulo; }
    std::string getSubtitulo()  { return subtitulo; }
    std::string getCorpo()  { return corpo; }
    std::string getAutor()  { return autor; }
    std::string getImagem()  { return imagem; }
    int getTipo()  { return tipo; } 

    void formatar() {
        if (autor.empty()) {
            autor = "Anônimo";
        }
    }
    virtual void exibir() = 0;
    virtual ~Noticia() {}
};

#endif