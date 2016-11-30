//
// Created by Fran on 23/11/2016.
//

#ifndef P7ED_THASHCERRADA_H
#define P7ED_THASHCERRADA_H

#include "vDinamico.h"
template<typename T>
class Nodo{
private:
    bool ocupado;
    T dato;
public:
    Nodo():ocupado(false){}
    Nodo(const Nodo &orig):ocupado(orig.ocupado),dato(orig.dato){}
    Nodo<T> &operator=(const Nodo &orig){ocupado=orig.ocupado;dato=orig.dato;return *this;}
    void setDato(T &dat){dato=dat;}
    void setClave(bool clav){ocupado=clav;}
    T getDato(){return dato;}
    bool getClave(){return ocupado;}

};
template<typename T>
class THashCerrada {
private:
    vDinamico<Nodo<T>> tabla;
    int maxColisiones;
    unsigned long numIns,tamMax;
public:
    THashCerrada():numIns(0),maxColisiones(0){
        Nodo<T> tmp= Nodo<T>();
        tabla=vDinamico<Nodo<T>>(10001,tmp);
        tamMax=tabla.tama();
    }
    THashCerrada(const THashCerrada<T> &orig){tamMax=orig.tamMax;numIns=orig.numIns;maxColisiones=orig.maxColisiones;tabla=orig.tabla;}
    THashCerrada<T>& operator=(const THashCerrada<T> &orig){tamMax=orig.tamMax;numIns=orig.numIns;maxColisiones=orig.maxColisiones;tabla=orig.tabla; return *this;}
    double factorCarga(){return numIns/tamMax;}
    bool insertar(unsigned long key,const T &dato);
    bool borrar(unsigned long key, T &resultado);
    bool buscar(unsigned long key, T &resultado);
    unsigned long tamaTabla(){return numIns;}
    unsigned long hash(const unsigned long &key,const int &intento ){return (key+(intento*intento))%tamMax;}

};
template<typename T>
bool THashCerrada<T>::insertar(unsigned long key, const T &dato) {
    if(key>=tamMax){
        throw std::range_error("Fuera de rango");
    }
    int intent=0;
    unsigned long clave;
    while(intent<5) {
        clave = hash(key, intent);
        if (!tabla[clave].getClave()) {
            tabla[clave].setDato(dato);
            tabla[clave].setClave(true);
            return true;
        } else { ++intent; }
    }
    return false;

}
template<typename T>
bool THashCerrada<T>::buscar(unsigned long key, T &resultado) {
    if(key>=tamMax){
        throw std::range_error("Fuera de rango");
    }
    int intent=0;
    unsigned long clave;
    while(intent<5) {
        clave = hash(key,intent);
        if (tabla[clave].getClave()) {
           if(tabla[clave].getDato()==resultado){
               resultado = tabla[clave].getDato();
               return true;
           }
        }
        ++intent;
    }
    resultado= nullptr;
    return false;
}
template<typename T>
bool THashCerrada<T>::borrar(unsigned long key, T &resultado) {
    if(key>=tamMax){
        throw std::range_error("Fuera de rango");
    }
    int intent=0;
    unsigned long clave;
    while(intent<5) {
        clave = hash(key,intent);
        if (tabla[clave].getClave()) {
            resultado = tabla[clave].getDato();
            tabla[clave].setClave(false);
            return true;
        }
        ++intent;
    }
    resultado= nullptr;
    return false;
}

#endif //P7ED_THASHCERRADA_H
