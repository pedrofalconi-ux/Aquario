#include "Avisos.hpp"

void Avisos::formatar() {
    data.setData(0, 0, 0); 
    data.setHora(0, 0);    
    
    if (achadosPerdido.empty()) {
        achadosPerdido = "Aviso Geral";
    }
}

void Avisos::exibir() {
}
