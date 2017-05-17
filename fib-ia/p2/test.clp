; Tue May 16 19:48:41 CEST 2017
; 
;+ (version "3.5")
;+ (build "Build 660")


; Tue May 16 19:49:53 CEST 2017
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
    (multislot bebidaCompatible
        (type INSTANCE)
;+      (allowed-classes Bebida)
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
    (multislot disponible
        (type SYMBOL)
        (allowed-values TodoElAno Primavera Otono Verano Invierno)
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
    (multislot temperatura
        (type SYMBOL)
        (allowed-values Frio Caliente)
        (create-accessor read-write))
    (single-slot evento
        (type INSTANCE)
;+      (allowed-classes Evento)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot platos
        (type INSTANCE)
;+      (allowed-classes Plato)
;+      (inverse-slot ingredientes)
        (create-accessor read-write))
    (single-slot tipoIngrediente
        (type SYMBOL)
        (allowed-values Vegetal Carne Pescado OrigenAnimal)
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
    (multislot tipoPlato
        (type SYMBOL)
        (allowed-values Primero Segundo Postre)
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
        (allowed-values America Espana Italia China Japon India Turquia)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (single-slot esVino
        (type SYMBOL)
        (allowed-values FALSE TRUE)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot compatiblesBebidas
        (type INSTANCE)
;+      (allowed-classes Plato)
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
    (multislot disponible
        (type SYMBOL)
        (allowed-values TodoElAno Primavera Otono Verano Invierno)
        (create-accessor read-write))
    (multislot ingredientes
        (type INSTANCE)
;+      (allowed-classes Ingrediente)
        (create-accessor read-write))
    (multislot bebidaCompatible
        (type INSTANCE)
;+      (allowed-classes Bebida)
        (create-accessor read-write))
    (single-slot dificultad
        (type INTEGER)
        (range 0 10)
;+      (cardinality 0 1)
        (create-accessor read-write))
    (multislot temperatura
        (type SYMBOL)
        (allowed-values Frio Caliente)
        (create-accessor read-write))
    (single-slot t%C3%ADpico
        (type SYMBOL)
        (allowed-values America Espana Italia China Japon India Turquia)
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
    (multislot tipoPlato
        (type SYMBOL)
        (allowed-values Primero Segundo Postre)
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
    (multislot compatiblesBebidas
        (type INSTANCE)
;+      (allowed-classes Plato)
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
    (multislot platos
        (type INSTANCE)
;+      (allowed-classes Plato)
        (create-accessor read-write))
    (single-slot tipoIngrediente
        (type SYMBOL)
        (allowed-values Vegetal Carne Pescado OrigenAnimal)
;+      (cardinality 0 1)
        (create-accessor read-write)))

        
;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------                   INSTANCIAS                          ----------                              INSTANCIAS
;;;------------------------------------------------------------------------------------------------------------------------------------------------------
    
(definstances instances 

; Tue May 16 19:04:16 CEST 2017
; 
;+ (version "3.5")
;+ (build "Build 660")

; Tue May 16 19:49:53 CEST 2017
; 
;+ (version "3.5")
;+ (build "Build 660")

([ontologia_Class0] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 3)
    (disponible Invierno)
    (ingredientes
        [ontologia_Class10002]
        [ontologia_Class20003]
        [ontologia_Class20004]
        [ontologia_Class10023]
        [ontologia_Class10029])
    (nombrePlato "Alubias con verduras")
    (precioPlato 7)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10002] of  Ingrediente

    (nombreIngrediente "Alubias")
    (platos [ontologia_Class0])
    (tipoIngrediente Vegetal))

([ontologia_Class10003] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20038]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (esVino TRUE)
    (nombreBebida "Vino Rosado")
    (precioBebida 7))

([ontologia_Class10004] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (nombreBebida "Refresco")
    (precioBebida 3))

([ontologia_Class10005] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (nombreBebida "Agua")
    (precioBebida 2))

([ontologia_Class10006] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (nombreBebida "Cerveza")
    (precioBebida 3))

([ontologia_Class10007] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (nombreBebida "Zumo Natural")
    (precioBebida 4))

([ontologia_Class10008] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20038]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (nombreBebida "Cava")
    (precioBebida 6))

([ontologia_Class10009] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20038]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (nombreBebida "Champagn")
    (precioBebida 8))

([ontologia_Class10010] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 2)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10011]
        [ontologia_Class10013]
        [ontologia_Class10014]
        [ontologia_Class10015]
        [ontologia_Class10016]
        [ontologia_Class10017]
        [ontologia_Class10012])
    (nombrePlato "Ensalada de Primavera")
    (precioPlato 6)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10011] of  Ingrediente

    (nombreIngrediente "Brocoli")
    (platos
        [ontologia_Class10010]
        [ontologia_Class20039])
    (tipoIngrediente Vegetal))

([ontologia_Class10012] of  Ingrediente

    (nombreIngrediente "Queso")
    (platos
        [ontologia_Class10046]
        [ontologia_Class10010]
        [ontologia_Class10025]
        [ontologia_Class10069]
        [ontologia_Class10081]
        [ontologia_Class10117]
        [ontologia_Class20009]
        [ontologia_Class20010]
        [ontologia_Class20038])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10013] of  Ingrediente

    (nombreIngrediente "Fresa")
    (platos
        [ontologia_Class10010]
        [ontologia_Class10052]
        [ontologia_Class10057]
        [ontologia_Class10117])
    (tipoIngrediente Vegetal))

([ontologia_Class10014] of  Ingrediente

    (nombreIngrediente "Remolacha")
    (platos [ontologia_Class10010])
    (tipoIngrediente Vegetal))

([ontologia_Class10015] of  Ingrediente

    (nombreIngrediente "Calabaza")
    (platos
        [ontologia_Class10010]
        [ontologia_Class20039])
    (tipoIngrediente Vegetal))

([ontologia_Class10016] of  Ingrediente

    (nombreIngrediente "Apio")
    (platos [ontologia_Class10010])
    (tipoIngrediente Vegetal))

([ontologia_Class10017] of  Ingrediente

    (nombreIngrediente "Genjibre")
    (platos [ontologia_Class10010])
    (tipoIngrediente Vegetal))

([ontologia_Class10018] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 1)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10019]
        [ontologia_Class10020]
        [ontologia_Class10021]
        [ontologia_Class10022]
        [ontologia_Class10024])
    (nombrePlato "Huevos Primavera")
    (precioPlato 5)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10019] of  Ingrediente

    (nombreIngrediente "Huevo")
    (platos
        [ontologia_Class10018]
        [ontologia_Class10071]
        [ontologia_Class10081]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10118]
        [ontologia_Class20006]
        [ontologia_Class20010]
        [ontologia_Class20015]
        [ontologia_Class20024])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10020] of  Ingrediente

    (nombreIngrediente "Patata")
    (platos
        [ontologia_Class10018]
        [ontologia_Class10061]
        [ontologia_Class20031])
    (tipoIngrediente Vegetal))

([ontologia_Class10021] of  Ingrediente

    (nombreIngrediente "Perejil")
    (platos
        [ontologia_Class10018]
        [ontologia_Class20021])
    (tipoIngrediente Vegetal))

([ontologia_Class10022] of  Ingrediente

    (nombreIngrediente "Crema")
    (platos
        [ontologia_Class10018]
        [ontologia_Class10081]
        [ontologia_Class20041])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10023] of  Ingrediente

    (nombreIngrediente "Cebolla")
    (platos
        [ontologia_Class10046]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10084]
        [ontologia_Class10096]
        [ontologia_Class10103]
        [ontologia_Class0]
        [ontologia_Class20007]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20028]
        [ontologia_Class20033])
    (tipoIngrediente Vegetal))

([ontologia_Class10024] of  Ingrediente

    (nombreIngrediente "Oregano")
    (platos [ontologia_Class10018])
    (tipoIngrediente Vegetal))

([ontologia_Class10025] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 5)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10026]
        [ontologia_Class10030]
        [ontologia_Class10031]
        [ontologia_Class10028]
        [ontologia_Class10027]
        [ontologia_Class10012])
    (nombrePlato "Pasta de primavera")
    (precioPlato 8)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10026] of  Ingrediente

    (nombreIngrediente "Pasta")
    (platos [ontologia_Class10025])
    (tipoIngrediente Vegetal))

([ontologia_Class10027] of  Ingrediente

    (nombreIngrediente "Tomate")
    (platos
        [ontologia_Class10046]
        [ontologia_Class10040]
        [ontologia_Class10025]
        [ontologia_Class10061]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10092]
        [ontologia_Class20014]
        [ontologia_Class20031]
        [ontologia_Class20033]
        [ontologia_Class20040])
    (tipoIngrediente Vegetal))

([ontologia_Class10028] of  Ingrediente

    (nombreIngrediente "Esparrago")
    (platos
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class20039])
    (tipoIngrediente Vegetal))

([ontologia_Class10029] of  Ingrediente

    (nombreIngrediente "Zanahoria")
    (platos
        [ontologia_Class10040]
        [ontologia_Class10103]
        [ontologia_Class0]
        [ontologia_Class20015])
    (tipoIngrediente Vegetal))

([ontologia_Class10030] of  Ingrediente

    (nombreIngrediente "Pollo")
    (platos
        [ontologia_Class10025]
        [ontologia_Class10090])
    (tipoIngrediente Carne))

([ontologia_Class10031] of  Ingrediente

    (nombreIngrediente "Ajo")
    (platos
        [ontologia_Class10025]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10084]
        [ontologia_Class10090]
        [ontologia_Class10103]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20033])
    (tipoIngrediente Vegetal))

([ontologia_Class10033] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 4)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10034]
        [ontologia_Class10035]
        [ontologia_Class10036]
        [ontologia_Class10037]
        [ontologia_Class10038]
        [ontologia_Class10039])
    (nombrePlato "Rollos de Primavera")
    (precioPlato 6)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico India))

([ontologia_Class10034] of  Ingrediente

    (nombreIngrediente "Lechuga")
    (platos
        [ontologia_Class10033]
        [ontologia_Class20033])
    (tipoIngrediente Vegetal))

([ontologia_Class10035] of  Ingrediente

    (nombreIngrediente "Menta")
    (platos
        [ontologia_Class10033]
        [ontologia_Class10069])
    (tipoIngrediente Vegetal))

([ontologia_Class10036] of  Ingrediente

    (nombreIngrediente "Albahaca")
    (platos [ontologia_Class10033])
    (tipoIngrediente Vegetal))

([ontologia_Class10037] of  Ingrediente

    (nombreIngrediente "Cilantro")
    (platos [ontologia_Class10033])
    (tipoIngrediente Vegetal))

([ontologia_Class10038] of  Ingrediente

    (nombreIngrediente "Repollo")
    (platos [ontologia_Class10033])
    (tipoIngrediente Vegetal))

([ontologia_Class10039] of  Ingrediente

    (nombreIngrediente "Pepino")
    (platos
        [ontologia_Class10033]
        [ontologia_Class10069])
    (tipoIngrediente Vegetal))

([ontologia_Class10040] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 5)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10041]
        [ontologia_Class10043]
        [ontologia_Class10044]
        [ontologia_Class10029]
        [ontologia_Class10045]
        [ontologia_Class10027])
    (nombrePlato "Couscous de Pescado")
    (precioPlato 7)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico India))

([ontologia_Class10041] of  Ingrediente

    (nombreIngrediente "Couscous")
    (platos [ontologia_Class10040])
    (tipoIngrediente Vegetal))

([ontologia_Class10043] of  Ingrediente

    (nombreIngrediente "CaldoPescado")
    (platos
        [ontologia_Class10040]
        [ontologia_Class10092]
        [ontologia_Class20014])
    (tipoIngrediente Pescado))

([ontologia_Class10044] of  Ingrediente

    (nombreIngrediente "Pimiento")
    (platos
        [ontologia_Class10040]
        [ontologia_Class10065]
        [ontologia_Class10092]
        [ontologia_Class10103])
    (tipoIngrediente Vegetal))

([ontologia_Class10045] of  Ingrediente

    (nombreIngrediente "Puerro")
    (platos
        [ontologia_Class10040]
        [ontologia_Class10078])
    (tipoIngrediente Vegetal))

([ontologia_Class10046] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10047]
        [ontologia_Class10023]
        [ontologia_Class10027]
        [ontologia_Class10012]
        [ontologia_Class10028]
        [ontologia_Class10048]
        [ontologia_Class10049]
        [ontologia_Class10050])
    (nombrePlato "Lomo de Cerdo")
    (precioPlato 12)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class10047] of  Ingrediente

    (nombreIngrediente "LomoCerdo")
    (platos [ontologia_Class10046])
    (tipoIngrediente Carne))

([ontologia_Class10048] of  Ingrediente

    (nombreIngrediente "Pimienta")
    (platos
        [ontologia_Class10046]
        [ontologia_Class10078]
        [ontologia_Class10084]
        [ontologia_Class10090]
        [ontologia_Class10092]
        [ontologia_Class10100])
    (tipoIngrediente Vegetal))

([ontologia_Class10049] of  Ingrediente

    (nombreIngrediente "Tomillo")
    (platos [ontologia_Class10046])
    (tipoIngrediente Vegetal))

([ontologia_Class10050] of  Ingrediente

    (nombreIngrediente "Mostaza")
    (platos
        [ontologia_Class10046]
        [ontologia_Class10074])
    (tipoIngrediente Vegetal))

([ontologia_Class10051] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20038]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (esVino TRUE)
    (nombreBebida "Vino Casero")
    (precioBebida 2))

([ontologia_Class10052] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 1)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10053]
        [ontologia_Class10054]
        [ontologia_Class10055]
        [ontologia_Class10056]
        [ontologia_Class10013])
    (nombrePlato "Milhojas de Fresa")
    (precioPlato 7)
    (temperatura Frio)
    (tipoPlato Postre)
    (t%C3%ADpico Italia))

([ontologia_Class10053] of  Ingrediente

    (nombreIngrediente "PastaFilo")
    (platos [ontologia_Class10052])
    (tipoIngrediente Vegetal))

([ontologia_Class10054] of  Ingrediente

    (nombreIngrediente "Azucar")
    (platos
        [ontologia_Class10052]
        [ontologia_Class10057]
        [ontologia_Class10081]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class20006]
        [ontologia_Class20010]
        [ontologia_Class20024])
    (tipoIngrediente Vegetal))

([ontologia_Class10055] of  Ingrediente

    (nombreIngrediente "Nata")
    (platos
        [ontologia_Class10052]
        [ontologia_Class10057]
        [ontologia_Class10117]
        [ontologia_Class20018]
        [ontologia_Class20041])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10056] of  Ingrediente

    (nombreIngrediente "Sirope")
    (platos [ontologia_Class10052])
    (tipoIngrediente Vegetal))

([ontologia_Class10057] of  Plato

    (dificultad 2)
    (disponible Primavera)
    (ingredientes
        [ontologia_Class10058]
        [ontologia_Class10013]
        [ontologia_Class10059]
        [ontologia_Class10055]
        [ontologia_Class10054]
        [ontologia_Class10060])
    (nombrePlato "Mousse de Frutas")
    (precioPlato 6)
    (temperatura Frio)
    (tipoPlato Postre)
    (t%C3%ADpico Espana))

([ontologia_Class10058] of  Ingrediente

    (nombreIngrediente "Kiwi")
    (platos [ontologia_Class10057])
    (tipoIngrediente Vegetal))

([ontologia_Class10059] of  Ingrediente

    (nombreIngrediente "Naranja")
    (platos
        [ontologia_Class10057]
        [ontologia_Class20006]
        [ontologia_Class20012])
    (tipoIngrediente Vegetal))

([ontologia_Class10060] of  Ingrediente

    (nombreIngrediente "Chocolate")
    (platos
        [ontologia_Class10057]
        [ontologia_Class10118]
        [ontologia_Class20024])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10061] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 5)
    (disponible Verano)
    (ingredientes
        [ontologia_Class10020]
        [ontologia_Class10062]
        [ontologia_Class10027]
        [ontologia_Class10063]
        [ontologia_Class10064]
        [ontologia_Class10023])
    (nombrePlato "Ensalada de Verano")
    (precioPlato 11)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10062] of  Ingrediente

    (nombreIngrediente "Aguacate")
    (platos
        [ontologia_Class10061]
        [ontologia_Class10117]
        [ontologia_Class10119])
    (tipoIngrediente Vegetal))

([ontologia_Class10063] of  Ingrediente

    (nombreIngrediente "Sardinas")
    (platos [ontologia_Class10061])
    (tipoIngrediente Pescado))

([ontologia_Class10064] of  Ingrediente

    (nombreIngrediente "Uvas")
    (platos [ontologia_Class10061])
    (tipoIngrediente Vegetal))

([ontologia_Class10065] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 2)
    (disponible Verano)
    (ingredientes
        [ontologia_Class10066]
        [ontologia_Class10067]
        [ontologia_Class10023]
        [ontologia_Class10044]
        [ontologia_Class10068])
    (nombrePlato "Ensalada Perla Negra")
    (precioPlato 8)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10066] of  Ingrediente

    (nombreIngrediente "Oliva")
    (platos [ontologia_Class10065])
    (tipoIngrediente Vegetal))

([ontologia_Class10067] of  Ingrediente

    (nombreIngrediente "Bacalado")
    (platos
        [ontologia_Class10065]
        [ontologia_Class10092])
    (tipoIngrediente Pescado))

([ontologia_Class10068] of  Ingrediente

    (nombreIngrediente "Vinagre")
    (platos
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071])
    (tipoIngrediente Vegetal))

([ontologia_Class10069] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 2)
    (disponible Verano)
    (ingredientes
        [ontologia_Class10012]
        [ontologia_Class10039]
        [ontologia_Class10070]
        [ontologia_Class10035]
        [ontologia_Class10031]
        [ontologia_Class10068])
    (nombrePlato "Gazpacho Natural")
    (precioPlato 6)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10070] of  Ingrediente

    (nombreIngrediente "Melon")
    (platos [ontologia_Class10069])
    (tipoIngrediente Vegetal))

([ontologia_Class10071] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 4)
    (disponible Verano)
    (ingredientes
        [ontologia_Class10027]
        [ontologia_Class10031]
        [ontologia_Class10068]
        [ontologia_Class10072]
        [ontologia_Class10019]
        [ontologia_Class10073])
    (nombrePlato "Salmorejo Cordobes")
    (precioPlato 9)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10072] of  Ingrediente

    (nombreIngrediente "Pan")
    (platos [ontologia_Class10071])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10073] of  Ingrediente

    (nombreIngrediente "JamonSerrano")
    (platos [ontologia_Class10071])
    (tipoIngrediente Carne))

([ontologia_Class10074] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10075]
        [ontologia_Class10023]
        [ontologia_Class10031]
        [ontologia_Class10027]
        [ontologia_Class10076]
        [ontologia_Class10050])
    (nombrePlato "Costillar de Cerdo")
    (precioPlato 12)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class10075] of  Ingrediente

    (nombreIngrediente "CostillarCerdo")
    (platos [ontologia_Class10074])
    (tipoIngrediente Carne))

([ontologia_Class10076] of  Ingrediente

    (nombreIngrediente "Miel")
    (platos
        [ontologia_Class10074]
        [ontologia_Class10096])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10077] of  Plato

    (dificultad 4)
    (nombrePlato "Fritura Sardinas")
    (precioPlato 8)
    (tipoPlato Segundo Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10078] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10048]
        [ontologia_Class10079]
        [ontologia_Class10045]
        [ontologia_Class10023]
        [ontologia_Class10080])
    (nombrePlato "Lengua de Cerdo")
    (precioPlato 25)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class10079] of  Ingrediente

    (nombreIngrediente "LenguaCerdo")
    (platos [ontologia_Class10078])
    (tipoIngrediente Carne))

([ontologia_Class10080] of  Ingrediente

    (nombreIngrediente "Clavo")
    (platos [ontologia_Class10078])
    (tipoIngrediente Vegetal))

([ontologia_Class10081] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 4)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10082]
        [ontologia_Class10083]
        [ontologia_Class10054]
        [ontologia_Class10012]
        [ontologia_Class10019]
        [ontologia_Class10022])
    (nombrePlato "Pionono de Atun")
    (precioPlato 12)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Italia))

([ontologia_Class10082] of  Ingrediente

    (nombreIngrediente "Atun")
    (platos
        [ontologia_Class10081]
        [ontologia_Class10092]
        [ontologia_Class20007])
    (tipoIngrediente Pescado))

([ontologia_Class10083] of  Ingrediente

    (nombreIngrediente "Harina")
    (platos
        [ontologia_Class10081]
        [ontologia_Class10109]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class20006]
        [ontologia_Class20028])
    (tipoIngrediente Vegetal))

([ontologia_Class10084] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 8)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10085]
        [ontologia_Class10086]
        [ontologia_Class10031]
        [ontologia_Class10087]
        [ontologia_Class10088]
        [ontologia_Class10089]
        [ontologia_Class10023]
        [ontologia_Class10048])
    (nombrePlato "Sopa de Cangrejo")
    (precioPlato 17)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class10085] of  Ingrediente

    (nombreIngrediente "Cangrejo")
    (platos [ontologia_Class10084])
    (tipoIngrediente Pescado))

([ontologia_Class10086] of  Ingrediente

    (nombreIngrediente "Judia")
    (platos
        [ontologia_Class10084]
        [ontologia_Class20039])
    (tipoIngrediente Vegetal))

([ontologia_Class10087] of  Ingrediente

    (nombreIngrediente "Coco")
    (platos [ontologia_Class10084])
    (tipoIngrediente Vegetal))

([ontologia_Class10088] of  Ingrediente

    (nombreIngrediente "SalsaSoja")
    (platos [ontologia_Class10084])
    (tipoIngrediente Vegetal))

([ontologia_Class10089] of  Ingrediente

    (nombreIngrediente "Leche")
    (platos
        [ontologia_Class10084]
        [ontologia_Class10112]
        [ontologia_Class20009]
        [ontologia_Class20010]
        [ontologia_Class20012]
        [ontologia_Class20018])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10090] of  Plato

    (dificultad 3)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10030]
        [ontologia_Class10048]
        [ontologia_Class10031]
        [ontologia_Class10091])
    (nombrePlato "Alitas de Pollo")
    (precioPlato 8)
    (temperatura Caliente)
    (tipoPlato Primero Segundo)
    (t%C3%ADpico America))

([ontologia_Class10091] of  Ingrediente

    (nombreIngrediente "SalsaBarbacoa")
    (platos [ontologia_Class10090])
    (tipoIngrediente Vegetal))

([ontologia_Class10092] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 8)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10067]
        [ontologia_Class10082]
        [ontologia_Class10093]
        [ontologia_Class10094]
        [ontologia_Class10044]
        [ontologia_Class10048]
        [ontologia_Class10095]
        [ontologia_Class10027]
        [ontologia_Class10043])
    (nombrePlato "Paella de Mar")
    (precioPlato 27)
    (temperatura Caliente)
    (tipoPlato Primero Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class10093] of  Ingrediente

    (nombreIngrediente "Gambas")
    (platos
        [ontologia_Class10092]
        [ontologia_Class20007]
        [ontologia_Class20014])
    (tipoIngrediente Pescado))

([ontologia_Class10094] of  Ingrediente

    (nombreIngrediente "Arroz")
    (platos
        [ontologia_Class10092]
        [ontologia_Class20007]
        [ontologia_Class20014])
    (tipoIngrediente Vegetal))

([ontologia_Class10095] of  Ingrediente

    (nombreIngrediente "Mejillones")
    (platos [ontologia_Class10092])
    (tipoIngrediente Pescado))

([ontologia_Class10096] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 8)
    (disponible Verano)
    (ingredientes
        [ontologia_Class10097]
        [ontologia_Class10098]
        [ontologia_Class10076]
        [ontologia_Class10023]
        [ontologia_Class10099])
    (nombrePlato "Filete de Lubina")
    (precioPlato 12)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class10097] of  Ingrediente

    (nombreIngrediente "Lubina")
    (platos [ontologia_Class10096])
    (tipoIngrediente Pescado))

([ontologia_Class10098] of  Ingrediente

    (nombreIngrediente "Limon")
    (platos [ontologia_Class10096])
    (tipoIngrediente Vegetal))

([ontologia_Class10099] of  Ingrediente

    (nombreIngrediente "Rucula")
    (platos [ontologia_Class10096])
    (tipoIngrediente Vegetal))

([ontologia_Class10100] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible Otono)
    (ingredientes
        [ontologia_Class10101]
        [ontologia_Class10102]
        [ontologia_Class10048])
    (nombrePlato "Conejo al Horno")
    (precioPlato 13)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class10101] of  Ingrediente

    (nombreIngrediente "Conejo")
    (platos [ontologia_Class10100])
    (tipoIngrediente Carne))

([ontologia_Class10102] of  Ingrediente

    (nombreIngrediente "Mojo")
    (platos [ontologia_Class10100])
    (tipoIngrediente Vegetal))

([ontologia_Class10103] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible Otono)
    (ingredientes
        [ontologia_Class10104]
        [ontologia_Class10023]
        [ontologia_Class10044]
        [ontologia_Class10031]
        [ontologia_Class10029]
        [ontologia_Class10105])
    (nombrePlato "Risotto de Setas")
    (precioPlato 15)
    (temperatura Caliente)
    (tipoPlato Primero))

([ontologia_Class10104] of  Ingrediente

    (nombreIngrediente "Setas")
    (platos
        [ontologia_Class10103]
        [ontologia_Class20009]
        [ontologia_Class20018])
    (tipoIngrediente Vegetal))

([ontologia_Class10105] of  Ingrediente

    (nombreIngrediente "CaldoPollo")
    (platos
        [ontologia_Class10103]
        [ontologia_Class20028])
    (tipoIngrediente Carne))

([ontologia_Class10106] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10107]
        [ontologia_Class10054]
        [ontologia_Class10108])
    (nombrePlato "Dulce de Membrillo")
    (precioPlato 9)
    (temperatura Frio)
    (tipoPlato Postre))

([ontologia_Class10107] of  Ingrediente

    (nombreIngrediente "Membrillo")
    (platos [ontologia_Class10106])
    (tipoIngrediente Vegetal))

([ontologia_Class10108] of  Ingrediente

    (nombreIngrediente "Canela")
    (platos
        [ontologia_Class10106]
        [ontologia_Class20012])
    (tipoIngrediente Vegetal))

([ontologia_Class10109] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible Otono)
    (ingredientes
        [ontologia_Class10054]
        [ontologia_Class10083]
        [ontologia_Class10110]
        [ontologia_Class10111]
        [ontologia_Class10019])
    (nombrePlato "Tarta de Otono")
    (precioPlato 7)
    (temperatura Frio)
    (tipoPlato Postre))

([ontologia_Class10110] of  Ingrediente

    (nombreIngrediente "Levadura")
    (platos
        [ontologia_Class10109]
        [ontologia_Class10119]
        [ontologia_Class20006])
    (tipoIngrediente Vegetal))

([ontologia_Class10111] of  Ingrediente

    (nombreIngrediente "Vainilla")
    (platos [ontologia_Class10109])
    (tipoIngrediente Vegetal))

([ontologia_Class10112] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 8)
    (disponible Otono)
    (ingredientes
        [ontologia_Class10113]
        [ontologia_Class10054]
        [ontologia_Class10019]
        [ontologia_Class10089]
        [ontologia_Class10114]
        [ontologia_Class10115]
        [ontologia_Class10116])
    (nombrePlato "Tarta de Castanas")
    (precioPlato 12)
    (temperatura Frio)
    (tipoPlato Postre))

([ontologia_Class10113] of  Ingrediente

    (nombreIngrediente "Castanas")
    (platos [ontologia_Class10112])
    (tipoIngrediente Vegetal))

([ontologia_Class10114] of  Ingrediente

    (nombreIngrediente "Mantequilla")
    (platos
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class20007])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10115] of  Ingrediente

    (nombreIngrediente "Galleta")
    (platos
        [ontologia_Class10112]
        [ontologia_Class10117])
    (tipoIngrediente Vegetal))

([ontologia_Class10116] of  Ingrediente

    (nombreIngrediente "Gelatina")
    (platos
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class20010])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class10117] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 6)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10062]
        [ontologia_Class10054]
        [ontologia_Class10013]
        [ontologia_Class10115]
        [ontologia_Class10116]
        [ontologia_Class10114]
        [ontologia_Class10055]
        [ontologia_Class10012])
    (nombrePlato "Tarta de Queso")
    (precioPlato 6)
    (temperatura Frio)
    (tipoPlato Postre))

([ontologia_Class10118] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 5)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10054]
        [ontologia_Class10060]
        [ontologia_Class10083]
        [ontologia_Class10019]
        [ontologia_Class10114])
    (nombrePlato "Brownie")
    (precioPlato 6)
    (temperatura Frio)
    (tipoPlato Postre))

([ontologia_Class10119] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 10)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10062]
        [ontologia_Class10054]
        [ontologia_Class10083]
        [ontologia_Class10110]
        [ontologia_Class10114])
    (nombrePlato "Bunuelos")
    (precioPlato 5)
    (temperatura Frio)
    (tipoPlato Postre))

([ontologia_Class2] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20038]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (esVino TRUE)
    (nombreBebida "Vino Blanco")
    (precioBebida 7))

([ontologia_Class20003] of  Ingrediente

    (nombreIngrediente "Acelgas")
    (platos [ontologia_Class0])
    (tipoIngrediente Vegetal))

([ontologia_Class20004] of  Ingrediente

    (nombreIngrediente "Guistantes")
    (platos
        [ontologia_Class0]
        [ontologia_Class20021]
        [ontologia_Class20039])
    (tipoIngrediente Vegetal))

([ontologia_Class20006] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 7)
    (disponible Invierno)
    (ingredientes
        [ontologia_Class10054]
        [ontologia_Class10083]
        [ontologia_Class10019]
        [ontologia_Class10110]
        [ontologia_Class10059])
    (nombrePlato "Bizcocho de Invierno")
    (precioPlato 9)
    (temperatura Frio)
    (tipoPlato Postre)
    (t%C3%ADpico Espana))

([ontologia_Class20007] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 6)
    (disponible Invierno)
    (ingredientes
        [ontologia_Class10094]
        [ontologia_Class10082]
        [ontologia_Class10093]
        [ontologia_Class10023]
        [ontologia_Class10114])
    (nombrePlato "Risotto de Mar")
    (precioPlato 12)
    (temperatura Caliente)
    (tipoPlato Primero))

([ontologia_Class20009] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 6)
    (disponible Otono Invierno)
    (ingredientes
        [ontologia_Class10089]
        [ontologia_Class10012]
        [ontologia_Class10104])
    (nombrePlato "Tallarines Funghi")
    (precioPlato 9)
    (temperatura Caliente)
    (tipoPlato Primero Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class20010] of  Plato

    (dificultad 4)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10054]
        [ontologia_Class10116]
        [ontologia_Class10019]
        [ontologia_Class10089]
        [ontologia_Class10012]
        [ontologia_Class20011])
    (nombrePlato "Flan de Queso")
    (precioPlato 7)
    (temperatura Frio)
    (tipoPlato Postre)
    (t%C3%ADpico Espana))

([ontologia_Class20011] of  Ingrediente

    (nombreIngrediente "Cuajada")
    (platos [ontologia_Class20010])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class20012] of  Plato

    (dificultad 1)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10089]
        [ontologia_Class10059]
        [ontologia_Class20013]
        [ontologia_Class10108])
    (nombrePlato "Batido Manzana y Naranja")
    (precioPlato 5)
    (temperatura Frio)
    (tipoPlato Postre)
    (t%C3%ADpico Espana))

([ontologia_Class20013] of  Ingrediente

    (nombreIngrediente "Manzana")
    (platos [ontologia_Class20012])
    (tipoIngrediente Vegetal))

([ontologia_Class20014] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 4)
    (disponible Invierno)
    (ingredientes
        [ontologia_Class10031]
        [ontologia_Class10094]
        [ontologia_Class10043]
        [ontologia_Class10023]
        [ontologia_Class10093]
        [ontologia_Class10027])
    (nombrePlato "Arroz Caldoso")
    (precioPlato 9)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20015] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 8)
    (disponible Invierno)
    (ingredientes
        [ontologia_Class10031]
        [ontologia_Class10023]
        [ontologia_Class10029]
        [ontologia_Class20016]
        [ontologia_Class20017]
        [ontologia_Class10019])
    (nombrePlato "Lentejas al Caviar")
    (precioPlato 17)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20016] of  Ingrediente

    (nombreIngrediente "Curry")
    (platos [ontologia_Class20015])
    (tipoIngrediente Vegetal))

([ontologia_Class20017] of  Ingrediente

    (nombreIngrediente "Bacon")
    (platos
        [ontologia_Class20015]
        [ontologia_Class20033]
        [ontologia_Class20041])
    (tipoIngrediente Carne))

([ontologia_Class20018] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 7)
    (disponible Otono Invierno)
    (ingredientes
        [ontologia_Class10031]
        [ontologia_Class10055]
        [ontologia_Class10104]
        [ontologia_Class10089]
        [ontologia_Class20019])
    (nombrePlato "Bistec a la Trufa")
    (precioPlato 14)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class20019] of  Ingrediente

    (nombreIngrediente "Bistec de Ternera")
    (platos [ontologia_Class20018])
    (tipoIngrediente Carne))

([ontologia_Class20021] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 5)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10031]
        [ontologia_Class20004]
        [ontologia_Class10021]
        [ontologia_Class20022])
    (nombrePlato "Guisantes salteados con Sepia")
    (precioPlato 11)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class20022] of  Ingrediente

    (nombreIngrediente "Sepia")
    (platos [ontologia_Class20021])
    (tipoIngrediente Pescado))

([ontologia_Class20024] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 6)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class20025]
        [ontologia_Class10054]
        [ontologia_Class10019]
        [ontologia_Class20026]
        [ontologia_Class20027]
        [ontologia_Class10060])
    (nombrePlato "Tiramisú Casero")
    (precioPlato 8)
    (temperatura Frio)
    (tipoPlato Postre)
    (t%C3%ADpico Italia))

([ontologia_Class20025] of  Ingrediente

    (nombreIngrediente "Queso Mascarpone")
    (platos [ontologia_Class20024])
    (tipoIngrediente OrigenAnimal))

([ontologia_Class20026] of  Ingrediente

    (nombreIngrediente "Cafe")
    (platos [ontologia_Class20024])
    (tipoIngrediente Vegetal))

([ontologia_Class20027] of  Ingrediente

    (nombreIngrediente "Licor")
    (platos [ontologia_Class20024])
    (tipoIngrediente Vegetal))

([ontologia_Class20028] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 4)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class20029]
        [ontologia_Class20030]
        [ontologia_Class10031]
        [ontologia_Class10105]
        [ontologia_Class10023]
        [ontologia_Class10083])
    (nombrePlato "Albondigas con Champinones")
    (precioPlato 4)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class20029] of  Ingrediente

    (nombreIngrediente "Albondiga")
    (platos [ontologia_Class20028])
    (tipoIngrediente Carne))

([ontologia_Class20030] of  Ingrediente

    (nombreIngrediente "Champinon")
    (platos
        [ontologia_Class20028]
        [ontologia_Class20037]
        [ontologia_Class20039])
    (tipoIngrediente Vegetal))

([ontologia_Class20031] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 1)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10020]
        [ontologia_Class10027]
        [ontologia_Class10031]
        [ontologia_Class20032])
    (nombrePlato "Bravas")
    (precioPlato 4)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20032] of  Ingrediente

    (nombreIngrediente "Mayonesa")
    (platos [ontologia_Class20031])
    (tipoIngrediente Vegetal))

([ontologia_Class20033] of  Plato

    (dificultad 3)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10031]
        [ontologia_Class20017]
        [ontologia_Class10023]
        [ontologia_Class10034]
        [ontologia_Class10027]
        [ontologia_Class20036])
    (nombrePlato "Hamburguesa Ternera")
    (precioPlato 4)
    (temperatura Caliente)
    (tipoPlato Segundo)
    (t%C3%ADpico Espana))

([ontologia_Class20036] of  Ingrediente

    (nombreIngrediente "Hamburguesa")
    (platos [ontologia_Class20033])
    (tipoIngrediente Carne))

([ontologia_Class20037] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 3)
    (disponible TodoElAno)
    (ingredientes [ontologia_Class20030])
    (nombrePlato "Croquetas de Champinones")
    (precioPlato 3)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20038] of  Plato

    (bebidaCompatible
        [ontologia_Class10008]
        [ontologia_Class10009]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4])
    (dificultad 1)
    (disponible TodoElAno)
    (ingredientes [ontologia_Class10012])
    (nombrePlato "Tabla de Quesos")
    (precioPlato 17)
    (temperatura Frio)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20039] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 3)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10011]
        [ontologia_Class10015]
        [ontologia_Class20030]
        [ontologia_Class10028]
        [ontologia_Class20004]
        [ontologia_Class10086])
    (nombrePlato "Pure de verduras")
    (precioPlato 4)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20040] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 2)
    (disponible TodoElAno)
    (ingredientes [ontologia_Class10027])
    (nombrePlato "Sopa de Tomate")
    (precioPlato 3)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20041] of  Plato

    (bebidaCompatible
        [ontologia_Class10005]
        [ontologia_Class10008]
        [ontologia_Class10006]
        [ontologia_Class10009]
        [ontologia_Class10004]
        [ontologia_Class2]
        [ontologia_Class10051]
        [ontologia_Class10003]
        [ontologia_Class4]
        [ontologia_Class10007])
    (dificultad 3)
    (disponible TodoElAno)
    (ingredientes
        [ontologia_Class10022]
        [ontologia_Class10055]
        [ontologia_Class20017]
        [ontologia_Class20017])
    (nombrePlato "Espaguetis Carbonara")
    (precioPlato 7)
    (temperatura Caliente)
    (tipoPlato Primero)
    (t%C3%ADpico Espana))

([ontologia_Class20042] of  Ingrediente

    (nombreIngrediente "Espagueti")
    (tipoIngrediente Vegetal))

([ontologia_Class4] of  Bebida

    (compatiblesBebidas
        [ontologia_Class10040]
        [ontologia_Class10010]
        [ontologia_Class10018]
        [ontologia_Class10046]
        [ontologia_Class10025]
        [ontologia_Class10033]
        [ontologia_Class10052]
        [ontologia_Class10061]
        [ontologia_Class10065]
        [ontologia_Class10069]
        [ontologia_Class10071]
        [ontologia_Class10074]
        [ontologia_Class10078]
        [ontologia_Class10081]
        [ontologia_Class10084]
        [ontologia_Class10092]
        [ontologia_Class10096]
        [ontologia_Class10100]
        [ontologia_Class10103]
        [ontologia_Class10106]
        [ontologia_Class10109]
        [ontologia_Class10112]
        [ontologia_Class10117]
        [ontologia_Class10118]
        [ontologia_Class10119]
        [ontologia_Class0]
        [ontologia_Class20006]
        [ontologia_Class20007]
        [ontologia_Class20009]
        [ontologia_Class20014]
        [ontologia_Class20015]
        [ontologia_Class20018]
        [ontologia_Class20021]
        [ontologia_Class20024]
        [ontologia_Class20028]
        [ontologia_Class20031]
        [ontologia_Class20037]
        [ontologia_Class20038]
        [ontologia_Class20039]
        [ontologia_Class20040]
        [ontologia_Class20041])
    (esVino TRUE)
    (nombreBebida "Vino Tinto")
    (precioBebida 7))




)


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

(defmessage-handler Plato imprime primary ()
    (printout t " Plato:  " ?self:nombrePlato "( " ?self:precioPlato " )" crlf)
    (progn$ (?ingr ?self:ingredientes)
        (send ?ingr imprime)
    )
    (printout t crlf)
)

(defmessage-handler Usuario imprime primary ()
    (printout t " Usuario:  " ?self:nombreUsuario crlf) 
)

(defmessage-handler Bebida imprime primary ()
    (printout t " Bebida:  " ?self:nombreBebida crlf) 
)

(defmessage-handler Evento imprime primary ()
    (printout t " Evento:  " ?self:epocaEvento crlf) 
)

(defmessage-handler Ingrediente imprime primary ()
    (printout t "-" ?self:nombreIngrediente "( " ?self:tipoIngrediente " )" crlf) 
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
    (bind ?q (pregunta-numerica "¿Cual es el numero de comensales?" 0 200))
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
    (assert (ins_evento))
)

(defrule restriccionPrecioMax "regla para saber el precio maximo del menu"
    (nuevo_usuario)
    ?restrp <- (object (is-a RestriccionPrecio))
    => 
    (bind ?q (pregunta-numerica "¿Cual es el precio maximo del menu?" 1 1000))
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
    (assert (ins_restr_precio))
)

(defrule tipoDeComida "regla para saber el tipo de comida"
    (nuevo_usuario)
    ?restrt <- (object (is-a RestriccionTipo)) 
    => 
    (bind ?q (pregunta-indice "¿Que tipo de comida prefieres?" (create$ Indiferente Vegetariano Vegano)))
    (switch ?q
        (case 1 then (send ?restrt put-alimentacion Indiferente))
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
    =>
    (if (eq ?v TRUE) then
        (bind ?q (pregunta-indice "¿Como quieres el vino?" (create$ Unico CadaPlato)))
        (switch ?q
            (case 1 then (send ?restrt put-tipoVino Unico))
            (case 2 then (send ?restrt put-tipoVino CadaPlato))
        )
    )
    (assert (ins_tipo_tvino))
)

(defrule insertarRestriccionTipo "regla para insertar la restriccion de tipo al usuario"
    (nuevo_usuario)
    (ins_tipo_alimentacion)
    (ins_tipo_estilo)
    (ins_tipo_vino)
    (ins_tipo_tvino)
    ?restrt <- (object (is-a RestriccionTipo))
    ?usuario <- (object (is-a Usuario))
    =>
    (slot-insert$ ?usuario restricciones 1 ?restrt)
    (assert (ins_restr_tipo))
)

(defrule finPreguntas
    (nuevo_usuario)
    =>
    (printout t crlf)
    (printout t "Restricciones y Preferencias almacenadas" crlf)
    (printout t "Modulo: Inferencia"crlf)
    
    (focus inferir_datos)
)

;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------               MODULO DE INFERENCIA DE EXPEDIENTE              ----------                      MODULO DE INFERENCIA DE EXPEDIENTE  
;;;------------------------------------------------------------------------------------------------------------------------------------------------------

;; En este modulo se hace la inferencia de la informacion almacenada en el expediente 

(defmodule inferir_datos
    (import MAIN ?ALL)
    (import hacer_preguntas ?ALL)
    (export ?ALL)
)

(defrule infEpocaEventoP "regla para inferir la epoca del evento"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (epocaEvento ?epoca))
    (test (eq ?epoca Primavera))
    =>
    (assert (filtEpocaOtono))
    (assert (filtEpocaVerano))
    (assert (filtEpocaInvierno))
)

(defrule infEpocaEventoO "regla para inferir la epoca del evento"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (epocaEvento ?epoca))
    (test (eq ?epoca Otono))
    =>
    (assert (filtEpocaPrimavera))
    (assert (filtEpocaVerano))
    (assert (filtEpocaInvierno))
)


(defrule infEpocaEventoV "regla para inferir la epoca del evento"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (epocaEvento ?epoca))
    (test (eq ?epoca Verano))
    =>
    (assert (filtEpocaOtono))
    (assert (filtEpocaPrimavera))
    (assert (filtEpocaInvierno))
)


(defrule infEpocaEventoI "regla para inferir la epoca del evento"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (epocaEvento ?epoca))
    (test (eq ?epoca Invierno))
    =>
    (assert (filtEpocaOtono))
    (assert (filtEpocaVerano))
    (assert (filtEpocaPrimavera))
)

(defrule infNumComensales40 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 20) (< ?numC 40)))
    =>
    (assert (filtDificultad 10))
)

(defrule infNumComensales60 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 39) (< ?numC 60)))
    =>
    (assert (filtDificultad 9))
)

(defrule infNumComensales80 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 59) (< ?numC 80)))
    =>
    (assert (filtDificultad 8))
)

(defrule infNumComensales100 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 79) (< ?numC 100)))
    =>
    (assert (filtDificultad 7))
)

(defrule infNumComensales120 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 99) (< ?numC 120)))
    =>
    (assert (filtDificultad 6))
)

(defrule infNumComensales140 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 119) (< ?numC 140)))
    =>
    (assert (filtDificultad 5))
)

(defrule infNumComensales160 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 139) (< ?numC 160)))
    =>
    (assert (filtDificultad 4))
)

(defrule infNumComensales180 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (and(> ?numC 159) (< ?numC 180)))
    =>
    (assert (filtDificultad 3))
)

(defrule infNumComensales200 "regla para inferir el numero de comensales"
    (nuevo_usuario)
    (ins_evento)
    ?evento <- (object (is-a Evento) (numeroComensales ?numC))
    (test (> ?numC 179))
    =>
    (assert (filtDificultad 2))
)


(defrule infRestriccionPrecio "regla para inferir la restriccion de precio"
    (nuevo_usuario)
    (ins_restr_precio)
    ?restrp <- (object (is-a RestriccionPrecio) (maximo ?max) (minimo ?min))
    =>
    (assert (filtPrecioMax ?max))
    (assert (filtPrecioMin ?min))
)

(defrule infRestriccionTipoVege "regla para inferir la restriccion de tipo"
    (nuevo_usuario)
    (ins_restr_tipo)
    ?restrt <- (object (is-a RestriccionTipo) (alimentacion ?alim))
    (test (eq ?alim Vegetariano))
    =>
    (assert (filtAlimentacionCarne))
)

(defrule infRestriccionTipoVega "regla para inferir la restriccion de tipo"
    (nuevo_usuario)
    (ins_restr_tipo)
    ?restrt <- (object (is-a RestriccionTipo) (alimentacion ?alim))
    (test (eq ?alim Vegano))
    =>
    (assert (filtAlimentacionCarne))
    (assert (filtAlimentacionOAnimal))
)

(defrule infRestriccionVino "regla para inferir la restriccion de tipo"
    (nuevo_usuario)
    (ins_restr_tipo)
    ?restrt <- (object (is-a RestriccionTipo) (vino ?v))
    (test (eq ?v FALSE))
    =>
    (assert (filtVino))
)

(defrule fininferencia "regla para pasar al modulo de filtrado"
    (nuevo_usuario)
    =>
    (printout t crlf)
    (printout t "Inferencia de datos hecha" crlf)
    (printout t "Modulo: Filtrado" crlf)
    (focus filtrado)
)


;;;------------------------------------------------------------------------------------------------------------------------------------------------------
;;;----------               MODULO DE FILTRADO                  ----------                          MODULO DE FILTRADO  
;;;------------------------------------------------------------------------------------------------------------------------------------------------------

;; En este modulo se obtienen todos los platos instanciados
;; y se irán descartando si no cumplen alguna restriccion

(defmodule filtrado
    (import MAIN ?ALL) 
    (import hacer_preguntas ?ALL)
    (import inferir_datos ?ALL) 
    (export ?ALL)
)

(defrule descartarEpocaPrimavera "quitar platos de primavera"
    (nuevo_usuario)
    (filtEpocaPrimavera)
    ?plato <- (object (is-a Plato) (disponible Primavera))
    =>
    (printout t " Eliminado por ser un plato de primavera:" crlf)
    (send ?plato imprime)
    (send ?plato delete)
)

(defrule descartarEpocaOtono "quitar platos de otono"
    (nuevo_usuario)
    (filtEpocaOtono)
    ?plato <- (object (is-a Plato) (disponible Otono))
    =>
    (printout t " Eliminado por ser un plato de otono:" crlf)
    (send ?plato imprime)
    (send ?plato delete)
)

(defrule descartarEpocaVerano "quitar platos de verano"
    (nuevo_usuario)
    (filtEpocaVerano)
    ?plato <- (object (is-a Plato) (disponible Verano))
    =>
    (printout t " Eliminado por ser un plato de verano:" crlf)
    (send ?plato imprime)
    (send ?plato delete)
)

(defrule descartarEpocaInvierno "quitar platos de invierno"
    (nuevo_usuario)
    (filtEpocaInvierno)
    ?plato <- (object (is-a Plato) (disponible Invierno))
    =>
    (printout t " Eliminado por ser un plato de invierno:" crlf)
    (send ?plato imprime)
    (send ?plato delete)
)

(defrule descartarDificultad "quitar platos por dificultad"
    (nuevo_usuario)
    (filtDificultad ?dif)
    ?plato <- (object (is-a Plato) (dificultad ?comp))
    (test (>= ?comp ?dif))
    =>
    (printout t " Eliminado por ser un plato de dificultad >=" ?dif ":" crlf)
    (send ?plato imprime)
    (send ?plato delete)
)

(defrule descartarTipoAlimentoCarne "quito platos por tipo de alimento"
    (nuevo_usuario)
    (filtAlimentacionCarne)
    ?plato <- (object (is-a Plato))
    =>
    (bind ?ingredientes (send ?plato get-ingredientes))
    (progn$ (?i ?ingredientes)
        (bind ?tipo (send (instance-address * ?i) get-tipoIngrediente))
        (if (eq ?tipo Carne) 
            then 
            (printout t " Eliminado por ser un plato que contiene carne:" crlf)
            (send ?plato imprime) 
            (send ?plato delete)
            (break))
    )
)

(defrule descartarTipoAlimentoOAnimal "quito platos por tipo de alimento"
    (nuevo_usuario)
    (filtAlimentacionOAnimal)
    ?plato <- (object (is-a Plato))
    =>
    (bind ?ingredientes (send ?plato get-ingredientes))
    (progn$ (?i ?ingredientes)
        (bind ?tipo (send (instance-address * ?i) get-tipoIngrediente))
        (if (eq ?tipo OrigenAnimal) 
            then 
            (printout t " Eliminado por ser un plato que contiene carne:" crlf)
            (send ?plato imprime) 
            (send ?plato delete)
            (break))
    )
)

(defrule descartarVino "quitar bebida por vino"
    (nuevo_usuario)
    (filtVino)
    ?bebida <- (object (is-a Bebida) (esVino TRUE))
    =>
    (printout t " Eliminado por ser vino:" crlf)
    (send ?bebida imprime)
    (send ?bebida delete)
)


; (defrule imprimePlatos "regla parl usuario"
;     (declare (salience -1))
;     (nuevo_usuario)
;     ?plato <- (object (is-a Plato))
;     =>
;     (send ?plato imprime)
; )