//
// Created by Fran on 23/11/2016.
//

#ifndef P7ED_THASHCERRADA_H
#define P7ED_THASHCERRADA_H


#include "vDinamico.h"

enum class estado {
    libre, usado, borrado
};

template<typename T>
class Nodo {
private:
    estado ocupacion;
    T dato;
public:
    Nodo() { ocupacion = estado::libre; }

    Nodo(const Nodo<T> &orig) {
        ocupacion = orig.ocupacion;
        dato = orig.dato;
    }

    Nodo<T> &operator=(const Nodo &orig) {
        ocupacion = orig.ocupacion;
        dato = orig.dato;
        return *this;
    }

    void setUsado() { ocupacion = estado::usado; }

    void setBorrado() { ocupacion = estado::borrado; }

    void setDato(T &dat) { dato = dat; }

    T getDato() { return dato; }

    bool checkEstado(const estado &orig) { return ocupacion == orig; }

};

template<typename T>
class THashCerrada {
private:
    double numIns;
    const static int tammax = 38675;//31033 doble
    Nodo<T> tabla[tammax];
    int maxColisiones;
public:
    THashCerrada() : numIns(0), maxColisiones(0) {
    }

    THashCerrada(const THashCerrada<T> &orig) {
        numIns = orig.numIns;
        maxColisiones = orig.maxColisiones;
        for (int i = 0; i < tammax; ++i) {
            tabla[i] = orig.tabla[i];
        }
    }

    THashCerrada<T> &operator=(const THashCerrada<T> &orig) {
        numIns = orig.numIns;
        maxColisiones = orig.maxColisiones;
        for (int i = 0; i < tammax; ++i) {
            tabla[i] = orig.tabla[i];
        }
        return *this;
    }

    const double factorCarga() {
        return numIns / tammax;
    }

    int maxColision() { return maxColisiones; }

    bool insertar(unsigned long key, T &dato);

    bool borrar(unsigned long key, T &resultado);

    bool buscar(unsigned long key, T &resultado);

    unsigned long tamaTabla() { return tammax; }

    unsigned long hash(const unsigned long &key, const int &intento) { return (key + intento * intento) % tammax; }

    unsigned long hash2(const unsigned long &key, const int &intento) {
        int h1, h2;
        h1 = key % 23549;
        h2 = key % 25373;
        return (h1 + (intento * (key - h2))) % tammax;
    }

};

template<typename T>
bool THashCerrada<T>::insertar(unsigned long key, T &dato) {
    int intent = 0;
    unsigned long clave;
    bool insertado = false;
    while (!insertado && (numIns < tammax)) {
        clave = hash(key, intent);
        if (tabla[clave].checkEstado(estado::libre) || tabla[clave].checkEstado(estado::borrado)) {
            tabla[clave].setDato(dato);
            tabla[clave].setUsado();
            if (intent > maxColisiones) { maxColisiones = intent; }
            ++numIns;
            return true;
        } else {
            ++intent;
        }
    }
    return false;

}

template<typename T>
bool THashCerrada<T>::buscar(unsigned long key, T &resultado) {
    int intent = 0;
    unsigned long clave;
    clave = hash(key, intent);
    while (!tabla[clave].checkEstado(estado::libre)) {
        if (tabla[clave].checkEstado(estado::usado)) {
            if(resultado==tabla[clave].getDato()) {
                resultado = tabla[clave].getDato();
                ++intent;
                return true;
            }
        }
        clave = hash2(key, intent);
    }
    return false;
}

template<typename T>
bool THashCerrada<T>::borrar(unsigned long key, T &resultado) {
    int intent = 0;
    unsigned long clave;
    clave = hash(key, intent);
    while (!tabla[clave].checkEstado(estado::libre)) {
        if (tabla[clave].checkEstado(estado::usado)) {
            if(resultado==tabla[clave].getDato()) {
                resultado = tabla[clave].getDato();
                tabla[clave].setBorrado();
                ++intent;
                return true;
            }
        }
        clave = hash2(key, intent);
    }
    return false;
}

#endif //P7ED_THASHCERRADA_H
