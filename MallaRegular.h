/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MallaRegular.h
 * Author: Miguel González García y Fernando Jiménez Quesada
 *
 * Created on 30 de noviembre de 2019, 11:40
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H

#include <vector>
#include <list>
#include <iostream>

template<typename Y>
class Casilla;

template <class T>
class MallaRegular {
private:
    float xMin, yMin, xMax, yMax;
    float tamCasillaX, tamCasillaY;
    unsigned taml, NDivx, NDivY;
    std::vector<std::vector<Casilla<T> > > mr;
    Casilla<T> *obtenerCasilla(float x, float y);
public:
    MallaRegular(int aXMin, int aYMin, int aXMax, int aYMax, int nDivX, int nDivY);
    T buscarCercano(float x, float y);
    bool fueraAmbito(float x, float y);
    unsigned maxElementosPorCelda();
    unsigned mediaElementosPorCelda();
    void insertar(float x, float y, const T &dato);
    T *buscarDato(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);
};

template<typename T>
class Casilla {
private:
    std::list<T> puntos;
public:
    friend class MallaRegular<T>;

    Casilla() : puntos() {
    }

    void insertar(const T &dato) {
        puntos.push_back(dato);
    }
    T *buscar(const T &dato);
    bool borrar(const T &dato);
};

template<typename T>
T *Casilla<T>::buscar(const T& dato) {
    typename std::list<T>::iterator it;
    it = puntos.begin();
    while (it != puntos.end()) {
        if (*it == dato)
            return &(*it);
        ++it;
    }
    return 0;
}

template<typename T>
bool Casilla<T>::borrar(const T& dato) {
    typename std::list<T>::iterator it;
    it = puntos.begin();
    while (it != puntos.end()) {
        if (*it == dato) {
            puntos.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

template<typename T>
MallaRegular<T>::MallaRegular(int aXMin, int aYMin, int aXMax, int aYMax, int anDivX, int anDivY) : xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax), NDivY(anDivY), NDivx(anDivX), taml(0) {
    tamCasillaX = (xMax - xMin) / anDivX;
    tamCasillaY = (yMax - yMin) / anDivY;
    mr.insert(mr.begin(), anDivX, std::vector<Casilla<T> >(anDivY, Casilla<T>()));
}

template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamCasillaX;
    int j = (y - yMin) / tamCasillaY;
    return &mr[i][j];
}

template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    c->insertar(dato);
    taml++;
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    taml--;
    return c->borrar(dato);
}

template<typename T>
unsigned MallaRegular<T>::maxElementosPorCelda() {
    unsigned max = 0;
    for (int i = 0; i < mr.size(); ++i) {
        for (int j = 0; j < mr[i].size(); ++j) {
            unsigned aux = obtenerCasilla((float) i, (float) j)->puntos.size();
            if (max < aux) max = aux;
        }
    }
    return max;
}

template<typename T>
unsigned MallaRegular<T>::mediaElementosPorCelda() {
    unsigned total = 0;
    for (int i = 0; i < mr.size(); ++i) {
        for (int j = 0; j < mr[i].size(); ++j) {
            unsigned aux = obtenerCasilla((float) i, (float) j)->puntos.size();
            total += aux;
        }
    }
    return total / NDivY*NDivx;
}

template<typename T>
bool MallaRegular<T>::fueraAmbito(float x, float y) {
    for (float i = x - tamCasillaX; i < x + tamCasillaX; i += tamCasillaX) {
        for (float j = y - tamCasillaY; j < y + tamCasillaY; j += tamCasillaY) {
            if (i >= xMin && i <= xMax && j >= xMin && j <= xMax) {
                Casilla<T> *cl = obtenerCasilla(i, j);
                if (cl->puntos.size() != 0) {
                    typename std::list<T>::iterator it;
                    for (it = cl->puntos.begin(); it != cl->puntos.end(); it++) {
                        if ((*it).GetX() >= x - tamCasillaX && (*it).GetX() <= x + tamCasillaX && (*it).GetY() >= y - tamCasillaY && (*it).GetY() <= y + tamCasillaY)
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

template<typename T>
T MallaRegular<T>::buscarCercano(float x, float y) {
    T cercano;
    double distancia = 99999999;
    Casilla<T> *c1;
    for (float i = x - (tamCasillaX); i < x + (tamCasillaX); i = i + tamCasillaX) {
        for (float j = y - (tamCasillaY); j < y + (tamCasillaY); j = j + tamCasillaY) {
            if (i >= xMin && i <= xMax && j >= yMin && j <= yMax) {
                typename std::list<T>::iterator it;
                c1 = obtenerCasilla(i, j);

                for (it = c1->puntos.begin(); it != c1->puntos.end(); it++) {
                    double d = sqrt(pow((*it).GetX() - x, 2) + pow((*it).GetY() - y, 2));
                    if (d < distancia) {
                        cercano = *it;
                        distancia = d;
                    }
                }
            }
        }
    }
    return cercano;
}

template<typename T>
T *MallaRegular<T>::buscarDato(float x, float y, const T& dato) {
    Casilla<T> *c = obtenerCasilla(x, y);
    return c->buscar(dato);
}

#endif /* MALLAREGULAR_H */

