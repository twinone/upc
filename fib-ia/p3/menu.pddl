(define (domain menu)
  	(:requirements :adl :typing :fluents)
  	(:types tipus dia - object
            primer segon - plat)
  	(:predicates 
  		(primer ?p - plat ?t - tipus) 
      (segon ?s - plat ?t - tipus) 
  		(incompatible ?p1 - primer ?p2 - segon) 
      (diainici ?d - dia) (seguent ?d1 ?d2 - dia) 
      (diac ?d - dia)
      (menuprimer ?d - dia ?p - tipus)
      (menusegon ?d - dia ?p - tipus)  
      (utilitzat ?p - plat) 
      (restriccio ?d - dia ?p - plat)
  	)
    (:functions
      (calories ?p - plat)
      (total-cal)
    )
    (:action setmenu
      :parameters (?dact - dia ?tpact ?tsact - tipus ?pact - primer ?sact - segon)
      :precondition
      (and
        (not (diac ?dact))
        (not (utilitzat ?pact))
        (not (utilitzat ?sact))
        (not (incompatible ?pact ?sact))
        (primer ?pact ?tpact)
        (segon ?sact ?tsact)
        (<= (+ (calories ?pact) (calories ?sact)) 1500)
        (>= (+ (calories ?pact) (calories ?sact)) 1000)
        (or 
          (restriccio ?dact ?pact) 
          (not (exists (?d3 - dia) (restriccio ?d3 ?pact)))
          )
        (or 
          (restriccio ?dact ?sact) 
          (not (exists (?d3 - dia) (restriccio ?d3 ?sact)))
          )
        (or
          (diainici ?dact)
          (and
            (not (exists (?daux - dia) (and (seguent ?daux ?dact) (menuprimer ?daux ?tpact))))
            (not (exists (?daux - dia) (and (seguent ?daux ?dact) (menusegon ?daux ?tsact))))
            )
          )
        )
      :effect (and (diac ?dact) (utilitzat ?pact) (utilitzat ?sact) (menuprimer ?dact ?tpact) (menusegon ?dact ?tsact) (increase (total-cal) (+ (calories ?pact) (calories ?sact))))
      )
)
