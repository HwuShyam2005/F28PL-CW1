(** CW2, QUESTION 2 **)

(* a (3 marks) *)

(*RECURSIVE  FUNCTION EXTRACTMIN*)
let rec extractMin lst =

(*IF LST IS EMPTY , RAISES THE EXCEPTION "LIST IS EMPTY"*)
(*IF LST HAS 1 ELEMENT , IT RETURNS THAT ELEMENT AND AN EMPTY LIST*)
(*IF LST HAS MORE THAN 1 ELEMENT , IT RECUSIVELY CALLS EXTRACTMIN ON THE TAIL*)
  match lst with
  | [] -> failwith "List is empty"  
  | [x] -> (x, [])  
  | x :: xs ->
    let (minimum, rest) = extractMin xs in

(*1)RETURNS (X,XS) WITH X AS NEW MINIMUM AND XS AS REST OF LIST*)
(*2)RETURNS (MINIMUM , X::REST) WITH EXISTING MINIMUM AND X IS APPENDED AT END OF LIST *)
if minimum > x then
      (x, xs)
    else
      (minimum, x :: rest)

let result = extractMin [1; 2; 3];;





(* b (3 marks) *)
(*RECURSIVE FUNCTION EXTRACTSORT*)
let rec extractSort lst =

(*IF LST IS EMPTY , IT RETURNS AN EMPTY LIST*)
(*IF LST IS NOT EMPTY , IT PROCEEDS WITH THE SORTING PROCESS*)

match lst with
  | [] -> []  (* An empty list is already sorted *)
  | _ ->

(*USES EXTRACTMIN TO FIND AND EXTRACT ELEMENT MIN FROM LST*)
    let (min, rest) = extractMin lst in

(*THIS IS OBTAINED RECURSIVELY CALLING EXTRACTSORT ON REST IN ASCENDING ORDER*)
    min :: extractSort rest;;

extractSort[3; 6; 8; 5];;





(* c (2 marks) *)
(* Provide your answer in this comment block
extractSort [2; 3; 1]
=> (1, [2; 3])
=> 1 :: extractSort [2; 3]
=> 1 :: (2, [3])
=> 1 :: 2 :: extractSort [3]
=> 1 :: 2 :: (3, [])
=> 1 :: 2 :: 3 :: extractSort []
=> 1 :: 2 :: 3 :: []

 *)

(* d (2 marks) *)
(* Provide your answer in this comment block
extractMin is tail-recursive and does not generate garbage, while extractSort is not tail-recursive and generates garbage.


*)
