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

    while ((ch = getch()) != KEY_DOWN && ch != KEY_UP && ch != '\n' && ch != '\r' && 
           ch != 27 && ch != 19 && ch != 12 && ch != 17 && ch != ']' &&
           ch != ('S' & 0x1F) && ch != ('L' & 0x1F) && ch != ('Q' & 0x1F)) {
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
                if (strlen(buffer) < buffer_size - 1 && ch >= 32 && ch <= 126) {
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

void Controle::executarEditor(int tipoNoticia) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, yMax, xMax);
    clear();

    textos = {titulo, subtitulo, autor, corpo, imagem};
    
    // Rótulos simples
    vector<const char*> rotulos = {
        "Titulo:    ", 
        "Subtitulo: ", 
        "Autor:     ", 
        "Corpo:     ", 
        "Imagem:    "
    };
    vector<int> tamanhos = {50, 100, 50, 10000, 100};

    int campo_atual = 0;
    ch = 0;
    
    // Determinar tipo simples
    string tipoNome = "Noticia";
    string iconeHeader = "";
    if (tipoNoticia >= 1 && tipoNoticia <= 5) {
        string tipos[] = {"", "Avisos", "Fofoca", "Humor", "StackOverflow", "Anonimo"};
        tipoNome = tipos[tipoNoticia];
    }
    
    while (true) {
        // Cabeçalho simples do editor
        mvprintw(0, 15, "EDITOR DE %s", tipoNome.c_str());
        
        // Mostrar campos simples
        for (size_t i = 0; i < textos.size(); i++) {
            if (i == campo_atual) {
                attron(A_REVERSE);
                mvprintw(3 + i, 0, ">%s%s", rotulos[i], textos[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(3 + i, 0, " %s%s", rotulos[i], textos[i]);
            }
            move(3 + i, strlen(rotulos[i]) + strlen(textos[i]) + 1);
            clrtoeol();
        }
        
        // Editar campo atual
        mover(strlen(rotulos[campo_atual]) + 1, 3 + campo_atual, textos[campo_atual], tamanhos[campo_atual]);

        // Controles simples
        mvprintw(yMax-4, 0, "Navegacao: setas ou Enter = Mudar campo");
        mvprintw(yMax-3, 0, "] = Salvar | Ctrl+L = Carregar | ESC = Sair");
        
        // Status simples
        mvprintw(yMax-1, 0, "Editando: %s | Campo: %d/5", 
                (campo_atual == 0 ? "Titulo" : 
                 campo_atual == 1 ? "Subtitulo" : 
                 campo_atual == 2 ? "Autor" : 
                 campo_atual == 3 ? "Corpo" : "Imagem"),
                campo_atual + 1);
        
        // Verificar teclas pressionadas
        if (ch == 27) { // ESC
            break;
        }
        else if (ch == ']') { // Salvar
            mvprintw(yMax-1, 0, "Salvando dados...                    ");
            refresh();
            salvarDados(tipoNoticia);
            mvprintw(yMax-1, 0, "Dados salvos! Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }
        else if (ch == 19 || ch == ('S' & 0x1F)) { // Ctrl+S
            mvprintw(yMax-1, 0, "Salvando dados...                    ");
            refresh();
            salvarDados(tipoNoticia);
            mvprintw(yMax-1, 0, "Dados salvos! Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }
        else if (ch == 12 || ch == ('L' & 0x1F)) { // Ctrl+L
            mvprintw(yMax-1, 0, "Carregando dados...                  ");
            refresh();
            carregarDados(tipoNoticia);
            mvprintw(yMax-1, 0, "Dados carregados! Pressione qualquer tecla...");
            refresh();
            getch();
        }
        else if (ch == 17 || ch == ('Q' & 0x1F)) { // Ctrl+Q
            break;
        }
        else if (ch == '\n' || ch == '\r') {
            campo_atual = (campo_atual < textos.size() - 1) ? campo_atual + 1 : 0;
        }
        else if (ch == KEY_UP) {
            campo_atual = (campo_atual > 0) ? campo_atual - 1 : textos.size() - 1;
        }
        else if (ch == KEY_DOWN) {
            campo_atual = (campo_atual < textos.size() - 1) ? campo_atual + 1 : 0;
        }
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
    js["Tipo"] = i;

    // Usar título como nome do arquivo, removendo caracteres inválidos
    string nomeArquivo = string(titulo);
    // Remover caracteres que não podem estar em nomes de arquivo
    for (char& c : nomeArquivo) {
        if (c == '/' || c == '\\' || c == ':' || c == '*' || c == '?' || c == '"' || c == '<' || c == '>' || c == '|' || c == ' ') {
            c = '_';
        }
    }
    if (nomeArquivo.empty()) {
        nomeArquivo = "noticia_" + to_string(i) + "_" + to_string(time(nullptr));
    }
    nomeArquivo += ".json";
    
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

// Função auxiliar para obter lista de arquivos JSON
vector<string> Controle::obterArquivosJSON() {
    vector<string> arquivos;
    
    // Usar comando system para listar arquivos .json
    system("ls *.json > temp_list.txt 2>/dev/null");
    
    ifstream file("temp_list.txt");
    string linha;
    while (getline(file, linha)) {
        if (!linha.empty()) {
            arquivos.push_back(linha);
        }
    }
    file.close();
    system("rm -f temp_list.txt");
    
    return arquivos;
}

// Função para carregar dados de um arquivo específico
void Controle::carregarDadosArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (arquivo.good()) {
        try {
            arquivo >> js;
            
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
        } catch (json::parse_error& e) {
            std::cerr << "Erro de parsing no JSON: " << e.what() << std::endl;
        }
    }
    arquivo.close();
}

// CRUD usando ncurses
void Controle::executarCRUD() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    int opcao = 0;
    int ch;
    
    while (true) {
        clear();
        
        // Logo simples
        mvprintw(2, 20, "SISTEMA AQUARIO");
        mvprintw(3, 18, "Gerenciamento de Noticias");
        
        // Menu simples
        mvprintw(6, 20, "MENU PRINCIPAL");
        
        mvprintw(9, 15, "1. Adicionar Noticia");
        mvprintw(10, 15, "2. Listar Noticias");
        mvprintw(11, 15, "3. Deletar Noticia");
        mvprintw(12, 15, "4. Editar Noticia");
        mvprintw(13, 15, "0. Sair do Sistema");
        
        // Destaque da opção selecionada
        mvprintw(9 + opcao, 13, ">");
        
        // Instruções simples
        mvprintw(16, 10, "Use setas para navegar | Enter para selecionar | ESC para sair");
        
        refresh();
        ch = getch();
        
        switch(ch) {
            case KEY_UP:
                opcao = (opcao > 0) ? opcao - 1 : 4;
                break;
            case KEY_DOWN:
                opcao = (opcao < 4) ? opcao + 1 : 0;
                break;
            case '\n':
            case '\r':
                switch(opcao) {
                    case 0: // Adicionar
                        adicionarNoticia();
                        break;
                    case 1: // Listar
                        listarNoticias();
                        break;
                    case 2: // Deletar
                        deletarNoticia();
                        break;
                    case 3: // Editar
                        editarNoticiaExistente();
                        break;
                    case 4: // Sair
                        endwin();
                        return;
                }
                break;
            case 27: // ESC
                endwin();
                return;
        }
    }
}

void Controle::adicionarNoticia() {
    clear();
    
    // Cabeçalho simples
    mvprintw(2, 20, "ADICIONAR NOTICIA");
    mvprintw(4, 15, "Selecione o tipo de noticia:");
    
    // Tipos simples
    mvprintw(7, 15,  "1. Avisos");
    mvprintw(8, 15,  "2. Fofoca");
    mvprintw(9, 15,  "3. Humor");
    mvprintw(10, 15, "4. StackOverflow");
    mvprintw(11, 15, "5. Anonimo");
    mvprintw(12, 15, "0. Voltar");
    
    int opcao = 0;
    int ch; 
    
    while (true) {
        // Limpar destaques
        for (int i = 0; i <= 5; i++) {
            mvprintw(7 + i, 13, " ");
        }
        
        // Destacar opção atual
        mvprintw(7 + opcao, 13, ">");
        
        // Instruções
        mvprintw(15, 10, "Use setas para navegar | Enter para confirmar | ESC para voltar");
        
        refresh();
        ch = getch();
        
        switch(ch) {
            case KEY_UP:
                opcao = (opcao > 0) ? opcao - 1 : 5;
                break;
            case KEY_DOWN:
                opcao = (opcao < 5) ? opcao + 1 : 0;
                break;
            case '\n':
            case '\r':
                if (opcao == 5) {
                    return; // Voltar
                } else {
                    // Limpar campos antes de editar
                    apagar(All);
                    endwin();
                    executarEditor(opcao + 1); // Passar o tipo correto
                    initscr();
                    cbreak();
                    noecho();
                    keypad(stdscr, TRUE);
                    return;
                }
                break;
            case 27: // ESC
                return;
        }
    }
}

void Controle::listarNoticias() {
    vector<string> arquivos = obterArquivosJSON();
    
    if (arquivos.empty()) {
        clear();
        mvprintw(5, 20, "LISTAR NOTICIAS");
        mvprintw(10, 15, "Aquario vazio!");
        mvprintw(11, 15, "Nenhuma noticia encontrada.");
        mvprintw(15, 15, "Dica: Crie noticias no menu principal");
        mvprintw(18, 15, "Pressione qualquer tecla para voltar...");
        refresh();
        getch();
        return;
    }
    
    int opcaoAtual = 0;
    int ch;
    
    while (true) {
        clear();
        
        // Cabeçalho simples
        mvprintw(2, 20, "LISTAR NOTICIAS");
        mvprintw(4, 5, "Use setas para navegar | Enter para detalhes | ESC para voltar");
        
        // Mostrar lista de arquivos simples
        for (size_t i = 0; i < arquivos.size(); i++) {
            carregarDadosArquivo(arquivos[i]);
            vector<string> dados = listar();
            
            // Determinar tipo simples
            string tipoStr = "Desconhecido";
            ifstream arqTemp(arquivos[i]);
            if (arqTemp.good()) {
                json jsTemp;
                arqTemp >> jsTemp;
                if (jsTemp.contains("Tipo")) {
                    int tipo = jsTemp["Tipo"];
                    string tipos[] = {"", "Avisos", "Fofoca", "Humor", "StackOverflow", "Anonimo"};
                    if (tipo >= 1 && tipo <= 5) {
                        tipoStr = tipos[tipo];
                    }
                }
            }
            arqTemp.close();
            
            if (i == opcaoAtual) {
                attron(A_REVERSE);
                mvprintw(7 + i, 5, "> [%s] %s", tipoStr.c_str(), dados[0].c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(7 + i, 5, "  [%s] %s", tipoStr.c_str(), dados[0].c_str());
            }
        }
        
        // Preview simples
        if (!arquivos.empty()) {
            carregarDadosArquivo(arquivos[opcaoAtual]);
            vector<string> dados = listar();
            
            int linha_detalhe = 7 + arquivos.size() + 2;
            mvprintw(linha_detalhe, 5, "--- PREVIEW ---");
            mvprintw(linha_detalhe + 1, 5, "Titulo: %.45s", dados[0].c_str());
            mvprintw(linha_detalhe + 2, 5, "Autor: %.45s", dados[2].c_str());
            mvprintw(linha_detalhe + 3, 5, "Resumo: %.45s", dados[3].c_str());
        }
        
        refresh();
        ch = getch();
        
        switch(ch) {
            case KEY_UP:
                opcaoAtual = (opcaoAtual > 0) ? opcaoAtual - 1 : arquivos.size() - 1;
                break;
            case KEY_DOWN:
                opcaoAtual = (opcaoAtual < arquivos.size() - 1) ? opcaoAtual + 1 : 0;
                break;
            case '\n':
            case '\r': {
                // Mostrar detalhes completos com design melhorado
                clear();
                carregarDadosArquivo(arquivos[opcaoAtual]);
                vector<string> dados = listar();
                
                mvprintw(2, 15, "DETALHES COMPLETOS");
                mvprintw(4, 5, "Titulo: %s", dados[0].c_str());
                mvprintw(5, 5, "Subtitulo: %s", dados[1].c_str());
                mvprintw(6, 5, "Autor: %s", dados[2].c_str());
                mvprintw(7, 5, "Imagem: %s", dados[4].c_str());
                
                mvprintw(9, 5, "--- CONTEUDO ---");
                
                // Quebrar corpo em múltiplas linhas simples
                string corpo = dados[3];
                int linha_corpo = 10;
                size_t pos = 0;
                while (pos < corpo.length() && linha_corpo < 20) {
                    string linha = corpo.substr(pos, 50);
                    mvprintw(linha_corpo++, 5, "%s", linha.c_str());
                    pos += 50;
                }
                
                mvprintw(22, 15, "Pressione qualquer tecla para voltar...");
                refresh();
                getch();
                break;
            }
            case 27: // ESC
                return;
        }
    }
}

void Controle::deletarNoticia() {
    vector<string> arquivos = obterArquivosJSON();
    
    if (arquivos.empty()) {
        clear();
        mvprintw(5, 20, "DELETAR NOTICIAS");
        mvprintw(10, 15, "Aquario vazio!");
        mvprintw(11, 15, "Nenhuma noticia para deletar.");
        mvprintw(15, 15, "Crie noticias primeiro!");
        mvprintw(18, 15, "Pressione qualquer tecla para voltar...");
        refresh();
        getch();
        return;
    }
    
    int opcaoAtual = 0;
    int ch;
    
    while (true) {
        clear();
        
        // Cabeçalho simples
        mvprintw(2, 20, "DELETAR NOTICIAS");
        mvprintw(4, 5, "CUIDADO: Selecione a noticia para DELETAR PERMANENTEMENTE");
        mvprintw(5, 5, "Use setas para navegar | Enter para deletar | ESC para cancelar");
        
        // Lista simples
        for (size_t i = 0; i < arquivos.size(); i++) {
            carregarDadosArquivo(arquivos[i]);
            vector<string> dados = listar();
            
            // Tipo simples
            string tipoStr = "Desconhecido";
            ifstream arqTemp(arquivos[i]);
            if (arqTemp.good()) {
                json jsTemp;
                arqTemp >> jsTemp;
                if (jsTemp.contains("Tipo")) {
                    int tipo = jsTemp["Tipo"];
                    string tipos[] = {"", "Avisos", "Fofoca", "Humor", "StackOverflow", "Anonimo"};
                    if (tipo >= 1 && tipo <= 5) {
                        tipoStr = tipos[tipo];
                    }
                }
            }
            arqTemp.close();
            
            if (i == opcaoAtual) {
                attron(A_REVERSE);
                mvprintw(8 + i, 5, "> [DEL] [%s] %s", tipoStr.c_str(), dados[0].c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(8 + i, 5, "       [%s] %s", tipoStr.c_str(), dados[0].c_str());
            }
        }
        
        // Preview simples
        if (!arquivos.empty()) {
            carregarDadosArquivo(arquivos[opcaoAtual]);
            vector<string> dados = listar();
            
            int linha_preview = 8 + arquivos.size() + 2;
            mvprintw(linha_preview, 5, "--- SERA DELETADA ---");
            mvprintw(linha_preview + 1, 5, "Titulo: %.35s", dados[0].c_str());
            mvprintw(linha_preview + 2, 5, "Autor: %.35s", dados[2].c_str());
            mvprintw(linha_preview + 3, 5, "Arquivo: %.35s", arquivos[opcaoAtual].c_str());
        }
        
        refresh();
        ch = getch();
        
        switch(ch) {
            case KEY_UP:
                opcaoAtual = (opcaoAtual > 0) ? opcaoAtual - 1 : arquivos.size() - 1;
                break;
            case KEY_DOWN:
                opcaoAtual = (opcaoAtual < arquivos.size() - 1) ? opcaoAtual + 1 : 0;
                break;
            case '\n':
            case '\r': {
                // Tela de confirmação melhorada
                clear();
                carregarDadosArquivo(arquivos[opcaoAtual]);
                vector<string> dados = listar();
                
                mvprintw(3, 15, "CONFIRMACAO CRITICA");
                mvprintw(5, 10, "ATENCAO! Esta acao e IRREVERSIVEL!");
                mvprintw(7, 10, "Titulo: %s", dados[0].c_str());
                mvprintw(8, 10, "Autor: %s", dados[2].c_str());
                mvprintw(9, 10, "Arquivo: %s", arquivos[opcaoAtual].c_str());
                
                // Opções simples
                mvprintw(12, 15, "Confirme sua decisao:");
                mvprintw(14, 20, "SIM - Deletar PERMANENTEMENTE");
                mvprintw(15, 20, "NAO - Cancelar e manter seguro");
                
                int opcaoConfirm = 1; // Começar em NÃO por segurança
                int chConfirm;
                
                while (true) {
                    // Destacar opção selecionada
                    mvprintw(14, 18, " ");
                    mvprintw(15, 18, " ");
                    
                    if (opcaoConfirm == 0) {
                        mvprintw(14, 18, ">");
                        attron(A_REVERSE);
                        mvprintw(14, 20, "SIM - Deletar PERMANENTEMENTE");
                        attroff(A_REVERSE);
                        mvprintw(15, 20, "NAO - Cancelar e manter seguro");
                    } else {
                        mvprintw(15, 18, ">");
                        mvprintw(14, 20, "SIM - Deletar PERMANENTEMENTE");
                        attron(A_REVERSE);
                        mvprintw(15, 20, "NAO - Cancelar e manter seguro");
                        attroff(A_REVERSE);
                    }
                    
                    mvprintw(18, 5, "Use setas para navegar - Enter para confirmar - ESC para fugir");
                    mvprintw(19, 5, "Atalhos: S = Deletar - N = Cancelar");
                    refresh();
                    
                    chConfirm = getch();
                    
                    switch(chConfirm) {
                        case KEY_UP:
                            opcaoConfirm = (opcaoConfirm == 0) ? 1 : 0;
                            break;
                        case KEY_DOWN:
                            opcaoConfirm = (opcaoConfirm == 1) ? 0 : 1;
                            break;
                        case '\n':
                        case '\r':
                            if (opcaoConfirm == 0) { // SIM - Deletar
                                if (remove(arquivos[opcaoAtual].c_str()) == 0) {
                                    clear();
                                    mvprintw(10, 15, "NOTICIA DELETADA!");
                                    mvprintw(12, 15, "Operacao realizada com sucesso!");
                                } else {
                                    clear();
                                    mvprintw(10, 15, "ERRO CRITICO!");
                                    mvprintw(12, 15, "Nao foi possivel deletar o arquivo!");
                                }
                                mvprintw(15, 15, "Pressione qualquer tecla para voltar...");
                                refresh();
                                getch();
                                return;
                            } else { // NÃO - Cancelar
                                clear();
                                mvprintw(10, 15, "NOTICIA SALVA!");
                                mvprintw(12, 15, "Operacao cancelada com sabedoria!");
                                mvprintw(15, 15, "Pressione qualquer tecla para voltar...");
                                refresh();
                                getch();
                                return;
                            }
                            break;
                        case 27: // ESC
                            clear();
                            mvprintw(10, 15, "FUGA REALIZADA!");
                            mvprintw(12, 15, "Sua noticia continua segura");
                            mvprintw(15, 15, "Pressione qualquer tecla para voltar...");
                            refresh();
                            getch();
                            return;
                        case 's':
                        case 'S':
                            // Atalho direto para deletar
                            if (remove(arquivos[opcaoAtual].c_str()) == 0) {
                                clear();
                                mvprintw(10, 15, "NOTICIA VAPORIZADA!");
                            } else {
                                clear();
                                mvprintw(10, 15, "ERRO: Nao foi possivel deletar!");
                            }
                            mvprintw(15, 15, "Pressione qualquer tecla para voltar...");
                            refresh();
                            getch();
                            return;
                        case 'n':
                        case 'N':
                            // Atalho direto para cancelar
                            clear();
                            mvprintw(10, 15, "CANCELADO! Sua noticia esta salva!");
                            mvprintw(15, 15, "Pressione qualquer tecla para voltar...");
                            refresh();
                            getch();
                            return;
                    }
                }
                break;
            }
            case 27: // ESC
                return;
        }
    }
}

void Controle::editarNoticiaExistente() {
    vector<string> arquivos = obterArquivosJSON();
    
    if (arquivos.empty()) {
        clear();
        mvprintw(2, 15, "=== EDITAR NOTICIA ===");
        mvprintw(10, 15, "Nenhuma noticia encontrada para editar!");
        mvprintw(22, 10, "Pressione qualquer tecla para voltar...");
        refresh();
        getch();
        return;
    }
    
    int opcaoAtual = 0;
    int ch;
    
    clear();
    mvprintw(2, 15, "EDITAR NOTICIA");
    mvprintw(4, 5, "Selecione a noticia para EDITAR - Use setas para navegar, Enter para editar, ESC para voltar");
    
    while (true) {        // Mostrar lista de arquivos
        for (size_t i = 0; i < arquivos.size(); i++) {
            // Carregar dados do arquivo para mostrar título e tipo
            carregarDadosArquivo(arquivos[i]);
            vector<string> dados = listar();
            
            // Determinar o tipo
            string tipoStr = "Desconhecido";
            int tipoNum = 1;
            ifstream arqTemp(arquivos[i]);
            if (arqTemp.good()) {
                json jsTemp;
                arqTemp >> jsTemp;
                if (jsTemp.contains("Tipo")) {
                    tipoNum = jsTemp["Tipo"];
                    string tipos[] = {"", "Avisos", "Fofoca", "Humor", "StackOverflow", "Anonimo"};
                    if (tipoNum >= 1 && tipoNum <= 5) {
                        tipoStr = tipos[tipoNum];
                    }
                }
            }
            arqTemp.close();
            
            if (i == opcaoAtual) {
                attron(A_REVERSE);
                mvprintw(7 + i, 5, "> [%s] %s", tipoStr.c_str(), dados[0].c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(7 + i, 5, "  [%s] %s", tipoStr.c_str(), dados[0].c_str());
            }
        }
        
        // Preview simples
        if (!arquivos.empty()) {
            carregarDadosArquivo(arquivos[opcaoAtual]);
            vector<string> dados = listar();
            
            int linha_preview = 7 + arquivos.size() + 2;
            mvprintw(linha_preview, 5, "--- PREVIEW ---");
            mvprintw(linha_preview + 1, 5, "Titulo: %s", dados[0].c_str());
            mvprintw(linha_preview + 2, 5, "Autor: %s", dados[2].c_str());
            mvprintw(linha_preview + 3, 5, "Corpo: %.30s%s", dados[3].c_str(),
                    dados[3].length() > 30 ? "..." : "");
        }
        
        refresh();
        ch = getch();
        
        switch(ch) {
            case KEY_UP:
                opcaoAtual = (opcaoAtual > 0) ? opcaoAtual - 1 : arquivos.size() - 1;
                break;
            case KEY_DOWN:
                opcaoAtual = (opcaoAtual < arquivos.size() - 1) ? opcaoAtual + 1 : 0;
                break;
            case '\n':
            case '\r': {
                // Carregar dados e editar
                carregarDadosArquivo(arquivos[opcaoAtual]);
                
                // Remover arquivo antigo antes de editar
                string arquivoAntigo = arquivos[opcaoAtual];
                
                // Determinar o tipo para o editor
                int tipoNum = 1;
                ifstream arqTemp(arquivos[opcaoAtual]);
                if (arqTemp.good()) {
                    json jsTemp;
                    arqTemp >> jsTemp;
                    if (jsTemp.contains("Tipo")) {
                        tipoNum = jsTemp["Tipo"];
                    }
                }
                arqTemp.close();
                
                endwin();
                executarEditor(tipoNum);
                
                // Remover arquivo antigo após salvar com novo nome
                if (arquivoAntigo != string(titulo) + ".json") {
                    remove(arquivoAntigo.c_str());
                }
                
                initscr();
                cbreak();
                noecho();
                keypad(stdscr, TRUE);
                return;
            }
            case 27: // ESC
                return;
        }
    }
}