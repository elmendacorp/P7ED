//
// Created by Fran on 23/11/2016.
//

#ifndef P7ED_THASHCERRADA_H
#define P7ED_THASHCERRADA_H


#include "vDinamico.h"

template<typename T>
class Nodo {
private:
    estado ocupacion;
    T dato;
public:
    enum estado {
        libre, usado, borrado
    };
    Nodo() { ocupacion = libre; }

    Nodo(const Nodo<T> &orig) {
        ocupacion = orig.ocupacion;
        dato = orig.dato;
    }

    Nodo<T> &operator=(const

                       Nodo &orig
    ) {
        ocupacion = orig.ocupacion;
        dato = orig.dato;
        return *this;
    }

    void setUsado(){ocupacion=usado;}

    void setLibre(){ocupacion=libre;}

    void setBorrado(){ocupacion=borrado;}

    void setDato(T &dat) { dato = dat; }

    void setClave(estado clav) { ocupacion = clav; }

    T getDato() { return dato; }

    estado getClave() { return ocupacion; }

};

template<typename T>
class THashCerrada {
private:
    unsigned long numIns;
    const
    int tammax = 10000;
    Nodo<T> tabla[tammax];
    int maxColisiones;

public:
    THashCerrada() : numIns(0), maxColisiones(0) {
    }

    THashCerrada(const

                 THashCerrada<T> &orig
    ) {
        numIns = orig.numIns;
        maxColisiones = orig.maxColisiones;
        tabla = orig.tabla;
    }

    THashCerrada<T> &operator=(const

                               THashCerrada<T> &orig
    ) {
        numIns = orig.numIns;
        maxColisiones = orig.maxColisiones;
        tabla = orig.tabla;
        return *this;
    }

    double factorCarga() { return numIns / tammax; }

    bool insertar(unsigned long key, const

    T &dato
    );

    bool borrar(unsigned long key, T &resultado);

    bool buscar(unsigned long key, T &resultado);

    unsigned long tamaTabla() { return numIns; }

    unsigned long hash(const

                       unsigned long &key, const
                       int &intento
    ) { return (key + (intento * intento)) % tammax; }

};

template<typename T>
bool THashCerrada<T>::insertar(unsigned long key, const T &dato) {
    if (dato == nullptr) {
        throw std::invalid_argument("dato nulo");
    }
    int intent = 0;
    unsigned long clave;
    while (intent < 5) {
        clave = hash(key, intent);
        if (!tabla[clave].getClave()) {
            tabla[clave].setDato(dato);
            tabla[clave].setClave(ocupado);
            return true;
        } else {
            ++
                    intent;
        }
    }
    return false;

}

template<typename T>
bool THashCerrada<T>::buscar(unsigned long key, T &resultado) {
    if (resultado == nullptr) {
        throw std::invalid_argument("dato nulo");
    }
    int intent = 0;
    unsigned long clave;
    while (intent < 5) {
        clave = hash(key, intent);
        if (tabla[clave].getClave()) {
            if (tabla[clave].getDato() == resultado) {
                resultado = tabla[clave].getDato();
                return true;
            }
            ++intent;
        }
    }
    resultado = nullptr;
    return false;
}

template<typename T>
bool THashCerrada<T>::borrar(unsigned long key, T &resultado) {
    if (resultado == nullptr) {
        throw std::invalid_argument("dato nulo");
    }
    int intent = 0;
    unsigned long clave;
    while (intent < 5) {
        clave = hash(key, intent);
        if (tabla[clave].getClave()) {
            resultado = tabla[clave].getDato();
            tabla[clave].setClave(false);
            return true;
        }
        ++intent;
    }
    resultado = nullptr;
    return false;
}

#endif //P7ED_THASHCERRADA_H
