CC=g++
CFLAGS=-c -Wall -std=c++11 -g -I/usr/local/include/
LDFLAGS=
SOURCES=main.cpp Object.cpp Ball.cpp Input.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pong
ALLEGRO_LIBRARIES := allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_color-5
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))

.PHONY: clean

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(ALLEGRO_FLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	echo Clean done.


