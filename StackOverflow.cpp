#include "StackOverflow.hpp"


void StackOverflow::exibir() {
}

string StackOverflow::exibirMais()
{
    return "Tópico: " + topico + "\n" + "Pergunta: " + problema + "\n";
}

void StackOverflow::setTudo(const string top, const string prob)
{
    topico = top;
    problema = prob;
}
