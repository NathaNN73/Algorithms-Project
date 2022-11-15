#pragma once
#include "Entidad.h"

class Enemigo3 : public Entidad {
public:
	Enemigo3() : Entidad(1250, 480 + rand() % 120, 0, 0, 2, 2) {
		this->dx = -5;
		this->dy = 0;
		//this->dy = (rand() % 21 - 10) / 2;
		this->ancho = 176;
		this->alto = 166;
	}
	~Enemigo3() {}
};

