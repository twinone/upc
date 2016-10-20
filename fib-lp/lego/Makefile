CC := g++
PROG := lego
CC_FLAGS := -Wno-write-strings
all:
	antlr -gt $(PROG).g
	dlg -ci parser.dlg scan.c
	$(CC) $(CC_FLAGS) -o $(PROG).o $(PROG).c scan.c err.c
	@make halfclean


halfclean:
	rm -f *.c *.h *.dlg

clean: halfclean
	rm $(PROG).o

.PHONY: clean
