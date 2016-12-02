//
// Created by Fran on 16/11/2016.
//

#ifndef UNTITLED_LISTA_H
#define UNTITLED_LISTA_H

/**
 * Clase que define un nodo de la lista enlazada
 */
template<typename T>
class Nodo2{
private:
    T dato;
    Nodo2<T> * siguiente;
    Nodo2<T> * anterior;
public:
    Nodo2():siguiente(0), anterior(0){}
    Nodo2(T &dato):dato(dato){}
    Nodo2(const Nodo2<T> &orig):siguiente(orig.siguiente), anterior(orig.anterior), dato(orig.dato){}
    bool haySiguiente(){return siguiente!=0;}
    bool hayAnterior(){return anterior!=0;}
    Nodo2<T> * getSiguiente(){return siguiente;}
    Nodo2<T> * getAnterior(){return anterior;}
    T & getDato(){return dato;}
    void setSiguiente(Nodo2<T> *orig){siguiente= orig;}
    void setAnterior(Nodo2<T> *orig){anterior= orig;}
    bool operator ==(const Nodo2<T> &orig){return dato==orig.dato;}
    bool operator !=(const Nodo2<T> &orig){return dato!=orig.dato;}

};

template<typename T>
class IteradorL{
private:
    Nodo2<T> * getNodo(){return nodoapuntado;}
public:
    Nodo2<T> * nodoapuntado;
    IteradorL():nodoapuntado(0){}
    IteradorL(Nodo2<T> * orig){nodoapuntado=orig;}
    IteradorL(const IteradorL<T> &orig):nodoapuntado(orig.nodoapuntado){}
    bool haySiguiente(){return nodoapuntado!=0;}
    bool hayAnterior(){return nodoapuntado!=0;}
    void siguiente(){nodoapuntado=nodoapuntado->getSiguiente();}
    void anterior(){nodoapuntado=nodoapuntado->getAnterior();}
    bool operator!=(const IteradorL<T> &orig){return nodoapuntado!=orig.nodoapuntado;}
    bool operator==(const IteradorL<T> &orig){return nodoapuntado==orig.nodoapuntado;}
    T &dato(){ return nodoapuntado->getDato();}

};

template<typename T>
class Lista {
private:
    Nodo2<T> *cabecera;
    Nodo2<T> *cola;
    Nodo2<T> *inicio(){return cabecera;}
    Nodo2<T> *fin(){return cola;}
    void insertarInicio(T &orig);
    void insertarFin(T &orig);
    void borrarInicio();
    void borrarFin();
public:
    Lista():cabecera(0), cola(0){}
    ~Lista();
    Lista(const Lista<T> &orig);
    IteradorL<T> iteradorInicio(){return IteradorL<T>(cabecera);}
    IteradorL<T> iteradorFin(){ return IteradorL<T>(cola);}
    void insertar(IteradorL<T> &it, T &dato);
    void borrar(IteradorL<T> &it);
    IteradorL<T> buscaElemento(const T &orig);

};
template<typename T>
void Lista<T>::insertarInicio(T &orig) {
    if(cabecera!=0){
        Nodo2<T> *tmp=new Nodo2<T>(orig);
        tmp->setSiguiente(cabecera);
        cabecera->setAnterior(tmp);
        cabecera=tmp;
    }else{
        Nodo2<T> *tmp=new Nodo2<T>(orig);
        cabecera=tmp;
        cola=cabecera;
    }
}
template<typename T>
void Lista<T>::insertarFin(T &orig) {
    if(cabecera!=0){
        Nodo2<T> *tmp=new Nodo2<T>(orig);
        cola->setSiguiente(tmp);
        tmp->setAnterior(cola);
        cola=tmp;
    }else{
        Nodo2<T> *tmp=new Nodo2<T>(orig);
        cola=tmp;
        cabecera=cola;
    }
}
template<typename T>
void Lista<T>::borrarInicio() {
    if(cabecera!=0){
        cabecera=cabecera->getSiguiente();
        delete cabecera->getAnterior();
    }
}
template<typename T>
void Lista<T>::borrarFin() {
    if(cabecera!=0){
        cola=cola->getAnterior();
        delete cola->getSiguiente();
    }
}

template<typename T>
Lista<T>::~Lista() {
    while(cabecera!=cola){
        cola=cola->getAnterior();
        delete cola->getSiguiente();
    }
    delete cabecera;
}
template<typename T>
Lista<T>::Lista(const Lista &orig) {
    Nodo2<T> *tmp=orig.cabecera;
    while(tmp!=orig.cola){
        this->insertarFin(tmp->getDato());
        tmp=tmp->getSiguiente();
    }
}
template<typename T>
void Lista<T>::insertar(IteradorL<T> &it, T &dato) {
    if(it==this->iteradorInicio()){
        this->insertarInicio(dato);
    }else if(it==iteradorFin()) {
        this->insertarFin(dato);
    }else{
        Nodo2<T> *tmp=new Nodo2<T>();
        tmp->setSiguiente(it.nodoapuntado->getSiguiente());
        tmp->setAnterior(it.nodoapuntado);
        it.nodoapuntado->getSiguiente()->setAnterior(tmp);
        it.nodoapuntado->setSiguiente(tmp);
    }
}
template<typename T>
void Lista<T>::borrar(IteradorL<T> &it) {
    if(it==this->iteradorInicio()){
        this->borrarInicio();
    }else if(it==this->iteradorFin()){
        this->borrarFin();
    }else{
        Nodo2<T> *tmp=new Nodo2<T>();
        tmp=it.nodoapuntado;
        tmp->getSiguiente()->setAnterior(tmp->getAnterior());
        tmp->getAnterior()->setSiguiente(tmp->getSiguiente());
        delete tmp;
    }
}
template<typename T>
IteradorL<T> Lista<T>::buscaElemento(const T &orig) {
    Nodo2<T> *tmp=cabecera;
    while(tmp!=cola){
        if(tmp->getDato()==orig){
            return IteradorL<T>(tmp);
        }
        tmp=tmp->getSiguiente();
    }
    return this->iteradorFin();
}


#endif //UNTITLED_LISTA_H
