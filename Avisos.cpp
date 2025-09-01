#include "Avisos.hpp"

void Avisos::formatar() {
    Noticia::formatar();
    if (achadosPerdidos.empty()) {
        achadosPerdidos = "Aviso Geral";
    }
}

void Avisos::exibir() {
}

string Avisos::exibirMais()
{
    return "Achados e Perdidos: " + achadosPerdidos + "\n" + "Importante: " + problemas + "\n";
}

string Avisos::getPerdidos()
{
    return achadosPerdidos;
}

string Avisos::getProblemas()
{
    return problemas;
}