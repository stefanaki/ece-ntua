(* round.sml *)

(* Giorgos Stefanakis *)
(* Fragiskos Kondilis *)

fun parse file =
  let
    (* A function to read an integer from specified input. *)
    fun readInt input =
      Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) input)

    (* Open input file. *)
  	val inStream = TextIO.openIn file

    val T = readInt inStream
    val V = readInt inStream
    val _ = TextIO.inputLine inStream

    (* A function to read N integers from the open file. *)
    fun readInts 0 acc = rev acc
      | readInts i acc = readInts (i - 1) (readInt inStream :: acc)
  in
 	  (T, V, readInts V [])
  end


fun distance ([], _, T, sum, max) = (sum, max)
  | distance ((h::t), final, T, sum, max) =
      if final >= h then
        distance (t, final, T, sum + final - h, Int.max(max, final - h))
      else
        distance (t, final,  T, sum + T + final - h, Int.max(max, T + final - h))

fun solver(init, sum, index, final, T) =
  if final = T then (sum, index)
  else
    let
      val (currentSum, currentMax) = distance(init, final, T, 0, 0)
    in
      if currentMax > currentSum - currentMax + 1 orelse currentSum > sum  then
        solver (init, sum, index, final + 1, T)
      else if currentSum < sum then
        solver (init, currentSum, final, final + 1, T)
      else solver (init, sum, index, final + 1, T)
    end

fun round input =
  let
    val (T, V, init) = parse input
    val (M, C) = solver (init, 1073741823, 0, 0, T)
  in
    print (Int.toString M ^ " " ^ Int.toString C ^ "\n")
  end