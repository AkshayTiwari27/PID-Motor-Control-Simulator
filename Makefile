# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I. -g
LDFLAGS =

# Source files
SRCS = main.c pid_controller.c motor_model.c logger.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = pid_sim

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET) log.csv

# Phony targets
.PHONY: all clean
