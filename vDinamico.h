/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vDinamico.h
 * Author: Fran
 *
 * Created on 1 de octubre de 2016, 17:44
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <stdexcept>
#include <cmath>

template<typename T>
class vDinamico {
public:
    vDinamico();

    ~vDinamico();

    vDinamico(unsigned tam, const T &dato);

    vDinamico(const vDinamico<T> &orig);

    vDinamico<T> &operator=(const vDinamico<T> &orig);

    T &operator[](unsigned pos);

    unsigned tama() {
        return (unsigned) tamal;
    }


    //T busca(const T &dato);


private:
    int tamal, tamaf;
    T *v;
};

/**
 * constructor por defecto
 */
template<typename T>
vDinamico<T>::vDinamico() {
    tamal = 0;
    v = new T[tamaf=1];
}

/**
 * constructor con valor por defecto
 * @param tam
 * @param dato
 */
template<typename T>
vDinamico<T>::vDinamico(unsigned tam, const T &dato) {
    tamaf = pow(2, ((unsigned) log2(tam)) + 1);
    v = new T[tamaf];
    tamal = tamaf;
    for (unsigned i = 0; i < tamaf; ++i) {
        v[i] = dato;
    }
}

/**
 * constructor de copia
 * @param orig
 */
template<typename T>
vDinamico<T>::vDinamico(const vDinamico<T> &orig) {
    v = new T[tamaf= orig.tamaf];
    tamal = orig.tamal;
    for (unsigned i = 0; i < tamal; ++i) {
        v[i] = orig.v[i];
    }
}


/**
  * operador cochete
  * @param pos
  * @return
  */
template<typename T>
T &vDinamico<T>::operator[](unsigned pos) {
    if (pos<0) {
        throw std::out_of_range("Fuera de rango");
    }
    if(pos>=tamaf){
        tamaf = (int)pow(2, ((unsigned) log2((pos))) + 1);
        T *vaux = new T[tamaf];
        for (unsigned i = 0; i < tamal; i++) {
            vaux[i] = v[i];
        };
        delete []v;
        v = vaux;
        tamal=pos;
    }
    return v[pos];
}

/**
 * Destructor de la clase
 */
template<typename T>
vDinamico<T>::~vDinamico() {
    delete[] v;
}


/**
     * COnstructor de copia
     * @param orig
     * @return
     */
template<typename T>
vDinamico<T> &vDinamico<T>::operator=(const vDinamico<T> &orig) {
    delete []v;
   v=new T[tamaf=orig.tamaf];
    tamal = orig.tamal;
    for (unsigned i = 0; i < tamal; ++i) {
        v[i] = orig.v[i];
    }
    return *this;
}


#endif /* VDINAMICO_H */

