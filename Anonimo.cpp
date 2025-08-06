#include "Anonimo.hpp"

Anonimo::Anonimo() {
    autor = "Anônimo";
}

void Anonimo::formatar() {
    data.setData(0, 0, 0); 
    data.setHora(0, 0);   
    
    autor = "Anônimo";
}

void Anonimo::exibir() {
}
