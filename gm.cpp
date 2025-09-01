#include "Controle.hpp"


//Roda tudo da main

void Controle::iniciar_a_Porra_Toda() {


    initscr();

    cbreak();

    noecho();

    keypad(stdscr, TRUE);

    clear();


    cout << "=== SISTEMA AQUÁRIO ===" << endl;

    cout << "Sistema de Gerenciamento de Notícias" << endl;

    cout << endl;

    

    int opcao;

    string option;

    string problem;


    do {

        

        vector<const char*> tipos = {

            "Criar Nova Notícia",

            "Exibir Todas as Notícias", 

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

                    cout << "\n--- CRIANDO NOVA NOTÍCIA ---" << endl;

                    editarNoticiaAtual();

                    salvarDados();

                    cout << "Notícia criada com sucesso!" << endl;

                    break;


                case 1:

                    cout << "Escolha a notícia que deseja editar: " << endl;

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

                    gerarHTML();

                    break;


                case 3:

                    cout << "Encerrando sistema..." << endl;

                    break;


                default:

                    cout << "Opção inválida!" << endl;

            }


            #if defined (_WIN32) || (_WIN64)

                system("cls");

            #endif


    } while (opcao != 3);


    endwin();

}

void Controle::selecionarTipoNoticia() {

    initscr();

    cbreak();

    noecho();

    keypad(stdscr, TRUE);

    clear();

    

    vector<const char*> tipos = {

        "0 - Avisos",

        "1 - Fofoca", 

        "2 - Humor",

        "3 - StackOverflow",

        "4 - Anonimo"

    };

    

    int escolha = 0;

    int ch = 0;

    

    while(ch != '\n') {

        clear();

        mvprintw(0, 0, "=== SELECIONAR TIPO DE NOTÍCIA ===");

        

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

        }

    }

    

    tipoNoticiaAtual = escolha;

    endwin();

}


void Controle::editarNoticiaAtual() {

    

    apagar(All); //Somente limpando o buffer

    selecionarTipoNoticia();


    Inicializar(tipoNoticiaAtual);

    

    executarEditor();

}


string Controle::exibirNoticias(int ind) {


    string lista;


    lista = "\n--- Notícia " + to_string(ind + 1) + " ---" + "\n"

          + "Tipo: " + getTipoNoticiaString(noticias[ind]->getTipo()) + "\n"

          + "Autor: " + noticias[ind]->getAutor() + "\n"

          + "Título: " + noticias[ind]->getTitulo() + "\n";


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


    lista += + "Data: " + noticias[ind]->getDataFormatada() + "\n"

            + "Hora: " + noticias[ind]->getHoraFormatada() + "\n";

    

    return lista;

}


void Controle::gerarHTML() {

    ofstream arquivo("noticias.html");

    

    arquivo << "<!DOCTYPE html>" << endl;

    arquivo << "<html><head><title>Aquário - Notícias</title></head>" << endl;

    arquivo << "<body><h1>Sistema Aquário</h1>" << endl;

    

    for(size_t i = 0; i < noticias.size(); i++) {

        arquivo << "<div class='noticia'>" << endl;

        arquivo << "<h2>" << noticias[i]->getTitulo() << "</h2>" << endl;

        arquivo << "<p><strong>Autor:</strong> " << noticias[i]->getAutor() << "</p>" << endl;

        arquivo << "<p>" << noticias[i]->getCorpo() << "</p>" << endl;

        arquivo << "</div><hr>" << endl;

    }

    

    arquivo << "</body></html>" << endl;

    arquivo.close();

    

    cout << "HTML gerado: noticias.html" << endl;

}


string Controle::getTipoNoticiaString(int tipo) {

    switch(tipo) {

        case 0: return "Avisos";

        case 1: return "Fofoca";

        case 2: return "Humor"; 

        case 3: return "StackOverflow";

        case 4: return "Anonimo";

        default: return "Desconhecido";

    }

}


#ifdef __linux__


Controle::Controle()

{

    textos.resize(rotulos.size(), L" ");


    // Inicializa tipo de notícia padrão

    tipoNoticiaAtual = 0; // Avisos por padrão

}


void Controle::Inicializar(int tipoNoticia)

{


    vector<wstring> temp = std_labels;

    

    switch(tipoNoticia)

    {

        case 0:

            temp.insert(temp.begin() + 5, L"Achados e Perdidos: ");

            temp.insert(temp.begin() + 6, L"Problemas: ");

            break;

        case 1:

            temp.insert(temp.begin() + 5, L"Fofoca:    ");

            break;

        case 2:

            temp.insert(temp.begin() + 5, L"Piada:     ");

            break;

        case 3:

            temp.insert(temp.begin() + 5, L"Topico:    ");

            temp.insert(temp.begin() + 6, L"Pergunta:  ");

            break;

        case 4:

            break;

    }


    rotulos = temp;

    textos.clear();

    textos.resize(rotulos.size());


}


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

    

    novaNoticia->setTitulo(wstringToUtf8(textos[Title]));

    novaNoticia->setSubtitulo(wstringToUtf8(textos[Subtitle]));

    novaNoticia->setAutor(wstringToUtf8(textos[Author]));

    novaNoticia->setCorpo(wstringToUtf8(textos[Body]));

    novaNoticia->setImagem(wstringToUtf8(textos[Image]));


    novaNoticia->setTipo(tipo);


    int dia = 0, mes = 0, ano = 0, h = 0, min = 0;

    int ind_data = 5;

    int ind_hour = 6;   


    switch(tipoNoticiaAtual)

    {

        case 0:

            dynamic_cast<Avisos*>(novaNoticia.get())->setCategoria(wstringToUtf8(textos[5]));

            dynamic_cast<Avisos*>(novaNoticia.get())->setProblema(wstringToUtf8(textos[6]));

            ind_data += 2;

            ind_hour += 2;

            break;

        case 1:

            dynamic_cast<Fofoca*>(novaNoticia.get())->setAssunto(wstringToUtf8(textos[5]));

            ind_data++;

            ind_hour++;

            break;

        case 2:

            dynamic_cast<Humor*>(novaNoticia.get())->setPiada(wstringToUtf8(textos[5]));

            ind_data++;

            ind_hour++;

            break;

        case 3:

            dynamic_cast<StackOverflow*>(novaNoticia.get())->setTudo(wstringToUtf8(textos[5]), wstringToUtf8(textos[6]));

            ind_data += 2;

            ind_hour += 2;

            break;

        default:

            break;

    }


    if(!(textos[ind_data].size() < 8))

    {

        dia = stoi(textos[ind_data].substr(0, 2));

        mes = stoi(textos[ind_data].substr(2, 2));

        ano = stoi(textos[ind_data].substr(4));

    }

    if(!(textos[ind_hour].size() < 4))

    {

        h = stoi(textos[ind_hour].substr(0, 2));

        min = stoi(textos[ind_hour].substr(2));

    }


    novaNoticia->setData(dia, mes, ano);

    novaNoticia->setHora(h, min);

    

    novaNoticia->formatar();

    noticias.push_back(move(novaNoticia));

}


void Controle::mover(int cx, int cy, wstring &buffer) {

    refresh();

    int i = (int)buffer.size();

    x = cx + i;

    y = cy;


    curs_set(1);

    move(y, x);

    

    while ((get_wch(&wch)) != KEY_DOWN && wch != KEY_UP) {

        if((int)wch == ERR)

            continue;

        if (wch == L'\n' || wch == L'\r') {

            break;

        }

        

        switch (wch) {

            case KEY_LEFT:

                if (i > 0) { 

                    i--;

                    x--; 

                }

                break;

            case KEY_RIGHT:

                if (i < (int)buffer.size()) { 

                    i++;

                    x++; 

                }

                break;

            case KEY_UP:

            case KEY_DOWN:

                return;

            case KEY_BACKSPACE:

            case 127: case 8:

                if (i > 0) {

                    i--;

                    x--;        

                    buffer.erase(i, 1);

                    mvaddch(y, x, ' ');

                    clrtoeol();

                }

                break;

            default:

                    mvaddch(y, x, (wchar_t)wch);

                    buffer.insert(i, 1, (wchar_t)wch);

                    i++; x++;

                break;

        }


        //redesenhando a tela depois de cada interação

        clear();

        //clrtoeol();

        for (size_t j = 0; j < textos.size(); j++) {

            mvprintw(j, 0, "%s%s", wstringToUtf8(rotulos[j]).c_str(), wstringToUtf8(textos[j]).c_str());

        }

        move(y, x);


        refresh();

    }

    curs_set(0);

}


void Controle:: executarEditor() {

    initscr();

    setlocale(LC_ALL, "");

    cbreak();

    noecho();

    keypad(stdscr, TRUE);

    getmaxyx(stdscr, yMax, xMax);

    clear();


    int campo_atual = 0;

    wch = 0;

    while (true) {

        if ((campo_atual == (int)textos.size() - 1 && (ch == L'\n' || ch == L'\r' || ch ==27)) || ch == L'\033') 

            break;


        for (size_t i = 0; i < textos.size(); i++) {

            

            move(i, rotulos[i].size() + textos[i].size());

            clrtoeol();


            mvprintw(i, 0, "%s%s", wstringToUtf8(rotulos[i]).c_str(), wstringToUtf8(textos[i]).c_str());


            //mvaddwstr(i,0,rotulos[i].c_str());          // desenha rótulo

            //mvaddwstr(i, rotulos[i].size() + 3, textos[i].c_str()); // desenha texto

        }

        

        mover(rotulos[campo_atual].size(), campo_atual, textos[campo_atual]);


        if (wch == L'\n') {

            if (campo_atual == (int)textos.size() - 1) {

                break; // sai do editor apenas se for o último campo

            } else {

                campo_atual++; // Enter pula pro próximo campo

            }

        }

        else if 

            (wch == KEY_UP) campo_atual = (campo_atual > 0) ? campo_atual - 1 : (int)textos.size() - 1;

        else 

            campo_atual = (campo_atual < (int)  textos.size() - 1) ? campo_atual + 1 : 0;

    }


    endwin();

}


void Controle::apagar(int t) {

    switch (t) {

        case Title:

            textos[Title].clear();

            break;

        case Subtitle:

            textos[Subtitle].clear();

            break;

        case Author:

            textos[Author].clear();

            break;

        case Body:

            textos[Body].clear();

            break;

        case Image:

            textos[Image].clear();

            break;

        case Dataa:

            textos[Dataa].clear();

            break;

        case Hour:

            textos[Hour].clear();

            break;

        case All:

            textos.clear();

            break;

        default:

            break;

    }

}


int Controle::pesquisar() {

    setlocale(LC_ALL, "");

    initscr();

    cbreak();

    noecho();

    keypad(stdscr, TRUE);

    getmaxyx(stdscr,yMax,xMax);

    clear();

    

    x = 1;

    

    vector<string> nomes;

    vector<int> indv;

    wstring bufe;

    // bufe.resize(1, L' ');


    noticias.clear();

    carregarDados();


    int car = 0;

    

    int ind = -1;

    int escolha = 0;

    

    wch = L' ';

    while(wch != L'\n') {

        clear();


        nomes.clear();

        indv.clear();


        if (wch == L'\033') {

            throw 8000;

        }


        for(int i = 0; i < noticias.size(); i++)

        {   

            if(noticias.at(i)->getTitulo().find(wstringToUtf8(bufe)) != string::npos || bufe.empty())

            {

                nomes.push_back(noticias.at(i)->getTitulo());

                indv.push_back(i);

            }

            

        }

        

        mvprintw(0, 0, "======Pesquisar======");


        mvprintw(1, 1, "%s", wstringToUtf8(bufe).c_str());

        

        for(size_t i = 0; i < nomes.size(); i++) {

            string linha = ((int)i == escolha ? "> " : "  ") + nomes[i];

            if((int)i == escolha) {

                attron(A_REVERSE);

                mvprintw(i + 3, 0, linha.c_str());

                attroff(A_REVERSE);

            } else {

                mvprintw(i + 3, 0, linha.c_str());

            }


        }

        

        //mvprintw(nomes.size() + 4, 0, "Use setas para navegar, Enter para selecionar");


         move(1, x);


          mvprintw(nomes.size() + 4, 0, "=== Nada Encontrado ===");


        move(1, x);

        

        //Segurança para evitar uns crash de entrar num vetor vazio

        if (!indv.empty()) {

            if (escolha >= 0 && escolha < indv.size()) {

                string aparece = exibirNoticias(indv.at(escolha)) + "\nUse setas para navegar, Enter para selecionar\n";

                mvprintw(nomes.size() + 4, 0, aparece.c_str());

            }

            } else {

            mvprintw(4, 0, "Nenhum resultado encontrado.");

            escolha = 0;

        }


         refresh();

        

        get_wch(&wch);


        if((int)wch == ERR)

            continue;

        

        switch(wch) {

            case KEY_UP:

                escolha = (escolha > 0) ? escolha - 1 : nomes.size() - 1;

                break;

            case KEY_DOWN:

                escolha = (escolha < (int)nomes.size() - 1) ? escolha + 1 : 0;

                break;

            case KEY_BACKSPACE:

            case 127: case 8:

                if(car > 0)

                {

                    car--;

                    x--;        

                    bufe.erase(car, 1);

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

                if (car < (int)bufe.size()) { 

                    car++;

                    x++; 

                }

                break;

            default:

                    mvaddch(1, x, (wchar_t)wch);

                    bufe.insert(car, 1, (wchar_t)wch);

                    car++;

                    x++;

                break;

        }

    }

    clear();

    refresh();


    if(!indv.empty())

        ind = indv.at(escolha);


    endwin();

    return ind;

}


void Controle::salvarDadoIndice(int contador) {

    ofstream arquivo;


    js["Titulo"] = wstringToUtf8(textos[Title]);

    js["Subtitulo"] = wstringToUtf8(textos[Subtitle]);

    js["Autor"] = wstringToUtf8(textos[Author]);

    js["Corpo"] = wstringToUtf8(textos[Body]);

    js["Imagem"] = wstringToUtf8(textos[Image]);

    js["Tipo"] = tipoNoticiaAtual;


    switch(tipoNoticiaAtual)

    {

        case 0:

            js["AchadosEPerdidos"] = wstringToUtf8(textos[5]);

            js["Problemas"] = wstringToUtf8(textos[6]);

            js["Data"] = wstringToUtf8(textos[Dataa + 2]);

            js["Hora"] = wstringToUtf8(textos[Hour + 2]);

            break;

        case 1:

            js["Fofoca"] = wstringToUtf8(textos[5]);

            js["Data"] = wstringToUtf8(textos[Dataa + 1]);

            js["Hora"] = wstringToUtf8(textos[Hour + 1]);

            break;

        case 2:

            js["Piada"] = wstringToUtf8(textos[5]);

            js["Data"] = wstringToUtf8(textos[Dataa + 1]);

            js["Hora"] = wstringToUtf8(textos[Hour + 1]);

            break;

        case 3:

            js["Topico"] = wstringToUtf8(textos[5]);

            js["Pergunta"] = wstringToUtf8(textos[6]);

            js["Data"] = wstringToUtf8(textos[Dataa + 2]);

            js["Hora"] = wstringToUtf8(textos[Hour + 2]);

            break;

        default:

            js["Data"] = wstringToUtf8(textos[Dataa]);

            js["Hora"] = wstringToUtf8(textos[Hour]);

            break;

    }


    string nomeArquivo = "./Pasta/arquivo" + to_string(contador) + ".json";

    arquivo.open(nomeArquivo);


    arquivo << js;

    arquivo.close();

}


void Controle::carregarDadoIndice(int indice) {

    ifstream arquivo;


   string nomeArquivo = "./Pasta/arquivo" + to_string(indice) + ".json";

        arquivo.open(nomeArquivo);

        if (arquivo.is_open()) 

        {

            try {

                arquivo >> js; // Se botar um indice invalido dá erro

            } catch (json::parse_error& e) {

                std::cerr << "Erro de parsing no JSON: " << e.what() << std::endl;

                throw range_error("Nenhum usuário foi criado!!!!!!!");

            }

            arquivo.close();


            string json_string_recebida = js.dump();

            json dados_lidos = json::parse(json_string_recebida);


            textos[Title] = utf8ToWstring(dados_lidos["Titulo"]);


            textos[Subtitle] = utf8ToWstring(dados_lidos["Subtitulo"]);


            textos[Author] = utf8ToWstring(dados_lidos["Autor"]);


            textos[Body] = utf8ToWstring(dados_lidos["Corpo"]);


            textos[Image] = utf8ToWstring(dados_lidos["Imagem"]);


            switch(tipoNoticiaAtual)

            {

                case 0:

                    textos[5] = utf8ToWstring(dados_lidos["AchadosEPerdidos"]);

                    textos[6] = utf8ToWstring(dados_lidos["Problemas"]);

                    textos[Dataa + 2] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 2] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                case 1:

                    textos[5] = utf8ToWstring(dados_lidos["Fofoca"]);

                    textos[Dataa + 1] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 1] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                case 2:

                    textos[5] = utf8ToWstring(dados_lidos["Piada"]);

                    textos[Dataa + 1] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 1] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                case 3:

                    textos[5] = utf8ToWstring(dados_lidos["Topico"]);

                    textos[6] = utf8ToWstring(dados_lidos["Pergunta"]);

                    textos[Dataa + 2] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 2] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                default:

                    textos[Dataa] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour] = utf8ToWstring(dados_lidos["Hora"]);

            }

        }

        else

            throw 9000;

}


void Controle::editarNoticia(int indice) {

    carregarDadoIndice(indice);

    executarEditor();

    salvarDadoIndice(indice);

}


void Controle::salvarDados() {

    ofstream arquivo;

    

    int contador = 0;

    json indice;


    string nomeDiretorio = "Pasta";

    fs::create_directory(nomeDiretorio);


    ifstream if_indice("./Pasta/Indice.json");

    if (if_indice.is_open()) {

        if_indice >> indice;

        if_indice.close();


        if (indice.count("Indice")) {

            contador = indice["Indice"].get<int>();

            contador++;

        } else {

            contador = 0;

        }

    } else {

        contador = 0;

    }


    ofstream of_indice("./Pasta/Indice.json");

    

    indice["Indice"] = contador;

    of_indice << indice;

    of_indice.close();


    js["Tipo"] = tipoNoticiaAtual;

    js["Titulo"] = wstringToUtf8(textos[Title]);

    js["Subtitulo"] = wstringToUtf8(textos[Subtitle]);

    js["Autor"] = wstringToUtf8(textos[Author]);

    js["Corpo"] = wstringToUtf8(textos[Body]);

    js["Imagem"] = wstringToUtf8(textos[Image]);


    switch(tipoNoticiaAtual)

    {

        case 0:

            js["AchadosEPerdidos"] = wstringToUtf8(textos[5]);

            js["Problemas"] = wstringToUtf8(textos[6]);

            js["Data"] = wstringToUtf8(textos[Dataa + 2]);

            js["Hora"] = wstringToUtf8(textos[Hour + 2]);

            break;

        case 1:

            js["Fofoca"] = wstringToUtf8(textos[5]);

            js["Data"] = wstringToUtf8(textos[Dataa + 1]);

            js["Hora"] = wstringToUtf8(textos[Hour + 1]);

            break;

        case 2:

            js["Piada"] = wstringToUtf8(textos[5]);

            js["Data"] = wstringToUtf8(textos[Dataa + 1]);

            js["Hora"] = wstringToUtf8(textos[Hour + 1]);

            break;

        case 3:

            js["Topico"] = wstringToUtf8(textos[5]);

            js["Pergunta"] = wstringToUtf8(textos[6]);

            js["Data"] = wstringToUtf8(textos[Dataa + 2]);

            js["Hora"] = wstringToUtf8(textos[Hour + 2]);

            break;

        default:

            js["Data"] = wstringToUtf8(textos[Dataa]);

            js["Hora"] = wstringToUtf8(textos[Hour]);

            break;

    }


    string nomeArquivo = "./Pasta/arquivo" + to_string(contador) + ".json";

    arquivo.open(nomeArquivo);


    arquivo << js;

    arquivo.close();


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

                std::cerr << "Erro de parsing no JSON: " << e.what() << std::endl;

            }

            arquivo.close();


            string json_string_recebida = js.dump();

            json dados_lidos = json::parse(json_string_recebida);


            tipoNoticiaAtual = dados_lidos["Tipo"].get<int>();


            apagar(All);

            Inicializar(tipoNoticiaAtual);


            textos[Title] = utf8ToWstring(dados_lidos["Titulo"]);


            textos[Subtitle] = utf8ToWstring(dados_lidos["Subtitulo"]);


            textos[Author] = utf8ToWstring(dados_lidos["Autor"]);


            textos[Body] = utf8ToWstring(dados_lidos["Corpo"]);


            textos[Image] = utf8ToWstring(dados_lidos["Imagem"]);


            switch(tipoNoticiaAtual)

            {

                case 0:

                    textos[5] = utf8ToWstring(dados_lidos["AchadosEPerdidos"]);

                    textos[6] = utf8ToWstring(dados_lidos["Problemas"]);

                    textos[Dataa + 2] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 2] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                case 1:

                    textos[5] = utf8ToWstring(dados_lidos["Fofoca"]);

                    textos[Dataa + 1] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 1] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                case 2:

                    textos[5] = utf8ToWstring(dados_lidos["Piada"]);

                    textos[Dataa + 1] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 1] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                case 3:

                    textos[5] = utf8ToWstring(dados_lidos["Topico"]);

                    textos[6] = utf8ToWstring(dados_lidos["Pergunta"]);

                    textos[Dataa + 2] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour + 2] = utf8ToWstring(dados_lidos["Hora"]);

                    break;

                default:

                    textos[Dataa] = utf8ToWstring(dados_lidos["Data"]);

                    textos[Hour] = utf8ToWstring(dados_lidos["Hora"]);

            }

            

            criarNoticia(tipoNoticiaAtual); 

        }

    }

}


void Controle::imprimir() {

    cout << "=== SISTEMA AQUÁRIO - NOTÍCIAS ===" << endl;

    cout << "Função de impressão implementada!" << endl;

}


string Controle::wstringToUtf8(const std::wstring &wstr) {

    return boost::locale::conv::utf_to_utf<char>(wstr);

}


wstring Controle::utf8ToWstring(const std::string &str) {

    return boost::locale::conv::utf_to_utf<wchar_t>(str);

}


#endif