#pragma once
#include "Entidad.h"

class Enfermera : public Entidad {
private:

public:
	Enfermera(Graphics^ g) : Entidad(50, 50, 0, 0, 3, 4) {
		x = g->VisibleClipBounds.Width + 50;
		y = g->VisibleClipBounds.Height / 2 + 70;
		dx = 5;
		dy = 0;
		orientacion = Izquierda;
	}
	~Enfermera() {

	}
	//HACER UN CAMBIAR DIRECCION, para que cuando rebote su orientacion cambien y su dx y dy tambien 
	/*void desplazamiento(direccion d) {
		switch (orientacion) {
		case Izquierda:
			indiceY = 1;
			indiceX++;
			if (indiceX == maxindiceX) {
				indiceX = 0;
				indiceY = 1;
			}
			break;
		case Derecha:
			indiceY = 2;
			indiceX++;
			if (indiceX == maxindiceX) {
				indiceX = 0;
				indiceY = 2;
			}
			break;
		case Abajo:
			indiceY = 0;
			indiceX++;
			if (indiceX == maxindiceX) {
				indiceX = 0;
				indiceY = 0;
			}
			break;
		case Arriba:
			indiceY = 3;
			indiceX++;
			if (indiceX == maxindiceX) {
				indiceX = 0;
				indiceY = 3;
			}
			break;
		}
	}*/

	void mostrar(Graphics^ g, Bitmap^ bmpEnfermera) {
		ancho = bmpEnfermera->Width / maxindiceX;
		alto = bmpEnfermera->Height / maxindiceY;
		EscalaAncho = ancho;
		EscalaAlto = alto;
		Rectangle porcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle aumentoBMP = Rectangle(x, y, EscalaAncho, EscalaAlto);
		g->DrawImage(bmpEnfermera, aumentoBMP, porcionAUsar, GraphicsUnit::Pixel);
	}

	/*void restricciones(Graphics^ g) {
		if (x + dx >= 0 && x + dx + EscalaAncho < g->VisibleClipBounds.Width) {
			x += dx;
		}
		if (y + dy >= 0 && y + dy + EscalaAlto < g->VisibleClipBounds.Height) {
			y += dy;
		}
		if (x + dx < 0 || x + dx + EscalaAncho > g->VisibleClipBounds.Width)dx *= -1;
		if (y + dy < 0 || y + dy + EscalaAlto > g->VisibleClipBounds.Height)dy *= -1;


		//int MAX_ALTO = g->VisibleClipBounds.Width;
		//int MAX_ANCHO = g->VisibleClipBounds.Height;
		//y = g->VisibleClipBounds.Height / 2; //Quiere colocar en determinada posicion de Y
		//if (x > 3 * (MAX_ALTO / 4)) {
		//	x -= dx;
		//	orientacion = Izquierda;
		//}
		//else {
		//	if (y > 3 * (MAX_ANCHO / 4)) {
		//		y -= dy;
		//		orientacion = Arriba;
		//	}
		//	else {
		//		if (orientacion == Arriba || orientacion == Izquierda) {
		//			orientacion = Abajo;
		//			indiceX = 0;
		//		}
		//		else {
		//			//direccion = Ninguno;
		//			indiceX = 0;
		//		}
		//		dx = 0;
		//		dy = 0;
		//	}
		//}
	}
	*/
	//Esto se llama para dibujar todo 
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

		/*desplazamiento(orientacion);
		mostrar(g, bmpEnfermera);*/
		//restricciones(g);
	}

};