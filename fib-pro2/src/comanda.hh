/** @file comanda.hh
    @brief Classe Comanda
 */

#ifndef COMANDA_HH
#define COMANDA_HH

#include <sstream>
#include <vector>
#include <string>
#include "stdlib.h"
#include <iostream>
#include "token.hh"
using namespace std;

/** @class Comanda
    @brief Representa una comanda (línia de text d'entrada).
 El mètode llegir permet utilitzar consultores sobre la comanda llegida i comprovar
 que no tingui errors sintàctics.
 */
class Comanda {

private:
    static const int MAX_i_data = 2;
    
    vector<Token> e;
    int mida;

    bool e_insercio;
    bool e_consulta;
    bool e_passat;
    bool e_modificacio;
    bool e_rellotge;
    bool e_esborrat;
    bool e_acabament;

    int  n_dates;
    vector<string> i_data;

    bool t_hora;
    string i_hora;
    
    bool t_titol;
    string i_titol;
    
    int  n_etiquetes;
    vector<string> i_etiqueta;
    
    bool t_expressio;
    string i_expressio;
    
    string i_esborrat;
    
    int i_tasca;
    
    bool error;
    
    // inicialitzar atributs de la comanda
    void iniciar();
    
    void anotar_titol(int& i);
    
    void anotar_hora(int& i);
    
    void anotar_data(int& i);
    
    void anotar_etiqueta(int& i);
    
    void anotar_temps(int& i);
    
    void afegir_elements();
    
    void tractar_insercio();

    void tractar_consulta();
    
    void tractar_consulta_rapida(bool& el_que_sigui);
    
    void tractar_modificacio();
    
    void tractar_esborrat_parcial();
    
    void tractar_esborrat_tasca();
    
    void fixar_temps_rellotge();
    
public:
    // Constructores
    
    Comanda();
    
    // Modificadores
    
    /** @brief Llegeix una comanda (línia de text d'entrada) i actualitza la informació interna perquè funcionin bé les consultores
    \pre cert
    \post si s'ha llegit una comanda sense errors sintàctics, be = cert i s'escriu la comanda; si la comanda té errors sintàctics, be = fals i s'escriu "Error de format"; retorna cert quan la comanda no és "sortir" */
    bool llegir(bool& be);
    
    // Consultores
    
    /** @brief Comprova si la comanda és una inserció ("+" és el primer string)
    \pre: cert
    \post: cert si és una inserció */
    bool es_insercio();
    
    /** @brief Comprova si la comanda és una consulta ("?", "passat?" o "rellotge?" és el primer string)
    \pre cert
    \post cert si és una consulta */
    bool es_consulta();
    
    /** @brief Comprova si la comanda és una consulta del passat ("passat?" és el primer string)
    \pre cert
    \post cert si és una consulta sobre el passat */
    bool es_passat();
    
    /** @brief Comprova si la comanda és una modificació (el primer string és un enter, però el segon no comença per "-")
    \pre cert
    \post cert si és una modificació */
    bool es_modificacio();
    
    /** @brief Comprova si la comanda és sobre el rellotge (el primer string és "rellotge" o "rellotge?")
    \pre cert
    \post cert si la comanda és una consulta sobre el rellotge o una modificació del 
     temps del rellotge */
    bool es_rellotge();
    
    /** @brief Comprova si la comanda és d'esborrat (comença per "-k" o per "k -x", on k és un enter)
    \pre cert
    \post cert si és un esborrat */
    bool es_esborrat();
    
    /** @brief Consulta el tipus d'esborrat
    \pre la comanda és d'esborrat
    \post retorna el tipus d'esborrat: "etiquetes" (si cal esborrar totes les etiquetes), "etiqueta" (si cal esborrar-ne una) o "tasca" (si cal esborrar la tasca) */
    string tipus_esborrat();
    
    /** @brief Consulta el nombre de dates contingudes en la comanda
    \pre cert
    \post retorna el nombre de dates proporcionades en la comanda (0, 1 o 2) */
    int  nombre_dates();
    
    /** @brief Consulta una data individual de la comanda
    \pre 1 <= i <= nombre_dates()
    \post retorna la data i-èsima de la comanda */
    string data(int i);
    
    /** @brief Comprova si la comanda conté hora
    \pre cert
    \post cert si la comanda conté hora */
    bool te_hora();
    
    /** @brief Consulta l'hora de la comanda
    \pre la comanda conté hora
    \post retorna l'hora continguda en la comanda */
    string hora();
    
    /** @brief Comprova si la comanda conté un títol (una seqüència de paraules, és a dir, strings que comencen per una lletra i no contenen ni "." ni "," ni ":" ni "#")
    \pre cert
    \post retorna cert si la comanda conté un títol */
    bool te_titol();
    
    /** @brief Consulta el títol de la comanda
    \pre és una inserció o és una modificació amb títol
    \post retorna el títol contingut en la comanda */
    string titol();
    
    /** @brief Consulta el nombre d'etiquetes de la comanda (strings que comencen per # seguit d'una paraula)
    \pre cert
    \post retorna el nombre d'etiquetes contingudes en la comanda */
    int nombre_etiquetes();
    
    /** @brief Consulta una etiqueta de la comanda
    \pre 1 <= i <= nombre_etiquetes()
    \post retorna l'etiqueta i-èsima de la comanda */
    string etiqueta(int i);
    
    /** @brief Consulta la presència d'una expressió booleana d'etiquetes en la comanda, és a dir, una expressió ben parentitzada, on els operadors són "," (disjunció binària) i "." (conjunció binària) i els operands són etiquetes
    \pre cert
    \post cert si la comanda conté una expressió booleana d'etiquetes */
    bool te_expressio();

    /** @brief Consulta una expressió d'etiquetes
    \pre la comanda conté una expressió d'etiquetes
    \post retorna l'expressio booleana d'etiquetes continguda en la comanda */
    string expressio();
    
    /** @brief Consulta el número de tasca que hi ha a la comanda
    \pre la comanda és un esborrat o una modificació
    \post retorna el número de tasca de l'operació continguda en la comanda */
    int tasca();
};

#endif