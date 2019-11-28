/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Itinerario.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 * 
 * Created on 5 de octubre de 2019, 11:33
 */

#include "Itinerario.h"
#include "Moto.h"

Itinerario::Itinerario(int _id, UTM &_inicio, UTM &_fin, Fecha &_fecha, int _minutos, Moto *_moto) :
id(_id), inicio(_inicio), fin(_fin), fecha(_fecha), minutos(_minutos), vehiculos(_moto) {
}

void Itinerario::SetVehiculos(Moto* vehiculos) {
    this->vehiculos = vehiculos;
}

Moto* Itinerario::GetVehiculos() {
    return vehiculos;
}

Itinerario::Itinerario(const Itinerario& orig) :
id(orig.id), inicio(orig.inicio),
fin(orig.fin), fecha(orig.fecha), minutos(orig.minutos), vehiculos(orig.vehiculos) {
}

Itinerario::~Itinerario() {
}

std::string Itinerario::GuardaItinerario() {
    int dia = fecha.verDia();
    int mes = fecha.verMes();
    int anio = fecha.verAnio();
    int hora = fecha.verHora();
    int min = fecha.verMin();
    std::string lineadatos = std::to_string(id) + ";" + std::to_string(dia) + ";" + std::to_string(mes)
            + ";" + std::to_string(anio) + ";" + std::to_string(hora) + ";" + std::to_string(min)
            + ";" + std::to_string(minutos) + ";" + std::to_string(inicio.GetLatitud())
            + ";" + std::to_string(inicio.GetLongitud()) + ";" + std::to_string(fin.GetLatitud())
            + ";" + std::to_string(fin.GetLongitud()) + ";" + vehiculos->GetId();
    return lineadatos;
}
