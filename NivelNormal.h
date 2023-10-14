#pragma once
#include "Juego.h"
#include "PerdisteBosque.h"
#include "GanasteBosque.h"

namespace TrabajoF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;
	/// <summary>
	/// Resumen de NivelNormal
	/// </summary>
	public ref class NivelNormal : public System::Windows::Forms::Form
	{
	private:
		Graphics^ g;
		BufferedGraphicsContext^ espacioBuffer;
		BufferedGraphics^ buffer;

		Juego* juegoNormal;
		Bitmap^ imgDoctor;
		Bitmap^ imgEnemigo1;
		Bitmap^ imgEnemigo2;
		Bitmap^ imgEnemigo3;
		Bitmap^ fondoBosque;
		Bitmap^ imgProyecDoc;
		Bitmap^ imgMedic;
		Bitmap^ imgMoco;
		Bitmap^ imgEnf;
		Bitmap^ imgFum;
		int maxenf = 0;
		int maxfu = 0;
		SoundPlayer^ musicFondo = gcnew SoundPlayer("sounds/soundNormal.wav");
	public:
		NivelNormal(void)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			espacioBuffer = BufferedGraphicsManager::Current;
			buffer = espacioBuffer->Allocate(g, this->ClientRectangle);

			imgEnemigo1 = gcnew Bitmap("sprites/Zancudo1.png");
			imgEnemigo2 = gcnew Bitmap("sprites/Zancudo2.png");
			imgEnemigo3 = gcnew Bitmap("sprites/Zancudo3.png");
			fondoBosque = gcnew Bitmap("sprites/FondoBosque.png");
			imgDoctor = gcnew Bitmap("sprites/jugador.png");
			imgEnf = gcnew Bitmap("sprites/Enfermera.png");
			imgFum = gcnew Bitmap("sprites/Fumigador.png");
			imgProyecDoc = gcnew Bitmap("sprites/proyecDoc.png");
			imgMedic = gcnew Bitmap("sprites/medicina.png");
			imgMoco = gcnew Bitmap("sprites/moco.png");
			imgMedic->MakeTransparent(imgMedic->GetPixel(0, 0));
			juegoNormal = new Juego(1, buffer->Graphics, imgDoctor, 7, 8, 6);
			
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~NivelNormal()
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
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(NivelNormal::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &NivelNormal::timer1_Tick);
			// 
			// NivelNormal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"NivelNormal";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NivelNormal";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &NivelNormal::NivelNormal_FormClosed);
			this->Load += gcnew System::EventHandler(this, &NivelNormal::NivelNormal_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NivelNormal::NivelNormal_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &NivelNormal::NivelNormal_KeyUp);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &NivelNormal::NivelNormal_MouseDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void NivelNormal_Load(System::Object^ sender, System::EventArgs^ e) {
		musicFondo->Play();
	}
	private: System::Void NivelNormal_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::W: juegoNormal->gestionarDireccionJugador(Arriba); break;
		case Keys::S: juegoNormal->gestionarDireccionJugador(Abajo); break;
		case Keys::A: juegoNormal->gestionarDireccionJugador(Izquierda); break;
		case Keys::D: juegoNormal->gestionarDireccionJugador(Derecha); break;
		case Keys::D8: juegoNormal->setVidasJugador(10); break; //Easter egg al cumple del profesor 
		case Keys::N: juegoNormal->setBalas(10); break; //Easter egg al mes de cumpleaños N oviembre
		case Keys::F: if (maxfu < 1) {
			juegoNormal->agregarAliado(buffer->Graphics, 1);
			_sleep(100);
			maxfu++;
		} break;
		case Keys::E: if (maxenf < 1) {
			juegoNormal->agregarAliado(buffer->Graphics, 2);
			_sleep(100);
			maxenf++;
		} break;
		}

		
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		int ancho = g->VisibleClipBounds.Width;
		int alto = g->VisibleClipBounds.Height;
		buffer->Graphics->DrawImage(fondoBosque, 0, 0, ancho, alto);

		if (juegoNormal->getVidasJugador() == 0) {
			PerdisteBosque^ formPerdiste = gcnew PerdisteBosque();
			this->timer1->Enabled = false;
			musicFondo->Stop();
			this->Hide();
			formPerdiste->RecogerDatos(juegoNormal->getEnemigosEli(), juegoNormal->getMedicamentosRecol());
			formPerdiste->Show();
		}


		if (juegoNormal->getEnemigosEli() >= 30 && juegoNormal->getMedicamentosRecol() >= 15) {
			GanasteBosque^ formGanaste = gcnew GanasteBosque();
			this->timer1->Enabled = false;
			musicFondo->Stop();
			this->Hide();
			formGanaste->RecogerDatos(juegoNormal->getEnemigosEli(), juegoNormal->getMedicamentosRecol());
			formGanaste->Show();
		}
		juegoNormal->Jugar(buffer->Graphics, imgDoctor, imgProyecDoc, imgEnemigo1, imgEnemigo2, imgEnemigo3, imgFum, imgEnf, imgMedic, imgMoco);

		buffer->Render(g);
	}
	private: System::Void NivelNormal_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		juegoNormal->gestionarDireccionJugador(Ninguna);
	}
private: System::Void NivelNormal_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (juegoNormal->getCantidadMaxBalas() > 0) {
		juegoNormal->agregarBalaJugador(e->X, e->Y);
		juegoNormal->restarBalas();
	}
}
private: System::Void NivelNormal_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	musicFondo->Stop();
}
};
}
