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
            EcoCityMoto ecocity(tamas[0], false, 2);
            cout << "Añadir un Cliente en Jaen: " << endl;
            Cliente fernando("26529258T", "Fernando", "aguila", "Calle Caldereros, nº 16", 37.5, 3.5, &ecocity); 
            if (!ecocity.nuevoCliente(fernando))
                throw invalid_argument("Cliente NO insertado: el cliente ya existe o no entro en la Tabla");
            std::cout << "Cliente con id: " << fernando.GetDNI() << " insertado correctamente " << std::endl;
            std::cout << "Cliente con nombre: " << fernando.GetNOMBRE() << std::endl;
            std::cout << "Cliente con latitud: " << fernando.GetUTM().GetLatitud() << std::endl;
            std::cout << "Cliente con longitud: " << fernando.GetUTM().GetLongitud() << std::endl;
            std::cout << "Cliente con direccion: " << fernando.GetDIRECCION() << std::endl;
            
            cout << "--------------------------------------------------" << endl;
            cout << "Localizo dicho Cliente en Jaen: " << endl;
            Cliente *cli = ecocity.buscarCliente("26529258T");
            std::cout << "Cliente: " << cli->GetDNI() << " Situado en: " << cli->GetUTM().GetLatitud() << "," << cli->GetUTM().GetLongitud() << std::endl;
            std::cout << "Nombre: " << cli->GetNOMBRE()<<endl;
            std::cout << "Direccion: " << cli->GetDIRECCION()<<endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Puntos del Cliente despues del Itinerario: " << cli->getPuntos() << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Localizo Moto mas cercana al Cliente: " << endl;
            Moto *moto = cli->buscarMotoCercana();
            std::cout << "Moto mas cercana: " << moto->GetId() << " situada en: " << moto->getPosicion().GetLatitud() << "," << moto->getPosicion().GetLongitud() << std::endl;
            std::cout << "Estado: " << moto->getEstado()<<endl;
            std::cout << "Bateria: " << moto->getPorcentajeBateria()<<endl;
            
            cli->desbloquearMoto(moto);
            //cout<<"Moto usada por: "<<m->getUsadoPor()->GetNOMBRE()<<endl;
            
            std::cout << "Estado: " <<cli->getMiMoto()->mostrarEstado()<<endl;
            ecocity.setIdUltimo(ecocity.getIdUltimo() + 1);

            cout << "--------------------------------------------------" << endl;
            cout << "Motos sin Bateria y no dejadas en Punto de Recarga: " << endl;
            vector<Moto> v = ecocity.localizaMotosSinBateria();
            cout << "Total de Motos sin batería y lejos de un Punto de Recarga: " << v.size() << endl;
            
            cout << "--------------------------------------------------" << endl;
            std::cout << "Comienza Ruta n: " << ecocity.getIdUltimo() << std::endl;
            cli->getMiMoto()->mostrarEstado();
            std::cout << "Desbloqueamos la Moto: " << moto->GetId() << std::endl;
            float auxiliar=moto->getPorcentajeBateria();
            //m->setPorcentajeBateria(14);
            moto->descargarBateria();
            std::cout << "Bateria de la moto antes de cargarla: " << moto->getPorcentajeBateria() << std::endl;
            if (moto->getStatus() == SINBATERIA) {
                cout << "La moto Utilizada quedo sin bateria (Pulsa 1 para recargar o cualquiera para No llevarla): ";
                int dici;
                cin >> dici;
                if (dici == 1) {
                    cout << "el Cliente la lleva a un Punto de recarga" << endl;
                    puntoRecarga p = cli->PuntoRecargaCercano();
                    if (&p != 0) {
                        cli->recargarMoto(p);
                        cout << "Moto Cargada.......hasta 100%" << endl;
                        if (cli->getPuntos() < 10) {
                            cli->incrementarPunto();
                        } else {
                            cout << "No se pueden Incrementar más Puntos ya tienes el MAXIMO" << endl;
                        }
                    } else {
                        cout << "Punto de Recarga NO ENCONTRADO"<<endl;
                    }
                } else {
                    cout << "el Cliente NO la lleva a un Punto de recarga" << endl;
                    cli->decrementarPunto();
                    if (cli->getPuntos() == 0)
                        if (ecocity.eliminarCliente(fernando))
                            cout << "Borrando cliente SIN PUNTOS: " << fernando.GetDNI() << endl;
                }
                cout << "Puntos del Cliente despues del Itinerario: " << cli->getPuntos() << endl;
            }
            std::cout << "Bateria de la moto despues de cargarla: " << moto->getPorcentajeBateria() << std::endl;
            cout << "--------------------------------------------------" << endl;
            cli->terminarTrayecto();
            cli->getMiMoto()->mostrarEstado();

            cout << "Finaliza la  Ruta del Cliente con la Moto: " << endl;
            std::cout << "Fin de la Ruta: " << cli->getItinerario().back().GetFecha().cadena() << ", Minutos: " << cli->getItinerario().back().GetMinutos() << ", Id: " << cli->getItinerario().back().GetVehiculos()->GetId() << ", Pos Fin: " << cli->getItinerario().back().GetFin().GetLatitud() << "<-->" << cli->getItinerario().back().GetFin().GetLongitud() << std::endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Vemos si hay que recargar la moto: " << endl;
            cout << "Bateria de la moto: " <<moto->getPorcentajeBateria() <<endl;
            
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