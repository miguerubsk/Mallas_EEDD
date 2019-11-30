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
public:
    MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
    T buscarCercano(float x, float y);
    bool fueraAmbito(float x, float y);
    unsigned maxElementosPorCelda();
    unsigned mediaElementosPorCelda();
}


#endif /* MALLAREGULAR_H */

