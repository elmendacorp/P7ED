//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_GITCODE_H
#define CPPAPPLICATION_2_GITCODE_H

#include "Fichero.h"
#include "Commit.h"
#include "fecha.h"
#include <vector>
#include <map>
#include <list>
#include <set>


class Gitcode {
private:
    std::map<std::string, std::list<Commit *>::iterator> ABBbuscar;
    std::list<Commit *> commits;
    std::vector<Fichero *> ficheros;
    std::map<std::string, Fichero *> ficherosActivos;
public:
    /**
     * Busca un commit por su  V1
     * @param commi
     * @return
     */
    Commit *getCommit(const std::string &commi);

    /**
     * Constructor de la clase commit
     * @param fich archivo con los ficheros
     * @param commi archivo con los commits
     */
    Gitcode(const std::string &fich, const std::string &commi);

    /**
     * Busca los commits entre dos fechas dadas
     * @param f1 fecha comienzo
     * @param f2 fecha fin
     * @return
     */
    std::vector<Commit *> getCommitFechas(const Fecha &f1, const Fecha &f2);

    /**
     * Busca los commits que tienen en su modificacion un fichero
     * @param nombre nombre del fichero
     * @return
     */
    std::vector<Commit *> getCommitFichero(const std::string &nombre);

    /**
     * Crea e inserta un nuevo commit
     * @param codigo
     * @param texto
     * @param timestamp
     * @param fichAfectados
     */
    void nuevoCommit(const std::string &codigo, const std::string &texto, const Fecha &timestamp,
                     const std::set<std::string> &fichAfectados);

    /**
     * Elimina un commit segun su codigo
     * @param code_commit
     */
    void borrarCommit(const std::string &code_commit);

    /**
     * Numero de ficheros activos
     * @return
     */
    int getNumFicherosActivos();

    /**
     * vector con los fichero que estan activos en este momento
     * @return
     */
    std::vector<Fichero *> getFicherosActivos();

    /**
     * Crea un nuevo fichero
     * @param fichero
     */
    void nuevoFichero(const Fichero &fichero);

    /**
     * Crea varios fichero
     * @param ficherosInsertar
     */
    void nuevoFichero(const std::vector<Fichero> &ficherosInsertar);

    /**
     * Borra un fichero
     * @param nombreFichero
     */
    void borraFichero(const std::string &nombreFichero);

    /**
     * Destructor de la clase
     */
    ~Gitcode();

    unsigned long djb2(unsigned char *str){
        unsigned long hash = 5381;
        int c;
        while(c = *str++) hash= ((hash<<5)+hash)+c;
        return hash;
    }

};


#endif //CPPAPPLICATION_2_GITCODE_H
