flatten([]).
flatten([X|L]):-
	flatten(X),
	flatten(L).
flatten(_).

