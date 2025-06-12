all: bf

bf: src/main.c src/args.c src/check.c src/parser.c src/input.c src/output.c
	gcc src/main.c src/args.c src/check.c src/parser.c src/input.c src/output.c -o bf
	@echo "Build complete: bf created successfully."

clean:
	@rm -f bf compiler/src/main.c
	@find compiler/ -maxdepth 1 -type f -exec rm -f {} +
	@echo "Cleaned build files."
