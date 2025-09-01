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
    int tipo; // ADICIONADO: Variável para guardar o tipo da notícia

public:
    std::string getDataFormatada() const { return data.getDataFormatada(); }
    std::string getHoraFormatada() const { return data.getHoraFormatada(); }
    // Métodos para definir dados da notícia
    void setTitulo( std::string t) { titulo = t; }
    void setSubtitulo( std::string s) { subtitulo = s; }
    void setCorpo( std::string c) { corpo = c; }
    void setAutor( std::string a) { autor = a; }
    void setImagem( std::string i) { imagem = i; }
    void setTipo(int t) { tipo = t; } 
    
    // Métodos para obter dados da notícia
    std::string getTitulo()  { return titulo; }
    std::string getSubtitulo()  { return subtitulo; }
    std::string getCorpo()  { return corpo; }
    std::string getAutor()  { return autor; }
    std::string getImagem()  { return imagem; }
    int getTipo()  { return tipo; } 
    string getData() { return data.getData(); }
    void setData(int di, int me, int an) { data.setData(di,me,an); }
    string getHora() { return data.getHora(); }
    void setHora(int ho, int mi) { data.setHora(ho, mi); }

    void formatar() {
        if (autor.empty()) {
            autor = "Anônimo";
        }
    }
    virtual void exibir() = 0;
    virtual ~Noticia() {}
};

#endif