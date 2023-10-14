#pragma once
#include "Entidad.h"
#include "Moco.h"

class Enemigo2 : public Entidad {
private:
	vector <Moco*> vecMocos;
public:
	Enemigo2() : Entidad(1550, 130, 0, 0, 11, 11) {
		this->dx = rand() % 6 - 10;
		this->dy = 0;
		this->ancho = 282;
		this->alto = 265;
		this->vecMocos = vector<Moco*>();
	}
	~Enemigo2() {
		for (Moco* mocos : vecMocos) {
			delete mocos;
		}
		vecMocos.clear();
	}

	Rectangle getArea() { return Rectangle(x, y, ancho/3, alto/3); }
	void disparar(Graphics ^ g, Bitmap ^imgMoco) {
		for (int i = 0; i < vecMocos.size(); i++) {
			vecMocos[i]->mostrar(g,imgMoco);
		}
	}
};