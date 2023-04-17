CC=clang
CFLAGS=-Wall -std=c11 -g

SRCPATH=src
BINPATH=bin
DEPS=$(SRCPATH)/highscores.h
OBJ=$(SRCPATH)/main.o $(SRCPATH)/highscores.o


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(BINPATH)/$@ $^

clean:
	rm -f bin/main
	rm -f src/*.o