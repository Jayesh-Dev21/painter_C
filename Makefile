CC = gcc
CFLAGS = -Wall

TARGET = paint_C
# SRC = $(wildcard src/*.c)
# HEADERS = $(wildcard src/*.h)
SRC = src/main.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ) 
	$(CC) $(OBJ) -o $(TARGET) `sdl2-config --cflags --libs`
# target app is compiled using the object files *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ `sdl2-config --cflags --libs`
# Make object files beforehand and compile only the changes *.c files 
#results in faster execution.

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJ)