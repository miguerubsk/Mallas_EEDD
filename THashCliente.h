/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashCliente.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on November 18, 2019, 4:17 PM
 */

#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include "Cliente.h"
#include <vector>

enum Estado {
    vacia, disponible, ocupada
};

class Entrada {
public:
    Cliente dato;
    long clave;
    std::string dni;
    Estado marca;

    Entrada() : marca(vacia), clave(0), dni(""), dato(Cliente()) {
    }

    ~Entrada() {
    };
};

class THashCliente {
private:
    std::vector<Entrada> v;
    unsigned int tamf, taml, maxcoli, totalColisiones, primorelativo, colisionesultimoinsertado, tipoHash;
    int PrimoPorDebajo(unsigned x);
    bool EsPrimo(unsigned n);

        /**
     * @brief dispersion cuadrática del hash
     **/
    inline unsigned int hash(unsigned long int clave, int i) {
        unsigned long posicionfinal;
        posicionfinal = (clave + (i * i)) % tamf;
        return posicionfinal;
    };

        /**
     * @brief primera dispersion doble del hash
     **/
    inline unsigned int hash2(unsigned long int clave, int i) {
        unsigned long posicion, posicionfinal;
        posicion = clave % tamf;
        posicionfinal = (posicion + (i * (primorelativo - (clave % (primorelativo))))) % tamf;
        return posicionfinal;
    }

        /**
     * @brief segunda dispersion doble del hash
     **/
    unsigned hash3(unsigned clave, int i) {
        unsigned long posicion, posicionfinal;

        posicion = clave % tamf;
        posicionfinal = (posicion + (i * (1 + (clave % (primorelativo))))) % tamf;
        return posicionfinal;
    }

    unsigned long djb2(const unsigned char *str) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++)
            hash = ((hash << 5) + hash) + c;
        return hash;
    }

public:
    THashCliente(int tam, int _tipoHash = 3);
    ~THashCliente();
    bool inserta(const std::string& dni, Cliente &cli);
    bool borra(long int clave);
    bool borracliente(string& dni);
    bool busca(const std::string &dni, Cliente* &cli);
    vector<string> iterar();

    //devuelve el tamaño fisico de la tabla

    unsigned int tamanio() {
        return tamf;
    }

    unsigned int totalClientes() {
        return taml;
    }

    int maxcolisiones() {
        return maxcoli;
    }

    float colisionesMedias() {
        return (float) totalColisiones / taml;
    }

    float carga() {
        return (float) taml / tamf;
    }
    void redispersar(unsigned long tam);
    unsigned int GetColisionesultimoinsertado() const;
};

#endif /* THASHCLIENTE_H */

