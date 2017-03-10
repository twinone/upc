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
