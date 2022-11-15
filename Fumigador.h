#pragma once
#include "Entidad.h"

class Fumigador : public Entidad {
private:

public:
	Fumigador(Graphics^ g) : Entidad(50, 50, 0, 0, 3, 4) {
		x = -150;
		y = g->VisibleClipBounds.Height / 2 + 70;
		dx = 5;
		dy = 0;
		orientacion = Derecha;
	}
	~Fumigador() {

	}


	void mostrar(Graphics^ g, Bitmap^ bmpFumigador) {
		ancho = bmpFumigador->Width / maxindiceX;
		alto = bmpFumigador->Height / maxindiceY;
		EscalaAncho = ancho;
		EscalaAlto = alto;
		Rectangle porcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle aumentoBMP = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmpFumigador, aumentoBMP, porcionAUsar, GraphicsUnit::Pixel);
	}

	//Esto se llama para dibujar todo 
	void MoverFumigador(Graphics^ g, Bitmap^ bmpFumigador) {
		if (x + EscalaAncho < (g->VisibleClipBounds.Width / 4)) {
			x += dx;
			orientacion = Derecha;
		}
		else {
			if (y > 3 * (g->VisibleClipBounds.Height / 4)) {
				y -= dy; orientacion = Arriba;
			}
			else {
				if (orientacion == Arriba || orientacion == Derecha) {
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
		mostrar(g, bmpFumigador);

		/*desplazamiento(orientacion);
		mostrar(g, bmpEnfermera);*/
		//restricciones(g);
	}

};

