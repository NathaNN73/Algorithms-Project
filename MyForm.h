#pragma once
#include "Juego.h"
#include "Perdiste1.h"
#include "Ganaste.h"
#include <iostream>
#include <conio.h>


namespace TrabajoF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;
	using namespace System::Drawing::Text;
	using namespace System::Drawing::Drawing2D;
	using namespace std;
	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			g = this->CreateGraphics();
			espacioBuffer = BufferedGraphicsManager::Current;
			buffer = espacioBuffer->Allocate(g, this->ClientRectangle);


				imgEnemigo1 = gcnew Bitmap("sprites/Zancudo1.png");
				imgEnemigo2 = gcnew Bitmap("sprites/Zancudo2.png");
				imgEnemigo3 = gcnew Bitmap("sprites/Zancudo3.png");
				fondoCiudad = gcnew Bitmap("sprites/FondoCiudad.png");
				imgDoctor = gcnew Bitmap("sprites/jugador.png");
				imgEnf = gcnew Bitmap("sprites/Enfermera.png");
				imgFum = gcnew Bitmap("sprites/Fumigador.png");
				imgProyecDoc = gcnew Bitmap("sprites/proyecDoc.png");
				imgMedic = gcnew Bitmap("sprites/medicina.png");
				imgMoco = gcnew Bitmap("sprites/moco.png");
				imgMedic->MakeTransparent(imgMedic->GetPixel(0, 0));
				objJuego = new Juego(2, buffer->Graphics, imgDoctor, 6, 8, 4);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete buffer;
			delete espacioBuffer;
			delete g;
			delete soundFondo;
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// Variable del diseñador necesaria.
		Juego* objJuego;
		Bitmap^ imgDoctor;
		Bitmap^ imgEnemigo1;
		Bitmap^ imgEnemigo2;
		Bitmap^ imgEnemigo3;
		Bitmap^ fondoCiudad;
		Bitmap^ imgProyecDoc;
		Bitmap^ imgMedic;
		Bitmap^ imgMoco;
		SoundPlayer^ soundFondo = gcnew SoundPlayer("sounds/soundAvanzado.wav");
		
		int maxenf = 0;
		int maxfu = 0;
		Bitmap^ imgEnf;
		Bitmap^ imgFum;
		
		Graphics^ g;
		BufferedGraphicsContext^ espacioBuffer;
	private: System::Windows::Forms::Timer^ TimerAparicionEnemigo;
		
		BufferedGraphics^ buffer;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->TimerAparicionEnemigo = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// TimerAparicionEnemigo
			// 
			this->TimerAparicionEnemigo->Enabled = true;
			this->TimerAparicionEnemigo->Interval = 500;
			this->TimerAparicionEnemigo->Tick += gcnew System::EventHandler(this, &MyForm::TimerAparicionEnemigo_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		int ancho = g->VisibleClipBounds.Width;
		int alto = g->VisibleClipBounds.Height;
		buffer->Graphics->DrawImage(fondoCiudad, 0, 0, ancho, alto);

		if (objJuego->getVidasJugador() == 0) {
			Perdiste1^ formPerdiste = gcnew Perdiste1();
			this->timer1->Enabled = false;
			soundFondo->Stop();
			this->Hide();
			formPerdiste->RecogerDatos(objJuego->getEnemigosEli(), objJuego->getMedicamentosRecol());
			formPerdiste->Show();
		}

		if (objJuego->getEnemigosEli() >= 50 && objJuego->getMedicamentosRecol() >= 25) {
			Ganaste^ formGanaste = gcnew Ganaste();
			this->timer1->Enabled = false;
			soundFondo->Stop();
			this->Hide();
			formGanaste->RecogerDatos(objJuego->getEnemigosEli(), objJuego->getMedicamentosRecol());
			formGanaste->Show();
		}

		objJuego->Jugar(buffer->Graphics, imgDoctor, imgProyecDoc , imgEnemigo1, imgEnemigo2, imgEnemigo3, imgFum, imgEnf,imgMedic,imgMoco);
			
		buffer->Render(g);
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::W: objJuego->gestionarDireccionJugador(Arriba); break;
		case Keys::S: objJuego->gestionarDireccionJugador(Abajo); break;
		case Keys::A: objJuego->gestionarDireccionJugador(Izquierda); break;
		case Keys::D: objJuego->gestionarDireccionJugador(Derecha); break;
		case Keys::D8: objJuego->setVidasJugador(10); break; //Easter egg al cumple del profesor 
		case Keys::N: objJuego->setBalas(10); break; //Easter egg al mes de cumpleaños N oviembre
		case Keys::F: if (maxfu < 1) {
			objJuego->agregarAliado(buffer->Graphics, 1);
			_sleep(100);
			maxfu++;
		} break;
		case Keys::E: if (maxenf < 1) {
			objJuego->agregarAliado(buffer->Graphics, 2);
			_sleep(100);
			maxenf++;
		} break;
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		objJuego->gestionarDireccionJugador(Ninguna);
	}


	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (objJuego->getCantidadMaxBalas() > 0) {
			objJuego->agregarBalaJugador(e->X, e->Y);
			objJuego->restarBalas();
		}
		
	}
	private: System::Void TimerAparicionEnemigo_Tick(System::Object^ sender, System::EventArgs^ e) {

	}

	
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	
	soundFondo->Play();
}
private: System::Void MyForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	soundFondo->Stop();
}
};
};
