# Nome do executável
EXEC = build/labirinto

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Arquivos fonte e objetos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Regra padrão (compila o executável)
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para compilar os objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar e executar o programa
run: all
	./$(EXEC)

# Limpeza
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

# Regra para recriar tudo
rebuild: clean all
