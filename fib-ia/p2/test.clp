; Sun May 14 20:17:15 CEST 2017
; 
;+ (version "3.5")
;+ (build "Build 660")


(defclass %3ACLIPS_TOP_LEVEL_SLOT_CLASS "Fake class to save top-level slot information"
    (is-a USER)
    (role abstract)
    (single-slot segundaBebida
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoEvento
        (type SYMBOL)
        (allowed-values Familiar Congreso)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot postrePlato
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot bebidaCompatible
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
;+      (inverse-slot compatiblesBebidas)
        (create-accessor read-write))
    (single-slot minimo
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot primerPlato
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot alimentacion
        (type SYMBOL)
        (allowed-values Omnivoro Vegetariano Vegano Carnivoro Indiferente)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot maximo
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot segundoPlato
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot primeraBebida
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot nombreUsuario
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot ontologia_Class8
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot epocaEvento
        (type SYMBOL)
        (allowed-values Primavera Otono Verano Invierno)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot restricciones
        (type INSTANCE)
;+      (allowed-classes Restriccion)
        (create-accessor read-write))
    (single-slot disponible
        (type SYMBOL)
        (allowed-values TodoElAno Primavera Otono Verano Invierno)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot menus
        (type INSTANCE)
;+      (allowed-classes Menu)
        (cardinality 3 3)
        (create-accessor read-write))
    (multislot ingredientes
        (type INSTANCE)
;+      (allowed-classes Ingrediente)
;+      (inverse-slot platos)
        (create-accessor read-write))
    (single-slot dificultad
        (type INTEGER)
        (range 0 10)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot temperatura
        (type SYMBOL)
        (allowed-values Frio Caliente)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot evento
        (type INSTANCE)
;+      (allowed-classes Evento)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot platos
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
;+      (inverse-slot ingredientes)
        (create-accessor read-write))
    (single-slot tipoIngrediente
        (type SYMBOL)
        (allowed-values Vegetal Carne Pescado)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot compatibilesPlato
        (type INSTANCE)
;+      (allowed-classes Plato)
        (create-accessor read-write))
    (single-slot nombreIngrediente
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot precioBebida
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot numeroComensales
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipo
        (type SYMBOL)
        (allowed-values Familiar Congreso)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoVino
        (type SYMBOL)
        (allowed-values Unico CadaPlato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot vino
        (type SYMBOL)
        (allowed-values FALSE TRUE)
        (default FALSE)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot nombrePlato
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot precioPlato
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoPlato
        (type SYMBOL)
        (allowed-values Primero Segundo Postre)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot estilo
        (type SYMBOL)
        (allowed-values Clasico Moderno Regional Sibarita Indiferente)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot nombreBebida
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot nombre
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot t%C3%ADpico
        (type SYMBOL)
        (allowed-values Espana Rusia Francia Italia Argentina Cuba)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot esVino
        (type SYMBOL)
        (allowed-values FALSE TRUE)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot compatiblesBebidas
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
;+      (inverse-slot bebidaCompatible)
        (create-accessor read-write))
    (single-slot postreBebida
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write)))

(defclass Evento
    (is-a USER)
    (role concrete)
    (single-slot numeroComensales
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot epocaEvento
        (type SYMBOL)
        (allowed-values Primavera Otono Verano Invierno)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoEvento
        (type SYMBOL)
        (allowed-values Familiar Congreso)
;+      (cardinality 0 1)
        (create-accessor read-write)))

(defclass Usuario
    (is-a USER)
    (role concrete)
    (multislot menus
        (type INSTANCE)
;+      (allowed-classes Menu)
        (cardinality 3 3)
        (create-accessor read-write))
    (single-slot nombreUsuario
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot evento
        (type INSTANCE)
;+      (allowed-classes Evento)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot restricciones
        (type INSTANCE)
;+      (allowed-classes Restriccion)
        (create-accessor read-write)))

(defclass Menu
    (is-a USER)
    (role concrete)
    (single-slot segundaBebida
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot postrePlato
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot primerPlato
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot segundoPlato
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot postreBebida
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot primeraBebida
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write)))

(defclass Plato
    (is-a USER)
    (role concrete)
    (single-slot disponible
        (type SYMBOL)
        (allowed-values TodoElAno Primavera Otono Verano Invierno)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot ingredientes
        (type INSTANCE)
;+      (allowed-classes Ingrediente)
        (create-accessor read-write))
    (single-slot bebidaCompatible
        (type INSTANCE)
;+      (allowed-classes Bebida)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot dificultad
        (type INTEGER)
        (range 0 10)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot temperatura
        (type SYMBOL)
        (allowed-values Frio Caliente)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot t%C3%ADpico
        (type SYMBOL)
        (allowed-values Espana Rusia Francia Italia Argentina Cuba)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot nombrePlato
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot precioPlato
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoPlato
        (type SYMBOL)
        (allowed-values Primero Segundo Postre)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot compatibilesPlato
        (type INSTANCE)
;+      (allowed-classes Plato)
        (create-accessor read-write)))

(defclass Bebida
    (is-a USER)
    (role concrete)
    (single-slot nombreBebida
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot esVino
        (type SYMBOL)
        (allowed-values FALSE TRUE)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot precioBebida
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot compatiblesBebidas
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write)))

(defclass Restriccion
    (is-a USER)
    (role concrete))

(defclass RestriccionPrecio
    (is-a Restriccion)
    (role concrete)
    (single-slot minimo
        (type INTEGER)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot maximo
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write)))

(defclass RestriccionTipo
    (is-a Restriccion)
    (role concrete)
    (single-slot estilo
        (type SYMBOL)
        (allowed-values Clasico Moderno Regional Sibarita Indiferente)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoVino
        (type SYMBOL)
        (allowed-values Unico CadaPlato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot vino
        (type SYMBOL)
        (allowed-values FALSE TRUE)
        (default FALSE)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot alimentacion
        (type SYMBOL)
        (allowed-values Omnivoro Vegetariano Vegano Carnivoro Indiferente)
;+      (cardinality 0 1)
        (create-accessor read-write)))

(defclass Ingrediente
    (is-a USER)
    (role concrete)
    (single-slot nombreIngrediente
        (type STRING)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot platos
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot tipoIngrediente
        (type SYMBOL)
        (allowed-values Vegetal Carne Pescado)
;+      (cardinality 0 1)
        (create-accessor read-write)))


;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------                                   FUNCIONES                                                       ----------                                                              EXTRAS
;;;-------------------------------------------------------------------------------------------------------------------------------------------------------


;;; Funcion para hacer una pregunta con respuesta cualquiera
(deffunction pregunta-general (?pregunta)
    (format t "%s " ?pregunta)
    (bind ?respuesta (read))
    (while (not (lexemep ?respuesta)) do
        (format t "%s " ?pregunta)
        (bind ?respuesta (read))
    )
    ?respuesta
)

;;; Funcion para hacer una pregunta general con una serie de respuestas admitidas
(deffunction pregunta-opciones (?question $?allowed-values)
   (format t "%s "?question)
   (progn$ (?curr-value $?allowed-values)
        (format t "[%s]" ?curr-value)
    )
   (printout t ": ")
   (bind ?answer (read))
   (if (lexemep ?answer) 
       then (bind ?answer (lowcase ?answer)))
   (while (not (member ?answer ?allowed-values)) do
      (format t "%s "?question)
      (progn$ (?curr-value $?allowed-values)
        (format t "[%s]" ?curr-value)
      )
      (printout t ": ")
      (bind ?answer (read))
      (if (lexemep ?answer) 
          then (bind ?answer (lowcase ?answer))))
   ?answer
)

;;; Funcion para hacer una pregunta de tipo si/no
(deffunction pregunta-si-no (?question)
   (bind ?response (pregunta-opciones ?question si no))
   (if (or (eq ?response si) (eq ?response s))
       then TRUE 
       else FALSE)
)

;;; Funcion para hacer una pregunta con respuesta en un rango dado
(deffunction pregunta-numerica (?pregunta ?rangini ?rangfi) 
        (format t "%s [%d, %d] " ?pregunta ?rangini ?rangfi) 
        (bind ?respuesta (read)) 
        (while (not(and(>= ?respuesta ?rangini)(<= ?respuesta ?rangfi))) do 
                (format t "¿%s? [%d, %d] " ?pregunta ?rangini ?rangfi) 
                (bind ?respuesta (read)) 
        ) 
        ?respuesta
)


;;; Funcion para hacer pregunta con indice de respuestas posibles
(deffunction pregunta-indice (?pregunta $?valores-posibles)
    (bind ?linea (format nil "%s" ?pregunta))
    (printout t ?linea crlf)
    (progn$ (?var ?valores-posibles) 
            (bind ?linea (format nil "  %d. %s" ?var-index ?var))
            (printout t ?linea crlf)
    )
    (bind ?respuesta (pregunta-numerica "Escoge una opción:" 1 (length$ ?valores-posibles)))
    ?respuesta
)

;;; Funcion para hacer una pregunta multi-respuesta con indices
(deffunction pregunta-multi (?pregunta $?valores-posibles)
    (bind ?linea (format nil "%s" ?pregunta))
    (printout t ?linea crlf)
    (progn$ (?var ?valores-posibles) 
            (bind ?linea (format nil "  %d. %s" ?var-index ?var))
            (printout t ?linea crlf)
    )
    (format t "%s" "Indica los números separados por un espacio: ")
    (bind ?resp (readline))
    (bind ?numeros (str-explode ?resp))
    (bind $?lista (create$ ))
    (progn$ (?var ?numeros) 
        (if (and (integerp ?var) (and (>= ?var 1) (<= ?var (length$ ?valores-posibles))))
            then 
                (if (not (member$ ?var ?lista))
                    then (bind ?lista (insert$ ?lista (+ (length$ ?lista) 1) ?var))
                )
        ) 
    )
    ?lista
)

;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------                   MENSAJES                            ----------                              MENSAJES
;;;------------------------------------------------------------------------------------------------------------------------------------------------------

;;; Mensajes a las clases 

(defmessage-handler Usuario imprime primary ()
    (printout t " Usuario:  " ?self:nombreUsuario crlf) 
)



;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------                                    MAIN                                                   ----------                                                              MAIN
;;;------------------------------------------------------------------------------------------------------------------------------------------------------

;; Este es el modulo principal, en este se comprobara l existencia del estudiante 
;; en el conjunto de instancias del sistema

(defmodule MAIN (export ?ALL))

(defrule comienzo "regla inicial"
        (initial-fact)
        =>
        (printout t crlf)
        (printout t "--------------------------------------------------------------" crlf)
        (printout t "--------------- Sistema de Recomendacion de Menu -------------" crlf)
        (printout t "--------------------------------------------------------------" crlf)
        (printout t crlf)
        (assert (nuevo_usuario))             
)

(defrule pedir_nombre "regla para iniciar el modulo de preguntas"
    (nuevo_usuario)
    =>
    (bind ?nombre (pregunta-general "Nombre: "))
    (bind ?usu (make-instance usuario1 of Usuario))
    (make-instance evento1 of Evento)
    (make-instance restr_precio of RestriccionPrecio)
    (make-instance restr_tipo of RestriccionTipo)
    (send ?usu put-nombreUsuario ?nombre)
    (focus hacer_preguntas)   
)


;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------                           MODULO DE PREGUNTAS                                             ----------                                                      MODULO DE PREGUNTAS
;;;------------------------------------------------------------------------------------------------------------------------------------------------------

;; En este se le haran las preguntas al estudiantes 
;; para obtener la informacion de sus restricciones y/o preferencias 

(defmodule hacer_preguntas
    (import MAIN ?ALL)
    (export ?ALL)
)


(defrule tipoDeEvento "regla para saber el tipo de evento"
    (nuevo_usuario)
    ?evento <- (object (is-a Evento))  
    => 
    (bind ?q (pregunta-indice "¿Que tipo de evento es?" (create$ Familiar Congreso)))
    (switch ?q
        (case 1 then (send ?evento put-tipoEvento Familiar))
        (case 2 then (send ?evento put-tipoEvento Congreso)) 
    )
    (assert (ins_evento_tipo))
)


(defrule epocaDelEvento "regla para saber la epoca del ano"
    (nuevo_usuario)
    ?evento <- (object (is-a Evento))  
    => 
    (bind ?q (pregunta-indice "¿Que epoca del anyo es?" (create$ Primavera Otono Verano Invierno)))
    (switch ?q
        (case 1 then (send ?evento put-epocaEvento Primavera))
        (case 2 then (send ?evento put-epocaEvento Otono))
        (case 3 then (send ?evento put-epocaEvento Verano))
        (case 4 then (send ?evento put-epocaEvento Invierno))
    )
    (assert (ins_evento_epoca))
)

(defrule numeroDeComensales "regla para saber el numero de comensales"
    (nuevo_usuario)
    ?evento <- (object (is-a Evento))  
    => 
    (bind ?q (pregunta-numerica "¿Cual es el numero de comensales?" 0 9999))
    (send ?evento put-numeroComensales ?q)
    (assert (ins_evento_comensales))
    
)

(defrule insertarEvento "regla para insertar el evento al usuario"
    (nuevo_usuario)
    (ins_evento_tipo)
    (ins_evento_epoca)
    (ins_evento_comensales)
    ?evento <- (object (is-a Evento))
    ?usuario <- (object (is-a Usuario))
    =>
    (send ?usuario put-evento ?evento)
)

(defrule restriccionPrecioMax "regla para saber el precio maximo del menu"
    (nuevo_usuario)
    ?restrp <- (object (is-a RestriccionPrecio))
    => 
    (bind ?q (pregunta-numerica "¿Cual es el precio maximo del menu?" 1 9999))
    (send ?restrp put-maximo ?q)
    (assert (ins_precio_max))
)

(defrule restriccionPrecioMin "regla para saber el precio minimo del menu"
    (nuevo_usuario)
    (ins_precio_max)
    ?restrp <- (object (is-a RestriccionPrecio) (maximo ?max))
    => 
    (bind ?q (pregunta-numerica "¿Cual es el precio minimo del menu?" 0 ?max))
    (send ?restrp put-minimo ?q)
    (assert (ins_precio_min))
    
)

(defrule insertarRestriccionPrecio "regla para insertar la restriccion de precio al usuario"
    (nuevo_usuario)
    (ins_precio_min)
    (ins_precio_max)
    ?restrp <- (object (is-a RestriccionPrecio))
    ?usuario <- (object (is-a Usuario))
    =>
    (slot-insert$ ?usuario restricciones 1 ?restrp)
)

(defrule tipoDeComida "regla para saber el tipo de comida"
    (nuevo_usuario)
    ?restrt <- (object (is-a RestriccionTipo)) 
    => 
    (bind ?q (pregunta-indice "¿Que tipo de comida prefieres?" (create$ Indiferente Omnivoro Carnivoro Vegetariano Vegano)))
    (switch ?q
        (case 1 then (send ?restrt put-alimentacion Indiferente))
        (case 2 then (send ?restrt put-alimentacion Omnivoro))
        (case 3 then (send ?restrt put-alimentacion Carnivoro))
        (case 4 then (send ?restrt put-alimentacion Vegetariano))
        (case 5 then (send ?restrt put-alimentacion Vegano))
    )
    (assert (ins_tipo_alimentacion))
)

(defrule estiloDeComida "regla para saber el estilo de comida"
    (nuevo_usuario)
    ?restrt <- (object (is-a RestriccionTipo)) 
    => 
    (bind ?q (pregunta-indice "¿Que estilo de comida prefieres?" (create$ Indiferente Clasico Moderno Regional Sibarita)))
    (switch ?q
        (case 1 then (send ?restrt put-estilo Indiferente))
        (case 2 then (send ?restrt put-estilo Clasico))
        (case 3 then (send ?restrt put-estilo Moderno))
        (case 4 then (send ?restrt put-estilo Regional))
        (case 5 then (send ?restrt put-estilo Sibarita))
    )
    (assert (ins_tipo_estilo))
)

(defrule vinoEnComida "regla para saber si se quiere vino en la comida"
    (nuevo_usuario)
    ?restrt <- (object (is-a RestriccionTipo)) 
    => 
    (bind ?q (pregunta-si-no "¿Quieres vino en la comida?"))
    (send ?restrt put-vino ?q)
    (assert (ins_tipo_vino))
)

(defrule tipoVinoEnComida "regla para saber el tipo de vino que se quiere en la comida"
    (nuevo_usuario)
    (ins_tipo_vino)
    ?restrt <- (object (is-a RestriccionTipo) (vino ?v))
    (test (eq ?v TRUE)) 
    => 
    (bind ?q (pregunta-indice "¿Como quieres el vino?" (create$ Unico CadaPlato)))
    (switch ?q
        (case 1 then (send ?restrt put-tipoVino Unico))
        (case 2 then (send ?restrt put-tipoVino CadaPlato))
    )
    (assert (ins_tipo_tvino))
)

(defrule insertarRestriccionPrecio "regla para insertar la restriccion de precio al usuario"
    (nuevo_usuario)
    (ins_tipo_alimentacion)
    (ins_tipo_estilo)
    (ins_tipo_vino)
    ?restrt <- (object (is-a RestriccionTipo))
    ?usuario <- (object (is-a Usuario))
    =>
    (slot-insert$ ?usuario restricciones 1 ?restrt)
)
