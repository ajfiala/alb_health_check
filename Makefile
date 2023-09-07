# Compiler to use
CC = gcc

# Flags to pass to the compiler
CFLAGS = -Wall -std=c99

# Name of the final executable
TARGET = healthcheck_app

# Source and object files
SRC = main.c socket.c
OBJ = $(SRC:.c=.o)

# Default rule
all: $(TARGET)

# Rule for memory leak checking
memcheck: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile each source file
%.o: %.c socket.h
	$(CC) $(CFLAGS) -c $<

# Rule to clean intermediate files
clean:
	rm -f $(OBJ) $(TARGET)

# Rule for running the program
run: $(TARGET)
	./$(TARGET)