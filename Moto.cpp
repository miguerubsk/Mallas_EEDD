/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Moto.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 * 
 * Created on October 24, 2019, 12:07 PM
 */

#include <iostream>
#include "Moto.h"
#include "Cliente.h"

/**
 * @brief constructor por defecto de moto
 **/
Moto::Moto() : id(""), posicion(0, 0), estado(BLOQUEADA), usadoPor(0) {
    srand(time(NULL));
    porcentajeBateria = 0 + rand() % (100 - 0);
    if (porcentajeBateria < 15) estado = SINBATERIA;
    else estado = BLOQUEADA;
}

void Moto::setEstado(Status estado) {
    this->estado = estado;
}

Status Moto::getEstado() const {
    return estado;
}

void Moto::setUsadoPor(Cliente* usadoPor) {
    this->usadoPor = usadoPor;
}

Cliente* Moto::getUsadoPor() const {
    return usadoPor;
}

void Moto::setPosicion(UTM posicion) {
    this->posicion = posicion;
}

void Moto::setId(std::string id) {
    this->id = id;
}

void Moto::setPorcentajeBateria(float porcentajeBateria) {
    if (porcentajeBateria < 15) {
        this->setEstado(SINBATERIA);
    }
    if (porcentajeBateria >= 0 && porcentajeBateria <= 100) {
        this->porcentajeBateria = porcentajeBateria;
    } else {
        throw std::invalid_argument("Porcentaje de bateria erroneo");
    }

}

float Moto::getPorcentajeBateria() const {
    return porcentajeBateria;
}

/**
 * @brief constructor copia de moto
 * @param orig es la moto de la cual queremos hacer la copia
 **/
Moto::Moto(const Moto& orig) : id(orig.id), usadoPor(orig.usadoPor), estado(orig.estado), posicion(orig.posicion), porcentajeBateria(orig.porcentajeBateria) {
}

/**
 * @brief destructor correpondiente de moto
 **/
Moto::~Moto() {
}

/**
 * @brief funcion get de la posicion
 * @return devuelve la posicion de la moto
 **/
UTM& Moto::getPosicion() {
    return posicion;
}

void Moto::darAviso(){
    switch (estado){
        case BLOQUEADA: usadoPor->mostrarMensaje("BLOQUEADAaaaaa"); break;
        case ACTIVA: usadoPor->mostrarMensaje("ACTIVADaaaA"); break;
        case '2': usadoPor->mostrarMensaje("SIN BATERIA"); break;
        case '3': usadoPor->mostrarMensaje("ROTA"); break;
    }
}

string Moto::mostrarEstado(){
    string aux;
    switch (estado){
        case 0: aux = "BLOQUEADA"; break;
        case 1: aux = "ACTIVADA"; break;
        case 2: aux = "SIN BATERIA"; break;
        case 3: aux = "ROTA"; break;
    }
    return aux;
}

/**
 * @brief funcion get del estado
 * @return devuelve el estado de la moto
 **/
Status& Moto::getStatus() {
    return estado;
}

/**
 * @brief funcion del operador igual para la clase moto
 * @param orig es la moto la cual queremos igualar
 * @return devuelve la moto del resultado de hacer el igual
 **/
Moto& Moto::operator=(const Moto &orig) {
    if (this != &orig) {
        id = orig.id;
        posicion = orig.posicion;
        usadoPor = orig.usadoPor;
        porcentajeBateria = orig.porcentajeBateria;
    }
    return *this;
}

/**
 * @brief funcion del operador menor para la clase moto
 * @param orig es la moto la cual queremos comparar
 * @return devuelve TRUE o FALSE dependiendo si es menor o mayor
 **/
bool Moto::operator<(const Moto &orig) {
    return id < orig.id;
}

/**
 * @brief funcion del operador de comparacion para ordenar las motos
 * @param orig es la moto la cual queremos comparar
 * @return devuelve TRUE o FALSE dependiendo si es la misma o no
 **/
bool Moto::operator==(const Moto &orig) { //para ordenar las motos
    return id == orig.id;
}

/**
 * @brief funcion para activar la moto de un cliente
 * @param cli es un puntero al cliente que vamos a usar para activarle la moto en cuestion
 **/
void Moto::seActiva(Cliente *cli) {
    estado = ACTIVA;
    usadoPor = cli;
}

/**
 * @brief funcion para desactivar la moto de un cliente
 **/
void Moto::seDesactiva() {
    estado = BLOQUEADA;
    usadoPor = 0;
}

std::string Moto::GetId() const {
    return id;
}

Moto::Moto(std::string _id, double _latitud, double _longitud, int _estado, float _porcentajeBateria) :id(_id), posicion(_latitud, _longitud) {
    if (_porcentajeBateria <= 100 && _porcentajeBateria >= 0){
        porcentajeBateria = _porcentajeBateria;
    }else{
        porcentajeBateria = 100;
    }

    
    switch (_estado) {
        case 0: estado = BLOQUEADA;
            break;
        case 1: estado = ACTIVA;
            break;
        case 2: estado = SINBATERIA;
            break;
        case 3: estado = ROTA;
            break;
    }
    if (porcentajeBateria < 15)
        estado = SINBATERIA;
}

