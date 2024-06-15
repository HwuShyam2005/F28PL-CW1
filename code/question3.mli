(* This is an *interface* file, which specifies the types of top-level
   functions exported from its analogue for usage and testing: do not touch! *)

type move = Fill of int | Drain of int | Transfer of int * int

val doMove : int list -> int list -> move -> int list

val check : int -> int list -> bool

val run : int list -> int -> move list -> bool

val solve : int list -> int -> move list option
