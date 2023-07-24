CC = gcc
CFLAGS = -g
TARGET = test
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean stacksize defaultstack run

all: stacksize $(TARGET) defaultstack

stacksize:
	ulimit -s unlimited

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

defaultstack:
	ulimit -s default

run: $(TARGET)
	ulimit -s unlimited && ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

