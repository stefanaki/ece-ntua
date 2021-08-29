% longest.pl

% Giorgos Stefanakis
% Fragiskos Kondilis

read_input(File, K, N, C) :-
    open(File, read, Stream),
    read_line(Stream, [K, N]),
    read_line(Stream, C).

read_line(Stream, L) :-
    read_line_to_codes(Stream, Line),
    atom_codes(Atom, Line),
    atomic_list_concat(Atoms, ' ', Atom),
    maplist(atom_number, Atoms, L).

incr(X, X1) :- X1 is X + 1.

modify(L, N, Modified_List) :-
    modify(L, N, [], Modified_List_Rev),
    reverse(Modified_List_Rev, Modified_List).

modify([], _, Modified_List, Modified_List).

modify([Head|Tail], N, R, Modified_List) :-
    Temp is -Head - N,
    modify(Tail, N, [Temp|R], Modified_List).

prefix_sum(L, PL) :-
    prefix_sum(L, 0, [], L1),
    reverse(L1, PL).

prefix_sum([], _, R, R).

prefix_sum([Head|Tail], 0, R, PL) :-
    prefix_sum(Tail, 1, [Head|R], PL).

prefix_sum([Head|Tail], 1, R, PL) :-
    R = [RHead|_],
    Temp is Head + RHead,
    prefix_sum(Tail, 1, [Temp|R], PL).

left_min(PL, LM) :-
    left_min(PL, 0, [], L),
    reverse(L, LM).

left_min([Head|Tail], 0, R, L) :-
    left_min(Tail, 1, [Head|R], L).

left_min([], 1, R, R).

left_min([Head|Tail], 1, R, L) :-
    R = [RHead|_],
    Temp is min(RHead, Head),
    left_min(Tail, 1, [Temp|R], L).

right_max(PL, RM):-
  reverse(PL, L),
  right_max(L, 0, [], RM).

right_max([Head|Tail], 0, R, L) :-
    right_max(Tail, 1, [Head|R], L).

right_max([], 1, R, R).

right_max([Head|Tail], 1, R, L) :-
    R = [RHead|_],
    Temp is max(RHead, Head),
    right_max(Tail, 1, [Temp|R], L).

calc_length(PL, Length) :-
    calc_length(PL, 0, 0, Length).

calc_length([], _, Len, Len).

calc_length([Head|Tail], I, Len, L) :-
    ( Head >= 0 -> NewLen is I + 1, NewI is I + 1, calc_length(Tail, NewI, NewLen, L)
    ; NewI is I + 1, calc_length(Tail, NewI, Len, L)
    ).

calc_longest(LM, RM, Length, Result) :-
    calc_longest(LM, RM, Length, 0, 0, Result).

calc_longest(_, [], Length, _, _, Length).
calc_longest([], _, Length, _, _, Length).

calc_longest([LHead|LTail], [RHead|RTail], Length, I, J, Result) :-
    ( RHead >= LHead -> NewLength is max(Length, J - I), NewJ is J + 1,
      calc_longest([LHead|LTail], RTail, NewLength, I, NewJ, Result)
    ; NewI is I + 1, calc_longest(LTail, [RHead|RTail], Length, NewI, J, Result)
    ).


longest(File, Result) :-
    read_input(File, K, N, L),
    modify(L, N, Modified_List),
    prefix_sum(Modified_List, Prefix_List),
    left_min(Prefix_List, Left_Min),
    right_max(Prefix_List, Right_Max),
    calc_length(Prefix_List, Length),
    calc_longest(Left_Min, Right_Max, Length, Result).
