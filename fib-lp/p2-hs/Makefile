CC := g++
PARSER := parser
MAIN := main
BINPATH := 
CC_FLAGS := -Wno-write-strings

all: parser.o main


main:
	ghc $(MAIN).hs

parser.o:
	$(BINPATH)antlr -gt $(PARSER).g
	$(BINPATH)dlg -ci parser.dlg scan.c
	$(ENV) $(CC) $(CC_FLAGS) -o $(PARSER) $(PARSER).c scan.c err.c
	@make halfclean



halfclean:
	rm -f *.c *.h *.dlg *.o *.hi

clean: halfclean
	rm -f $(MAIN) $(PARSER)

.PHONY: clean
