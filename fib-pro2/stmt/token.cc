// classe Token

#include "token.hh"

void Token::iniciar() {
    nombre = false;
    text = false;
    etiqueta = false;
    hora = false;
    data = false;
    expressio = false;
    esborrat = false;
    consulta = false;
    error = false;
}

bool Token::es_digit(const char& c) {
    return (c >= '0' and c <= '9');
}

bool Token::es_nombre(string& s) {
    bool nombre = s.size() > 0;
    int i = 0;
    while (nombre and i < s.size()) {
        if (es_digit(s[i]))
            ++i;
        else
            nombre = false;
    }
    return nombre;
}

bool Token::es_lletra(const char& c) {
    return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or (int(c) == -61);
}

void Token::es_paraula(string& p) {
    if (p.size() > 0 and es_lletra(p[0])) {
        int i = 1;
        while (i < p.size() and p[i] != '.' and p[i] != ',' and p[i] != ':' and p[i] != '#')
            ++i;
        if (i < p.size())
            error = true;
    } else
        error = true;
}

void Token::tractar_hora() {
    hora = true;
    nombre = false;
    bool be = (m.size() == 5);
    be = be and es_digit(m[1]) and m[2] == ':' and es_digit(m[3]) and es_digit(m[4]);
    be = be and atoi(m.substr(0,2).c_str()) <= 23 and atoi(m.substr(3,2).c_str()) <= 59;
    error = error or not be;
}

void Token::tractar_data() {
    data = true;
    nombre = false;
    bool be = (m.size() == 8);
    be = be and es_digit(m[1]) and m[2] == '.' and es_digit(m[3]) and es_digit(m[4]);
    be = be and m[5] == '.' and es_digit(m[6]) and es_digit(m[7]);
    if (be) {
        int dia = atoi(m.substr(0,2).c_str());
        int mes = atoi(m.substr(3,2).c_str());
        int any = atoi(m.substr(6,2).c_str());
        be = be and (mes > 0) and (mes <= 12) and (dia > 0) and (dia <= 31);
        if (((mes == 4) or (mes == 6) or (mes == 9) or (mes == 11)) and (dia == 31))
            be = false;
        if (mes == 2) {
            if (any%4 == 0)
                be = be and (dia <= 29);
            else
                be = be and (dia <= 28);
        }
    }
    error = error or not be;
}

void Token::llegir_etiqueta(string& s, int& i) {
    while (i < s.size() and s[i] != '.' and s[i] != ',' and s[i] != '(' and s[i] != ')')
        ++i;
    --i;
}

void Token::tractar_expressio() {
    int s = 1;
    int i = 1;
    while (s > 0 and i < m.size() and not error) {
        if (m[i] == '(')
            ++s;
        else if (m[i] == ')')
            --s;
        else if (m[i] == '#')
            llegir_etiqueta(m,i);
        else if (m[i] != '.' and m[i] != ',')
            error = true;
        ++i;
    }
    if (i == m.size() and s == 0)
        expressio = true;
    else
        error = true;
}

Token::Token() {}

Token::Token(const string& s, bool& be) {
    m = s;
    iniciar();
    if (m.empty())
        return;
    if (m == "?" or m == "passat?" or m == "rellotge?")
        consulta = true;
    else if (m[0] == '#') {
        etiqueta = true;
        string s = m.substr(1);
        es_paraula(s);
    } else if (m[0] == '(')
        tractar_expressio();
    else if (es_digit(m[0])) {
        nombre = true;
        int i = 1;
        while (nombre and i < m.size()) {
            if (m[i] == ':')
                tractar_hora();
            else if (m[i] == '.')
                tractar_data();
            else {
                nombre = nombre and es_digit(m[i]);
                ++i;
            }
        }
    } else if (es_lletra(m[0])) {
        text = true;
        string s = m;
        es_paraula(s);
    } else if (m[0] == '-' and m[1] == '#') {
        esborrat = true;
        t_esborrat = "etiqueta";
        string s = m.substr(2);
        es_paraula(s);
    } else if (m[0] == '-') {
        esborrat = true;
        string s = m.substr(1);
        if (s == "etiquetes")
            t_esborrat = "etiquetes";
        else if (es_nombre(s))
            t_esborrat = "tasca";
        else
            error = true;
    }
    be = not error;
}

string Token::cos() {return m;}

bool Token::es_nombre() {return nombre;}

bool Token::es_text() {return text;}

bool Token::es_etiqueta() {return etiqueta;}

bool Token::es_hora() {return hora;}

bool Token::es_data() {return data;}

bool Token::es_expressio() {return expressio;}

bool Token::es_esborrat() {return esborrat;}

string Token::tipus_esborrat() {return t_esborrat;}

bool Token::es_consulta() {return consulta;}

