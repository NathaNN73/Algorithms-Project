#pragma once
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Enemigo3.h"
#include <vector>

class VecEnemigos {
private:
	vector<Enemigo1*> vecEne1;
	vector<Enemigo2*> vecEne2;
	vector<Enemigo3*> vecEne3;
public:
	VecEnemigos() {
		this->vecEne1 = vector<Enemigo1*>();
		this->vecEne2 = vector<Enemigo2*>();
		this->vecEne3 = vector<Enemigo3*>();
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

	void dispararMoco() {
		for (int i = 0; i < vecEne2.size(); i++) {
			if (vecEne2[i]->getindiceX() == 10 && vecEne2[i]->getindiceY() == 10) {
				vecEne2[i]->disparar();
			}
		}
	}
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
	void moverEnemigos(Graphics^ g, Bitmap^ img_e1, Bitmap^ img_e2, Bitmap^ img_e3) {
		for (Enemigo1* e1 : vecEne1) {
			e1->moverE(g, img_e1, 3);
		}
		for (Enemigo2* e2 : vecEne2) {
			e2->moverE(g, img_e2, 3);
		}
		for (Enemigo3* e3 : vecEne3) {
			e3->moverE(g, img_e3, 2);
		}
	}
};

