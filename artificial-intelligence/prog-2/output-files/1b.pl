
  fiveCommonGenres(X, Y) :-
    genre(X, N1),
    genre(X, N2), N2 \= N1,
    genre(X, N3), N3 \= N1, N3 \= N2,
    genre(X, N4), N4 \= N1, N4 \= N2, N4 \= N3,
    genre(X, N5), N5 \= N1, N5 \= N2, N5 \= N3, N5 \= N4,
    genre(Y, N1),
    genre(Y, N2),
    genre(Y, N3),
    genre(Y, N4),
    genre(Y, N5),
    X \= Y.

  fourCommonGenres(X, Y) :-
    genre(X, N1),
    genre(X, N2), N2 \= N1,
    genre(X, N3), N3 \= N1, N3 \= N2,
    genre(X, N4), N4 \= N1, N4 \= N2, N4 \= N3,
    genre(Y, N1),
    genre(Y, N2),
    genre(Y, N3),
    genre(Y, N4),
    X \= Y.

  threeCommonGenres(X, Y) :-
    genre(X, N1),
    genre(X, N2), N2 \= N1,
    genre(X, N3), N3 \= N1, N3 \= N2,
    genre(Y, N1),
    genre(Y, N2),
    genre(Y, N3),
    X \= Y.

  twoCommonGenres(X, Y) :-
    genre(X, N1),
    genre(Y, N1),
    genre(X, N2), N2 \= N1,
    genre(Y, N2),
    X \= Y.

  oneCommonGenre(X, Y) :-
    genre(X, N1),
    genre(Y, N1),
    X \= Y.

  commonDirector(X, Y):-
    director(X, D),
    director(Y, D),
    X \= Y.

  fiveCommonKeywords(X, Y) :-
    keywords(X, N1),
    keywords(X, N2), N2 \= N1,
    keywords(X, N3), N3 \= N1, N3 \= N2,
    keywords(X, N4), N4 \= N1, N4 \= N2, N4 \= N3,
    keywords(X, N5), N5 \= N1, N5 \= N2, N5 \= N3, N5 \= N4,
    keywords(Y, N1),
    keywords(Y, N2),
    keywords(Y, N3),
    keywords(Y, N4),
    keywords(Y, N5),
    X \= Y.

  fourCommonKeywords(X, Y) :-
    keywords(X, N1),
    keywords(X, N2), N2 \= N1,
    keywords(X, N3), N3 \= N1, N3 \= N2,
    keywords(X, N4), N4 \= N1, N4 \= N2, N4 \= N3,
    keywords(Y, N1),
    keywords(Y, N2),
    keywords(Y, N3),
    keywords(Y, N4),
    X \= Y.

  threeCommonKeywords(X, Y) :-
    keywords(X, N1),
    keywords(X, N2), N2 \= N1,
    keywords(X, N3), N3 \= N1, N3 \= N2,
    keywords(Y, N1),
    keywords(Y, N2),
    keywords(Y, N3),
    X \= Y.

  twoCommonKeywords(X, Y) :-
    keywords(X, N1),
    keywords(Y, N1),
    keywords(X, N2), N2 \= N1,
    keywords(Y, N2),
    X \= Y.

  oneCommonKeywords(X, Y) :-
    keywords(X, N1),
    keywords(Y, N1),
    X \= Y.

  actor(X, N) :- actor1(X, N).
  actor(X, N) :- actor2(X, N).
  actor(X, N) :- actor3(X, N).

  sameActors(X, Y) :-
    actor(X, N1),
    actor(X, N2), N2 \= N1,
    actor(X, N3), N3 \= N1, N3 \= N2,
    actor(Y, N1),
    actor(Y, N2),
    actor(Y, N3),
    X \= Y.

  twoCommonActors(X, Y) :-
    actor(X, N1),
    actor(X, N2), N2 \= N1,
    actor(Y, N1),
    actor(Y, N2),
    X \= Y.

  oneCommonActor(X, Y) :-
    actor(X, N),
    actor(Y, N),
    X \= Y.

  sameLanguage(X, Y) :-
    language(X, N),
    language(Y, N),
    X \= Y.

  blackAndWhite(X) :-
    keywords(X, 'black and white').

  commonCompany(X, Y) :-
    productionCompany(X, N),
    productionCompany(Y, N),
    X \= Y.

  commonCountry(X, Y) :-
    productionCountry(X, N),
    productionCountry(Y, N),
    X \= Y.

  equals(X, X).

  sameDecade(X, Y) :-
    titleYear(X, A),
    titleYear(Y, B),
    atom_number(A, N1),
    atom_number(B, N2),
    P is div(N1, 1000),
    Q is div(N2, 1000),
    equals(P, Q),
    R is div(N1, 10),
    S is mod(R, 10),
    T is div(N2, 10),
    W is mod(T, 10),
    equals(S, W),
    X \= Y.

  highlyVoted(X) :-
    voteAverage(X, A),
    atom_number(A, N),
    N > 7.

  simillarHighlyVoted(X, Y) :-
    twoCommonKeywords(X, Y),
    highlyVoted(Y),
    X \= Y.
  