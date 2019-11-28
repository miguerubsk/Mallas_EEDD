/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashCliente.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 * 
 * Created on November 18, 2019, 4:17 PM
 */

#include "THashCliente.h"

/**
 * @brief constructor de la tabla hash
 * @param A tamaño de la tabla hash por defecto=0
 * @param B tipo del hash que vamos a utilizar cuando entrenamos la tabla hash
 **/
THashCliente::THashCliente(int tam = 0, int _tipoHash) : v(tam, Entrada()) {
    tamf = tam;
    primorelativo = PrimoPorDebajo(tam);
    taml = 0;
    maxcoli = 0;
    totalColisiones = 0;
    colisionesultimoinsertado = 0;
    Cliente();
    tipoHash = _tipoHash;
}

/**
 * @brief destructor de la tabla hash
 **/
THashCliente::~THashCliente() {
}

/**
 * @brief funcion para desplazarse por la tabla y por cada hueco ocupado lo añade a un vector
 * @return devuelve el vector con los datos del DNI de los clientes
 **/
vector<string> THashCliente::iterar() {
    vector<string> aux;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i].marca == ocupada) {
            aux.push_back(v[i].dato.GetDNI());
        }
    }
    return aux;
}

/**
 * @brief funcion para pider insertar un cliente en a tabla hash
 * @param A es el DNI que estamos insertando del cliente en cuestion
 * @param B es el cliente que queremos insertar en la tabla
 * @return devuelve versdadero o falso si lo inserta o no en la tabla
 **/
bool THashCliente::inserta(const std::string& dni, Cliente &cli) {
    unsigned i = 0, y;
    int p = -1, final;
    bool encontrado = false, aux = false;
    unsigned long clave = djb2((unsigned char*) dni.c_str());

    while (!encontrado) {
        switch (tipoHash) {
            case 1: y = hash(clave, i); break;
            case 2: y = hash2(clave, i); break;
            case 3: y = hash3(clave, i); break;
        }
        if (v[y].marca == vacia) {
            if (p == -1)
                final = y;
            else
                final = p;
            taml++;
            v[final].dni = dni;
            v[final].marca = ocupada;
            v[final].clave = clave;
            v[final].dato = cli;
            encontrado = true;
            colisionesultimoinsertado = i;

        } else {
            if (v[y].marca == disponible && aux == false) {
                p = y;
                aux = true;
            } else
                if (v[y].dato.GetDNI() == dni)
                return false;
            ++i;
        }
    }
    if (i > maxcoli) {
        maxcoli = i;
    }

    totalColisiones += i;

    return encontrado;
};

/**
 * @brief funcion para borrar un dato/cliente en cuestion y quitarlo de la tabla hash
 * @param A es la clave del dato a buscar y borrar
 * @return devuelve versdadero o falso si lo borra o no en la tabla
 **/
bool THashCliente::borra(long int clave) {
    unsigned x, i = 0;
    bool borrado = false;
    while (!borrado) {
        x = hash2(clave, i);
        //si no esta ocupada por su termino, mira si esta libre para dejar de buscar
        if (v[x].marca == ocupada) {
            v[x].marca = disponible; //lo borro y la dejo marcada
            v.clear();
            borrado = true;
            taml--;
        } else {
            if (v[x].marca == vacia)
                break;
            else
                ++i; //No he dado aun con su posicion
        }//No he dado aun con su posicion
    }
    return borrado;
};

/**
 * @brief funcion para borrar un cliente en cuestion y quitarlo de la tabla hash
 * @param A es el dni del cliente a borrar
 * @return devuelve versdadero o falso si lo borra o no en la tabla
 **/
bool THashCliente::borracliente(string& dni) {
    int intento = 0;
    unsigned long int clave;
    do {
        clave = hash(djb2((unsigned char*) dni.c_str()), intento);
        if (v[clave].marca == vacia) {
            return false;
        } else {
            if (v[clave].marca == ocupada && v[clave].dato.GetDNI() == dni) {
                v[clave].marca = disponible;
                taml--;
                return true;
            }
        }
        intento++;

    } while (v[clave].marca != vacia);
    return false;
}

/**
 * @brief funcion para buscar un cliente dado en la tabla hash
 * @param A es el DNI que estamos buscando del cliente en cuestion
 * @param B es el cliente que queremos que devuelva al buscarlo en la tabla
 * @return devuelve versdadero o falso si lo encuentra o no en la tabla
 **/
bool THashCliente::busca(const std::string& dni, Cliente* &cli) {
    unsigned i = 0, x;
    bool esta = false;
    unsigned long clave = djb2((unsigned char*) dni.c_str());
    while (!esta) {
        x = hash2(clave, i);
        if (v[x].marca == ocupada) {
            cli = &(v[x].dato);
            return &(v[x].dato);
        } else {
            if (v[x].marca == vacia) {
                cli = &(v[x].dato);
                esta = true;

            } else {
                i++;
            }//no estaba en esa posicion y aumenta un aumento
        }

    }
    return 0; //no encontrado
};

/**
 * @brief funcion para saber si un numero es primo o no
 * @param A es el numero el cual queremos saber si es primo
 * @return devuelve versdadero o falso si es primo o no
 **/
bool THashCliente::EsPrimo(unsigned n) {
    float x = sqrt(n);
    for (int i = 2; i < x; ++i)
        if (n % i == 0)
            return false;
    return true;
}

/**
 * @brief funcion para sacar el numero primo por debajo de uno dado
 * @param A es el numero en cuestion queremos calcular el primo por debajo
 * @return devuelve el numero primo en cuestion
 **/
int THashCliente::PrimoPorDebajo(unsigned x) {
    x = x - 1;
    while (!EsPrimo(x)) {
        --x;
    }
    return x;
}

/**
 * @brief funcion para redispersar la tabla hash
 * @param A es el tamaño de la tabla hash antes de redispersar
 **/
void THashCliente::redispersar(unsigned long tam) {
    vector<Entrada> aux(tam, Entrada());
    tamf = tam;
    totalColisiones = 0;
    primorelativo = PrimoPorDebajo(tamf);
    for (int i = 0; i < v.size(); i++) {
        unsigned intento = 0, y;
        bool encontrado = false;
        if (v[i].marca == ocupada) {
            //unsigned long clave=djb2((unsigned char*)tabla[i].dni.c_str());
            while (!encontrado) {
                y = hash2(v[i].clave, intento);
                if (aux[y].marca == vacia || aux[y].marca == disponible) {
                    aux[y].dni = v[i].dni;
                    aux[y].marca = ocupada;
                    aux[y].clave = v[i].clave;
                    aux[y].dato = v[i].dato; //push_back(dato);                                                
                    encontrado = true; //Encontre un sitio libre  
                } else

                    ++intento; //No he dado aun con una posicion libre
            }
            totalColisiones += intento;
            if (!encontrado)
                cout << " Cliente no insertado: " << v[i].dni << endl;
        }
    }
    v = aux;
}

/**
 * @brief funcion get de la variable colisionesultimoinsertado
 * @return devuelve una variable de la clase tabla hash
 **/
unsigned int THashCliente::GetColisionesultimoinsertado() const {
    return colisionesultimoinsertado;
}