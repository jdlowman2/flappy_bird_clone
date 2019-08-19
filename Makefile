# OBJS specifies which files to compile as part of the project
OBJS = main.cc

# CC specifies which compiler we're using
CC = g++ -std=c++11

LIBS = bird.hh

# COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall will turn on all standard warnings
COMPILER_FLAGS = -Wall

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(LIBS) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

graphics:
	$(CC) draw_map.cc -o sfml-draw_map -lsfml-graphics -lsfml-window -lsfml-system