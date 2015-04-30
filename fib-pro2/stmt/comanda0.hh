/** @file comanda.hh
    @brief Classe Comanda
 */

#ifndef COMANDA_HH
#define COMANDA_HH

/** @class Comanda
    @brief Representa una comanda (linia de text d'entrada).
 El metode llegir permet utilitzar consultores sobre la comanda llegida i comprovar
 que no tingui errors sintactics.
 */
class Comanda {

public:
    // Constructores
    
    Comanda();
    
    // Modificadores
    
    /** @brief Llegeix una comanda (linia de text d'entrada) i actualitza la informacio interna perque funcionin be les consultores
    \pre cert
    \post si s'ha llegit una comanda sense errors sintactics, be = cert i s'escriu la comanda; si la comanda te errors sintactics, be = fals i s'escriu "Error de format"; retorna cert quan la comanda no es "sortir" */
    bool llegir(bool& be);
    
    // Consultores
    
    /** @brief Comprova si la comanda es una insercio ("+" es el primer string)
    \pre: cert
    \post: cert si es una insercio */
    bool es_insercio();
    
    /** @brief Comprova si la comanda es una consulta ("?", "passat?" o "rellotge?" es el primer string)
    \pre cert
    \post cert si es una consulta */
    bool es_consulta();
    
    /** @brief Comprova si la comanda es una consulta del passat ("passat?" es el primer string)
    \pre cert
    \post cert si es una consulta sobre el passat */
    bool es_passat();
    
    /** @brief Comprova si la comanda es una modificacio (el primer string es un enter, pero el segon no comença per "-")
    \pre cert
    \post cert si es una modificacio */
    bool es_modificacio();
    
    /** @brief Comprova si la comanda es sobre el rellotge (el primer string es "rellotge" o "rellotge?")
    \pre cert
    \post cert si la comanda es una consulta sobre el rellotge o una modificacio del 
     temps del rellotge */
    bool es_rellotge();
    
    /** @brief Comprova si la comanda es d'esborrat (comença per "-k" o per "k -x", on k es un enter)
    \pre cert
    \post cert si es un esborrat */
    bool es_esborrat();
    
    /** @brief Consulta el tipus d'esborrat
    \pre la comanda es d'esborrat
    \post retorna el tipus d'esborrat: "etiquetes" (si cal esborrar totes les etiquetes), "etiqueta" (si cal esborrar-ne una) o "tasca" (si cal esborrar la tasca) */
    string tipus_esborrat();
    
    /** @brief Consulta el nombre de dates contingudes en la comanda
    \pre cert
    \post retorna el nombre de dates proporcionades en la comanda (0, 1 o 2) */
    int  nombre_dates();
    
    /** @brief Consulta una data individual de la comanda
    \pre 1 <= i <= nombre_dates()
    \post retorna la data i-esima de la comanda */
    string data(int i);
    
    /** @brief Comprova si la comanda conte hora
    \pre cert
    \post cert si la comanda conte hora */
    bool te_hora();
    
    /** @brief Consulta l'hora de la comanda
    \pre la comanda conte hora
    \post retorna l'hora continguda en la comanda */
    string hora();
    
    /** @brief Comprova si la comanda conte un titol (una sequencia de paraules, es a dir, strings que comencen per una lletra i no contenen ni "." ni "," ni ":" ni "#")
    \pre cert
    \post retorna cert si la comanda conte un titol */
    bool te_titol();
    
    /** @brief Consulta el titol de la comanda
    \pre es una insercio o es una modificacio amb titol
    \post retorna el titol contingut en la comanda */
    string titol();
    
    /** @brief Consulta el nombre d'etiquetes de la comanda (strings que comencen per # seguit d'una paraula)
    \pre cert
    \post retorna el nombre d'etiquetes contingudes en la comanda */
    int nombre_etiquetes();
    
    /** @brief Consulta una etiqueta de la comanda
    \pre 1 <= i <= nombre_etiquetes()
    \post retorna l'etiqueta i-esima de la comanda */
    string etiqueta(int i);
    
    /** @brief Consulta la presencia d'una expressio booleana d'etiquetes en la comanda, es a dir, una expressio ben parentitzada, on els operadors son "," (disjuncio binaria) i "." (conjuncio binaria) i els operands son etiquetes
    \pre cert
    \post cert si la comanda conte una expressio booleana d'etiquetes */
    bool te_expressio();

    /** @brief Consulta una expressio d'etiquetes
    \pre la comanda conte una expressio d'etiquetes
    \post retorna l'expressio booleana d'etiquetes continguda en la comanda */
    string expressio();
    
    /** @brief Consulta el numero de tasca que hi ha a la comanda
    \pre la comanda es un esborrat o una modificacio
    \post retorna el numero de tasca de l'operacio continguda en la comanda */
    int tasca();
};

#endif