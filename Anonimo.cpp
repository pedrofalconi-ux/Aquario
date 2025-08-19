#include "Anonimo.hpp"
#include <iostream>

// Construtor
Anonimo::Anonimo() {}

void Anonimo::formatar() {
    // Implementação para formatar anônimo
    data.setData(0, 0, 0);  // Usa data atual
    data.setHora(0, 0);     // Usa hora atual
}

void Anonimo::exibir() {
    std::cout << "=== ANÔNIMO ===" << std::endl;
    std::cout << "Título: " << titulo << std::endl;
    std::cout << "Subtítulo: " << subtitulo << std::endl;
    std::cout << "Autor: [ANÔNIMO]" << std::endl;
    std::cout << "Data: " << data.getData() << " Hora: " << data.getHora() << std::endl;
    std::cout << "Corpo: " << corpo << std::endl;
    std::cout << "===============" << std::endl;
}
