//
// Created by Fran on 25/10/2016.
//

#include "Gitcode.h"
#include <fstream>
#include <iostream>

/*
Commit *Gitcode::getCommit(const std::string &commi) {
    if(ABBbuscar.find(commi)!=ABBbuscar.end()) {
        return *ABBbuscar.find(commi)->second;
    }else{
        return 0;
    }

}
*/

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
            f = new Fichero(nombre, ubicacion, tamaBytes);
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
        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find_last_of(';');
            auto indice = lineaActual.substr(pos + 1, lineaActual.size() - 2);
            auto substr1 = lineaActual.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto mensaje = substr1.substr(pos + 1, substr1.size());
            substr1 = substr1.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto marcaTiempo = substr1.substr(pos + 1, substr1.size());
            Fecha fch = Fecha(1, 1, 1, 1, 1);
            fch.anadirMin(std::stoi(marcaTiempo.substr(10, 2)) - 1);
            fch.anadirHoras(std::stoi(marcaTiempo.substr(8, 2)) - 1);
            fch.anadirDias(std::stoi(marcaTiempo.substr(6, 2)) - 1);
            fch.anadirMeses(std::stoi(marcaTiempo.substr(4, 2)) - 1);
            fch.anadirAnios(std::stoi(marcaTiempo.substr(0, 4)) - 1);


            auto codigo = substr1.substr(0, pos);
            Commit *inserta = new Commit(codigo, fch, mensaje);

            pos = 0;
            indice = indice.substr(0, (indice.size() - 1));
            while (pos != indice.find_first_of(',')) {
                pos = indice.find_last_of(',');
                ref = std::stoi(indice.substr(pos + 1, substr1.size()));
                inserta->anadeFichero(ficheros[ref]);
                indice = indice.substr(0, pos);
            }
            auto it=commits.iteradorFin();
            commits.insertar(it, inserta);
            if(ABBbuscar.insertar(djb2(inserta->getCodigo()))){}



        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }
}

std::vector<Commit *> Gitcode::getCommitFechas(const Fecha &f1, const Fecha &f2) {
    std::vector<Commit *> temp;
    auto it = commits.begin();
    while (it != commits.end()) {
        Commit *tmp = *it;
        if (tmp->getMarcaDeTiempo() > f1 && tmp->getMarcaDeTiempo() < f2) {
            temp.push_back(tmp);
        }
        ++it;
    }
    return temp;
}

std::vector<Commit *> Gitcode::getCommitFichero(const std::string &nombre) {
    std::vector<Commit *> temp;
    auto it = commits.begin();
    while (it != commits.end()) {
        Commit *tmp = *it;

        if (tmp->buscaFichero(nombre)) {
            temp.push_back(tmp);
        }
        ++it;
    }
    return temp;
}

void Gitcode::nuevoCommit(const std::string &codigo, const std::string &texto, const Fecha &timestamp,
                          const std::set<std::string> &fichAfectados) {
    if(ABBbuscar.find(codigo)!=ABBbuscar.end()) {
        Commit *tmp = new Commit(codigo, timestamp, texto);
        auto it = fichAfectados.begin();
        while (it != fichAfectados.end()) {
            auto it2 = ficherosActivos.find(*it);
            if (it2 != ficherosActivos.end()) {
                tmp->anadeFichero(it2->second);
                ++it;
            } else {
                throw std::range_error("fichero inexistente");
            }
        }
        auto iter = commits.emplace(commits.end(), tmp);
        ABBbuscar.emplace(tmp->getCodigo(), iter);
    }
}

void Gitcode::borrarCommit(const std::string &code_commit) {
    auto it=ABBbuscar.find(code_commit);
    if(it!=ABBbuscar.end()){
        commits.erase(it->second);
        ABBbuscar.erase(code_commit);
    }
}

int Gitcode::getNumFicherosActivos() {
    return (int) ficherosActivos.size();
}

std::vector<Fichero *> Gitcode::getFicherosActivos() {
    std::vector<Fichero *> temp;
    auto it = ficherosActivos.begin();
    while (it != ficherosActivos.end()) {
        temp.push_back(it->second);
        ++it;
    }
    return temp;
}

void Gitcode::nuevoFichero(const Fichero &fichero) {
    if (ficherosActivos.find(fichero.getNombre()) != ficherosActivos.end()) {
        throw std::invalid_argument("El fichero ya existe");
    } else {
        Fichero *fch = new Fichero(fichero);
        ficheros.push_back(fch);
        ficherosActivos.emplace(fch->getNombre(), fch);
    }
}

void Gitcode::nuevoFichero(const std::vector<Fichero> &ficherosInsertar) {
    for (auto i=ficherosInsertar.begin(); i !=ficherosInsertar.end(); ++i) {
        this->nuevoFichero(*i);
    }
}

void Gitcode::borraFichero(const std::string &nombreFichero) {
    auto it=ficherosActivos.find(nombreFichero);
    if (it != ficherosActivos.end()) {
        ficherosActivos.erase(it);
    }
}

Gitcode::~Gitcode() {
    for(auto it=ficheros.begin();it!=ficheros.end();++it){
        delete *it;
    }
    for(auto it2=commits.begin();it2!=commits.end();++it2){
        delete *it2;
    }
}


