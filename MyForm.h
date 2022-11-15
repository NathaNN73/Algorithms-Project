#pragma once
#include "Juego.h"
#include "VecEnemigos.h"
#include "VecAliados.h"
#include "Enfermera.h"
#include "Fumigador.h"

namespace TrabajoF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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

			objJuego = new Juego(buffer->Graphics, imgDoctor);
			enf = new Enfermera(buffer->Graphics);
			fum = new Fumigador(buffer->Graphics);
			vecA = new VecAliados();

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
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// Variable del diseñador necesaria.
		Juego* objJuego;
		Enfermera* enf;
		Fumigador* fum;
		Bitmap^ imgDoctor;
		Bitmap^ imgEnemigo1;
		Bitmap^ imgEnemigo2;
		Bitmap^ imgEnemigo3;
		Bitmap^ fondoCiudad;
		Bitmap^ imgProyecDoc;
		int maxenf = 0;
		int maxfu = 0;
		VecAliados* vecA;
		Bitmap^ imgEnf;
		Bitmap^ imgFum;
		// Creamos los graficos del formulario
		Graphics^ g;
		// Reservamos un espacio para poner el Buffer
		BufferedGraphicsContext^ espacioBuffer;
		// Creamos un canvas dentro del espacio del buffer utilizando el canvas
		// del formulario
		BufferedGraphics^ buffer;
		// A partir de aquí todo los dibujos se deben realizar en el Canvas del Buffer
		// buffer->Graphics


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		//buffer->Graphics->Clear(Color::White);
		int ancho = g->VisibleClipBounds.Width;
		int alto = g->VisibleClipBounds.Height;
		buffer->Graphics->DrawImage(fondoCiudad, 0, 0, ancho, alto);

		objJuego->Jugar(buffer->Graphics, imgDoctor, imgProyecDoc , imgEnemigo1, imgEnemigo2, imgEnemigo3, imgFum, imgEnf);


		buffer->Render(g);
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::W: objJuego->gestionarDireccionJugador(Arriba); break;
		case Keys::S: objJuego->gestionarDireccionJugador(Abajo); break;
		case Keys::A: objJuego->gestionarDireccionJugador(Izquierda); break;
		case Keys::D: objJuego->gestionarDireccionJugador(Derecha); break;
		case Keys::D1: objJuego->agregarEnemigo(1); break;
		case Keys::D2: objJuego->agregarEnemigo(2); break;
		case Keys::D3: objJuego->agregarEnemigo(3); break;
		case Keys::F: if (maxfu < 1) {
			objJuego->agregarAliado(buffer->Graphics, 1);
			maxfu++;
		} break;
		case Keys::E: if (maxenf < 1) {
			objJuego->agregarAliado(buffer->Graphics, 2);
			maxenf++;
		} break;
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		objJuego->gestionarDireccionJugador(Ninguna);
	}

	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		objJuego->agregarBalaJugador(e->X, e->Y);
	}
};
}