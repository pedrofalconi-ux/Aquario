#include "Controle.hpp"

char titulo[50];
char subtitulo[100];
char autor[50];
char corpo[10000];
char imagem[100];

vector<char*> textos = {titulo, subtitulo, autor, corpo, imagem};

json js;


Controle::Controle() {
    
    // Garante que todas as strings terminem com '\0'
    titulo[49] = '\0';
    subtitulo[99] = '\0';
    autor[49] = '\0';
    corpo[9999] = '\0';
    imagem[99] = '\0';

}

// Implementação do método 'mover'
void Controle::mover(int cx, int cy, char* buffer, int buffer_size) {
    int i = strlen(buffer);
    x = cx + i;
    y = cy;

    curs_set(1);
    move(y, x);

    while ((ch = getch()) != KEY_DOWN && ch != KEY_UP) {
        if (ch == '\n' || ch == '\r') break;

        switch (ch) {
            case KEY_LEFT:
                if (i > 0) { 
                    i--;
                    x--; 
                }
                break;
            case KEY_RIGHT:
                if (i < strlen(buffer)) { 
                    i++;
                    x++; 
                }
                break;
            case KEY_BACKSPACE:
            case 127: case 8:
                if (i > 0) {
                    i--;
                    x--;
                    buffer[i] = '\0';
                    mvaddch(y, x, ' ');
                }
                break;
            default:
                if (strlen(buffer) < buffer_size - 1) {
                    mvaddch(y, x, ch);
                    buffer[i] = ch;
                    i++; x++;
                    buffer[i] = '\0';
                }
                break;
        }
        move(y, x);
        refresh();
    }
    curs_set(0);
}

void Controle::executarEditor() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, yMax, xMax);
    clear();

    textos = {titulo, subtitulo, autor, corpo, imagem};
    vector<const char*> rotulos = {"Titulo:    ", "Subtitulo: ", "Autor:     ", "Corpo:     ", "Imagem:    "};
    vector<int> tamanhos = {50, 100, 50, 10000, 100};

    int campo_atual = 0;
    ch = 0;
    while (ch != '\n') {
        for (size_t i = 0; i < textos.size(); i++) {
            mvprintw(i, 0, "%s%s", rotulos[i], textos[i]);
            move(i, strlen(rotulos[i]) + strlen(textos[i]));
            clrtoeol();
        }
        
        mover(strlen(rotulos[campo_atual]), campo_atual, textos[campo_atual], tamanhos[campo_atual]);

        if (ch == '\n') break;
        else if 
            (ch == KEY_UP) campo_atual = (campo_atual > 0) ? campo_atual - 1 : textos.size() - 1;
        else 
            campo_atual = (campo_atual < textos.size() - 1) ? campo_atual + 1 : 0;
    }

    endwin();
}

void Controle::apagar(int t) {
    switch (t) {
        case Title:
            titulo[0] = '\0';
            break;
        case Subtitle:
            subtitulo[0] = '\0';
            break;
        case Author:
            autor[0] = '\0';
            break;
        case Body:
            corpo[0] = '\0';
            break;
        case Image:
            imagem[0] = '\0';
            break;

        case All:
            titulo[0] = '\0';
            subtitulo[0] = '\0';
            autor[0] = '\0';
            corpo[0] = '\0';
            imagem[0] = '\0';
            break;
        default:
            break;
    }
}

vector<string> Controle::listar() {
    vector<string> resultados_finais;

    for (auto texto_final : textos) {
        resultados_finais.push_back(string(texto_final));
    }
    return resultados_finais;

}

void Controle::salvarDados(int i) {
    ofstream arquivo;

    js["Titulo"] = titulo;
    js["Subtitulo"] = subtitulo;
    js["Autor"] = autor;
    js["Corpo"] = corpo;
    js["Imagem"] = imagem;

    string nomeArquivo = "arquivo" + to_string(i) + ".json";
    arquivo.open(nomeArquivo);

    arquivo << js;
    arquivo.close();
}

void Controle::carregarDados(int i) {
    ifstream arquivo;

    string nomeArquivo = "arquivo" + to_string(i) + ".json";
    arquivo.open(nomeArquivo);
    try {
        arquivo >> js; // Se botar um indice invalido dá erro
    } catch (json::parse_error& e) {
        std::cerr << "Erro de parsing no JSON: " << e.what() << std::endl;
    }
    arquivo.close();
    
    string json_string_recebida = js.dump();
    json dados_lidos = json::parse(json_string_recebida);

    string temp;
    temp = dados_lidos["Titulo"];
    strcpy(titulo, temp.c_str());

    temp = dados_lidos["Subtitulo"];
    strcpy(subtitulo, temp.c_str());

    temp = dados_lidos["Autor"];
    strcpy(autor, temp.c_str());

    temp = dados_lidos["Corpo"];
    strcpy(corpo, temp.c_str());

    temp = dados_lidos["Imagem"];
    strcpy(imagem, temp.c_str());
    
}

void imprimir() {

}