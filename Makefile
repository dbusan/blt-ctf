CC=clang
# CXX=clang++
CFLAGS=-Wall -std=c11 -g

SRCPATH=src
BINPATH=bin
DEPS=$(SRCPATH)/highscores.h
OBJ=$(SRCPATH)/main.o $(SRCPATH)/highscores.o


# test: 
# 	$(CXX) -o tests/testmain tests/highscorestest.c -lCppUTest
# 	./tests/testmain -v


main: $(OBJ)
	$(CC) $(CFLAGS) -o $(BINPATH)/$@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f bin/main
	rm -f src/*.o
	rm -f src/*.a
	mkdir -p bin