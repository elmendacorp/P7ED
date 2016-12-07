//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_GITCODE_H
#define CPPAPPLICATION_2_GITCODE_H

#include "Fichero.h"
#include "Commit.h"
#include "fecha.h"
#include "vDinamico.h"
#include "Lista.h"
#include "THashCerrada.h"

class Gitcode {
private:
    class refCommit {
    public:
        std::string codCommit;
        IteradorL<Commit> itc;
        refCommit(){}
        refCommit(const std::string &cod,const IteradorL<Commit> &it) :codCommit(cod),itc(it){}
        refCommit(const refCommit &orig): codCommit(orig.codCommit),itc(orig.itc){}
        bool operator <(const refCommit &orig){return codCommit<orig.codCommit;}
        bool operator >(const refCommit &orig){return codCommit>orig.codCommit;}
        bool operator ==(const refCommit &orig){return codCommit==orig.codCommit;}
    };


    THashCerrada<refCommit> ABBbuscar;
    Lista<Commit> commits;
    vDinamico<Fichero *> ficheros;
public:
    void estadisticas();
    Gitcode(const std::string &fich, const std::string &commi);

    Commit getCommit(std::string &commi);

    vDinamico<Commit> getCommitFechas(const Fecha &inicio, const Fecha &fin);

    vDinamico<Commit> getCommitFichero(std::string fichero);

    void eliminaFichero(const std::string &fichero);

    void nuevoFichero(Fichero &orig);

    void nuevoCommit(Commit &c);

    void borraCommit(std::string codigo);

    int numFicheros(){return ficheros.tama();}

    unsigned long hf(std::string s) {
        unsigned long hash = 5381;
        char c;
        for (int i = 0; i < s.size(); i++) {
            c = s[i++];
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }
        return hash;
    }

};


#endif //CPPAPPLICATION_2_GITCODE_H
