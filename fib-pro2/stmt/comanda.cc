// classe Comanda

#include "comanda.hh"

Comanda::Comanda() {
    i_data = vector<string> (MAX_i_data);
}

void Comanda::iniciar() {
    mida = 0;
    e = vector<Token> ();
    error = false;
    e_insercio = false;
    e_consulta = false;
    e_passat = false;
    e_modificacio = false;
    e_rellotge = false;
    e_acabament = false;
    e_esborrat = false;
    t_titol = false;
    n_dates = 0;
    t_hora = false;
    n_etiquetes = 0;
    i_etiqueta = vector<string> ();
    t_expressio = false;
}

void Comanda::anotar_titol(int& i) {
    if (t_titol)
        error = true;
    else {
        t_titol = true;
        i_titol = e[i].cos();
        ++i;
        while (i < mida and e[i].es_text()) {
            i_titol += " " + e[i].cos();
            ++i;
        }
    }
}

void Comanda::anotar_hora(int& i) {
    if (t_hora)
        error = true;
    else {
        t_hora = true;
        i_hora = e[i].cos();
        ++i;
    }
}

void Comanda::anotar_data(int& i) {
    if (n_dates > 0)
        error = true;
    else {
        i_data[n_dates] = e[i].cos();
        ++i;
        ++n_dates;
    }
}

void Comanda::anotar_etiqueta(int& i) {
    i_etiqueta.push_back(e[i].cos());
    ++i;
    ++n_etiquetes;
}

void Comanda::anotar_temps(int& i) {
    if (e[i].es_hora())
        anotar_hora(i);
    else if (e[i].es_data())
        anotar_data(i);
    else
        error = true;
}

void Comanda::afegir_elements() {
    int i = 1;
    while (i < mida and not error) {
        if (e[i].es_text())
            anotar_titol(i);
        else if (e[i].es_hora())
            anotar_hora(i);
        else if (e[i].es_data())
            anotar_data(i);
        else if (e[i].es_etiqueta())
            anotar_etiqueta(i);
        else
            error = true;
    }
}

void Comanda::tractar_insercio() {
    e_insercio = true;
    afegir_elements();
    if (not t_titol or not t_hora)
        error = true;
}

void Comanda::tractar_modificacio() {
    e_modificacio = true;
    i_tasca =  atoi(e[0].cos().c_str());
    if (mida == 1)
        error = true;
    else
        afegir_elements();
}

void Comanda::tractar_consulta() {
    e_consulta = true;
    int i = 1;
    while (i < mida and not error) {
        if (e[i].es_etiqueta()) {
            if (n_etiquetes > 0)
                error = true;
            else {
                i_etiqueta.push_back(e[i].cos());
                ++i;
                ++n_etiquetes;
            }
        } else if (e[i].es_data()) {
            if (n_dates == 2)
                error = true;
            else {
                i_data[n_dates] = e[i].cos();
                ++i;
                ++n_dates;
            }
        } else if (e[i].es_expressio()) {
            if (t_expressio)
                error = false;
            else {
                t_expressio = true;
                i_expressio = e[i].cos();
                ++i;
            }
        } else
            error = true;
    }
}

void Comanda::tractar_consulta_rapida(bool& el_que_sigui) {
    if (mida > 1)
        error = true;
    else {
        e_consulta = true;
        el_que_sigui = true;
    }
}

void Comanda::tractar_esborrat_parcial() {
    if (mida != 2)
        error = true;
    else {
        e_esborrat = true;
        i_esborrat = e[1].tipus_esborrat();
        if (i_esborrat == "tasca")
            error = true;
        else {
            i_tasca =  atoi(e[0].cos().c_str());
            if (i_esborrat == "etiqueta") {
                n_etiquetes = 1;
                i_etiqueta.push_back(e[1].cos());
                i_etiqueta[0].erase(0,1);
            }
        }
    }
}

void Comanda::tractar_esborrat_tasca() {
    if (mida > 1)
        error = true;
    else {
        e_esborrat = true;
        i_esborrat = "tasca";
        string r = e[0].cos();
        i_tasca =  atoi(r.erase(0,1).c_str());
    }
}

void Comanda::fixar_temps_rellotge() {
    if (mida > 3)
        error = true;
    else {
        e_rellotge = true;
        int i = 1;
        if (i < mida)
            anotar_temps(i);
        if (i < mida)
            anotar_temps(i);
    }
}

bool Comanda::llegir(bool& be) {
    iniciar();
    string entrada;
    getline(cin,entrada);
    stringstream linia(entrada);
    string s;
    be = true;
    while (be and linia >> s) {
        Token t(s,be);
        e.push_back(t);
        ++mida;
    }
    if (be and mida > 0) {
        if (e[0].cos() == "+")
            tractar_insercio();
        else if (e[0].cos() == "passat?")
            tractar_consulta_rapida(e_passat);
        else if (e[0].cos() == "rellotge?")
            tractar_consulta_rapida(e_rellotge);
        else if (e[0].cos() == "rellotge")
            fixar_temps_rellotge();
        else if (e[0].cos() == "sortir" and mida == 1)
                e_acabament = true;
        else if (e[0].es_consulta())
            tractar_consulta();
        else if (e[0].es_nombre()){
            if (mida == 1)
                be = false;
            else if (e[1].es_esborrat())
                tractar_esborrat_parcial();
            else
                tractar_modificacio();
        } else if (e[0].es_esborrat() and e[0].tipus_esborrat() == "tasca")
            tractar_esborrat_tasca();
        else
            be = false;
        be = be and not error;
    }
    if (be)
        cout << endl << entrada << endl;
    else
        cout << "Error de format" << endl;
    return not e_acabament;
}

bool Comanda::es_insercio() {return e_insercio;}

bool Comanda::es_consulta() {return e_consulta;}

bool Comanda::es_passat() {return e_passat;}

bool Comanda::es_modificacio() {return e_modificacio;}

bool Comanda::es_rellotge() {return e_rellotge;}

bool Comanda::es_esborrat() {return e_esborrat;}

string Comanda::tipus_esborrat() {return i_esborrat;}

int Comanda::nombre_dates() {return n_dates;}

string Comanda::data(int i) {return i_data[i-1];}

bool Comanda::te_hora() {return t_hora;}

string Comanda::hora() {return i_hora;}

bool Comanda::te_titol() {return t_titol;}

string Comanda::titol() {return i_titol;}

int Comanda::nombre_etiquetes() {return n_etiquetes;}

string Comanda::etiqueta(int i) {return i_etiqueta[i-1];}

bool Comanda::te_expressio() {return t_expressio;}

string Comanda::expressio() {return i_expressio;}

int Comanda::tasca() {return i_tasca;}
