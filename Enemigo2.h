#pragma once
#include "Entidad.h"

class Enemigo2 : public Entidad {
public:
	Enemigo2() : Entidad(1600, 10 + rand() % 120, 0, 0, 11, 11) {
		this->dx = rand() % 6 - 10;
		this->dy = 0;
		//this->dy = (rand() % 21 - 10) / 2;
		this->ancho = 282;
		this->alto = 265;
	}
	~Enemigo2() {}
	
	void disparar() {

	}
};
