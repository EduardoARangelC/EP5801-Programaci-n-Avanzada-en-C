# Variables #
SRC := src
BUILD := build

main: main.o calculador.o
	@if not exist "$(BUILD)\bin" mkdir "$(BUILD)\bin"
	@gcc $(BUILD)/main.o $(BUILD)/calculador.o -o $(BUILD)/bin/main

main.o: $(SRC)/main.c
	@if not exist "$(BUILD)" mkdir "$(BUILD)"
	@gcc -c $(SRC)/main.c -o $(BUILD)/main.o

calculador.o: $(SRC)/calculador.c
	@if not exist "$(BUILD)" mkdir "$(BUILD)"
	@gcc -c $(SRC)/calculador.c -o $(BUILD)/calculador.o

clean:
	@if exist $(BUILD) rmdir /s /q $(BUILD)