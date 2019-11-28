/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on 19 de septiembre de 2019, 13:07
 */
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <ctime>
#include "Cliente.h"
#include "EcoCityMoto.h"
#include "Moto.h"


using namespace std;

double calculardistaciamaslejana(vector<Cliente> v) {
    double distancia, maxDistancia = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            distancia = v[i].distancia(v[j]);

            if (distancia > maxDistancia)
                maxDistancia = distancia;
        }
    }
    return maxDistancia;
}

void MaxMinLatLon(vector<Cliente> v, double &maxLon, double &maxLat, double &minLon, double &minLat) {
    maxLon = -9999999, maxLat = -9999999, minLon = 9999999, minLat = 9999999;
    for (int i = 0; i < v.size(); i++) {
        double x = v[i].GetUTM().GetLongitud();
        if (x > maxLon)
            maxLon = x;
        else
            if (x < minLon)
            minLon = x;
        x = v[i].GetUTM().GetLatitud();
        if (x > maxLat)
            maxLat = x;
        else
            if (x < minLat)
            minLat = x;

    }
}

void menu() {
    cout << "========================MENÚ========================" << endl;
    cout << "1 - Entrenamiento" << endl;
    cout << "2 - Ejecución" << endl;
    cout << "====================================================" << endl;
    cout << "Elegir opcion: ";
}

int main(int argc, char** argv) {
    int opcion=0;
    try {
        menu();
        cin >> opcion;
        if (opcion == 1) {
            cout << "Entrenando...." << endl;
            int tams[] = {15737, 16573, 16063, 16747};
            for (int i = 0; i < 4; ++i) {
                for (int j = 1; j <= 3; ++j) {
                    EcoCityMoto entrenaEco(tams[i], true, j);
                    cout << "==================================================================" << endl;
                    cout << "Probando tamaño: " << tams[i] << endl;
                    cout << "Usando función hash número " << j << endl;
                    cout << "Factor de carga de la tabla Hash: " << entrenaEco.GetClientes().carga() << endl;
                    cout << "Promedio de colisiones de la tabla Hash: " << entrenaEco.GetClientes().colisionesMedias() << endl;
                    cout << "Máximo de colisiones: " << entrenaEco.GetClientes().maxcolisiones() << endl;
                }
            }
        } else {
            //Creamos estructura y se cargan clientes y motos dentro
            EcoCityMoto pruebaEco;
            cout << "Factor de carga de la tablaHash: " << pruebaEco.GetClientes().carga() << endl;
            cout << "Promedio de colisiones de la tabla hash: " << pruebaEco.GetClientes().colisionesMedias() << endl;
            cout << "Máximo de colisiones: " << pruebaEco.GetClientes().maxcolisiones() << endl;
            //Buscamos un cliente, una moto, la utiliza y la deja
            Cliente ejemplo("77556358J", "miguel", "Miguerubsk", "Jaen", 37.3, 38.4, &pruebaEco);
            if (pruebaEco.nuevoCliente(ejemplo)) {
                cout << "-----SE HA AÑADIDO EL CLIENTE-----" << endl;
                cout << "DNI: " << ejemplo.GetDNI() << endl;
                cout << "Nombre: " << ejemplo.GetNOMBRE() << endl;
                cout << "Latitud: " << ejemplo.GetUTM().GetLatitud() << endl;
                cout << "Longitud: " << ejemplo.GetUTM().GetLongitud() << endl;
                cout << "Nº colisiones al insertar: " << pruebaEco.GetClientes().GetColisionesultimoinsertado() << endl;
                cout << "---------------------------------" << endl;
            } else {
                cout << "-----NO SE HA AÑADIDO EL CLIENTE-----" << endl;
            }

            Cliente *clienteRef = pruebaEco.buscarCliente(ejemplo.GetDNI());
            cout << "Cliente: " << clienteRef->GetDNI() << " Situado en: " <<
                    clienteRef->GetUTM().GetLatitud() << "," <<
                    clienteRef->GetUTM().GetLongitud() << std::endl;
            Moto *m = clienteRef->buscarMotoCercana();
            cout << "Moto mas cercana: " << m->GetId() << " situada en: " <<
                    m->getPosicion().GetLatitud() << "," << m->getPosicion().GetLongitud() << std::endl;

            clienteRef->desbloquearMoto(m);
            cout << "Comienza Ruta n: " << pruebaEco.getIdUltimo() << std::endl;
            std::vector<Moto> probar;
            probar = pruebaEco.localizaMotosSinBateria();
            cout << "Hay " << probar.size() << " motos sin bateria." << endl;

            clienteRef = pruebaEco.buscarCliente("77556358J");
            if (clienteRef->GetDNI() == "77556358J") {
                cout << "----------------------------ENCONTRADO----------------------------" << endl;
                cout << "DNI: " << clienteRef->GetDNI() << endl;
                cout << "Nombre: " << clienteRef->GetNOMBRE() << endl;
                cout << "Latitud: " << clienteRef->GetUTM().GetLatitud() << endl;
                cout << "Longitud: " << clienteRef->GetUTM().GetLongitud() << endl;
                cout << "------------------------------------------------------------------" << endl;
            } else {
                cout << "NO ESTA EL CLIENTE: " << endl;
            }
            Moto *aux;
            aux = ejemplo.buscarMotoCercana();
            ejemplo.desbloquearMoto(aux);
            cout << "-------------------------------MOTO-------------------------------" << endl;
            cout << "Matricula: " << aux->GetId() << endl;
            cout << "Estado: " << aux->mostrarEstado() << endl;
            cout << "Latitud: " << aux->getPosicion().GetLatitud() << endl;
            cout << "Longitud: " << aux->getPosicion().GetLongitud() << endl;
            cout << "Usado por: " << aux->getUsadoPor()->GetNOMBRE() << endl;
            cout << "------------------------------------------------------------------" << endl;
            ejemplo.mostrarMensaje(to_string(aux->getEstado()));
            cout << "Display inicial de la moto: " << ejemplo.getDisplay() << endl;
            cout << "PORCENTAJE BATERIA inicial de la moto: " << ejemplo.getItinerario().back().GetVehiculos()->getPorcentajeBateria() << endl;
            cout << "ESTADO inicial de la moto: " << ejemplo.getItinerario().back().GetVehiculos()->mostrarEstado() << endl;
            cout << "------------------------------------------------------------------" << endl;
            ejemplo.terminarTrayecto();
            cout << "----------------------TERMINARTRAYECTO----------------------------" << endl;
            cout << "------------------------------------------------------------------" << endl;
            ejemplo.mostrarMensaje(to_string(aux->getEstado()));
            cout << "Display final de la moto: " << ejemplo.getDisplay() << endl;
            cout << "PORCENTAJE BATERIA final de la moto: " << ejemplo.getItinerario().back().GetVehiculos()->getPorcentajeBateria() << endl;
            cout << "ESTADO final de la moto: " << ejemplo.getItinerario().back().GetVehiculos()->mostrarEstado() << endl;

            vector<Moto> v = pruebaEco.localizaMotosSinBateria();
            
            cout << "------------------------------------------------------------------" << endl;
            if (pruebaEco.eliminarCliente(ejemplo))
                cout << "Borrando cliente: " << ejemplo.GetDNI() << endl;
            if (!pruebaEco.nuevoCliente(ejemplo))
                throw invalid_argument("Cliente NO insertado: el cliente ya existe o no entro en la Tabla");
            cout << "Cliente con id: " << ejemplo.GetDNI() << " insertado correctamente" << std::endl;

            pruebaEco.borrarMilCientes();
            pruebaEco.redispersarTabla();
        }
    } catch (std::string &e) {
        cout << e << endl;
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;

    } catch (ErrorFechaIncorrecta &e) {
        std::cerr << "Fecha Incorrecta: " << std::endl;
    }
    return 0;
}
