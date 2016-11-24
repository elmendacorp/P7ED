//
// Created by Fran on 23/11/2016.
//

#ifndef P7ED_THASHCERRADA_H
#define P7ED_THASHCERRADA_H

#include "vDinamico.h"
template<typename T>
class Nodo{
private:
    unsigned long clave;
    T dato;
public:
    Nodo():clave(0){}
    Nodo(const Nodo &orig):clave(orig.clave),dato(orig.dato){}
    Nodo<T> &operator=(const Nodo &orig){clave=orig.clave;dato=orig.dato;return *this;}
    void setDato(T &dat){dato=dat;}
    void setClave(const unsigned long &clav){clave=clav;}
    T getDato(){return dato;}
    unsigned long getClave(){return clave;}

};
template<typename T>
class THashCerrada {
private:
    vDinamico<Nodo<T>> tabla;
    int maxColisiones;
    unsigned long numIns,tamMax;
public:
    THashCerrada():tamMax(0),numIns(0),maxColisiones(0){}
    THashCerrada(const THashCerrada<T> &orig){tamMax=orig.tamMax;numIns=orig.numIns;maxColisiones=orig.maxColisiones;tabla=orig.tabla;}
    THashCerrada<T>& operator=(const THashCerrada<T> &orig){tamMax=orig.tamMax;numIns=orig.numIns;maxColisiones=orig.maxColisiones;tabla=orig.tabla; return *this;}
    double factorCarga(){return numIns/tamMax;}
    bool insertar(unsigned long key,const T &dato);
    bool borrar(unsigned long key);
    T *buscar(unsigned long key);
    unsigned long tamaTabla(){return numIns;}

};
template<typename T>
bool THashCerrada<T>::insertar(unsigned long key, const T &dato) {
    unsigned long pos=0;

}

#endif //P7ED_THASHCERRADA_H
