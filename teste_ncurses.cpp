#include <ncurses.h>
#include <iostream>

using namespace std;

int main() {
    cout << "Testando ncurses básico..." << endl;
    cout << "Pressione Enter para continuar..." << endl;
    cin.get();
    
    // Inicializar ncurses
    initscr();
    
    // Mostrar mensagem
    mvprintw(5, 10, "=== TESTE NCURSES ===");
    mvprintw(7, 10, "Isso deveria aparecer em uma tela limpa!");
    mvprintw(8, 10, "Use as setas para navegar");
    mvprintw(10, 10, "Pressione 'q' para sair");
    
    // Atualizar tela
    refresh();
    
    // Esperar input
    int ch;
    while ((ch = getch()) != 'q') {
        mvprintw(12, 10, "Tecla pressionada: %c (codigo: %d)", ch, ch);
        refresh();
    }
    
    // Finalizar ncurses
    endwin();
    
    cout << "Teste finalizado!" << endl;
    return 0;
}
