CC=clang
CXX=clang++
CFLAGS=-Wall -std=c11 -g

SRCPATH=src
BINPATH=bin
DEPS=$(SRCPATH)/highscores.h
OBJ=$(SRCPATH)/main.o $(SRCPATH)/highscores.o


test: 
	$(CXX) -o tests/testmain tests/highscorestest.cpp -lCppUTest
	./tests/testmain -v


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(BINPATH)/$@ $^


clean:
	rm -f bin/main
	rm -f src/*.o