TARGET = build/meu_jogo

CC = gcc

CFLAGS = -Wall -g -Iinclude

SRC_DIR = src

BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)