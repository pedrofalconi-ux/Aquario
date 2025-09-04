#include "Controle.hpp"

//Roda tudo da main
void Controle::iniciar_a_Porra_Toda() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();

    cout << "=== SISTEMA AQUARIO ===" << endl;
    cout << "Sistema de Gerenciamento de Noticias" << endl;
    cout << endl;
    
    int opcao;
    string option;
    string problem;

    do {
        
        vector<const char*> tipos = {
            "Criar Nova Nota",
            "Exibir Todas as Notas",
            "Deletar Nota", 
            "Gerar HTML",
            "Sair"
        };

        int escolha = 0;
        int ch = 0;

        while(ch != '\n') {
            clear();
            mvprintw(0, 0, "=== SELECIONAR ===");

            for(size_t i = 0; i < tipos.size(); i++) {
                if((int)i == escolha) {
                    attron(A_REVERSE);
                    mvprintw(i + 2, 0, "> %s", tipos[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(i + 2, 0, "  %s", tipos[i]);
                }
            }

            mvprintw(8, 0, "Use setas para navegar, Enter para selecionar\n\n %s", problem.c_str());
            refresh();

            ch = getch();

            switch(ch) {
                case KEY_UP:
                    escolha = (escolha > 0) ? escolha - 1 : tipos.size() - 1;
                    break;
                case KEY_DOWN:
                    escolha = (escolha < (int)tipos.size() - 1) ? escolha + 1 : 0;
                    break;
            }
        }

        opcao = escolha;

        switch(opcao) {

                case 0:
                    problem.clear();
                    cout << "\n--- CRIANDO NOVA NOTA ---" << endl;
                    try
                    {
                    editarNoticiaAtual();
                    salvarDados();
                    cout << "Nota criada com sucesso!" << endl;
                    }
                    catch(int ui)
                    {

                    }
                    break;

                case 1:
                    cout << "Escolha a Nota que deseja editar: " << endl;
                    try
                    {
                    editarNoticia(pesquisar());
                    }
                    catch(range_error e)
                    {
                        problem = e.what();
                    }
                    catch(int iu)
                    {

                    }
                    
                    break;

                case 2:
                    problem.clear();
                    try
                    {
                        deletarNoticia();
                    }
                    catch(range_error e)
                    {
                        problem = e.what();
                    }
                    catch(int oi)
                    {

                    }
                    break;
                
                case 3:
                    gerarHTML();
                    break;

                case 4:
                    cout << "Encerrando sistema..." << endl;
                    break;

                default:
                    cout << "Opcao invalida!" << endl;
            }

            #if defined (_WIN32) || (_WIN64)
                system("cls");
            #endif

    } while (opcao != 4);

    endwin();
}

void Controle::selecionarTipoNoticia() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    
    vector<const char*> tipos = {
        "0 - Ideia",
        "1 - Lembrete", 
        "2 - Pensamento",
        "3 - Diario",
        "4 - Outro"
    };
    
    int escolha = 0;
    int ch = 0;
    
    while(ch != '\n') {
        clear();
        mvprintw(0, 0, "=== SELECIONAR TIPO DE NOTA ===");
        
        for(size_t i = 0; i < tipos.size(); i++) {
            if((int)i == escolha) {
                attron(A_REVERSE);
                mvprintw(i + 2, 0, "> %s", tipos[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i + 2, 0, "  %s", tipos[i]);
            }
        }
        
        mvprintw(8, 0, "Use setas para navegar, Enter para selecionar");
        refresh();
        
        ch = getch();
        
        switch(ch) {
            case KEY_UP:
                escolha = (escolha > 0) ? escolha - 1 : tipos.size() - 1;
                break;
            case KEY_DOWN:
                escolha = (escolha < (int)tipos.size() - 1) ? escolha + 1 : 0;
                break;
            case L'\033':
                throw 6;
                break;
        }
    }
    
    tipoNoticiaAtual = escolha;
    endwin();
}

void Controle::editarNoticiaAtual() {
    
    apagar(All); //Somente limpando o buffer
    selecionarTipoNoticia();
    
    executarEditor();
}

string Controle::exibirNoticias(int ind) {

    string lista;

    lista = "\n--- NOTA " + to_string(ind + 1) + " ---" + "\n"
          + "Tipo: " + getTipoNoticiaString(noticias[ind]->getTipo()) + "\n"
          + "Autor: " + noticias[ind]->getAutor() + "\n"
          + "Titulo: " + noticias[ind]->getTitulo() + "\n";

    auto* temp_ptr = noticias[ind].get();

    switch(noticias[ind]->getTipo())
    {
        case 0:
            lista += dynamic_cast<Avisos*>(temp_ptr)->exibirMais();
            break;
        case 1:
            lista += dynamic_cast<Fofoca*>(temp_ptr)->exibirMais();
            break;
        case 2:
            lista += dynamic_cast<Humor*>(temp_ptr)->exibirMais();
            break;
        case 3:
            lista += dynamic_cast<StackOverflow*>(temp_ptr)->exibirMais();
            break;
    }

    lista += + "Data: " + noticias[ind]->getData().substr(0, 2) + "/" + noticias[ind]->getData().substr(2, 2) + "/" + noticias[ind]->getData().substr(4) + "\n"
            + "Hora: " + noticias[ind]->getHora().substr(0, 2) + ":" + noticias[ind]->getHora().substr(2) + "\n";

    return lista;
}

string Controle::getTipoNoticiaString(int tipo) {
    switch(tipo) {
        case 0: return "Ideia";
        case 1: return "Lembrete";
        case 2: return "Pensamento"; 
        case 3: return "Diario";
        case 4: return "Outro";
        default: return "Desconhecido";
    }
}

void Controle::deletarNoticia() {
    int indiceParaDeletar = pesquisar();

    if (indiceParaDeletar == -1) {
        throw range_error("Nenhuma nota foi criada!!!!");
    }

    // Inicia uma tela de confirmação temporária
    initscr();
    cbreak();
    noecho();
    clear();
    mvprintw(0, 0, "Tem certeza que deseja deletar a nota %d (S/N)", indiceParaDeletar);
    refresh();

    int confirmacao = getch();
    
    endwin();

    if (confirmacao != 's' && confirmacao != 'S') {
        refresh();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        return;
    }

    json indiceJson;
    int maxIndice = -1;
    ifstream if_indice("./Pasta/Indice.json");
    if (if_indice.is_open()) {
        if_indice >> indiceJson;
        if_indice.close();
        if (indiceJson.count("Indice")) {
            maxIndice = indiceJson["Indice"].get<int>();
        }
    }

    if (maxIndice == -1) {
        refresh();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        return; 
    }

    string nomeArquivoParaDeletar = "./Pasta/arquivo" + to_string(indiceParaDeletar) + ".json";

    try {
        if (fs::exists(nomeArquivoParaDeletar)) {
            fs::remove(nomeArquivoParaDeletar);
        }

        for (int i = indiceParaDeletar; i < maxIndice; ++i) {
            string oldName = "./Pasta/arquivo" + to_string(i + 1) + ".json";
            string newName = "./Pasta/arquivo" + to_string(i) + ".json";
            if (fs::exists(oldName)) {
                fs::rename(oldName, newName);
            }
        }

        ofstream of_indice("./Pasta/Indice.json");
        indiceJson["Indice"] = maxIndice - 1;
        of_indice << indiceJson;
        of_indice.close();

    } catch (const filesystem::filesystem_error& e) {
        
    }

    refresh();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

Controle::Controle() {
    titulo[0] = '\0';
    subtitulo[0] = '\0';
    autor[0] = '\0';
    data[0] = '\0';
    hora[0] = '\0';

    textos = {titulo, subtitulo, autor, data, hora};
    
    // Inicializa tipo de notícia padrão
    tipoNoticiaAtual = 0; // Avisos por padrão
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

    textos = {titulo, subtitulo, autor, data, hora};
    vector<const char*> rotulos = {"Titulo:    ", "Descricao: ", "Autor:     ", "Data:    ", "Hora:    "};
    vector<int> tamanhos = {50, 10000, 50, 9, 5};

    int campo_atual = 0;
    ch = 0;

    while (ch != '\n') {

        if (ch == L'\033') {
            throw 8000;
        }

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
        case Dataa:
            data[0] = '\0';
            break;
        case Hour:
            hora[0] = '\0';
            break;

        case All:
            titulo[0] = '\0';
            subtitulo[0] = '\0';
            autor[0] = '\0';
            data[0] = '\0';
            hora[0] = '\0';
            break;
        default:
            break;
    }
}

void Controle::salvarDadoIndice(int contador) {

    const string finalPath = "./Pasta/arquivo" + to_string(contador) + ".json";
    const string tmpPath   = finalPath + ".tmp";

    // Sistema de segurança pois o sistema não aceita acentos
    try {
        Data dataFormt;
        int dia = 0, mes = 0, ano = 0, h = 0, min = 0;
        sscanf(data, "%2d%2d%4d", &dia, &mes, &ano);
        sscanf(hora, "%2d%2d", &h, &min);
        dataFormt.setData(dia, mes, ano);
        dataFormt.setHora(h, min);
        strcpy(data, dataFormt.getData().c_str());
        strcpy(hora, dataFormt.getHora().c_str());


        json j;
        j["Titulo"] = titulo;
        j["Subtitulo"] = subtitulo;
        j["Autor"] = autor;
        j["Tipo"] = tipoNoticiaAtual;
        j["Data"] = data;
        j["Hora"] = hora;


        {
            ofstream arq(tmpPath, ios::binary);
            if (!arq.is_open()) {
                cerr << "Erro ao abrir arquivo temp para escrita: " << tmpPath << endl;
                return;
            }

            arq << j;      
            if (!arq.good()) throw runtime_error("Falha ao escrever JSON no arquivo temp");
        }

        // Renomeia para o destino final (atômico)
        filesystem::rename(tmpPath, finalPath);
    }
    catch (const nlohmann::json::exception& e) {
        // Erro de JSON (ex.: UTF-8 inválido) -> NÃO cria arquivo
        if (filesystem::exists(tmpPath)) filesystem::remove(tmpPath);
        cerr << "Erro JSON em salvarDadoIndice: " << e.what() << endl;
        return;
    }
    catch (const exception& e) {
        // Qualquer outro erro de IO -> garante não deixar temp para trás
        if (filesystem::exists(tmpPath)) filesystem::remove(tmpPath);
        cerr << "Erro em salvarDadoIndice: " << e.what() << endl;
        return;
    }
}


void Controle::carregarDadoIndice(int indice) {
    ifstream arquivo;

   string nomeArquivo = "./Pasta/arquivo" + to_string(indice) + ".json";
    arquivo.open(nomeArquivo);
        if(arquivo.is_open()) {
            try {
                arquivo >> js; // Se botar um indice invalido dá erro
            } catch (json::parse_error& e) {
                cerr << "Erro de parsing no JSON: carregarDadoIndice" << e.what() << endl;
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

            temp = dados_lidos["Data"];
            strcpy(data, temp.c_str());

            temp = dados_lidos["Hora"];
            strcpy(hora, temp.c_str());
        }
}

void Controle::editarNoticia(int indice) {

    if (indice == -1) {
        throw 8000;
    }
    carregarDadoIndice(indice);
    executarEditor();
    salvarDadoIndice(indice);
}

void Controle::salvarDados() {

    const string dir = "Pasta";
    filesystem::create_directory(dir);

    json indice;
    int contador = 0;
    {
        ifstream if_indice("./Pasta/Indice.json");
        if (if_indice.is_open()) {
            if_indice >> indice;
            if (indice.count("Indice")) {
                contador = indice["Indice"].get<int>() + 1;
            }
        }
    }

    const string finalPath = "./Pasta/arquivo" + to_string(contador) + ".json";
    const string tmpPath   = finalPath + ".tmp";

    // Sistema de segurança pois o sistema não aceita acentos
    try {
        Data dataFormt;
        int dia = 0, mes = 0, ano = 0, h = 0, min = 0;
        sscanf(data, "%2d%2d%4d", &dia, &mes, &ano);
        sscanf(hora, "%2d%2d", &h, &min);
        dataFormt.setData(dia, mes, ano);
        dataFormt.setHora(h, min);
        strcpy(data, dataFormt.getData().c_str());
        strcpy(hora, dataFormt.getHora().c_str());

        json j;
        j["Titulo"] = titulo;
        j["Subtitulo"] = subtitulo;
        j["Autor"] = autor;
        j["Tipo"] = tipoNoticiaAtual;
        j["Data"] = data;
        j["Hora"] = hora;

        {
            ofstream arq(tmpPath, ios::binary);
            if (!arq.is_open()) {
                cerr << "Erro ao abrir arquivo temp para escrita: " << tmpPath << endl;
                return;
            }

            arq << j;          
            if (!arq.good()) throw runtime_error("Falha ao escrever JSON no arquivo temp");
        }

        filesystem::rename(tmpPath, finalPath);
        // **Só aqui** atualiza o índice porque deu tudo certo
        {
            ofstream of_indice("./Pasta/Indice.json");
            indice["Indice"] = contador;
            of_indice << indice;
        }
    }
    catch (const nlohmann::json::exception& e) {
        if (filesystem::exists(tmpPath)) filesystem::remove(tmpPath);
        cerr << "Erro JSON em salvarDados: " << e.what() << endl;
        // Não cria arquivo e NÃO atualiza Indice.json
        return;
    }
    catch (const exception& e) {
        if (filesystem::exists(tmpPath)) filesystem::remove(tmpPath);
        cerr << "Erro em salvarDados: " << e.what() << endl;
        // Não cria arquivo e NÃO atualiza Indice.json
        return;
    }
}




void Controle::carregarDados() {
    ifstream arquivo;
    json indice;
    int contador;

    ifstream if_indice("./Pasta/Indice.json");
    if (if_indice.is_open()) {
        if_indice >> indice;
        if_indice.close();

        if (indice.count("Indice")) {
            contador = indice["Indice"].get<int>();
        }
        
        for (int i = 0; i <= contador; i++) {
            string nomeArquivo = "./Pasta/arquivo" + to_string(i) + ".json";
            arquivo.open(nomeArquivo);
            try {
                arquivo >> js; // Se botar um indice invalido dá erro
            } catch (json::parse_error& e) {
                cerr << "Erro de parsing no JSON: carregarDados" << e.what() << endl;
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

            temp = dados_lidos["Data"];
            strcpy(data, temp.c_str());

            temp = dados_lidos["Hora"];
            strcpy(hora, temp.c_str());
        
            tipoNoticiaAtual = dados_lidos["Tipo"].get<int>();
        
            criarNoticia(tipoNoticiaAtual);

        }
    }
}

// ========== NOVOS MÉTODOS PARA INTEGRAÇÃO DE CONTROLE COM NOTICIA ==========

void Controle::criarNoticia(int tipo) {
    unique_ptr<Noticia> novaNoticia;
    
    switch(tipo) {
        case 0: novaNoticia = make_unique<Avisos>(); break;
        case 1: novaNoticia = make_unique<Fofoca>(); break;
        case 2: novaNoticia = make_unique<Humor>(); break;
        case 3: novaNoticia = make_unique<StackOverflow>(); break;
        case 4: novaNoticia = make_unique<Anonimo>(); break;
        default: novaNoticia = make_unique<Avisos>(); break;
    }
    
    novaNoticia->setTitulo(string(titulo));
    novaNoticia->setSubtitulo(string(subtitulo));
    novaNoticia->setAutor(string(autor));

    novaNoticia->setTipo(tipo);
    
        int dia = 0, mes = 0, ano = 0, h = 0, min = 0;

        sscanf(data, "%2d%2d%4d", &dia, &mes, &ano);
        sscanf(hora, "%2d%2d", &h, &min);

        novaNoticia->setData(dia, mes, ano);
        novaNoticia->setHora(h, min);
    
    novaNoticia->formatar();
    noticias.push_back(move(novaNoticia));
}

int Controle::pesquisar() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, yMax, xMax);
    clear();

    char bufe[256];   // buffer de busca
    bufe[0] = '\0';
    int car = 0;      // posição dentro do buffer
    x = 1;

    vector<string> nomes;
    vector<int> indv;

    noticias.clear();
    carregarDados();

    int ind = -1;
    int escolha = 0;

    ch = ' ';
    while (ch != '\n') {
        clear();
        nomes.clear();
        indv.clear();

        // Voltar caso clique Esc
        if (ch == '\033') {
            throw 8000;
        }

        // Filtra notícias
        for (int i = 0; i < (int)noticias.size(); i++) {
            if (strstr(noticias.at(i)->getTitulo().c_str(), bufe) != nullptr || strlen(bufe) == 0) {
                nomes.push_back(noticias.at(i)->getTitulo());
                indv.push_back(i);
            }
        }

        mvprintw(0, 0, "======Pesquisar======");
        mvprintw(1, 1, "%s", bufe);

        for (size_t i = 0; i < nomes.size(); i++) {
            string linha = ((int)i == escolha ? "> " : "  ") + nomes[i];
            if ((int)i == escolha) {
                attron(A_REVERSE);
                mvprintw(i + 3, 0, linha.c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(i + 3, 0, linha.c_str());
            }
        }

        mvprintw(nomes.size() + 4, 0, "=== Nada Encontrado ===");

        move(1, x);
        
        //Segurança para evitar uns crash de entrar num vetor vazio
        if (!indv.empty()) {
            if (escolha >= 0 && escolha < indv.size()) {
                mvprintw(nomes.size() + 4, 0, exibirNoticias(indv.at(escolha)).c_str());
            }
            } else {
            mvprintw(4, 0, "Nenhum resultado encontrado.");
            escolha = 0;
        }
        
        refresh();
        
        ch = getch();
        switch (ch) {
            case KEY_UP:
                escolha = (escolha > 0) ? escolha - 1 : nomes.size() - 1;
                break;
            case KEY_DOWN:
                escolha = (escolha < (int)nomes.size() - 1) ? escolha + 1 : 0;
                break;
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if (car > 0) {
                    car--;
                    x--;
                    bufe[car] = '\0';
                    mvaddch(1, x, ' ');
                    clrtoeol();
                }
                break;
            case KEY_LEFT:
                if (car > 0) {
                    car--;
                    x--;
                }
                break;
            case KEY_RIGHT:
                if (car < (int)strlen(bufe)) {
                    car++;
                    x++;
                }
                break;
            default:
                if (car < (int)sizeof(bufe) - 1 && isprint(ch)) {
                    mvaddch(1, x, ch);
                    bufe[car] = ch;
                    car++;
                    x++;
                    bufe[car] = '\0';
                }
                break;
        }
    }
    clear();
    refresh();

    if (!indv.empty())
        ind = indv.at(escolha);

    endwin();
    return ind;
}

void B(int x, int y, int tem)
{
        mvprintw(y, x, "oooooooooooo");
    if(tem >= 1)
        mvprintw(y+1,x, "o           o");
    if(tem >=2)
        mvprintw(y+2,x, "o            o");
    if(tem >= 3)
        mvprintw(y+3,x, "o           o");
    if(tem >= 4)
        mvprintw(y+4,x, "oooooooooooo");
    if(tem >= 5)
        mvprintw(y+5,x, "o           o");
    if(tem >=6)
        mvprintw(y+6,x, "o            o");
    if(tem >= 7)
        mvprintw(y+7,x, "o           o");
    if(tem >= 8)
        mvprintw(y+8,x, "oooooooooooo");
}

void E(int x, int y, int tem)
{
        mvprintw(y, x+15, "oooooooooooo");
    if(tem >= 1)
        mvprintw(y+1, x+15, "o");
    if(tem >= 2)
        mvprintw(y+2, x+15, "o");
    if(tem >= 3)
        mvprintw(y+3, x+15, "o");
    if(tem >= 4)
        mvprintw(y+4, x+15, "oooooooooooo");
    if(tem >= 5)
        mvprintw(y+5, x+15, "o");
    if(tem >= 6)
        mvprintw(y+6, x+15, "o");
    if(tem >= 7)
        mvprintw(y+7, x+15, "o");
    if(tem >= 8)
        mvprintw(y+8, x+15, "oooooooooooo");

}

void M(int x, int y, int tem) {
        mvprintw(y, x+28, "o           o");
    if (tem >= 1)
        mvprintw(y + 1, x+28, "oo         oo");
    if (tem >= 2)
        mvprintw(y + 2, x+28, "o o       o o");
    if (tem >= 3)
        mvprintw(y + 3, x+28, "o  o     o  o");
    if (tem >= 4)
        mvprintw(y + 4, x+28, "o   o   o   o");
    if (tem >= 5)
        mvprintw(y + 5, x+28, "o    o o    o");
    if (tem >= 6)
        mvprintw(y + 6, x+28, "o     o     o");
    if (tem >= 7)
        mvprintw(y + 7, x+28, "o           o");
    if (tem >= 8)
        mvprintw(y + 8, x+28, "o           o");
}

void V(int x, int y, int tem) {
        mvprintw(y, x+55, "o           o");
    if (tem >= 1)
        mvprintw(y + 1, x+55, "o           o");
    if (tem >= 2)
        mvprintw(y + 2, x+55, "o           o");
    if (tem >= 3)
        mvprintw(y + 3, x+55, " o         o ");
    if (tem >= 4)
        mvprintw(y + 4, x+55, "  o       o  ");
    if (tem >= 5)
        mvprintw(y + 5, x+55, "   o     o   ");
    if (tem >= 6)
        mvprintw(y + 6, x+55, "    o   o    ");
    if (tem >= 7)
        mvprintw(y + 7, x+55, "     o o     ");
    if (tem >= 8)
        mvprintw(y + 8, x+55, "      o      ");
}

void I(int x, int y, int tem) {
        mvprintw(y, x+69, "ooo");
    if (tem >= 1)
        mvprintw(y + 1, x+69, "ooo");
    if (tem >= 2)
        mvprintw(y + 2, x+69, "   ");
    if (tem >= 3)
        mvprintw(y + 3, x+69, " o ");
    if (tem >= 4)
        mvprintw(y + 4, x+69, " o ");
    if (tem >= 5)
        mvprintw(y + 5, x+69, " o ");
    if (tem >= 6)
        mvprintw(y + 6, x+69, " o ");
    if (tem >= 7)
        mvprintw(y + 7, x+69, " o ");
    if (tem >= 8)
        mvprintw(y + 8, x+69, " o ");
}

void N(int x, int y, int tem)
{
        mvprintw(y, x+73, "oo          o");
    if (tem >= 1)
        mvprintw(y + 1, x+73, "o o         o");
    if (tem >= 2)
        mvprintw(y + 2, x+73, "o  o        o");
    if (tem >= 3)
        mvprintw(y + 3, x+73, "o   o       o");
    if (tem >= 4)
        mvprintw(y + 4, x+73, "o    o      o");
    if (tem >= 5)
        mvprintw(y + 5, x+73, "o     o     o");
    if (tem >= 6)
        mvprintw(y + 6, x+73, "o      o    o");
    if (tem >= 7)
        mvprintw(y + 7, x+73, "o        o  o");
    if (tem >= 8)
        mvprintw(y + 8, x+73, "o          oo");
}

void D(int x, int y, int tem)
{
        mvprintw(y, x+88, "oooooooooo");
    if(tem >= 1)
        mvprintw(y+1,x+88, "o          o");
    if(tem >=2)
        mvprintw(y+2,x+88, "o            o");
    if(tem >= 3)
        mvprintw(y+3,x+88, "o             o");
    if(tem >= 4)
        mvprintw(y+4,x+88, "o             o");
    if(tem >= 5)
        mvprintw(y+5,x+88, "o             o");
    if(tem >=6)
        mvprintw(y+6,x+88, "o            o");
    if(tem >= 7)
        mvprintw(y+7,x+88, "o           o");
    if(tem >= 8)
        mvprintw(y+8,x+88, "oooooooooo");
}

void O(int x, int y, int tem)
{
        mvprintw(y, x+105,  " oooooooooo ");
    if(tem >= 1)
        mvprintw(y+1,x+105, "o          o");
    if(tem >=2)
        mvprintw(y+2,x+105, "o          o");
    if(tem >= 3)
        mvprintw(y+3,x+105, "o          o");
    if(tem >= 4)
        mvprintw(y+4,x+105, "o          o");
    if(tem >= 5)
        mvprintw(y+5,x+105, "o          o");
    if(tem >=6)
        mvprintw(y+6,x+105, "o          o");
    if(tem >= 7)
        mvprintw(y+7,x+105, "o          o");
    if(tem >= 8)
        mvprintw(y+8,x+105, " oooooooooo ");
}

void Controle::animation()
{

        initscr();
        cbreak();
        noecho();
        nodelay(stdscr,true);
        
            // Posição horizontal do ponto
        int max_x;
        int max_y;
        getmaxyx(stdscr, max_y, max_x);

        int y = max_y/5;
        int x = max_x/5;
        int tempo = 0;

    while(getch() == ERR)
    {

        clear();

        B(x,y,tempo);
        E(x,y,tempo);
        M(x,y,tempo);
        V(x,y,tempo);
        I(x,y,tempo);
        N(x,y,tempo);
        D(x,y,tempo);
        O(x,y,tempo);
        

        refresh();
        #ifdef __linux__
            usleep(110000);
        #endif
        #if defined (_WIN32) || (_WIN64)
            Sleep(110);
        #endif

        tempo++;
    }
    flushinp();
    nodelay(stdscr,false);
    endwin();
}

void Controle::gerarHTML() {
    noticias.clear();
    carregarDados();

    ofstream arquivo("notas.html");
    arquivo << "<!DOCTYPE html>\n";
    arquivo << "<html lang='pt-br'>\n";
    arquivo << "<head>\n";
    arquivo << "    <meta charset='UTF-8'>\n";
    arquivo << "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    arquivo << "    <title>Aquário - Notícias</title>\n";
    arquivo << "    <style>\n";
    arquivo << "        body { font-family: Arial, sans-serif; background: #153e75; margin: 0; padding: 0; color: #fff; } /* azul marinho, texto branco */\n";
    arquivo << "        .container { max-width: 900px; margin: 40px auto; background: rgba(21,62,117,0.95); box-shadow: 0 2px 16px #0d1c33; border-radius: 12px; padding: 40px 32px; }\n";
    arquivo << "        h1 { text-align: center; color: #eaf6fb; margin-bottom: 40px; font-size: 2.5em; letter-spacing: 2px; }\n";
    arquivo << "        .noticias-lista { display: flex; flex-direction: column; gap: 32px; }\n";
    arquivo << "        .noticia { background: #2188b6; border-radius: 8px; padding: 24px 20px; box-shadow: 0 1px 8px #153e75; } /* azul suave próximo ao ciano */\n";
    arquivo << "        .noticia h2 { color: #eaf6fb; margin: 0 0 12px 0; font-size: 1.5em; word-break: break-word; }\n";
    arquivo << "        .noticia .autor { font-size: 1em; color: #eaf6fb; margin-bottom: 10px; }\n";
    arquivo << "        .noticia .corpo { color: #fff; font-size: 1.1em; line-height: 1.7; word-break: break-word; white-space: pre-wrap; }\n";
    arquivo << "        @media (max-width: 600px) { .container { padding: 10px; } .noticia { padding: 12px 8px; } }\n";
    arquivo << "    </style>\n";
    arquivo << "</head>\n";
    arquivo << "<body>\n";
    arquivo << "    <div class='container'>\n";
    arquivo << "        <h1>Sistema Aquário</h1>\n";
    arquivo << "        <div class='noticias-lista'>\n";
    for(size_t i = 0; i < noticias.size(); i++) {
        arquivo << "            <div class='noticia'>\n";
        arquivo << "                <h2>" << noticias[i]->getTitulo() << "</h2>\n";
        arquivo << "                <div class='Subtitulo'><strong>Descrição:</strong> " << noticias[i]->getSubtitulo() << "</div>\n";
        arquivo << "                <div class='Autor'><strong>Autor:</strong> " << noticias[i]->getAutor() << "</div>\n";
        arquivo << "                <div class='Tipo'><strong>Tipo:</strong> " << getTipoNoticiaString(noticias[i]->getTipo()) << "</div>\n";
        arquivo << "                <div class='datahora'>";
        string dataStr = noticias[i]->getData();
        string horaStr = noticias[i]->getHora();
        if (dataStr.size() == 8) {
            dataStr = dataStr.substr(0,2) + "/" + dataStr.substr(2,2) + "/" + dataStr.substr(4,4);
        }
        if (horaStr.size() == 4) {
            horaStr = horaStr.substr(0,2) + ":" + horaStr.substr(2,2);
        }
        arquivo << "<span style='margin-right:16px'><strong>Data:</strong> " << dataStr << "</span>";
        arquivo << "<span><strong>Hora:</strong> " << horaStr << "</span>";
        arquivo << "                </div>\n";
        arquivo << "            </div>\n";
    }
    arquivo << "        </div>\n";
    arquivo << "    </div>\n";
    arquivo << "</body>\n";
    arquivo << "</html>\n";
    arquivo.close();
    cout << "HTML gerado: notas.html" << endl;
}