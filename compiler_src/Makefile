CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = .
OBJ_DIR = ../compiler_build
TARGET_DIR = ..

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET_NAME ?= a.out
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

GENERATED_FILE = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
	@echo "Build complete: $(TARGET) created successfully."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Build started: $(OBJ_DIR) directory created successfully."

clean:
	@rm -rf $(OBJ_DIR) $(GENERATED_FILE)
	@echo "Cleaned compiler_build directory and generated $(GENERATED_FILE)."
