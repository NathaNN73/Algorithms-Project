#pragma once
#include "Entidad.h"
#include "Proyectil.h"
#include <vector>

class Jugador :public Entidad {
private:
	int vidas;
	int CantidadBalas;
	int CantidadMedicinasRecol;
	int EnemigosEliminados;
	vector<Proyectil*> vecProyec;
public:
	Jugador(Graphics^ g, Bitmap^ imgDoc) :Entidad(0, 0, 3, 4) {
		vecProyec = vector<Proyectil*>();
		ancho = imgDoc->Width / maxindiceX;
		alto = imgDoc->Height / maxindiceY;
		Random r;
		x = r.Next(10, g->VisibleClipBounds.Height);
		y = g->VisibleClipBounds.Height / 2 + 180;
		vidas = 15;
		CantidadBalas = 50;
		CantidadMedicinasRecol = 0;
		EnemigosEliminados = 0;
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
		int factor = (finalX > this->x ? 1 : -1); //Dirección
		vecProyec.push_back(new Proyectil(this->x + ancho / 2, this->y + alto / 2, factor, pendiente, b));
	} //dy = m dx + b  m= y2 - y1/ x2 - x1  b = y - m x

	vector<Proyectil*> getVectorProyec() {
		return this->vecProyec;
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
	
	void RestarBalas() {CantidadBalas--;}
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
	void mostrar(Graphics^ g, Bitmap^ bmp,int tipoNiv) {
		desplazamiento(orientacion);
		dibujarJugador(g, bmp,tipoNiv);
	}
	void dibujarJugador(Graphics^ g, Bitmap^ bmp, int tipoNiv) {
		EscalaAncho = ancho ;
		EscalaAlto = alto ;
		Rectangle area = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle aumento = Rectangle(x, y, EscalaAncho, EscalaAlto);
		g->DrawImage(bmp, aumento, area, GraphicsUnit::Pixel);
		if (tipoNiv == 1) {
			if (x + dx >= 0 && x + dx + EscalaAncho < g->VisibleClipBounds.Width) {
				x += dx;
			}
			if (y + dy >= (g->VisibleClipBounds.Height / 2 + 100) && y + dy + EscalaAlto < g->VisibleClipBounds.Height - 30) {
				y += dy;
			}
		}
		else {
			if (x + dx >= 0 && x + dx + EscalaAncho < g->VisibleClipBounds.Width) {
				x += dx;
			}
			if (y + dy >= (g->VisibleClipBounds.Height / 2 + 80) && y + dy + EscalaAlto < g->VisibleClipBounds.Height - 20) {
				y += dy;
			}
		}
	}

	Rectangle getArea() { return Rectangle(x , y , ancho, alto); }
	void reducirVidas() {this->vidas--;}
	int getVidas() {return vidas;}
	int getMaxBalas() {return CantidadBalas;}
	void setBalas(int balas) { CantidadBalas += balas; }
	void setMedicinasRecolectadas(int aumentoMedicinas) {this->CantidadMedicinasRecol += aumentoMedicinas;}
	int getMedicinasRecolectadas() {return this->CantidadMedicinasRecol;}
	void setVidas(int vidas) {this->vidas += vidas;}
	void setEnemigosEli(int eneeli) {EnemigosEliminados += eneeli;}
	int getEnemigosEli() { return EnemigosEliminados; }
};
