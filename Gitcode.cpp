//
// Created by Fran on 25/10/2016.
//

#include "Gitcode.h"
#include <fstream>
#include <iostream>


void Gitcode::estadisticas() {
    double carga=ABBbuscar.factorCarga();
    printf("factor carga:%f colisiones: %d\n",carga, ABBbuscar.maxColision());
}


Gitcode::Gitcode(const std::string &fich, const std::string &commi) {
    std::string lineaActual;
    try {
        std::ifstream inputStream;
        inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        inputStream.open(fich);

        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            Fichero *f;
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find(';');
            auto ruta = lineaActual.substr(0, pos);
            auto tama = lineaActual.substr(pos + 1, ruta.length() - 1);

            pos = ruta.find_last_of('/');
            auto ubicacion = ruta.substr(0, pos + 1);
            auto nombre = ruta.substr(pos + 1, ruta.length());
            auto tamaBytes = std::stoi(tama);
            f =new Fichero(nombre, ubicacion, tamaBytes);
            ficheros.aumenta(f);



        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }

    int ref;
    try {
        std::ifstream inputStream;

        inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        inputStream.open(commi);
        Commit *MiCommit;
        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find_last_of(';');
            auto indice = lineaActual.substr(pos + 1, lineaActual.size()-2);
            auto substr1 = lineaActual.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto mensaje = substr1.substr(pos + 1, substr1.size());
            substr1 = substr1.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto marcaTiempo = substr1.substr(pos + 1, substr1.size());
            Fecha fch= Fecha(1,1,1,1,1);
            fch.anadirAnios(std::stoi(marcaTiempo.substr(0, 4))-1);
            fch.anadirMeses(std::stoi(marcaTiempo.substr(4, 6))-1);
            fch.anadirDias(std::stoi(marcaTiempo.substr(6, 8))-1);
            fch.anadirHoras(std::stoi(marcaTiempo.substr(8, 10))-1);
            fch.anadirMin(std::stoi(marcaTiempo.substr(10, 12))-1);

            auto codigo = substr1.substr(0, pos);
            Commit inserta = Commit(codigo, fch, mensaje);

            pos = 0;
            indice = indice.substr(0, (indice.size() - 1));
            while (pos != indice.find_first_of(',')) {
                pos = indice.find_last_of(',');
                ref = std::stoi(indice.substr(pos + 1, substr1.size()));
                inserta.anadeFichero(ficheros[ref]);
                indice = indice.substr(0, pos);
            }
            IteradorL<Commit> in=commits.iteradorFin();
            commits.insertar(in,inserta);
            refCommit inserta2=refCommit(inserta.getCodigo(),commits.iteradorFin());
            ABBbuscar.insertar(hf(inserta.getCodigo()),inserta2);




        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }
}

Commit Gitcode::getCommit(std::string &commi) {
    IteradorL<Commit> ini = commits.iteradorInicio();
    while (ini!=commits.iteradorFin()){
        if(ini.dato().getCodigo()==commi){
            return ini.dato();
        }else{
            ini.siguiente();
        }
    }
}

vDinamico<Commit> Gitcode::getCommitFechas(const Fecha &inicio, const Fecha &fin) {
    vDinamico<Commit> temporal;
    IteradorL<Commit> temp = commits.iteradorInicio();
    while(temp!=commits.iteradorFin()){
        if(temp.dato().getMarcaDeTiempo()<fin&&temp.dato().getMarcaDeTiempo()>inicio){
            Commit t=temp.dato();
            temporal.aumenta(t);
        }
        temp.siguiente();
    }

    return temporal;
}

vDinamico<Commit> Gitcode::getCommitFichero(std::string fichero) {
    vDinamico<Commit>temporal;
    auto tempo = commits.iteradorInicio();
    while(tempo!=commits.iteradorFin()){
        Fichero* t=tempo.dato().buscaFichero(fichero);
        if(t->getTamaBytes()!=0){
            Commit d=tempo.dato();
            temporal.aumenta(d);
        }
        tempo.siguiente();
    }

    return temporal;
}

void Gitcode::eliminaFichero(const std::string &fichero) {
    auto temp= commits.iteradorInicio();
    while(temp!=commits.iteradorFin()){
        temp.dato().borraFichero(fichero);
        temp.siguiente();
    }
}

void Gitcode::nuevoCommit(Commit &c) {
    refCommit tmp;
    if(!ABBbuscar.buscar(hf(c.getCodigo()),tmp)){
        IteradorL<Commit> in=commits.iteradorFin();
        commits.insertar(in,c);
        refCommit inserta2=refCommit(c.getCodigo(),commits.iteradorFin());
        ABBbuscar.insertar(hf(c.getCodigo()),inserta2);
    }
}


void Gitcode::borraCommit(std::string codigo) {
    refCommit tmp;
    if(ABBbuscar.borrar(hf(codigo),tmp)){
         commits.borrar(tmp.itc);
    }
}

void Gitcode::nuevoFichero(Fichero &orig) {
    if(!ficheros.busca(&orig)) {
        Fichero * f =new Fichero(orig);
        ficheros.aumenta(f);
    }
}
