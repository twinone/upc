(define (domain menu)
  	(:requirements :adl :typing :fluents)
  	(:types tipus dia - object
            primer segon - plat)
  	(:predicates 
  		(primer ?p - primer ?t - tipus) 
      (segon ?s - segon ?t - tipus) 
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
      (preu ?p - plat)
      (total-preu)
    )
    (:action setmenu
      :parameters (?dact - dia ?tpact ?tsact - tipus ?pact - primer ?sact - segon)
      :precondition
      (and
        ;comprueba que el dia actual no se ha hecho el menu
        (not (diac ?dact))
        ;comprueba que no se ha utilizado el primer plato
        (not (utilitzat ?pact))
        ;comprueba que no se ha utilizado el segundo plato
        (not (utilitzat ?sact))
        ;comprueba que no son incompatibles el primer y el segundo plato
        (not (incompatible ?pact ?sact))
        ;comprueba que ?tpact sea el tipo del primer plato
        (primer ?pact ?tpact)
        ;comprueba que ?tsact sea el tipo del segundo plato
        (segon ?sact ?tsact)
        ;comprueba que los dos platos no superan las 1500 calorias
        (<= (+ (calories ?pact) (calories ?sact)) 1500)
        ;comprueba que los dos platos no tienen menos de 1000 calorias
        (>= (+ (calories ?pact) (calories ?sact)) 1000)
        ;comprueba que si existe una restriccion de un primer plato y un dia 
        ;se correspondan con el dia ?dact y el primer plato ?pact
        (or 
          (restriccio ?dact ?pact) 
          (not (exists (?d3 - dia) (restriccio ?d3 ?pact)))
          )
        ;comprueba que si existe una restriccion de un segundo plato y un dia 
        ;se correspondan con el dia ?dact y el segundo plato ?sact
        (or 
          (restriccio ?dact ?sact) 
          (not (exists (?d3 - dia) (restriccio ?d3 ?sact)))
          )
        ;comprueba que el tipo del primer plato y el tipo del segundo plato del dia
        ;anterior no sean los mismos que los del dia actual
        (or
          (diainici ?dact)
          (and
            (not (exists (?daux - dia) (and (seguent ?daux ?dact) (menuprimer ?daux ?tpact))))
            (not (exists (?daux - dia) (and (seguent ?daux ?dact) (menusegon ?daux ?tsact))))
            )
          )
        )
      :effect (and (diac ?dact) (utilitzat ?pact) (utilitzat ?sact) (menuprimer ?dact ?tpact) (menusegon ?dact ?tsact) (increase (total-preu) (+ (preu ?pact) (preu ?sact))))
      )
)
