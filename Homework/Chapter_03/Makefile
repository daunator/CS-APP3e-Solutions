TARGET = prog
LIBS = -lm
CC = gcc
CFLAGS = -Og -g -Wall -std=gnu99
AS = as
ASFLAGS = -g

.PHONY: default all clean

default: $(TARGET)
all: default

C_OBJ = $(patsubst %.c, %.o, $(wildcard *.c))
ASM_OBJ = $(patsubst %.s, %.o, $(wildcard *.s))
OBJECTS = $(C_OBJ) $(ASM_OBJ)

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
