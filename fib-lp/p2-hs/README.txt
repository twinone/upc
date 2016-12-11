Installation
============

This program requires the random package:
sudo apt-get install cabal-install
cabal update
cabal install random

To create the executables: parser and main
1. Have antlr and dlg in yout PATH
2. export CPLUS_INCLUDE_PATH=/path/to/pccts/h/
make

Running
=======

Execute ./test <file> to execute the file
I hope you're not on windows ^^

For a nicer output: ./dbg.sh test/testcase.in

Notes
=====
1. Printing the number of instructions executed would require a different approach to the interpreter
2. Printing the randomly generated inputs would require a different approach to the interpreter
Either those, or use *very* ugly hacks (like storing the count in the symtable or the inputs list)


Assumptions
===========

1. A variable can have only one type, but it's type can change (like in js, python, ghci, etc)
This will even work when you pop from a stack to itself, (like 's = pop(s)' in other languages)

Example:
EMPTY S
PUSH S 1
POP S S // S would now be 1

2. Right hand value of := (Assign) must be a NExpr
You cannot do the following:
EMPTY P
S := P


