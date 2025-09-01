#ifndef AVISOS_HPP
#define AVISOS_HPP

#include "Noticia.hpp"
#include <string>

class Avisos : public Noticia {
private:
    std::string achadosPerdidos;
    std::string problemas;
    

public:
    void formatar();
    void exibir() override;
    
    // Métodos específicos para Avisos
    void setCategoria(const std::string& categoria) { achadosPerdidos = categoria; }
    void setProblema(const string& p) { problemas = p; }
    std::string getCategoria() const { return achadosPerdidos; }
    string exibirMais();
    string getPerdidos();
    string getProblemas();
};

#endif
