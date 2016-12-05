//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_COMMIT_H
#define CPPAPPLICATION_2_COMMIT_H

#include "Fichero.h"
#include <cassert>
#include <list>
#include <vector>
#include "fecha.h"

class Commit {
private:
    std::string codigo;
    Fecha marcaDeTiempo;
    std::string mensaje;
    std::vector<Fichero *> MisFicheros;
public:
    Commit() {
        codigo = "";
    }

    Commit(const std::string &codigo, Fecha marcaDeTiempo, const std::string &mensaje)
            : codigo(codigo), marcaDeTiempo(marcaDeTiempo), mensaje(mensaje) {

    }

    const std::string &getCodigo() const {
        return codigo;
    }

    Fecha getMarcaDeTiempo() const {
        return marcaDeTiempo;
    }

    const std::string &getMensaje() const {
        return mensaje;
    }

    void anadeFichero(Fichero *fichero) {
        MisFicheros.push_back(fichero);
    }

    bool borraFichero(const std::string &fichero) {
        auto ite = MisFicheros.begin();
        while (ite != MisFicheros.end()) {
            Fichero *tmp = *ite;
            if (tmp->getNombre() == fichero) {
                MisFicheros.erase(ite);
                return true;
            }
        }
        return false;

    }

    Fichero *&buscaFichero(std::string &fichero) {
        for (unsigned i = 0; i < MisFicheros.size(); ++i) {
            Fichero *tmp = MisFicheros[i];
            if (MisFicheros[i]->getNombre() == fichero) {
                return MisFicheros[i];
            }
        }
    }

    bool buscaFichero(const std::string &nombre) {
        for (int i = 0; i < MisFicheros.size(); ++i) {
            if (MisFicheros[i]->getNombre() == nombre) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Commit &orig) {
        return ((this->codigo == orig.codigo));
    }

    bool operator!=(const Commit &orig) {
        return ((this->codigo != orig.codigo));
    }

};


#endif //CPPAPPLICATION_2_COMMIT_H
