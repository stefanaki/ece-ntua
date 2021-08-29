% qssort.pl

% Fragiskos Kondilis
% Giorgos Stefanakis

read_input(File, N, C) :-
    open(File, read, Stream),
    read_line(Stream, N),
    read_line(Stream, C).

read_line(Stream, L) :-
    read_line_to_codes(Stream, Line),
    atom_codes(Atom, Line),
    atomic_list_concat(Atoms, ' ', Atom),
    maplist(atom_number, Atoms, L).

is_even(X, Y) :- Y is X mod 2.

check_sorted([]).
check_sorted([_]).
check_sorted([A, B|T]) :-
    A =< B,
    check_sorted([B|T]).

check_for_duplicates(state([H|_], [H|_]), Move) :- Move = "Q".

move(state([Q1Head|Q1Tail], S1), "Q", state(Q2, S2), CountQ, NewCountQ) :-
    S2 = [Q1Head|S1],
    Q2 = Q1Tail,
    NewCountQ is CountQ + 1.

move(state(Q1, [S1Head|S1Tail]), "S", state(Q2, S2), CountQ, CountQ) :-
    S2 = S1Tail,
    reverse(Q1, Q1Rev),
    Q3 = [S1Head|Q1Rev],
    reverse(Q3, Q2).

final(state(Queue, [])) :- check_sorted(Queue).

solve(state(Queue, Stack), [], _, _) :- final(state(Queue, Stack)).
solve(state(Queue, Stack), [Move|Moves], Len, CountQ) :-
    is_even(Len, 0),
    X is Len div 2,
    (
        CountQ =:= X -> Move = "S", move(state(Queue, Stack), Move, state(NQueue, NStack), CountQ, CountQ),
        solve(state(NQueue, NStack), Moves, Len, CountQ);
        (
            check_for_duplicates(state(Queue, Stack), Move) ->
                move(state(Queue, Stack), Move, state(NQueue, NStack), CountQ, NewCountQ),
                solve(state(NQueue, NStack), Moves, Len, NewCountQ);
            move(state(Queue, Stack), Move, state(NQueue, NStack), CountQ, NewCountQ),
            solve(state(NQueue, NStack), Moves, Len, NewCountQ)
        )
    ).

solve(Moves, Q, S) :-
    length(Moves, Len),
    solve(state(Q, S), Moves, Len, 0).

qssort(File, Answer) :-
    read_input(File, _, L),
    (
        final(state(L, [])) -> Answer = "empty";
        once(solve(A, L, [])), atomic_list_concat(A, "", Answer)
    ).
