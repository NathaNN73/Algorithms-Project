#pragma once
#include "Entidad.h"

class Enemigo3 : public Entidad {
public:
	Enemigo3() : Entidad(1550, 610 + rand() % 120, 0, 0, 2, 2) {
		this->dx = -5;
		this->dy = 0;
		this->ancho = 176;
		this->alto = 166;
	}
	~Enemigo3() {}
	Rectangle getArea() { return Rectangle(x, y, ancho / 2, alto / 2); }
};