(*
 * loop_rooms.sml
 *)

(*
 * Giorgos Stefanakis el18436
 * Fragiskos Kondilis el18828
 *)

local

fun parse file =
  let
    (* Open input file. *)
    fun readInt input =
	    Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) input)
  	val inStream = TextIO.openIn file
    val N = readInt inStream
    val M = readInt inStream

    (* Reads lines until EOF and puts them in a list as char lists *)
    fun readLines acc =
      let
        val newLineOption = TextIO.inputLine inStream
      in
        if newLineOption = NONE
        then (rev acc)
        else (readLines (explode (valOf newLineOption) :: acc))
    end;

    val plane = readLines []

  in
 	  (N, M, plane)
end

fun check_outter_rooms (maze, vis, N, M) =
  let
    fun check_first_last_col (maze, vis, i, N, M) =
      if i = N then ()
      else (
        if Array2.sub (maze, i, 0) = #"L" then (
          Array2.update (vis, i, 0, 1);
          ()
        ) else ();

        if Array2.sub (maze, i, M - 1) = #"R" then (
          Array2.update (vis, i, M - 1, 1);
          ()
        ) else ();

        check_first_last_col (maze, vis, i + 1, N, M)
      )

    fun check_first_last_row (maze, vis, j, N, M) =
      if j = M then ()
      else (
        if Array2.sub (maze, 0, j) = #"U" then (
          Array2.update (vis, 0, j, 1);
          ()
        ) else ();

        if Array2.sub (maze, N - 1, j) = #"D" then (
          Array2.update (vis, N - 1, j, 1);
          ()
        ) else ();

        check_first_last_row (maze, vis, j + 1, N, M)
      )

  in (
    check_first_last_col(maze, vis, 0, N, M);
    check_first_last_row(maze, vis, 0, N, M)
  ) end

fun find_good_maze_rooms (m, v, i, j, N, M) = (
  if (i - 1 >= 0 andalso Array2.sub (m, i - 1, j)= #"D" andalso Array2.sub (v, i - 1, j) = 0)
    then (
      Array2.update (v, i - 1, j, 1);
      find_good_maze_rooms (m, v, i - 1, j, N, M)
    ) else();

  if(j - 1 >= 0 andalso Array2.sub (m, i, j - 1) = #"R" andalso Array2.sub (v, i, j - 1) = 0)
    then (
      Array2.update (v, i, j - 1, 1);
      find_good_maze_rooms (m, v, i, j - 1, N, M)
    ) else ();

  if (i + 1 < N andalso Array2.sub (m, i + 1, j) = #"U" andalso Array2.sub (v, i + 1, j) = 0)
    then (
      Array2.update (v, i + 1, j, 1);
      find_good_maze_rooms (m, v, i + 1, j, N, M)
    ) else ();


  if (j + 1 < M andalso Array2.sub (m, i, j + 1) = #"L" andalso Array2.sub (v, i, j + 1) = 0)
    then (
      Array2.update (v, i, j + 1, 1);
      find_good_maze_rooms (m, v, i, j + 1, N, M)
    ) else ()
)

fun traverse_maze (maze, vis, N, M) =
  let
    fun traverse_first_last_col (maze, visited, i, N, M) =
      if i = N then ()
      else (
        if Array2.sub (visited, i, 0) = 1
        then (
          find_good_maze_rooms (maze, visited, i, 0, N, M);
          ()
        ) else ();

        if Array2.sub (visited, i, M - 1) = 1
        then (
          find_good_maze_rooms (maze, visited, i, M - 1, N, M);
          ()
        ) else ();

        traverse_first_last_col (maze, visited, i + 1, N, M)
      )

    fun traverse_check_first_last_row (maze, visited, j, N, M) =
      if j = M then ()
      else (
        if Array2.sub (visited, 0, j) = 1
        then (
          find_good_maze_rooms (maze, visited, 0, j, N, M);
          ()
        ) else ();

        if Array2.sub (visited, N - 1, j) = 1
        then (
          find_good_maze_rooms (maze, visited, N - 1, j, N, M);
          ()
        ) else ();

        traverse_check_first_last_row (maze, visited, j + 1, N, M)
      )

  in (
    traverse_first_last_col (maze, vis, 0, N, M);
    traverse_check_first_last_row (maze, vis, 0, N, M)
  ) end

fun array2_sum (array, i, N, M) =
  if i = N then 0 else
    let
      fun row_sum_array (array, i, j, M) =
        if j = M then 0 else
          Array2.sub (array, i, j) + row_sum_array (array, i, j + 1, M)

      val x = row_sum_array (array, i, 0, M)
    in
      x + array2_sum (array, i + 1, N, M)
    end

in

fun loop_rooms input_file =
  let
    val (N, M, maze) = parse input_file
    val maze_array = Array2.fromList (tl maze)
    val visited = Array2.array(N, M, 0)
  in (
    check_outter_rooms (maze_array, visited, N, M);
    traverse_maze (maze_array, visited, N, M);
    print (Int.toString (N * M - array2_sum (visited, 0, N, M)) ^ "\n")
  ) end

end
