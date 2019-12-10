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
puntoRecarga::puntoRecarga() : posicion() {
    id = "";
}

//Construcyotr parametrizado
puntoRecarga::puntoRecarga(std::string _id, UTM _posicion) {
    id = _id;
    posicion = _posicion;
}

//Constructor copia
puntoRecarga::puntoRecarga(const puntoRecarga& orig) {
    id = orig.id;
    posicion = orig.posicion;
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

float puntoRecarga::GetX() const {
    return (float)posicion.GetLatitud();
}

float puntoRecarga::GetY() const {
    return (float)posicion.GetLongitud();
}

//Setters
void puntoRecarga::SetId(std::string id) {
    this->id = id;
}

void puntoRecarga::SetPosicion(UTM posicion) {
    this->posicion = posicion;
}

//Operador =
puntoRecarga& puntoRecarga::operator=(const puntoRecarga& orig) {
    if (this != &orig) {
        id = orig.id;
        posicion = orig.posicion;
    }
    return *this;
}

bool puntoRecarga::operator ==(const puntoRecarga& orig){
    if (id == orig.id && posicion == orig.posicion)
        return true;
    return false;
}