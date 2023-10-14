#pragma once
#include "Entidad.h"

class Enfermera : public Entidad {
public:
	Enfermera(int tipoNiv, Graphics^ g) : Entidad(50, 50, 0, 0, 3, 4) {
		x = g->VisibleClipBounds.Width + 50;
		if (tipoNiv == 1)y = g->VisibleClipBounds.Height / 2 + 90;
		else y = g->VisibleClipBounds.Height / 2 + 70;
		dx = 5;
		dy = 0;
		orientacion = Izquierda;

	}
	~Enfermera() {}

	void mostrar(Graphics^ g, Bitmap^ bmpEnfermera) {
		ancho = bmpEnfermera->Width / maxindiceX;
		alto = bmpEnfermera->Height / maxindiceY;
		EscalaAncho = ancho;
		EscalaAlto = alto;
		Rectangle porcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle aumentoBMP = Rectangle(x, y, EscalaAncho, EscalaAlto);
		g->DrawImage(bmpEnfermera, aumentoBMP, porcionAUsar, GraphicsUnit::Pixel);
	}

	void MoverEnfermera(Graphics^ g, Bitmap^ bmpEnfermera) {
		if (x > 3 * (g->VisibleClipBounds.Width / 4)) {
			x -= dx;
			orientacion = Izquierda;
		}
		else {
			if (y > 3 * (g->VisibleClipBounds.Height / 4)) {
				y -= dy; orientacion = Arriba;
			}
			else {
				if (orientacion == Arriba || orientacion == Izquierda) {
					orientacion = Abajo; indiceX = 1;
				}
				else {
					orientacion = Ninguna; indiceX = 1;
				}
				dx = dy = 0;
			}
		}
		switch (orientacion) {
		case Izquierda:
			indiceY = 1;
			if (indiceX >= 0 && indiceX < 2)indiceX++;
			else indiceX = 0;
			break;
		case Derecha:
			indiceY = 2;
			if (indiceX >= 0 && indiceX < 2)indiceX++;
			else indiceX = 0;
			break;
		case Abajo:
			indiceY = 0;
			if (indiceX >= 0 && indiceX < 2)indiceX++;
			else indiceX = 0;
			break;
		case Arriba:
			indiceY = 3;
			if (indiceX >= 0 && indiceX < 2)indiceX++;
			else indiceX = 0;
			break;
		}
		mostrar(g, bmpEnfermera);
	}
};