/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Itinerario.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on 5 de octubre de 2019, 11:33
 */

#ifndef ITINERARIO_H
#define ITINERARIO_H

#include "fecha.h"
#include <cstdlib>
#include "UTM.h"
//#include "Moto.h"
class Moto;
class Itinerario {
public:
    Itinerario(int _id, UTM &_inicio, UTM &_fin, Fecha &_fecha, int _minutos, Moto *moto);
    Itinerario(const Itinerario& orig);
    virtual ~Itinerario();

    Fecha GetFecha() const {
        return fecha;
    }

    void SetFecha(Fecha fecha) {
        this->fecha = fecha;
    }

    UTM GetFin() const {
        return fin;
    }

    void SetFin(UTM fin) {
        this->fin = fin;
    }

    int GetId() const {
        return id;
    }

    void SetId(int id) {
        this->id = id;
    }

    UTM GetInicio() const {
        return inicio;
    }

    void SetInicio(UTM inicio) {
        this->inicio = inicio;
    }

    int GetMinutos() const {
        return minutos;
    }

    void SetMinutos(int minutos) {
        this->minutos = minutos;
    }
    void SetVehiculos(Moto* vehiculos);
    Moto* GetVehiculos();
    std::string GuardaItinerario();

private:

    int id, minutos;
    UTM inicio, fin;
    Fecha fecha;
    Moto *vehiculos;

};

#endif /* ITINERARIO_H */

