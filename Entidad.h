#pragma once
#include <iostream>

using namespace std;
using namespace System;
using namespace System::Drawing;

public enum direccion { Arriba, Abajo, Izquierda, Derecha, Ninguna };

class Entidad {
protected:
	int x, y, dx, dy;
	float ancho, alto;
	int indiceX, indiceY; 
	int maxindiceX, maxindiceY;
	float EscalaAncho, EscalaAlto;
	direccion orientacion;
	bool activo;
public:
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
	}

	~Entidad() {}

	virtual void mostrar(Graphics^ g, Bitmap^ bmp) {}
	virtual void mover(Graphics^ g) {}
	
	virtual void mostrarE(Graphics^ g, Bitmap^ bmp, float escala_img) {
		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escala = Rectangle(x, y, ancho / escala_img, alto / escala_img);
		g->DrawImage(bmp, escala, porcion, GraphicsUnit::Pixel);
	}
	virtual void moverE(Graphics^ g, Bitmap^ bmp, float escala_img) {
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
	
	virtual void desplazamiento(direccion d) {}

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setDx(int dx) { this->dx = dx; }
	void setDy(int dy) { this->dy = dy; }
	void setAncho(int ancho) { this->ancho = ancho; }
	void setAlto(int alto) { this->alto = alto; }
	void setActivo(bool estado) { this->activo = estado; }

	int getX() { return this->x; }
	int getY() { return this->y; }
	int getDx() { return this->dx; }
	int getDy() { return this->dy; }
	int getAncho() { return this->ancho; }
	int getAlto() { return this->alto; }
	int getindiceY() { return this->indiceY; }
	int getindiceX() { return this->indiceX; }
	bool getactivo() { return this->activo; }
	virtual Rectangle getArea() { return Rectangle(x, y, ancho, alto); }
};


