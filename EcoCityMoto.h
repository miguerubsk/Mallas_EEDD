/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EcoCityMoto.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on October 24, 2019, 12:07 PM
 */

#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include <vector>
#include "THashCliente.h"
#include "Moto.h"
#include <random>
#include "Cliente.h"
#include "PuntoRecarga.h"
#include "MallaRegular.h"

class Cliente;

class puntoRecarga;

class EcoCityMoto {
public:
    EcoCityMoto();
    EcoCityMoto(int tam, bool entrena, int tipoHash);
    EcoCityMoto(const EcoCityMoto& orig);
    virtual ~EcoCityMoto();
    Moto* LocalizaMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);
    unsigned int getIdUltimo() const;
    THashCliente& getClientes();
    void setIdUltimo(unsigned int idUltimo);
    Cliente* buscarCliente(std::string dni);
    bool nuevoCliente(Cliente &c);
    bool eliminarCliente(Cliente &c);
    std::vector<Moto>* GetMotos();
    std::vector<Moto> localizaMotosSinBateria();
    Moto* GetMotoRand();
    THashCliente GetClientes() const;
    void borrarMilCientes();
    void redispersarTabla();
    puntoRecarga PuntoCercano(Cliente *cli);


private:

    unsigned int idUltimo;
    bool entrena;
    std::vector<Moto> motos;
    THashCliente clientes;
    MallaRegular<puntoRecarga> puntosRecarga;
    vector<string> getDNIClientes();
//    THashCliente clientesTHash;

    void cargarClientes(std::string filename);
    void cargarMotos(std::string filename);
    void guardaClientesItinerarios(std::string fileName);
    void crearPuntosRecarga();
//    void guardaClientesItinerariosHash(std::string fileName);
    void guardarMotos(string fileName);
};

#endif /* ECOCITYMOTO_H */

