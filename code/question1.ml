(** CW1, QUESTION 1 **)

(* a (3 marks) *)

(*RECURSIVE FUNCTION "ALL"*)
(*PARAMETERS "P" PREDICATE FUNCTION AND "XS" LIST*)
let rec all p xs =

(*MATCHING XS WITH EITHER NON EMPTY LIST "[]" AND WITH HT AND TL*)
   match xs with
   | [] -> true 
   | hd :: tl -> 

(*IF P HD IS TRUE,IT RECURSIVELY CALLS ALL P TL*)
(*IF P HD IS FALS,IT RETURNS FALSE*)
   if p hd then all p tl else false;;
   
(*Example usage*)   
(*abc*)
(*IF GIVEN FUNCTION RETURNS 0 , IT MEANS X ISEVEN AND RETURNS TRUE*)
(*IF GIVEN FUNCTION DOES NOT RETURN 0 , IT RETURNS FALSE *)
let isEven x = x mod 2 = 0;;





(* b (3 marks) *)

(*RECURSIVE FUNCTION "FOLDLEFT"*)
(*THREE PARAMETERS "V2" INITIAL VALUE , "F2" BINARY FUNCTION AND "XS2" LIST*)
let rec foldLeft v2 f2 xs2 =

(*MATCHING XS2 WITH "[]" INCASE IF IT RETURNS VS*)
(*MATCHING XS2 WITH A NONEMPTY LIST X2 :: XS2 *)
   match xs2 with
   | [] -> v2

(*"X2" IS HEAD AND "XS2" IS TAIL*)
(*IF THIS CONDITION HAPPENS, IT RECURSIVELY CALLS FOLDLEFT*)
| x2 :: xs2 -> foldLeft (f2 v2 x2) f2 xs2;;

(*DEFINING EXIST FUNCTION*)
(*TWO PARAMETERS "P" PREDICATE FUNCTION AND "XS" LIST*)
let exists p xs =

(*USES LOCAL FUNCTION "F" AND ACCUMULATOR "ACC" AND ELEMENT "X"*)
(*F CHECKS IF P HOLDS TRUE FOR X *)
(*IF YES, IT RETURNS TRUE . OR ELSE FALSE*)
   let f acc x = acc || p x in
   foldLeft false f xs;;

(*DEFINES FUNCTION NAME ISEVEN*)
(*IF GIVEN FUNCTION RETURNS 0 , IT MEANS X ISEVEN AND RETURNS TRUE*)
(*IF GIVEN FUNCTION DOES NOT RETURN 0 , IT RETURNS FALSE *)   
let isEven x = x mod 2 = 0;;

 



(* c (2 marks) *)

(* Provide your answer in this comment (you are free to implement) allF if you find it useful!
The fundamental distinction between all and allF lies in their treatment of an empty list. While 
all inherently returns true when given an empty list due to its base case, allF is designed to 
also return true in this scenario. This distinction arises from the fact that allF initializes 
with true as the starting accumulator value and subsequently employs the logical "and" 
operator throughout the fold operation.

In this particular example, both all and allF yield true because every element in the list adheres to the condition specified by the isEven predicate.
*)





(* d (2 marks) *)
(* Once you figure out what parameters allSpec and existsSpec should
   take, replace the dummy paramter () with the chosen ones *)
   
(*ALLSPEC FUNCTION*)
(*TWO ARGUMENTS "P" PREDICATE FUNCTION AND "XS" LIST *)
   let allSpec p xs =
   
(*AN INNER RECURSIVE FUNCTION CHECKALL, THAT RECURSIVELY TRAVERSES THE "LST"*)   
      let rec checkAll lst =

(*IF LST IS EMPTY , IT RETURNS TRUE*)
(*IF LST IS NOT EMPTY , IT CHECKS IF P HOLDS TRUE FOR X *)
         match lst with
        | [] -> true
        | x :: xs -> p x && checkAll xs

(*FINAL RESULT OF THE LST NOT EMPTY CONDITION RECURSIVELY CALLS CHECKALL ON TAIL XS*)
      in
      checkAll xs;;
    
    (*Type : ('a -> bool) -> 'a list -> bool *)
(*EXISTSSPEC FUNCTION*)
(*TWO ARGUMENTS "P" PREDICATE FUNCTION AND "XS" LIST*)
    let existsSpec p xs =

(*DEFINING A INNER RECURSIVE FUNCTION CHECKEXISTS THAT RECURSIVELY TRAVERSES LST*)
      let rec checkExists lst =

(*IF LST IS EMPTY , IT RETURNS FALSE*)
(*IF LST IS NOT EMPTY , IT CHECKS IF P HOLDS TRUE FOR X*)
        match lst with
        | [] -> false
        | x :: xs -> p x || checkExists xs

(*FINAL RESULT OF THE LST IS NOT EMPTY CONDITION RECURSIVELY CALLS CHECKEXISTS ON TAIL XS*)        
      in
      checkExists xs;;
    
    (*Type : ('a -> bool) -> 'a list -> bool*)





