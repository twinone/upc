CC := g++
PROG := parser
BINPATH := 
CC_FLAGS := -Wno-write-strings

all:
	$(BINPATH)antlr -gt $(PROG).g
	$(BINPATH)dlg -ci parser.dlg scan.c
	$(ENV) $(CC) $(CC_FLAGS) -o $(PROG).o $(PROG).c scan.c err.c
	@make halfclean


halfclean:
	rm -f *.c *.h *.dlg

clean: halfclean
	rm -f $(PROG).o

.PHONY: clean
