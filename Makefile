CC=gcc-11
CFLAGS=-g -Wall -Wextra -O0
LDFLAGS=
SOURCES=main.c config.h structs.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=work1

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@