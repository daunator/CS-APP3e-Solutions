TARGET = prog
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -std=gnu99

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
2.92.o 2.93.o 2.94.o 2.95.o 2.96.o 2.97.o main.o: float_bits.h

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

