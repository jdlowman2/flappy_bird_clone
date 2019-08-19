OBJS = main.cc

CC = g++ -std=c++11

LIBS = bird.hh

# -Wall will turn on all standard warnings
COMPILER_FLAGS = -Wall

OUTPUT_NAME = flappy-bird

SFML_PACKAGES = -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) $(OBJS) $(LIBS) -o $(OUTPUT_NAME) $(SFML_PACKAGES)