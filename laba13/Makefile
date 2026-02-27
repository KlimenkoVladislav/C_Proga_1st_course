.PHONY : clear all run

CC = gcc
TARGET = main
SOURCE_DIR = src/

all: $(TARGET)

run: all
	./$(TARGET)

main: main.o func.o
	ar rc libFUNC.a func.o
	$(CC) main.o -o $(TARGET) -L. -lFUNC
	
main.o: $(SOURCE_DIR)/main.c
	$(CC) -c $(SOURCE_DIR)/main.c -o main.o -I ./include

func.o: $(SOURCE_DIR)/func.c
	$(CC) -c $(SOURCE_DIR)/func.c -o func.o -I ./include

clear: 
	rm -rf *.o *.a *.so $(TARGET)