concat2([], L, L).
concat2([X|Xs], L, [X|R]) :- concat2(Xs, L, R).

nat(0).
nat(N) :- nat(N1), N is N1 + 1.

%% list(N, R): generates a list from 1 to N
list(N, R):-findall(X, between(1, N, X), R).

pert_con_resto(X, L, Resto) :-
	concat2(L1, [X|L2], L),
	concat2(L1, L2, Resto).

permutacion([],[]).
permutacion(L, [X|P]) :- pert_con_resto(X,L,R), permutacion(R, P).




%% exercises

%% 2,3,5-9

%% 2: product of a list
prod([],1).
prod([X|XS],P):-
	prod(XS, P1),
	P is (X * P1).

%% 3: scalar product of 2 lists
scalar([],[],[]).
scalar([X|XS],[Y|YS],[R|RS]):-
	R is X * Y,
	scalar(XS, YS, RS).

%% 5: last(L, X)
last([X], X).
last([_|Xs], R) :- last(Xs, R). 

%% 5: reverse(L, R).
reverse([], []).
reverse([L|Ls], R) :- concat2(Ls, [L], R).


%% 6: fib(N, F).
fib(1,1).
fib(2,1).
fib(N,F) :-
	N > 2,
	N1 is N - 1,
	N2 is N - 2,
	fib(N1, F1),
	fib(N2, F2),
	F is F1 + F2.


%% 7: dados(P, N, L).
dados(P, 1, [P]).
dados(P, N, [X|L]) :-
	N > 1,
	N1 is N - 1,
	between(1, 6, X), X < P,
	P1 is P - X,
	dados(P1, N1, L).

%% 8:
sum_rest(X) :-
	sum_list(X, S),
	member(R, X),
	S is R*2.

%% 9:
sum_before(X) :- sum_aux(0, X).
sum_aux(S, [X|_]) :- X is S, !.
sum_aux(S, [X|Xs]) :- S1 is S + X, sum_aux(S1, Xs).

%% 10:
card(_, [], 0).
card(X, [X|Ls], R) :- card(X, Ls, R1), R is R1 + 1, !.
card(X, [_|Ls], R) :- card(X, Ls, R).

card_pair(L, X, [X,Y]) :- card(X, L, Y).
card(L, R) :-
	list_to_set(L, S),
	member(X, S),
	card_pair(L, X, R).

print_card(L) :-
	findall(X, card(L, X), R),
	write(R).

%% 11:
sorted([]).
sorted([_]).
sorted([X,Y|Z]) :-
	X < Y,
	sorted([Y|Z]),
	!.


%% 14:
%% given a sorted list L, inserts X into L at the correct position
insert(X, [], [X]).
insert(X, [L|Ls], [X,L|Ls]) :- X < L, !.
insert(X, [L|Ls], [L|R]) :- insert(X, Ls, R).

ins_sort([], []).
ins_sort([X|Xs], R) :-
	ins_sort(Xs, R1),
	insert(X, R1, R),
	!.
	

%% 17
alphabet(_, 0, "") :- !.
alphabet(A, N, R) :-
	N1 is N - 1,
	alphabet(A, N1, Word),
	member(Suffix, A),
	atom_concat(Word, Suffix, R).

dict(A, N) :-
	findall(X, alphabet(A, N, X), R),
	member(X, R),
	write(X), write(" "),
	fail.
dict(_,_).



%% sendmory

pad5([A,B,C,D], [0,A,B,C,D]).
pad5(_).

sum_digits(L1, L2, R) :-
	atomic_list_concat(L1, '', T1),
	atomic_list_concat(L2, '', T2),
	atom_number(T1, N1),
	atom_number(T2, N2),
	N3 is N2 + N1,
	atom_number(T3, N3),
	atom_chars(T3, ResChars),
	maplist(atom_number, ResChars, ResUnpadded),
	pad5(ResUnpadded, R).

send_mory :-
	permutacion([0,1,2,3,4,5,6,7,8,9], [S,E,N,D,M,O,R,Y,_,_]),
	sum_digits([S,E,N,D], [M,O,R,E], [M,O,N,E,Y]),
	write([S,E,N,D]),
	write(" + "),
	write([M,O,R,E]),
	write(" = "),
	write([M,O,N,E,Y]),
	nl, fail.
