#pragma once
#include "Fumigador.h"
#include "Enfermera.h"
#include <vector>

class VecAliados {
private:
	vector<Fumigador*> vecFum;
	vector<Enfermera*> vecEnf;
public:
	VecAliados() {
		this->vecFum = vector<Fumigador*>();
		this->vecEnf = vector<Enfermera*>();
	}
	~VecAliados() {
		for (Fumigador* fum : vecFum) {
			delete fum;
		}
		this->vecFum.clear();
		for (Enfermera* enf : vecEnf) {
			delete enf;
		}
		this->vecEnf.clear();

	}

	void agregarEnfermera(Graphics^ g) {

		Enfermera* enf = new Enfermera(g);
		this->vecEnf.push_back(enf);
	}
	void agregarFumigador(Graphics^ g) {
		Fumigador* fum = new Fumigador(g);
		this->vecFum.push_back(fum);
	}

	void moverAliados(Graphics^ g, Bitmap^ imgfumigador, Bitmap^ imgenfermera) {
		for (Fumigador* fum : vecFum) {
			fum->MoverFumigador(g, imgfumigador);
		}
		for (Enfermera* enf : vecEnf) {
			enf->MoverEnfermera(g, imgenfermera);
		}

	}
};