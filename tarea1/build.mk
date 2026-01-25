# Variables #
SRC := src
BUILD := build

calculador: calculador.o
	if not exist "$(BUILD)\bin" mkdir "$(BUILD)\bin"
	gcc $(BUILD)/calculador.o -o $(BUILD)/bin/calculador

calculador.o: $(SRC)/calculador.c
	if not exist "$(BUILD)" mkdir "$(BUILD)"
	gcc -c $(SRC)/calculador.c -o $(BUILD)/calculador.o

clean:
	if exist $(BUILD) rmdir /s /q $(BUILD)