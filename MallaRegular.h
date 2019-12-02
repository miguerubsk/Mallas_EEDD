/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MallaRegular.h
 * Author: Miguerubsk
 *
 * Created on 30 de noviembre de 2019, 11:40
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H

template <class T>
class MallaRegular {
private:
	float xMin, yMin, xMax, yMax;
	float tamCasillaX, tamCasillaY;
	vector<vector<Casilla<T> > > mr;
	Casilla<T> *obtenerCasilla(float x, float y);
public:
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
    T buscarCercano(float x, float y);
    bool fueraAmbito(float x, float y);
    unsigned maxElementosPorCelda();
    unsigned mediaElementosPorCelda();
    void insertar(float x, float y, const T &dato);
 	T *buscar(float x, float y, const T &dato);
 	bool borrar(float x, float y, const T &dato);
};

template<typename Y>
class Casilla{
private:
	list<Y> puntos;
public:
	friend class MallaRegular<Y>;
	Casilla(): puntos() {}
	void insertar(const Y &dato) { puntos.push_back(dato); }
	Y *buscar(const Y &dato);
	bool borrar(const Y &dato);
};

template<typename T>
T *Casilla<T>::buscar(const T& dato) {
	typename list<T>::iterator it;
	it = puntos.begin();
	for (it != puntos.end(); ++it){
		if (*it ==dato)
			return &(*it);
	}
	return 0;
}

template<typename T>
bool Casilla<T>::borrar(const T& dato) {
 	typename list<T>::iterator it;
 	it = puntos.begin();
 	for (;it != puntos.end(); ++it){
 		if (*it == dato) {
 			puntos.erase(it);
 			return true;
 		}
 	}
 	return false;
}

template<typename T>
MallaRegular<T>::MallaRegular(int aXMin, int aYMin, int aXMax, int aYMax, int aNDiv) : xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax){
 	tamCasillaX = (xMax - xMin)/aNDiv;
 	tamCasillaY = (yMax - yMin)/aNDiv;
 	mr.insert(mr.begin(), aNDiv, vector<Casilla<T> >(aNDiv));
}

template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla (float x, float y){
 	int i = (x - xMin) / tamCasillaX;
 	int j = (y - yMin) / tamCasillaY;
 	return &mr[j][i];
}

template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
 	Casilla<T> *c = obtenerCasilla(x,y);
 	c->insertar(dato);
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato){
 	Casilla<T> *c = obtenerCasilla(x,y);
 	return c->borrar(dato);
}

#endif /* MALLAREGULAR_H */

