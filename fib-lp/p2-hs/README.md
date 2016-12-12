# Invented language interpreter in Haskell

Complete project at https://github.com/twinone/fib-lp

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

For a nicer output: ./dbg.sh tests/testcase.in
To test all test cases: ./testall.sh

Notes
=====
1. The statement is not clear as to how to count the instructions.
Quoted:
> Es mostrarà la llista d’entrada, la de sortida i s’indicarà el
> nombre d’instruccions que s’han executat en el test. Cada instrucció s’ha
> de comptar un sol cop. 

How many instructions will there be for the following snippet?:
> INPUT X
> INPUT X

And what about:
> X := 2
> WHILE X > 0 DO X := X - 1 END

Since this is not clear in the statement, I've increased a counter each time an instruction is executed (everytime it's executed)


We were given a function signature which we could explicitly not modify:
interpretCommand :: (Num a, Ord a) =>SymTable a -> [a] -> Command a -> (Either String [a], SymTable a, [a])

To be able to track the number of instructions executed, as well as the inputs (without creating state hacks)
I've made a workaround to be able to track them:
The [a] of the return value of interpretCommand is supposed to store the output list. Instead of that, it will contain the
following protocol:
The number of elements of the list is always even.
A number preceded by 0 means this number was on the input list
A number preceded by 1 means this number was on the output list
A 1preceded by 2..8 means a command of type (Assign, Print, Input, Empty, Pop, Push, Size) has been executed, in that order.

So after a command has been executed, we can show the number of instructions, as well as the input parameters.

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


