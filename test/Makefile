OBJS = bird_test.cc

CC = g++ -std=c++11

LIBS = ../bird.hh

OUTPUT_NAME = bird_test

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(OUTPUT_NAME)

clean:
	rm *.o
