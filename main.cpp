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
    string option;
    
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
                sistema.salvarDados();
                cout << "Notícia criada com sucesso!" << endl;
                break;
                
            case 2:
                sistema.carregarDados();
                sistema.exibirNoticias();
                cout << "\nDeseja editar alguma notícia? Digite: [S/N]" << endl;
                cin >> option;
                if(option == "s" || option == "S" || option == "sim" || option == "Sim") {
                    cout << "Digite o indice da notícia que deseja editar: " << endl;
                    cin >> opcao;
                    cin.ignore();
                    sistema.editarNoticia(opcao - 1); //-1 pq i o primeiro indice é 0, mas visualmente botamos o 1
                }
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

        #if defined (_WIN32) || (_WIN64)
            system("cls");
        #endif

    } while(opcao != 0);
    
    return 0;
}
