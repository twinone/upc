CC := g++
PROG := lego
CC_FLAGS := -Wno-write-strings
ENV := CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/home/soft/PCCTS_v1.33/include

all:
	antlr -gt $(PROG).g
	dlg -ci parser.dlg scan.c
	$(ENV) $(CC) $(CC_FLAGS) -o $(PROG).o $(PROG).c scan.c err.c
	@make halfclean


halfclean:
	rm -f *.c *.h *.dlg

clean: halfclean
	rm $(PROG).o

.PHONY: clean
