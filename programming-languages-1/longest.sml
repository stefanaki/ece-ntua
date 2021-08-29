(*
 * longest.sml
 *)

(*
 * Giorgos Stefanakis el18436
 * Fragiskos Kondilis el18828
 *)

(* Explanation of the algorithm available in file longest.cpp *)

local

fun parse file =
  let
    (* A function to read an integer from specified input. *)
    fun readInt input =
    Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) input)

    (* Open input file. *)
    val inStream = TextIO.openIn file

    (* Read an integer (number of countries) and consume newline. *)
    val k = readInt inStream
    val n = readInt inStream
    val _ = TextIO.inputLine inStream

    (* A function to read N integers from the open file. *)
    fun readInts 0 acc = rev acc (* Replace with 'rev acc' for proper order. *)
      | readInts i acc = readInts (i - 1) (readInt inStream :: acc)
  in
 	  (k, n, readInts k [])
  end

fun prefix_sum (x, _) = x
fun index (_, x) = x

fun compare_greater (a, b) =
  if prefix_sum a = prefix_sum b then index a > index b
  else prefix_sum a > prefix_sum b

fun binary_search (array, l, r, x) =
  let
    val mid = (l + r) div 2
  in
    if (x = prefix_sum (Array.sub (array, mid))) then mid
    else
      if (x < prefix_sum (Array.sub (array, mid))) then
        binary_search (array, l, mid - 1, x)
      else binary_search (array, mid + 1, r, x)
  end

fun calculate_prefix_sums_indexes ([], s, i) = []
  | calculate_prefix_sums_indexes (l, s, i) =
      let
        val x = (s + hd l, i)
      in
        x :: calculate_prefix_sums_indexes (tl l, s + hd l, i + 1)
      end

fun calculate_minInd_list (pf_array, i, j, k) =
  if i = k then []
  else if i = 0 then
    let
      val temp = index (Array.sub (pf_array, 0))
    in
      temp :: calculate_minInd_list (pf_array, i + 1, temp, k)
    end
  else
    let
      val temp = Int.min (index (Array.sub (pf_array, i)), j)
    in
      temp :: calculate_minInd_list (pf_array, i + 1, temp, k)
    end

fun calculate_result ([], sum, result, len, pf_array, minind, k) = result
  | calculate_result (l, sum, result, len, pf_array, minind, k) =
    let
      val current_sum = sum + hd l
    in
      if current_sum >= 0 then
        calculate_result (tl l, current_sum, len, len + 1, pf_array, minind, k)
      else let
        val temp = binary_search (pf_array, 0, k - 1, current_sum)
        val min_index = Array.sub (minind, temp)
      in
        if min_index < len - 1 then
          calculate_result (tl l, current_sum,
            Int.max (result, len - 1 - min_index), len + 1, pf_array, minind, k)
        else calculate_result (tl l, current_sum, result, len + 1, pf_array, minind, k)
      end
    end

in

fun longest input =
  let
    val (K, N, list) = parse input
    val list = map (fn x => (~1 * x) - N) list
    val pf = calculate_prefix_sums_indexes (list, 0, 0)
    val pf = ListMergeSort.sort compare_greater pf
    val pf_array = Array.fromList pf
    val minInd_array = Array.fromList (calculate_minInd_list (pf_array, 0, 0, K))
  in
    print (Int.toString (calculate_result (list, 0, 0, 1, pf_array, minInd_array, K)) ^ "\n")
  end

end
