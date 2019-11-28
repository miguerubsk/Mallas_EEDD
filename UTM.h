/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UTM.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on 3 de octubre de 2019, 13:58
 */

#ifndef UTM_H
#define UTM_H

#include <math.h>

class UTM {
private:
    double latitud;
    double longitud;
public:

    UTM(double _lat = 0.0, double _long = 0.0) : latitud(_lat), longitud(_long) {
    }

    double GetLongitud() const {
        return longitud;
    }

    double distancia(const UTM &utm) {
        return sqrt(pow(utm.latitud - this->latitud, 2) + pow(utm.longitud - this->longitud, 2));
    }

    double GetLatitud() const {
        return latitud;
    }

};


#endif /* UTM_H */

