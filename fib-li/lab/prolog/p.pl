padre(juan,pedro).
padre(maria,pedro).
hermano(pedro,vicente).
hermano(pedro,alberto).
tio(X,Y):-padre(X,Z),hermano(Z,Y).

suma([],0).
suma([X|L],S):-suma(L,S1), S is X+S1.

pert(X,[X|_]).
pert(X,[_|L]):-pert(X,L).

% print all answers:
% pert(X,[1,2,7]), write(X),nl,fail.

%% concat(L1,L2,C).
concat([],X,X).
concat([X|L1],L2,[X|C]):-concat(L1,L2,C).

%% last([2,3,5], X)   X=5
last(L, U):-concat(_, [U] ,L).

%% factorial(N, F).
factorial(0, 1).
factorial(N, F):-
	N > 0,
	N1 is N-1,
	factorial(N1, F1),
	F is N * F1.



%% exercicis: 2,3,5-9

