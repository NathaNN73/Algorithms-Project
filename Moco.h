#pragma once
#include "Entidad.h"


class Moco : public Entidad {
public:
	Moco(int x, int y, Bitmap ^ imgMoco) :Entidad(0, 0, 1, 1) {
		ancho = imgMoco->Width / maxindiceX;
		alto = imgMoco->Height / maxindiceY;
		this->x = x;
		this->y = y;
		dx = 0;
		dy = 10 + rand() % 20;
	}
	~Moco() {}
	
	void mostrar(Graphics^ g, Bitmap^ bmp) {
		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escala = Rectangle(x, y, ancho / 4, alto / 4);
		g->DrawImage(bmp, escala, porcion, GraphicsUnit::Pixel);
		x += dx;
		y += dy;
	}
	Rectangle getArea() { return Rectangle(x, y, ancho / 4, alto / 4); }
};