CC = gcc
SRC = src/main.c src/args.c src/check.c src/parser.c src/input.c src/output.c src/compiler.c
OUT = bf
CFLAGS = -Wall -Wextra -O2

all: $(OUT)

$(OUT): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(OUT)
	@echo "Build complete: $(OUT) compiler created successfully."

clean:
	@rm -f $(OUT) compiler_src/main.c
	@find . -maxdepth 1 -type f ! -name 'Makefile' ! -name 'README.md' ! -name '.gitignore' -exec rm -f {} +
	@echo "Cleaned build and generated files."

clean_except_bf:
	@OUT=$(OUT); \
	find . -maxdepth 1 -type f ! -name "Makefile" ! -name "README.md" ! -name ".gitignore" ! -name "$$OUT" -exec rm -f {} +
	@echo "Cleaned generated files, except $(OUT) compiler."
