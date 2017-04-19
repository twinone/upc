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

casas :- Sol = [[1,_,_,_,_,_],
		[2,_,_,_,_,_],
		[3,_,_,_,_,_],
		[4,_,_,_,_,_],
		[5,_,_,_,_,_]],
	% casa, color, prof, animal, bebida, pais
	member([_,rojo,_,_,_,peru], Sol),
	member([_,_,_,perro,_,francia], Sol),
	member([_,_,pintor,_,_,japon], Sol),
	member([_,_,_,_,ron,china], Sol),
	member([1,_,_,_,_,hungria], Sol),
	member([_,verde,_,_,cognac,_], Sol),
	member([NumCasaBlanca,blanco,_,_,_,_], Sol),
	member([NumCasaVerde,verde,_,_,_,_], Sol),
	member([_,_,escultor,caracol,_,_], Sol),
	member([_,amarillo,actor,_,_,_], Sol),
	member([3,_,_,_,cava,_], Sol),
	member([NumCasaActor,_,actor,_,_,_], Sol),
	member([NumCasaCaballo,_,_,caballo,_,_], Sol),
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

% 3
programa(R) :-
	append(R1, ['end'], R),
	append(['begin'], Is, R1),
	instrucciones(Is), !.

instrucciones(R) :- instruccion(R), !.
instrucciones(R) :-
	append(R1, Is, R),
	append(I, [';'], R1),
	instruccion(I),	instrucciones(Is), !.

instruccion(R) :- 
	append(R3, X3, R),
	append(R2, ['+'], R3),
	append(R1, X2, R2),
	append(X1, ['='], R1),
	variable(X3), variable(X2), variable(X1).

instruccion(R) :-
	append(R7, ['endif'], R),
	append(R6, Is2, R7),
	append(R5, ['else'], R6),
	append(R4, Is, R5),
	append(R3, ['then'], R4),
	append(R2, X2, R3),
	append(R1, ['='], R2),
	append(['if'], X1, R1),
	instrucciones(Is2), instrucciones(Is),
	variable(X2), variable(X1).

variable([X]) :- member(X, ['x', 'y', 'z']), !.
