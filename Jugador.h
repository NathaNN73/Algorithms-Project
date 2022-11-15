#pragma once
#include "Entidad.h"
#include "Proyectil.h"
#include <vector>
using namespace System::Drawing; //Para buffer
using namespace System;


class Jugador :public Entidad {
private:
	int vidas;
	vector<Proyectil*> vecProyec;
public:
	Jugador() {

	}
	Jugador(Graphics^ g, Bitmap^ imgDoc) :Entidad(0, 0, 3, 4) {
		vecProyec = vector<Proyectil*>();
		ancho = imgDoc->Width / maxindiceX;
		alto = imgDoc->Height / maxindiceY;
		Random r;
		x = r.Next(10, g->VisibleClipBounds.Height);
		y = g->VisibleClipBounds.Height / 2 + 180;
		/*x = r->Next(10, g->VisibleClipBounds.Width - 30 );
		y = g->VisibleClipBounds.Height - alto*2;*/
		vidas = 15;

	}
	~Jugador() {
		for (Proyectil* p : vecProyec) {
			delete p;
		}
		this->vecProyec.clear();
	}
	void AddProyectil(int finalX, int finalY) {
		float pendiente = (finalY - this->y - alto / 2) / (1.0 * finalX - this->x - ancho / 2);
		float b = this->y + alto / 2 - pendiente * (this->x + ancho / 2);
		int factor = (finalX > this->x ? 1 : -1);
		vecProyec.push_back(new Proyectil(this->x + ancho / 2, this->y + alto / 2, factor, pendiente, b));
	}

	void GestionarBalas(Graphics^ g, Bitmap^ bmp) {
		for (Proyectil* proyec : vecProyec) {
			proyec->mostrar(g, bmp);
		}

		for (int i = 0; i < vecProyec.size(); ++i) {
			if (vecProyec[i]->getactivo()) continue;
			vecProyec.erase(vecProyec.begin() + i);
		}
	}
	

	void desplazamiento(direccion d) {
		orientacion = d;
		switch (orientacion)
		{
		case Ninguna:
			dx = 0; dy = 0;
			break;
		case Abajo:
			indiceY = 0;
			indiceX++;
			if (indiceX == 3) {
				indiceX = 0;
			}
			dx = 0;
			dy = 20;
			break;
		case Arriba:
			indiceY = 3;
			indiceX++;
			if (indiceX == 3) {
				indiceX = 0;
			}
			dx = 0;
			dy = -20;
			break;
		case Izquierda:
			indiceY = 2;
			indiceX++;
			if (indiceX == 3) {
				indiceX = 0;
			}
			dx = -20;
			dy = 0;
			break;
		case Derecha:
			indiceY = 1;
			indiceX++;
			if (indiceX == 3) {
				indiceX = 0;
			}
			dx = 20;
			dy = 0;
			break;
		}
	}
	void mostrar(Graphics^ g, Bitmap^ bmp) {
		desplazamiento(orientacion);
		dibujarJugador(g, bmp);
	}

	void dibujarJugador(Graphics^ g, Bitmap^ bmp) {

		EscalaAncho = ancho ;
		EscalaAlto = alto ;
		Rectangle area = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle aumento = Rectangle(x, y, EscalaAncho, EscalaAlto);
		g->DrawImage(bmp, aumento, area, GraphicsUnit::Pixel);

		if (x + dx >= 0 && x + dx + EscalaAncho < g->VisibleClipBounds.Width) {
			x += dx;
		}
		if (y + dy >= (g->VisibleClipBounds.Height / 2 + 60) && y + dy + EscalaAlto < g->VisibleClipBounds.Height) {
			y += dy;
		}
	}
	void reducirVidas() {
		this->vidas--;
	}
	int getVidas() {
		return vidas;
	}


};
