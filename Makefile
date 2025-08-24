# Makefile Completo - Sistema Aquário Integrado
CXX = g++
OS = $(shell uname)
CXXFLAGS = -std=c++17 

ifeq ($(OS), Linux)
# Para usar essas libs coloca no terminal: 

# Distros Debian:
# sudo apt-get update 
# sudo apt-get install libncurses5-dev libncursesw5-dev libboost-locale-dev
# sudo apt-get upgrade

# Distros fedora:
# sudo dnf install ncurses-devel boost-devel

# Distros Arch:
# sudo pacman -S ncurses boost

    LDFLAGS = -lncurses -lncursesw -ltinfo -lboost_locale 

else
    LDFLAGS = -L./Libs -l:pdcurses.a -static-libstdc++
endif

# Arquivos fonte
SOURCES_NOTICIA = Data.cpp Avisos.cpp fofoca.cpp Humor.cpp StackOverflow.cpp Anonimo.cpp
SOURCES_CONTROLE = Controle.cpp
SOURCES_ALL = $(SOURCES_NOTICIA) $(SOURCES_CONTROLE)

# Objetos
OBJECTS_NOTICIA = $(SOURCES_NOTICIA:.cpp=.o)
OBJECTS_CONTROLE = $(SOURCES_CONTROLE:.cpp=.o)
OBJECTS_ALL = $(SOURCES_ALL:.cpp=.o)

# Executável final
TARGET = aquario

# Regra principal - compila tudo
all: $(TARGET)

# Cria o executável
$(TARGET): $(OBJECTS_ALL) main.o
	$(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Sistema Aquário compilado com sucesso!"

# Compila apenas as classes de notícia (compatibilidade)
noticias: $(OBJECTS_NOTICIA)
	@echo "✅ Classes de notícia compiladas!"

# Compila apenas o controle
controle: $(OBJECTS_CONTROLE)
	@echo "✅ Classe Controle compilada!"

# Regra para objetos individuais
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria um main.cpp básico se não existir
main.cpp:
	@echo "Criando main.cpp básico..."
	@echo '#include "Controle.hpp"' > main.cpp
	@echo '#include <iostream>' >> main.cpp
	@echo 'using namespace std;' >> main.cpp
	@echo '' >> main.cpp
	@echo 'int main() {' >> main.cpp
	@echo '    Controle sistema;' >> main.cpp
	@echo '    cout << "Sistema Aquário iniciado!" << endl;' >> main.cpp
	@echo '    return 0;' >> main.cpp
	@echo '}' >> main.cpp

# Testa compilação
test: $(OBJECTS_ALL)
	@echo "✅ Teste de compilação bem-sucedido!"
	@echo "Objetos gerados: $(OBJECTS_ALL)"

# Executa o programa
run: $(TARGET)
	./$(TARGET)

# Limpa arquivos gerados
clean:
	rm -f $(OBJECTS_ALL) main.o $(TARGET) *.json

# Limpa tudo incluindo main.cpp gerado
distclean: clean
	rm -f main.cpp noticias.html *.json

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila sistema completo"
	@echo "  make noticias - Compila apenas classes de notícia"
	@echo "  make controle - Compila apenas classe Controle"
	@echo "  make test     - Testa compilação"
	@echo "  make run      - Compila e executa"
	@echo "  make clean    - Remove arquivos objeto"
	@echo "  make distclean- Remove tudo"
	@echo "  make help     - Mostra esta ajuda"

.PHONY: all noticias controle test run clean distclean help
