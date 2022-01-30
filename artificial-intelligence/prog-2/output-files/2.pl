
  findSim1(X, Y) :- twoCommonKeywords(X, Y), X \= Y.
  findSim1(X, Y) :- twoCommonGenres(X, Y), X \= Y.
  findSim1(X, Y) :- oneCommonActor(X, Y), X \= Y.
  findSim1(X, Y) :- commonDirector(X, Y), X \= Y.
  findSim1(X, Y) :- commonCountry(X, Y), X \= Y.
  findSim1(X, Y) :- sameLanguage(X, Y), X \= Y.
  %findSim1(X, Y) :- highlyVoted(X, Y), X \= Y.
  findSim1(X, Y) :- sameDecade(X, Y), X \= Y.

  findSim2(X, Y) :- twoCommonKeywords(X, Y), X \= Y.
  findSim2(X, Y) :- threeCommonGenres(X, Y), X \= Y.
  findSim2(X, Y) :- commonDirector(X, Y), X \= Y.
  findSim2(X, Y) :- oneCommonActor(X, Y), X \= Y.
  findSim2(X, Y) :- sameDecade(X, Y), commonCountry(X, Y), X \= Y.
  findSim1(X, Y) :- sameLanguage(X, Y), X \= Y.

  findSim3(X, Y) :- twoCommonKeywords(X, Y), X \= Y, threeCommonGenres(X, Y), X \= Y.
  findSim3(X, Y) :- sameDecade(X, Y), commonDirector(X, Y), X \= Y.
  findSim3(X, Y) :- sameDecade(X, Y), commonCountry(X, Y), X \= Y.
  findSim3(X, Y) :- oneCommonActor(X, Y), X \= Y.

  findSim4(X, Y) :- fourCommonKeywords(X, Y), threeCommonGenres(X, Y), X \= Y.
  findSim4(X, Y) :- fourCommonKeywords(X, Y), X \= Y.
  findSim4(X, Y) :- sameDecade(X, Y), commonDirector(X, Y), X \= Y.
  findSim4(X, Y) :- sameDecade(X, Y), commonCountry(X, Y), X \= Y.
  findSim4(X, Y) :- twoCommonActors(X, Y), X \= Y.

  findSim5(X, Y) :- fiveCommonKeywords(X, Y), fiveCommonGenres(X, Y), X \= Y.
  findSim5(X, Y) :- fiveCommonKeywords(X, Y), X \= Y.
  findSim5(X, Y) :- sameDecade(X, Y), commonDirector(X, Y), sameLanguage(X, Y), X \= Y.
  findSim5(X, Y) :- sameDecade(X, Y), commonCountry(X, Y), sameLanguage(X, Y), X \= Y.
  