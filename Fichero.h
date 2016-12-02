//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_FICHERO_H
#define CPPAPPLICATION_2_FICHERO_H

#include <string>

class Fichero {
public:
    const std::string getNombre() const {
        return nombre;
    }

    void setNombre(const std::string &nombre) {
        Fichero::nombre = nombre;
    }

    const std::string getUbicacion() const {
        return ubicacion;
    }

    void setUbicacion(const std::string &ubicacion) {
        Fichero::ubicacion = ubicacion;
    }

    int getTamaBytes() const {
        return tamaBytes;
    }

    void setTamaBytes(int tamaBytes) {
        Fichero::tamaBytes = tamaBytes;
    }

    Fichero(const std::string &nombre, const std::string &ubicacion, int tamaBytes) : nombre(nombre),
                                                                                      ubicacion(ubicacion),
                                                                                      tamaBytes(tamaBytes) {}

    Fichero() {
        nombre = "";
        ubicacion = "";
        tamaBytes = 0;
    }

    bool operator==(const Fichero &orig) {
        return (*this == orig);
    }

    bool operator !=(const Fichero & orig){
        return (*this!=orig);
    }

private:
    std::string nombre;
    std::string ubicacion;
    int tamaBytes;
};


#endif //CPPAPPLICATION_2_FICHERO_H
