(* This is an *interface* file, which specifies the types of top-level
   functions exported from its analogue for usage and testing: do not touch! *)

val all : ('a -> bool) -> 'a list -> bool

val exists : ('a -> bool) -> 'a list -> bool
