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
    int opcion = 0;
    try {
        cout << "1.-Entrenar, 2.- Ejecutar " << endl;
        opcion = 2;
        int tamas[] = {16531, 15937};
        if (opcion == 1) {

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 3; j++) {
                    EcoCityMoto eco(tamas[i], true, j);
                }
            }

        } else {
            cout << "Creando Eco.... Comienzo de lectura de ficheros " << endl;
            EcoCityMoto eco(tamas[0], false, 2);
            cout << "Añadir un Cliente en Jaen: " << endl;
            Cliente cliente("26529258T", "Fernando", "aguila", "Calle Caldereros, nº 16", 37.5, 3.5, &eco); 
            if (!eco.nuevoCliente(cliente))
                throw invalid_argument("Cliente NO insertado: el cliente ya existe o no entro en la Tabla");
            std::cout << "Cliente con id: " << cliente.GetDNI() << " insertado correctamente " << std::endl;
            std::cout << "Cliente con nombre: " << cliente.GetNOMBRE() << std::endl;
            std::cout << "Cliente con latitud: " << cliente.GetUTM().GetLatitud() << std::endl;
            std::cout << "Cliente con longitud: " << cliente.GetUTM().GetLongitud() << std::endl;
            std::cout << "Cliente con direccion: " << cliente.GetDIRECCION() << std::endl;
            
            cout << "--------------------------------------------------" << endl;
            cout << "Localizo dicho Cliente en Jaen: " << endl;
            Cliente *clienteRef = eco.buscarCliente("26529258T");
            std::cout << "Cliente: " << clienteRef->GetDNI() << " Situado en: " << clienteRef->GetUTM().GetLatitud() << "," << clienteRef->GetUTM().GetLongitud() << std::endl;
            std::cout << "Nombre: " << clienteRef->GetNOMBRE()<<endl;
            std::cout << "Direccion: " << clienteRef->GetDIRECCION()<<endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Puntos del Cliente despues del Itinerario: " << clienteRef->getPuntos() << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Localizo Moto mas cercana al Cliente: " << endl;
            Moto *m = clienteRef->buscarMotoCercana();
            std::cout << "Moto mas cercana: " << m->GetId() << " situada en: " << m->getPosicion().GetLatitud() << "," << m->getPosicion().GetLongitud() << std::endl;
            std::cout << "Estado: " << m->getEstado()<<endl;
            std::cout << "Bateria: " << m->getPorcentajeBateria()<<endl;
            
            clienteRef->desbloquearMoto(m);
            //cout<<"Moto usada por: "<<m->getUsadoPor()->GetNOMBRE()<<endl;
            
            std::cout << "Estado: " <<clienteRef->getMiMoto()->mostrarEstado()<<endl;
            eco.setIdUltimo(eco.getIdUltimo() + 1);

            cout << "--------------------------------------------------" << endl;
            cout << "Motos sin Bateria y no dejadas en Punto de Recarga: " << endl;
            vector<Moto> v = eco.localizaMotosSinBateria();
            cout << "Total de Motos sin batería y lejos de un Punto de Recarga: " << v.size() << endl;
            
            cout << "--------------------------------------------------" << endl;
            std::cout << "Comienza Ruta n: " << eco.getIdUltimo() << std::endl;
            clienteRef->getMiMoto()->mostrarEstado();
            std::cout << "Desbloqueamos la Moto: " << m->GetId() << std::endl;
            float auxiliar=m->getPorcentajeBateria();
            //m->setPorcentajeBateria(14);
            m->descargarBateria();
            std::cout << "Bateria de la moto antes de cargarla: " << m->getPorcentajeBateria() << std::endl;
            if (m->getStatus() == SINBATERIA) {
                cout << "La moto Utilizada quedo sin bateria (Pulsa 1 para recargar o cualquiera para No llevarla): ";
                int carga;
                cin >> carga;
                if (carga == 1) {
                    cout << "el Cliente la lleva a un Punto de recarga" << endl;
                    puntoRecarga p = clienteRef->PuntoRecargaCercano();
                    if (&p != 0) {
                        clienteRef->recargarMoto(p);
                        cout << "Moto Cargada.......hasta 100%" << endl;
                        if (clienteRef->getPuntos() < 10) {
                            clienteRef->incrementarPunto();
                        } else {
                            cout << "No se pueden Incrementar más Puntos ya tienes el MAXIMO" << endl;
                        }
                    } else {
                        cout << "Punto de Recarga NO ENCONTRADO"<<endl;
                    }
                } else {
                    cout << "el Cliente NO la lleva a un Punto de recarga" << endl;
                    clienteRef->decrementarPunto();
                    if (clienteRef->getPuntos() == 0)
                        if (eco.eliminarCliente(cliente))
                            cout << "Borrando cliente SIN PUNTOS: " << cliente.GetDNI() << endl;
                }
                cout << "Puntos del Cliente despues del Itinerario: " << clienteRef->getPuntos() << endl;
            }
            std::cout << "Bateria de la moto despues de cargarla: " << m->getPorcentajeBateria() << std::endl;
            cout << "--------------------------------------------------" << endl;
            clienteRef->terminarTrayecto();
            clienteRef->getMiMoto()->mostrarEstado();

            cout << "Finaliza la  Ruta del Cliente con la Moto: " << endl;
            std::cout << "Fin de la Ruta: " << clienteRef->getItinerario().back().GetFecha().cadena() <<
                    ", Minutos: " << clienteRef->getItinerario().back().GetMinutos() <<
                    ", Id: " << clienteRef->getItinerario().back().GetVehiculos()->GetId() <<
                    ", Pos Fin: " << clienteRef->getItinerario().back().GetFin().GetLatitud() << "<-->" <<
                    clienteRef->getItinerario().back().GetFin().GetLongitud() << std::endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Vemos si hay que recargar la moto: " << endl;
            cout << "Bateria de la moto: " <<m->getPorcentajeBateria() <<endl;
            
        }
    } catch (std::string &e) {
        cout << e << endl;
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;

    } catch (ErrorFechaIncorrecta &e) {
        std::cerr << "Fecha Incorrecta" << std::endl;
    }
    return 0;
}