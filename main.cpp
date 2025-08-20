#include "Controle.hpp"
#include <iostream>

using namespace std;

int main() {
    Controle sistema;
    sistema.animation();
    cout << "=== SISTEMA AQUÁRIO ===" << endl;
    cout << "Sistema de Gerenciamento de Notícias" << endl;
    cout << endl;
    
    int opcao;
    
    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1 - Criar Nova Notícia" << endl;
        cout << "2 - Exibir Todas as Notícias" << endl;
        cout << "3 - Gerar HTML" << endl;
        cout << "4 - Testar Editor Simples" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;
        cin.ignore(); // Limpa buffer
        
        switch(opcao) {
            case 1:
                cout << "\n--- CRIANDO NOVA NOTÍCIA ---" << endl;
                sistema.editarNoticiaAtual();
                cout << "Notícia criada com sucesso!" << endl;
                break;
                
            case 2:
                sistema.exibirNoticias();
                break;
                
            case 3:
                sistema.gerarHTML();
                break;
                
            case 4:
                cout << "\n--- EDITOR SIMPLES ---" << endl;
                sistema.executarEditor();
                cout << "Dados inseridos no editor!" << endl;
                break;
                
            case 0:
                cout << "Encerrando sistema..." << endl;
                break;
                
            default:
                cout << "Opção inválida!" << endl;
        }
        
    } while(opcao != 0);
    
    return 0;
}
