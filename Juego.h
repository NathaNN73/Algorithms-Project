#pragma once
#include "Jugador.h"
#include "VecEnemigos.h"
#include "VecAliados.h"

class Juego {
private:
	Jugador* doctor;
	VecEnemigos* vecEne = new VecEnemigos();
	VecAliados* vecAlia = new VecAliados();
public:
	Juego(Graphics^ g, Bitmap^ imgDoc) {
		doctor = new Jugador(g, imgDoc);
	}

	~Juego() {}

	void Jugar(Graphics^ g, Bitmap^ imgDoc, Bitmap^ imgProyecDoc, Bitmap^ imgEne1, Bitmap^ imgEne2, Bitmap^ imgEne3, Bitmap^ imgFum, Bitmap^ imgEnf) {
		vecAlia->moverAliados(g, imgFum, imgEnf);
		vecEne->moverEnemigos(g, imgEne1, imgEne2, imgEne3);
		doctor->mostrar(g, imgDoc);
		doctor->GestionarBalas(g, imgProyecDoc);
	}
	
	void gestionarDireccionJugador(direccion dir) {
		doctor->desplazamiento(dir);
	}

	void agregarEnemigo(int tipoEnemigo) {
		if (tipoEnemigo == 1) vecEne->agregarEnemigo1();
		else if (tipoEnemigo == 2) vecEne->agregarEnemigo2();
		else if (tipoEnemigo == 3) vecEne->agregarEnemigo3();
	}

	void agregarAliado(Graphics^ g, int tipoAliado) { //1- Fum__ 2 Enf
		if (tipoAliado == 1) vecAlia->agregarFumigador(g);
		else if (tipoAliado == 2) vecAlia->agregarEnfermera(g);
	}

	void agregarBalaJugador(int finalX , int finalY) {
		doctor->AddProyectil(finalX, finalY);
	}
};
