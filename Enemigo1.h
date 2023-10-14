#pragma once
#include "Entidad.h"

class Enemigo1 : public Entidad {
public:
    Enemigo1() : Entidad(-100, 450 + rand() % 120, 0, 0, 4, 3) {
        this->dx = 5;
        this->dy = rand() % 7;
        this->ancho = 280;
        this->alto = 350;
    }
    ~Enemigo1() {}

    Rectangle getArea() { return Rectangle(x, y, ancho/3, alto/3); }
	
	void moverE(Graphics^ g, Bitmap^ bmp, float escala_img) {
		if (y + dy < g->VisibleClipBounds.Height / 2 - 60 || y + dy + alto / escala_img > g->VisibleClipBounds.Height - 5) {
			dy *= -1;
		}
		indiceX++;
		if (indiceX == maxindiceX) {
			indiceX = 0;
			indiceY++;
			if (indiceY == maxindiceY)indiceY = 0;
		}
		x += dx;
		y += dy;
		mostrarE(g, bmp, escala_img);
	}
};