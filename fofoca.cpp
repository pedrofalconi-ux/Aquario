#include "fofoca.hpp"

void Fofoca::formatar() {
    data.setData(0, 0, 0); 
    data.setHora(0, 0);  
    
    if (autor.empty()) {
        autor = "Anônimo";
    }
}

void Fofoca::exibir() {
}
