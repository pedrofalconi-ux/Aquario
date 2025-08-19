#include "Controle.hpp"
#include <iostream>

using namespace std;

int main() {
    try {
        Controle sistema;
        sistema.executarCRUD();
        return 0;
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }
}
