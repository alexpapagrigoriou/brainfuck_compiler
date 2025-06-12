all: bf

bf: src/main.c src/args.c src/check.c src/parser.c src/input.c src/output.c src/compiler.c
	gcc src/main.c src/args.c src/check.c src/parser.c src/input.c src/output.c src/compiler.c -o bf
	@echo "Build complete: bf compiler created successfully."

clean:
	@rm -f bf compiler/src/main.c
	@find . -maxdepth 1 -type f ! -name 'Makefile' ! -name 'makefile' ! -name 'README.md' ! -name '.gitignore' -exec rm -f {} +
	@find compiler/ -maxdepth 1 -type f -exec rm -f {} +
	@echo "Cleaned build files."
