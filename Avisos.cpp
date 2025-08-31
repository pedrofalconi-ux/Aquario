#include "Avisos.hpp"

void Avisos::formatar() {
    Noticia::formatar();
    if (achadosPerdido.empty()) {
        achadosPerdido = "Aviso Geral";
    }
}

void Avisos::exibir() {
}
