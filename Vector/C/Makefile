CC=gcc
CFLAGS=-c -Wall -std=c11
SOURCES=main.c vector.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=vector

all: $(SOURCES) $(EXECUTABLE)

clean: 
	rm -f vector vector.o main.o
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@