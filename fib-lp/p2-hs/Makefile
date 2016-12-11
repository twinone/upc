CC := g++
PARSER := parser
MAIN := main
CC_FLAGS := -Wno-write-strings

all: parser main


main:
	ghc $(MAIN).hs

parser:
	antlr -gt $(PARSER).g
	dlg -ci parser.dlg scan.c
	$(ENV) $(CC) $(CC_FLAGS) -o $(PARSER) $(PARSER).c scan.c err.c
	@make halfclean



halfclean:
	rm -f *.c *.h *.dlg *.o *.hi programhs.txt

clean: halfclean
	rm -f $(MAIN) $(PARSER)

.PHONY: clean
