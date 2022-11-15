#pragma once
#include <iostream>
#include <conio.h>

using namespace std;
using namespace System;
using namespace System::Drawing;

public enum direccion { Arriba, Abajo, Izquierda, Derecha, Ninguna };

class Entidad {

protected:
	int x, y, dx, dy;
	float ancho, alto;
	int indiceX, indiceY; //indice X = colum , indice y = fila
	int maxindiceX, maxindiceY;
	float EscalaAncho, EscalaAlto;
	//int fila, colum, maxFila, maxColum;
	direccion orientacion;
	bool activo;
public:
	Entidad() {
		dx = 0;
		dy = 0;
		activo = true;
		orientacion = direccion::Ninguna;
	}

	Entidad(int x, int y, int indiceX, int indiceY, int maxindiceX, int maxindiceY) {
		this->x = x;
		this->y = y;
		this->indiceX = indiceX;
		this->indiceY = indiceY;
		this->maxindiceX = maxindiceX;
		this->maxindiceY = maxindiceY;
		orientacion = direccion::Ninguna;
		dx = 0;
		dy = 0;
		activo = true;
	}

	Entidad(int indiceX, int indiceY, int maxindiceX, int maxindiceY) {
		this->indiceX = indiceX;
		this->indiceY = indiceY;
		this->maxindiceX = maxindiceX;
		this->maxindiceY = maxindiceY;

		orientacion = direccion::Ninguna;
		dx = 0;
		dy = 0;
		activo = true;
		indiceX = 0;
		indiceY = 0;
	}

	~Entidad() {}

	virtual void mostrar(Graphics^ g, Bitmap^ bmp) {
		desplazamiento(orientacion);
		ancho = bmp->Width / maxindiceX;
		alto = bmp->Height / maxindiceY;
		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escala = Rectangle(x, y, ancho, alto);

		g->DrawImage(bmp, escala, porcion, GraphicsUnit::Pixel);

		indiceX++;
		if (indiceX == maxindiceX) indiceX = 0;
		mover(g);
	}
	virtual void mover(Graphics^ g) {

		if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
			x += dx;
		if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
			y += dy;
	}

	//MostrarE: Para mostrar a los enemigos
	virtual void mostrarE(Graphics^ g, Bitmap^ bmp, float escala_img) {
		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escala = Rectangle(x, y, ancho / escala_img, alto / escala_img);

		g->DrawImage(bmp, escala, porcion, GraphicsUnit::Pixel);
	}

	//moverE: Para mover a los enemigos
	virtual void moverE(Graphics^ g, Bitmap^ bmp, float escala_img) {

		if (y + dy < 0 || y + dy + alto / escala_img > g->VisibleClipBounds.Height) {
			dy *= -1;
		}
		indiceX++;
		//Condicion solo para el zancudo 2:
		if (indiceX == 9 && indiceY == maxindiceX - 1) { indiceY = 0; }
		//----
		else if (indiceX == maxindiceX) {
			indiceX = 0;
			indiceY++;
			if (indiceY == maxindiceY)indiceY = 0;
		}
		x += dx;
		y += dy;
		mostrarE(g, bmp, escala_img);
	}
	//////////////////////////////////////////////////////
	virtual void desplazamiento(direccion d) {
		dx = 0;
		dy = 0;
		orientacion = d;

		switch (d) {
		case direccion::Arriba:
			dy = -10;
			indiceY = 3;
			break;
		case direccion::Abajo:
			dy = 10;
			indiceY = 0;
			break;
		case direccion::Izquierda:
			dx = -10;
			indiceY = 2;
			break;
		case direccion::Derecha:
			dx = 10;
			indiceY = 1;
		}
	}

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setDx(int dx) { this->dx = dx; }
	void setDy(int dy) { this->dy = dy; }
	void setAncho(int ancho) { this->ancho = ancho; }
	void setAlto(int alto) { this->alto = alto; }
	void setindiceY(int indiceY) { this->indiceY = indiceY; }
	void setindiceX(int indiceX) { this->indiceX = indiceX; }
	void setmaxindiceY(int maxindiceY) { this->maxindiceY = maxindiceY; }
	void setmaxIndiceX(int maxindiceX) { this->maxindiceX = maxindiceX; }
	void setActivo(bool estado) { this->activo = estado; }
	void setOrientacion(direccion d) { this->orientacion = d; }


	int getX() { return this->x; }
	int getY() { return this->y; }
	int getDx() { return this->dx; }
	int getDy() { return this->dy; }
	int getAncho() { return this->ancho; }
	int getAlto() { return this->alto; }
	int getindiceY() { return this->indiceY; }
	int getindiceX() { return this->indiceX; }
	int getmaxindiceY() { return this->maxindiceY; }
	int getmaxIndiceX() { return this->maxindiceX; }
	bool getactivo() { return this->activo; }
	direccion getOrientacion() { return this->orientacion; }
	Rectangle getArea() { return Rectangle(x, y, ancho, alto); }
	Rectangle getNextArea() { return Rectangle(x + dx, y + dy, ancho, alto); }
};


