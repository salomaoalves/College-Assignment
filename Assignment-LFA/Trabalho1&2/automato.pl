palavravazia(['e']).
aceita(S,[]):- final(S),!.
aceita(S,[X|Y]):- trans(S,X,S1),aceita(S1,Y).
aceita(S,X):- vazia(S,S1),aceita(S1,X).
concatena([],L,L).
concatena([X|Z],Y,[X|R]):- concatena(Z,Y,R).
mudanca(R):- alfabeto(Y),palavravazia(Z),concatena(Y,Z,R).
pertence(X,[Y|_]) :-  X=Y,!.
pertence(X, [Z|Y]) :- not(X=Z), pertence(X,Y).
verifica([X]):- mudanca(Y),pertence(X,Y),!.
verifica([X|Z]):-mudanca(Y), pertence(X,Y),verifica(Z).
automato:-(read(A),string_chars(A,L)),consult('C:/Users/Samsung/Desktop/Trabalho LFA/vaiDaSim.pl'),inicial(Z),assert(trans(Z,'e',Z)),
((verifica(L)->aceita(Z,L),!,write('Linguagem aceita'));
(write('Essa palavra utiliza caracteres fora do alfabeto'),fail)).

