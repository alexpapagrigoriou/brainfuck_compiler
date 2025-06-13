CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = .
OBJ_DIR = ../compiler_build
TARGET_DIR = ../bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET_NAME ?= a.out
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR_NO_PREFIX := $(subst ../,,$(OBJ_DIR))
TARGET_DIR_NO_PREFIX := $(subst ../,,$(TARGET_DIR))

WORKING_DIR = compiler_src
GENERATED_FILE = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(TARGET_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
	@echo "Built $(TARGET_DIR_NO_PREFIX)/$(TARGET_NAME) executable"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $(WORKING_DIR)/$< -> $(patsubst ../%,%,$@)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Created $(OBJ_DIR_NO_PREFIX) directory"

$(TARGET_DIR):
	@mkdir -p $(TARGET_DIR)
	@echo "Created $(TARGET_DIR_NO_PREFIX) directory"

clean:
	@rm -rf $(OBJ_DIR) $(TARGET_DIR) $(GENERATED_FILE)
	@echo "Cleaned $(OBJ_DIR_NO_PREFIX) directory"
	@echo "Cleaned $(TARGET_DIR_NO_PREFIX) directory"
	@echo "Cleaned generated $(WORKING_DIR)/$(GENERATED_FILE)"
