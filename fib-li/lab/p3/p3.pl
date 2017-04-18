% 1
flatten([], []).
flatten([[X|Xs]|Xss], R) :-
	flatten([X|Xs], R1),
	flatten(Xss, R2),
	append(R1, R2, R),
	!.
flatten([X|Xs], [X|R]) :- flatten(Xs, R).



flattenNoRepetitions(L, R) :- flatten(L, R1), fnr(R1, R).
filter(_, [], []).
filter(X, [X|Xs], R) :- filter(X, Xs, R), !.
filter(X, [Y|Xs], [Y|R]) :- filter(X, Xs, R).

fnr([], []).
fnr([X|Xs], [X|R]) :- filter(X, Xs, R1), fnr(R1, R), !.


% 2

al_lado(X, Y) :- X is Y - 1.
al_lado(X, Y) :- Y is X - 1.

casas :- Sol = [ [1,A1,B1,C1,D1,E1],
		 [2,A2,B2,C2,D2,E2],
		 [3,A3,B3,C3,D3,E3],
		 [4,A4,B4,C4,D4,E4],
		 [5,A5,B5,C5,D5,E5]],

	% casa, color, prof, animal, bebida, pais
	member([_,rojo,_,_,_,peru], Sol),
	member([_,_,_,perro,_,francia], Sol),
	member([_,_,pintor,_,_,japon], Sol),
	member([_,_,_,_,ron,china], Sol),
	member([1,_,_,_,_,hungria], Sol),
	% casa, color, prof, animal, bebida, pais
	member([_,verde,_,_,cognac,_], Sol),
	member([NumCasaBlanca,blanco,_,_,_,_], Sol),
	member([NumCasaVerde,verde,_,_,_,_], Sol),
	member([_,_,escultor,caracol,_,_], Sol),
	member([_,amarillo,actor,_,_,_], Sol),
	member([3,_,_,_,cava,_], Sol),
	member([NumCasaActor,_,actor,_,_,_], Sol),
	member([NumCasaCaballo,_,_,caballo,_,_], Sol),
	% casa, color, prof, animal, bebida, pais
	member([NumCasaHungaro,_,_,_,_,hungria], Sol),
	member([NumCasaAzul,azul,_,_,_,_], Sol),
	member([_,_,notario,_,whisky,_], Sol),
	member([NumCasaMedico,_,medico,_,_,_], Sol),
	member([NumCasaArdilla,_,_,ardilla,_,_], Sol),

	NumCasaVerde is NumCasaBlanca - 1,
	al_lado(NumCasaActor, NumCasaCaballo),
	al_lado(NumCasaHungaro, NumCasaAzul),
	al_lado(NumCasaMedico, NumCasaArdilla),


%	member(X, Sol), write(X), nl, fail.
%casas.
	write(Sol), nl, !.
