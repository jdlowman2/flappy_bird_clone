OBJS = bird_test.cc

CC = g++ -std=c++11

LIBS = -../bird.hh

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bird_test

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

bird_test:
	$(CC) bird_test.cc ../bird.hh -o bird_test_exc

main_test:
	$(CC) main_test.cc -o main_test_exc

clean:
	rm *.o
