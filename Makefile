# Nome do arquivo executável
TARGET = build/meu_jogo

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g -Iinclude

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Arquivos fonte e objetos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Regra principal
all: $(TARGET)

# Criação do diretório de build, se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilação do executável
$(TARGET): $(BUILD_DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

# Compilação de cada arquivo .c para .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para rodar o programa
run: all
	./$(TARGET)

# Limpeza dos arquivos de build
clean:
	rm -rf $(BUILD_DIR)
