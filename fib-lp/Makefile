CC := g++
PROG := example2
CC_FLAGS := -Wno-write-strings
all:
	antlr -gt $(PROG).g
	dlg -ci parser.dlg scan.c
	$(CC) $(CC_FLAGS) -o $(PROG).o $(PROG).c scan.c err.c


clean:
	rm -f *.o *.c parser.dlg tokens.h mode.h

.PHONY: clean
