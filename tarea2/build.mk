# Variables
SRC := src
BUILD := build

main: main.o imprimir.o
	@mkdir -p $(BUILD)/bin
	@gcc $(BUILD)/main.o $(BUILD)/imprimir.o -o $(BUILD)/bin/main

main.o: $(SRC)/main.c
	@mkdir -p $(BUILD)
	@gcc -c $(SRC)/main.c -o $(BUILD)/main.o

imprimir.o: $(SRC)/imprimir.asm
	@mkdir -p $(BUILD)
	@nasm -f elf64 $(SRC)/imprimir.asm -o $(BUILD)/imprimir.o

clean:
	@rm -rf $(BUILD)
