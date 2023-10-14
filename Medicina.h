#pragma once
#include "Entidad.h"

class Medicina :public Entidad{
public:
	Medicina(int tipoNiv,Graphics ^ g, Bitmap ^ imgMedic) : Entidad(0,0,1,1) {
		Random^ r = gcnew Random();
		if (tipoNiv == 1) {
			x = r->Next(20, g->VisibleClipBounds.Width - 40);
			y = 610 + r->Next(0, 80);
		}
		else {
			x = r->Next(20, g->VisibleClipBounds.Width - 40);
			y = 610 + r->Next(0, 120);
		}
		ancho = imgMedic->Width;
		alto = imgMedic->Height;
	}
	~Medicina(){}

	void mostrar(Graphics ^g, Bitmap ^ imgMedic) {
		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escala = Rectangle(x, y, ancho/15, alto/15);
		g->DrawImage(imgMedic, escala, porcion, GraphicsUnit::Pixel);
	}
	Rectangle getArea() { return Rectangle(x, y, ancho / 15 - 15 , alto / 15 - 15); }
};