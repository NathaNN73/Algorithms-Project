#pragma once
#include "Jugador.h"
#include "VecEnemigos.h"
#include "VecAliados.h"
#include "Medicina.h"

class Juego {
private:
	Jugador* doctor;
	VecEnemigos* vecEne = new VecEnemigos();
	VecAliados* vecAlia = new VecAliados();
	vector<Medicina*>vecMedic;
	time_t tiempoMedicina;
	time_t tiempoEnemigo1;
	time_t tiempoEnemigo2;
	time_t tiempoEnemigo3;

	int tipoNivel; //1-Normal - 2 Avanzado
	int RegEnemigo1;
	int RegEnemigo2;
	int RegEnemigo3;
public:
	Juego(int tipoNiv, Graphics^ g, Bitmap^ imgDoc, int regEne1, int regEne2, int regEne3) {
		tiempoMedicina = time(0);
		tiempoEnemigo1 = time(0);
		tiempoEnemigo2 = time(0);
		tiempoEnemigo3 = time(0);
		doctor = new Jugador(g, imgDoc);
		RegEnemigo1	 = regEne1;
		RegEnemigo2 = regEne2;
		RegEnemigo3 = regEne3;
		tipoNivel = tipoNiv;
	}

	~Juego() {
		delete doctor;
		delete vecEne;
		delete vecAlia;
		for (Medicina* medic : vecMedic) {
			delete medic;
		}
		vecMedic.clear();
	}

	void Jugar(Graphics^ g, Bitmap^ imgDoc, Bitmap^ imgProyecDoc, Bitmap^ imgEne1, Bitmap^ imgEne2, Bitmap^ imgEne3, Bitmap^ imgFum, Bitmap^ imgEnf, Bitmap ^ imgMedic, Bitmap^ imgMoco) {
		DibujarPanelesArriba(g);
		vecAlia->moverAliados(g, imgFum, imgEnf);
		agregarEnemigosTiempo();
		vecEne->moverEnemigos(g, imgEne1, imgEne2, imgEne3, imgMoco);
		doctor->mostrar(g, imgDoc,tipoNivel);
		doctor->GestionarBalas(g, imgProyecDoc);
		AparecerMedicinas(g, imgMedic);
		Colisiones();
	}

	void DibujarPanelesArriba(Graphics^ g) {
		if (tipoNivel == 1) {
			g->DrawString(Convert::ToString(doctor->getVidas()), gcnew Font("Impact", 20), Brushes::Black, 130, 55);
			g->DrawString(Convert::ToString(doctor->getMedicinasRecolectadas()) + "/ 15", gcnew Font("Impact", 20), Brushes::Black, 320, 55);
			g->DrawString(Convert::ToString(doctor->getMaxBalas()), gcnew Font("Impact", 20), Brushes::Black, 1410, 55);
			g->DrawString(Convert::ToString(doctor->getEnemigosEli()) + "/ 30", gcnew Font("Impact", 20), Brushes::Black, 1200, 55);
		}
		else {
			g->DrawString(Convert::ToString(doctor->getVidas()), gcnew Font("Impact", 20), Brushes::Black, 140, 50);
			g->DrawString(Convert::ToString(doctor->getMedicinasRecolectadas()) + "/ 25", gcnew Font("Impact", 20), Brushes::Black, 320, 50);
			g->DrawString(Convert::ToString(doctor->getMaxBalas()), gcnew Font("Impact", 20), Brushes::Black, 1420, 50);
			g->DrawString(Convert::ToString(doctor->getEnemigosEli()) + "/ 50", gcnew Font("Impact", 20), Brushes::Black, 1205, 50);
		}
	}
	void agregarEnemigosTiempo() {
		if (difftime(time(0), tiempoEnemigo2) >= RegEnemigo2) {
			vecEne->agregarEnemigo2();
			tiempoEnemigo2 = time(0);
		}
		if (difftime(time(0), tiempoEnemigo1) >= RegEnemigo2) {
			vecEne->agregarEnemigo1();
			tiempoEnemigo1 = time(0);
		}
		if (difftime(time(0), tiempoEnemigo3) >= RegEnemigo3) {
			vecEne->agregarEnemigo3();
			tiempoEnemigo3 = time(0);
		}
	}
	void AparecerMedicinas(Graphics^ g, Bitmap^ imgMedic) {
		if (difftime(time(0), tiempoMedicina) > 4) {
			vecMedic.push_back(new Medicina(tipoNivel, g, imgMedic));
			tiempoMedicina = time(0);
		}
		MostrarMedicinas(g, imgMedic);
	}
	void MostrarMedicinas(Graphics^ g, Bitmap^ imgMedic) {
		for (int i = 0; i < vecMedic.size(); i++) {
			vecMedic[i]->mostrar(g, imgMedic);
		}
	}
	void Colisiones() {
		ColisionBalasconEnemigos();
		ColisionJugadorconMedicina();
		ColisionMedicinaconEnemigo3();
		ColisionEnemigosconJugador();
		ColisionMococonJugador();
	}
	void ColisionBalasconEnemigos() {
		vector<Proyectil*> vecProyec;
		vecProyec = doctor->getVectorProyec();
		for (int i = 0; i < vecProyec.size(); i++) {
			if (vecEne->ColisionEnemigos1(vecProyec[i]->getArea())) {
				vecProyec[i]->setActivo(false);
				vecProyec.erase(vecProyec.begin() + i);
				doctor->setEnemigosEli(1);
			}
			else if (vecEne->ColisionEnemigos2(vecProyec[i]->getArea())){
				vecProyec[i]->setActivo(false);
				vecProyec.erase(vecProyec.begin() + i);
				doctor->setEnemigosEli(1);
			}
			else if (vecEne->ColisionEnemigos3(vecProyec[i]->getArea())) {
				vecProyec[i]->setActivo(false);
				vecProyec.erase(vecProyec.begin() + i);
				doctor->setEnemigosEli(1);
			}
		}
	}
	void ColisionEnemigosconJugador() {
		if (vecEne->ColisionEnemigos1(doctor->getArea())) {
			doctor->reducirVidas();
		}
		else if (vecEne->ColisionEnemigos3(doctor->getArea())) {
			doctor->reducirVidas();
		}
	}
	void ColisionMococonJugador() {
		vector<Moco*> vecMocos;
		vecMocos = vecEne->getVectorMoco();
		for (int i = 0; i < vecMocos.size(); i++) {
			if (vecMocos[i]->getArea().IntersectsWith(doctor->getArea())) {
				vecMocos[i]->setActivo(false);
				vecMocos.erase(vecMocos.begin() + i);
				doctor->reducirVidas();
			}
		}
	}
	void ColisionMedicinaconEnemigo3() {
		for (int i = 0; i < vecMedic.size(); i++) {
			if (vecEne->ColisionEnemigos3ParaMedicina(vecMedic[i]->getArea())) {
				vecMedic.erase(vecMedic.begin() + i);
			}
		}
	}
	void ColisionJugadorconMedicina() {
		for (int i = 0; i < vecMedic.size(); i++) {
			if (vecMedic[i]->getArea().IntersectsWith(doctor->getArea())) {
				vecMedic.erase(vecMedic.begin() + i);
				doctor->setMedicinasRecolectadas(1);
				i--;
			}
		}
	}

	void agregarAliado(Graphics^ g, int tipoAliado) { //1- Fum 2 Enf
		if (tipoAliado == 1) {
			if (doctor->getEnemigosEli() >= 25) {
				vecAlia->agregarFumigador(tipoNivel, g);
				doctor->setBalas(20);
			}
		}
		else if (tipoAliado == 2) {
			if (doctor->getMedicinasRecolectadas() >= 10) {
				vecAlia->agregarEnfermera(tipoNivel, g);
				doctor->setVidas(5);
			}
		}
	}
	void agregarBalaJugador(int finalX, int finalY) {
		doctor->AddProyectil(finalX, finalY);
	}
	
	void gestionarDireccionJugador(direccion dir) {doctor->desplazamiento(dir);}
	void restarBalas() {doctor->RestarBalas();}
	void setVidasJugador(int vidas) { doctor->setVidas(vidas); }
	void setBalas(int balas) { doctor->setBalas(balas); }
	
	int getCantidadMaxBalas() {return doctor->getMaxBalas();}
	int getSizeVecProyecJug() {return doctor->getVectorProyec().size();}
	int getVidasJugador() {return doctor->getVidas();}
	int getEnemigosEli() {return doctor->getEnemigosEli();}
	int getMedicamentosRecol() { return doctor->getMedicinasRecolectadas(); }
};