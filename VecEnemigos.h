#pragma once
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Enemigo3.h"
#include "Moco.h"
#include <vector>

class VecEnemigos {
private:
	vector<Enemigo1*> vecEne1;
	vector<Enemigo2*> vecEne2;
	vector<Enemigo3*> vecEne3;
	vector <Moco*> vecMocos;
public:
	VecEnemigos() {
		this->vecEne1 = vector<Enemigo1*>();
		this->vecEne2 = vector<Enemigo2*>();
		this->vecEne3 = vector<Enemigo3*>();
		this->vecMocos = vector<Moco*>();
	}
	~VecEnemigos() {
		for (Enemigo1* e1 : vecEne1) {
			delete e1;
		}
		this->vecEne1.clear();
		for (Enemigo2* e2 : vecEne2) {
			delete e2;
		}
		this->vecEne2.clear();
		for (Enemigo3* e3 : vecEne3) {
			delete e3;
		}
		this->vecEne3.clear();
	}
	vector<Enemigo1*> getVecEnemigo1() {
		return this->vecEne1;
	}
	vector<Enemigo2*> getVecEnemigo2() {
		return this->vecEne2;
	}
	vector<Enemigo3*> getVecEnemigo3() {
		return this->vecEne3;
	}

	bool ColisionEnemigos2(Rectangle recProyec) {
		for (int i = 0; i < vecEne2.size(); i++) {
			if(vecEne2[i]->getArea().IntersectsWith(recProyec) == true){
				vecEne2.erase(vecEne2.begin() + i);
				return true;
			}
		}
		return false;
	}
	bool ColisionEnemigos1(Rectangle recProyec) {
		for (int i = 0; i < vecEne1.size(); i++) {
			if (vecEne1[i]->getArea().IntersectsWith(recProyec) == true) {
				vecEne1.erase(vecEne1.begin() + i);
				return true;
			}
		}
		return false;
	}
	bool ColisionEnemigos3(Rectangle recProyec) {
		for (int i = 0; i < vecEne3.size(); i++) {
			if (vecEne3[i]->getArea().IntersectsWith(recProyec) == true) {
				vecEne3.erase(vecEne3.begin() + i);
				return true;
			}
		}
		return false;
	}
	bool ColisionEnemigos3ParaMedicina(Rectangle recProyec) {
		for (int i = 0; i < vecEne3.size(); i++) {
			if (vecEne3[i]->getArea().IntersectsWith(recProyec) == true) {
				
				vecEne3[i]->setDy(-10);
				vecEne3[i]->setDx(vecEne3[i]->getDx() * 2);
				return true;
			}
		}
		return false;
	}

	vector<Moco*> getVectorMoco() {return this->vecMocos;}

	void agregarEnemigo1() {
		Enemigo1* e1 = new Enemigo1();
		this->vecEne1.push_back(e1);
	}
	void agregarEnemigo2() {
		Enemigo2* e2 = new Enemigo2();
		this->vecEne2.push_back(e2);
	}

	void agregarEnemigo3() {
		Enemigo3* e3 = new Enemigo3();
		this->vecEne3.push_back(e3);
	}

	void GestionarMocos(Graphics ^g, Bitmap ^ imgMoco) {
		for (int j = 0; j < vecMocos.size(); j++) {
				vecMocos[j]->mostrar(g, imgMoco);
		}
		for (int i = 0; i < vecMocos.size(); ++i) {
			if (vecMocos[i]->getactivo()) continue;
			vecMocos.erase(vecMocos.begin() + i);
		}
	}
	void moverEnemigos(Graphics^ g, Bitmap^ img_e1, Bitmap^ img_e2, Bitmap^ img_e3, Bitmap^ imgMoco) {
		for (Enemigo1* e1 : vecEne1) {
			e1->moverE(g, img_e1, 3);
		}
		for (int i = 0; i < vecEne2.size(); i++) {
			vecEne2[i]->moverE(g, img_e2, 3);
			if (vecEne2[i]->getindiceX() == 9 && vecEne2[i]->getindiceY() == 0 ) {
				vecMocos.push_back(new Moco(vecEne2[i]->getX() + vecEne2[i]->getAncho() / 6, vecEne2[i]->getY() + vecEne2[i]->getAlto() / 6 + 10, imgMoco));
			}	
		}
		GestionarMocos(g, imgMoco);
		for (Enemigo3* e3 : vecEne3) {
			e3->moverE(g, img_e3, 2);
		}
	}
};