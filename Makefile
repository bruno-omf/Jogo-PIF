
EXEC = build/labirinto

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(EXEC)

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

rebuild: clean all
