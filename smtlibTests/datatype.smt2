(set-logic ALL)
(declare-datatype Color ((Red) (Blue)))
(declare-fun x () Color)
(assert (not ((_ is Red) x)))
(assert (not ((_ is Blue) x)))
(check-sat)
