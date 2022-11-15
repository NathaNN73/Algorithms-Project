#pragma once
#include "Entidad.h"
using namespace System::Drawing;
using namespace System;

class Proyectil : public Entidad {
private:
	float pendiente;
	float b;
public:
	Proyectil(int X, int Y, int factor, float pendiente, float b) :Entidad(0, 0, 4, 2) {
		this->x = X;
		this->y = Y;
		this->activo = true;
		this->pendiente = pendiente;
		this->b = b;
		this->dx = 10 * factor;
	}

	~Proyectil(){}

	void mover(Graphics^ g) {
		if (x + dx >= 0 && x + ancho / 9 + dx < g->VisibleClipBounds.Width) {
			x += dx;
			int newY = pendiente * x + b;
			if (newY >= 0 && newY + alto / 9 < g->VisibleClipBounds.Height) y = newY;
			else {
				activo = false;
			}
		}
		else {
			activo = false;
		}
	}
	//SE LLAMA SIMPLEMENTE A ESTO
	void mostrar(Graphics^ g, Bitmap^ bmp) {

		ancho = bmp->Width / maxindiceX;
		alto = bmp->Height / maxindiceY;
		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escala = Rectangle(x, y, ancho / 9 , alto / 9);

		g->DrawImage(bmp, escala, porcion, GraphicsUnit::Pixel);

		indiceX++;
		if (indiceX == maxindiceX) {
			indiceX = 0;
			indiceY++;
			if (indiceY == maxindiceY)indiceY = 0;
		}
		mover(g);
	}
};