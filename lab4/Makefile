# Compiler and flags  -Wextra -std=c99
CC = gcc
CFLAGS = -Wall

# Source files
SRCS = Jaewon_libFS2025.c Jaewon_testfile2025.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = Jaewon_testapp

# Default target (run when you type 'make')
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c Jaewon_libFS2025.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
# clean:
# 	rm -f $(OBJS) $(TARGET)

# Phony targets (not actual files)
# .PHONY: all clean