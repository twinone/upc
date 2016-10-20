CC := g++
PROG := lego
CC_FLAGS := -Wno-write-strings
all:
	bin/antlr -gt $(PROG).g
	bin/dlg -ci parser.dlg scan.c
	$(CC) $(CC_FLAGS) -o $(PROG).o $(PROG).c scan.c err.c
	@make halfclean


halfclean:
	rm -f *.c *.h *.dlg

clean: halfclean
	rm $(PROG).o

.PHONY: clean
