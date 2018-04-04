/** @file token.hh
    @brief Classe Token
 */

#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>
#include "stdlib.h"
#include <iostream>
using namespace std;

/** @class Token
    @brief Representa un string rellevant per a la classe Comanda.
 */

class Token {

private:
    string m;
    bool nombre;
    bool text;
    bool etiqueta;
    bool hora;
    bool data;
    bool expressio;
    bool esborrat;
    string t_esborrat;
    bool consulta;
    
    bool error;
    
    static bool es_digit(const char& c);
    static bool es_nombre(string& s);
    static bool es_lletra(const char& c);
    void es_paraula(string& p);
    void tractar_hora();
    void tractar_data();
    static void llegir_etiqueta(string& s, int& i);
    void tractar_expressio();
    void iniciar();

public:
    
    // Constructores
    
    Token();
    
    /** @brief Fa el tractament d'una string actualitzant la informació interna perquè funcionin bé les consultores
     \pre cert
     \post be = cert si i només si s és un string vàlid que pot formar part d'una comanda; quan be = cert, s'ha creat un objecte Token sobre el qual es poden fer consultes */
    Token(const string& s, bool& be); // assigna s a m i actualitza atributs

    // Consultores
    
    /** @brief Consulta l'string contingut en el p.i.
     \pre cert
     \post retorna l'string contingut en el p.i. */
    string cos();
    
    /** @brief Comprova si és un nombre (seqüència de dígits no buida)
     \pre cert
     \post cert si el p.i. conté un nombre */
    bool es_nombre();
    
    /** @brief Comprova si és una paraula (seqüència de símbols que comença per una lletra i no conté ni "." ni "," ni ":" ni "#")
     \pre cert
     \post cert si el p.i. conté una paraula */
    bool es_text();
    
    /** @brief Comprova si és una etiqueta (símbol # seguit d'una paraula)
     \pre cert
     \post cert si el p.i. conté una etiqueta */
    bool es_etiqueta();
    
    /** @brief Comprova si és una hora (amb format **:**, on * és un dígit)
     \pre cert
     \post cert si el p.i. conté una hora */
    bool es_hora();
    
    /** @brief Comprova si és una data (amb format **.**.**, on * és un dígit)
     \pre cert
     \post cert si el p.i. conté una data */
    bool es_data();
    
    /** @brief Comprova si és una expressió booleana d'etiquetes (ben parentitzada, on els operadors són "," (disjunció binària) i "." (conjunció binària) i els operands són etiquetes) 
     \pre cert
     \post cert si el p.i. conté una expressió booleana d'etiquetes */
    bool es_expressio();
    
    /** @brief Comprova si és un esborrat (una seqüència de símbols que comença per "-")
     \pre cert
     \post cert si el p.i. és un esborrat */
    bool es_esborrat();
     
    /** @brief Consulta el tipus d'esborrat
     \pre el p.i. és un esborrat
     \post retorna "etiqueta" si el p.i. conté una etiqueta després del símbol "-", "etiquetes" si conté l'string "etiquetes" després de "-", i "tasca" si conté un nombre després de "-" */
    string tipus_esborrat();
    
    /** @brief Comprova si és una consulta ("?" o "passat?" o "rellotge?")
     \pre el p.i. és una consulta
     \post cert si el p.i. és una consulta */
    bool es_consulta(); // retorna consulta
    
};

#endif
