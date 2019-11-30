/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   puntoRecarga.cpp
 * Author: Miguerubsk
 * 
 * Created on 30 de noviembre de 2019, 11:42
 */

#include "puntoRecarga.h"

//Constructor por defecto
puntoRecarga::puntoRecarga(): posicion() {
    id = "";
    eco = 0;
}

//Construcyotr parametrizado
puntoRecarga::puntoRecarga(std::string _id, UTM _posicion, EcoCityMoto* _eco){
    id = _id;
    posicion = _posicion;
    eco = _eco;
}

//Constructor copia
puntoRecarga::puntoRecarga(const puntoRecarga& orig) {

}

//Destructor
puntoRecarga::~puntoRecarga() {

}

//Getters
std::string puntoRecarga::GetId() const {
    return id;
}

UTM puntoRecarga::GetPosicion() const {
    return posicion;
}

//Setters
void puntoRecarga::SetId(std::string id) {
    this->id = id;
}

void puntoRecarga::SetPosicion(UTM posicion) {
    this->posicion = posicion;
}