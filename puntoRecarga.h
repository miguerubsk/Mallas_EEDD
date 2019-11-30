/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   puntoRecarga.h
 * Author: Miguerubsk
 *
 * Created on 30 de noviembre de 2019, 11:42
 */

#ifndef PUNTORECARGA_H
#define PUNTORECARGA_H
#include"UTM.h"
#include "EcoCityMoto.h"


class puntoRecarga {
public:
    //Contructor por defecto
    puntoRecarga();
    //Contructor parametrizado
    puntoRecarga(std::string _id, UTM _posicion, EcoCityMoto* _eco);
    //Constructor copia
    puntoRecarga(const puntoRecarga& orig);
    //Getters
    UTM GetPosicion() const;
    std::string GetId() const;
    //Setters
    void SetPosicion(UTM posicion);
    void SetId(std::string id);
    //Destructor
    virtual ~puntoRecarga();
private:
    std::string id;
    UTM posicion;
    EcoCityMoto* eco;
};

#endif /* PUNTORECARGA_H */

