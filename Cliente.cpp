/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on October 27, 2019, 11:14 PM
 */

#include "Cliente.h"
#include "EcoCityMoto.h"
#include "Moto.h"

/**
 * @brief funcion para desbloquear la moto que esta asociada a cliente
 * @param m es la moto en cuestion que queremos desbloquear
 **/
void Cliente::desbloquearMoto(Moto *m) {
    if (m == 0) throw std::string("Cliente::desbloquearMoto: la moto es 0.");
    acceso->desbloqueaMoto(m, this);
    Fecha fecha;
    UTM final;
    acceso->setIdUltimo(acceso->getIdUltimo() + 1);
    Itinerario itinerario(acceso->getIdUltimo(), m->getPosicion(), final, fecha, 0, m);
    rutas.push_back(itinerario);
}

/**
 * @brief funcion añadir un itinerario a un cliente
 * @param id es el id del itinerario a crear
 * @param fecha es la fecha del itinerario
 * @param minutos son los minutos del itinerario
 * @param moto es el puntero a la moto de dicho itinerario
 * @param inicio es la posicion inicial
 * @param fin es la posicion final
 **/
void Cliente::addItinerario(int id, Fecha fecha, int minutos, Moto *moto, UTM inicio, UTM fin) {
    Itinerario it(id, inicio, fin, fecha, minutos, moto);
    rutas.push_back(it);
}

/**
 * @brief funcion para crear los itinerario del cliente
 * @param num es el numero de itinerarios a crear
 * @param IdUltimo es el IdUltimo del itinerario del cliente
 * @param min es la posicion minima posible
 * @param max es la posicion maxima posible
 **/
void Cliente::crearItinerarios(int num, int IdUltimo, const UTM& min, const UTM& max) {
    double lat;
    double longi;
    for (int i = 0; i < num; i++) {
        //GENERAR COORDENADAS RANDOM
        std::mt19937 rnd(std::time(NULL));
        std::uniform_real_distribution<> latitud(min.GetLatitud(), max.GetLatitud());
        std::uniform_real_distribution<> longitud(min.GetLongitud(), max.GetLongitud());
        UTM inicio(latitud(rnd), longitud(rnd));
        UTM fin(latitud(rnd), longitud(rnd));

        //GENERAR FECHA RANDOM
        Fecha fechaRandom;
        srand(time(NULL) + IdUltimo + i);
        int dia = 1 + rand() % (28 - 1);
        int mes = 1 + rand() % (12 - 1);
        int hora = 0 + rand() % (24 - 0);
        int minutos = 0 + rand() % (60 - 0);
        fechaRandom.asignarDia(dia, mes, 2019);
        fechaRandom.asignarHora(hora, minutos);

        Moto* moto = acceso->GetMotoRand();

        int minutosRandom = 0 + rand() % (120 - 0);

        Itinerario itinerarioAux(++IdUltimo, inicio, fin, fechaRandom, minutosRandom, moto);

        rutas.push_back(itinerarioAux);
    }
}

/**
 * @brief funcion de terminar trayecto de cliente para tener un tiempo aleatorio y modificar la bateria de dicha moto
 **/
void Cliente::terminarTrayecto() {
    auto iterador = rutas.begin();
    Fecha fechafin;
    srand(time(NULL));
    int aux = 1 + rand() % ((int) rutas.back().GetVehiculos()->getPorcentajeBateria() - 1);
    rutas.back().SetMinutos(aux);


    rutas.back().SetFin(posicion);
    rutas.back().GetVehiculos()->setPosicion(posicion);
    rutas.back().GetVehiculos()->darAviso();
    rutas.back().GetVehiculos()->seDesactiva();
    rutas.back().GetVehiculos()->setPorcentajeBateria((rutas.back().GetVehiculos()->getPorcentajeBateria()) - (float) aux);
}

/**
 * @brief funcion para buscar la moto mas cercana al cliente en cuestion
 * @return devuelve la moto la cual es la mas cercana del cliente(this)
 **/
Moto * Cliente::buscarMotoCercana() {
    Moto* m = acceso->LocalizaMotoCercana(posicion);
    return m;
}

/**
 * @brief funcion para devolver la lista de itinerarios
 * @return devuelve la lista doblemente enlazada de los itinerarios del cliente
 **/
list<Itinerario>& Cliente::getItinerario() {
    return rutas;
}
//OPERADOR << PARA CLIENTE

/**
 * @brief funcion para el operador << de la clase Cliente
 * @param os ostream &os
 * @param obj const Cliente & obj  
 * @return devuelve el contenido de las variables de cliente
 **/
ostream& operator<<(ostream & os, const Cliente & obj) {
    return os << "DNI: " << obj.GetDNI() << " | " << "Nombre: " << obj.GetNOMBRE() << " | " << "Direccion: " << obj.GetDIRECCION() << " Id del ultimo " << obj.acceso->getIdUltimo() << " | " << "\n";
}

/**
 * @brief funcion para guardar el cliente con sus datos
 * @return devuelve la linea en string de los datos del cliente para guardarlo
 **/
std::string Cliente::GuardaCliente() {
    std::string lineadatos = dni + ";" + pass + ";" + nombre
            + ";" + direccion + ";" + std::to_string(posicion.GetLatitud()) + ";" + std::to_string(posicion.GetLongitud())
            + ";" + std::to_string(rutas.size());
    return lineadatos;
}

string Cliente::getDisplay(){
    return display;
}

/**
 * @brief funcion get para la posicion del clieente
 * @return devuelve el valor de posicion
 **/
UTM Cliente::getPosicion() const {
    return posicion;
}

/**
 * @brief funcion get para el pass del cliente
 * @return devuelve el valor de pass
 **/
string Cliente::getPass() const {
    return pass;
}

void Cliente::mostrarMensaje(string aviso){
    display=aviso;
}