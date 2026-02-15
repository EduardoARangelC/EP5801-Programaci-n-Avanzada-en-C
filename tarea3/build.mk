# Variables
SRC := src
SENSORES := sensores
BUILD := build

main: main.o pos.o gest.o
	@mkdir -p $(BUILD)/bin
	@gcc $(BUILD)/main.o $(BUILD)/pos.o $(BUILD)/gest.o -o $(BUILD)/bin/main

main.o: $(SRC)/main.c
	@mkdir -p $(BUILD)
	@gcc -c $(SRC)/main.c -o $(BUILD)/main.o

pos.o: $(SRC)/$(SENSORES)/pos.c
	@mkdir -p $(BUILD)
	@gcc -c $(SRC)/$(SENSORES)/pos.c -o $(BUILD)/pos.o

gest.o: $(SRC)/$(SENSORES)/gest.c
	@mkdir -p $(BUILD)
	@gcc -c $(SRC)/$(SENSORES)/gest.c -o $(BUILD)/gest.o

# Limpieza
clean:
	@rm -rf $(BUILD)