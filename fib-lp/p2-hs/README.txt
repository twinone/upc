-- We assume you can do the following:

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


