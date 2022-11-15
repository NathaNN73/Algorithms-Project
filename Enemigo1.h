#pragma once
#include "Entidad.h"

class Enemigo1 : public Entidad {
public:
    Enemigo1() : Entidad(1, 480 + rand() % 120, 0, 0, 4, 3) {
        this->dx = +5;
        this->dy = 0;
        //this->dy = (rand() % 21 - 10) / 2;
        this->ancho = 280;
        this->alto = 350;
    }
    ~Enemigo1() {}

};
