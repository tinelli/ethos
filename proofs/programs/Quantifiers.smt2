(include "../theories/Builtin.smt2")
(include "../theories/Quantifiers.smt2")

(program substitute
  ((T Type) (U Type) (S Type) (V Type) (x S) (y S) (f (-> T U)) (a T) (z U) (w V))
  (S S U) U
  (
  ((substitute x y x)             y)
  ((substitute x y (skolem w))    (skolem w))   ; do not traverse into skolems
  ((substitute x y (f a))         (_ (substitute x y f) (substitute x y a)))
  ((substitute x y z)             z)
  )
)
(program substitute_list ((T Type) (U Type) (F U) (x T) (xs @List :list) (t T) (ts @List :list))
  (@List @List U) U
  (
    ((substitute_list (@list x xs) (@list t ts) F) (substitute_list xs ts (substitute x t F)))
    ((substitute_list alf.nil alf.nil F)           F)
  )
)
