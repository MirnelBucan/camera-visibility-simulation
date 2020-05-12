//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "pomocna.h"
#include <Vcl.ComCtrls.hpp>
#include <vector>
#include <list>
#include <utility>

using namespace std;
//---------------------------------------------------------------------------
class TGlavna : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TLabel *LabelBrojTacaka;
	TEdit *EditBrojTacaka;
	TButton *GenerisanjeTacaka;
	TLabel *LabelKoordinate;
	TEdit *EditKoordinate;
	TButton *DugmeProstiMnogougao;
	TLabel *TrenutnaAkcija;
	TRadioButton *DodavanjeTacaka;
	TRadioButton *CrtanjeMnogougla;
	TButton *Clear;
	TButton *ZavrsiMnogougao;
	TRadioButton *dodavanjeKamere;
	TTimer *Timer1;
	TImage *SlikaVidokruga;
	TCheckBox *stanjeSimulacije;
	TButton *resetSimulaciju;
	TButton *startSimulaciju;
	TButton *stopSimulaciju;
	TLabel *simulacijaLabela;
	TLabel *brzinaKameraLabel;
	TEdit *brzinaKamera;
	TLabel *ugaoRotacijeStepeni;
	TEdit *ugaoRotacije;
	TEdit *pocetakVidokrugaUgao;
	TLabel *pocetakVidokrugaLabel;
	TEdit *krajVidokrugaUgao;
	TLabel *krajVidokrugaLabel;
	void __fastcall GenerisanjeTacakaClick(TObject *Sender);
	void __fastcall SlikaVidokrugMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall DugmeProstiMnogougaoClick(TObject *Sender);
	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall ZavrsiMnogougaoClick(TObject *Sender);
	void __fastcall ClearClick(TObject *Sender);
	void __fastcall stanjeSimulacijaClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall DodavanjeTacakaClick(TObject *Sender);
	void __fastcall CrtanjeMnogouglaClick(TObject *Sender);
	void __fastcall UnutarProstogClick(TObject *Sender);
	void __fastcall dodavanjeKamereClick(TObject *Sender);
	void __fastcall akcijaSimulacijaClick(TObject *Sender);
	void __fastcall stanjeSimulacijeClick(TObject *Sender);
	void __fastcall resetSimulacijuClick(TObject *Sender);
	void __fastcall startSimulacijuClick(TObject *Sender);
	void __fastcall stopSimulacijuClick(TObject *Sender);
	void __fastcall brzinaKameraChange(TObject *Sender);
	void __fastcall ugaoRotacijeChange(TObject *Sender);
	void __fastcall SlikaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);


private:
	vector<Tacka> tacke;
	vector<Kamera> kamere;

	bool jePokrenutaSimulacija = false;
	void dodajTacku(Tacka);
	void dodajKameru(Kamera);
public:
	__fastcall TGlavna(TComponent* Owner);
};


//---------------------------------------------------------------------------
extern PACKAGE TGlavna *Glavna;
//---------------------------------------------------------------------------
#endif
