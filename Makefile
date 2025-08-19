CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
SOURCES = Data.cpp Avisos.cpp fofoca.cpp Humor.cpp StackOverflow.cpp Anonimo.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)
	@echo "Classes de notícia compiladas com sucesso!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(OBJECTS)
	@echo "Teste de compilação bem-sucedido!"
	@echo "Objetos gerados: $(OBJECTS)"

clean:
	rm -f $(OBJECTS)

help:
	@echo "Comandos disponíveis para branch noticia:"
	@echo "  make          - Compila todas as classes de notícia"
	@echo "  make test     - Testa a compilação"
	@echo "  make clean    - Remove arquivos objeto"
	@echo "  make help     - Mostra esta ajuda"

run:
	@echo "❌ Esta é a branch 'noticia' - apenas estruturas de dados!"
	@echo "🔄 Para executar o programa completo, use a branch com a classe Controle"
	@echo "✅ Use 'make test' para verificar se as classes compilam corretamente"

.PHONY: all test clean help run
