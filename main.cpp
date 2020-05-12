//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGlavna *Glavna;
//---------------------------------------------------------------------------
__fastcall TGlavna::TGlavna(TComponent* Owner)
	: TForm(Owner)
{
	srand(time(0));
	Timer1->Interval = StrToInt(brzinaKamera->Text);

	Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	SlikaVidokruga->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
}
//---------------------------------------------------------------------------
void TGlavna::dodajTacku(Tacka nova) {
	tacke.push_back(nova);
	nova.Crtaj(Slika);
}

//---------------------------------------------------------------------------
void TGlavna::dodajKameru(Kamera novaKamera) {
	kamere.push_back(novaKamera);
	novaKamera.crtaj(Slika);
}

//---------------------------------------------------------------------------
void __fastcall TGlavna::GenerisanjeTacakaClick(TObject *Sender)
{
  int broj_tacaka = EditBrojTacaka->Text.ToInt();
  for(int i=0;i<broj_tacaka;i++) {
	  Tacka nova(rand()%(Slika->Width),rand()%(Slika->Height));
	  dodajTacku(nova);
  }
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::SlikaMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
     EditKoordinate->Text = "( " + IntToStr(X) + " , " + IntToStr(Y) + " )";
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::SlikaVidokrugMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	EditKoordinate->Text = "( " + IntToStr(X) + " , " + IntToStr(Y) + " )";
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::DugmeProstiMnogougaoClick(TObject *Sender)
{
   for(int i=1;i<tacke.size();i++)
	 if(tacke[i] < tacke[0])
	   swap(tacke[i],tacke[0]);

   Tacka prva = tacke[0];
   sort(tacke.begin()+1,tacke.end(),[prva](Tacka A, Tacka B) {
										return Orijentacija(prva,A,B) == 1;
									});
   tacke.push_back(tacke[0]);

   iscrtajPoligon(tacke,Slika);

}
//---------------------------------------------------------------------------

void __fastcall TGlavna::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(DodavanjeTacaka->Checked) {
		Tacka nova(X,Y);
		dodajTacku(nova);
	} else if(CrtanjeMnogougla->Checked) {
		Tacka nova(X,Y);
		if(!tacke.empty()){
		   Slika->Canvas->LineTo(X,Y);
		} else {
			Slika->Canvas->MoveTo(X,Y);
		}
		dodajTacku(nova);
	} else if(dodavanjeKamere->Checked) {
		Tacka nova(X,Y);

		if(daLiJeUnutarProstogMnogougla(nova, Tacka(Slika->Width, Slika->Height),tacke)){
			dodajKameru(Kamera(nova));
			kamere[kamere.size()-1].ugaoRotacije = StrToInt(ugaoRotacije->Text);
			kamere[kamere.size()-1].odrediVidokrug(tacke, SlikaVidokruga, pocetakVidokrugaUgao, krajVidokrugaUgao);
			kamere[kamere.size()-1].iscrtajVidokrug(SlikaVidokruga);

		} else
		  ShowMessage("Tacka nije unutar mnogougla");
	}
}

void __fastcall TGlavna::ZavrsiMnogougaoClick(TObject *Sender)
{
	Slika->Canvas->LineTo(tacke[0].x,tacke[0].y);
	tacke.push_back(tacke[0]);
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::ClearClick(TObject *Sender)
{
  Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
  SlikaVidokruga->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
  SlikaVidokruga->Visible = false;
  jePokrenutaSimulacija = false;
  stanjeSimulacije->Checked = false;
  tacke.clear();
  kamere.clear();
}
//---------------------------------------------------------------------------


void __fastcall TGlavna::stanjeSimulacijaClick(TObject *Sender)
{
	SlikaVidokruga->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::Timer1Timer(TObject *Sender)
{
	if(jePokrenutaSimulacija && kamere.size() != 0) {
		SlikaVidokruga->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));

		for(int i=0; i< kamere.size();i++){
			kamere[i].rotirajKameru();
			kamere[i].odrediVidokrug(tacke, SlikaVidokruga, pocetakVidokrugaUgao, krajVidokrugaUgao);
			kamere[i].iscrtajVidokrug(SlikaVidokruga);
		}
	}

}
//---------------------------------------------------------------------------


void __fastcall TGlavna::DodavanjeTacakaClick(TObject *Sender)
{

	SlikaVidokruga->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::CrtanjeMnogouglaClick(TObject *Sender)
{
;
	SlikaVidokruga->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::UnutarProstogClick(TObject *Sender)
{

	SlikaVidokruga->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::dodavanjeKamereClick(TObject *Sender)
{
	stanjeSimulacije->Checked = false;
	SlikaVidokruga->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::akcijaSimulacijaClick(TObject *Sender)
{
	SlikaVidokruga->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	SlikaVidokruga->Visible = true;
	stanjeSimulacije->Checked;
	for(int i=0; i< kamere.size();i++){
		kamere[i].iscrtajVidokrug(SlikaVidokruga);
	}
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::stanjeSimulacijeClick(TObject *Sender)
{
	if(!stanjeSimulacije->Checked){
		if(jePokrenutaSimulacija){
			jePokrenutaSimulacija = false;
		}
		SlikaVidokruga->Visible = false;
	} else {
		SlikaVidokruga->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::resetSimulacijuClick(TObject *Sender)
{
	SlikaVidokruga->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));

	for(int i=0; i< kamere.size();i++){
		kamere[i].resetVidokrug();
		kamere[i].iscrtajVidokrug(SlikaVidokruga);
	}
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::startSimulacijuClick(TObject *Sender)
{
	stanjeSimulacije->Checked = true;
	SlikaVidokruga->Visible = true;
	jePokrenutaSimulacija = true;
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::stopSimulacijuClick(TObject *Sender)
{
    jePokrenutaSimulacija = false;
}
//---------------------------------------------------------------------------


void __fastcall TGlavna::brzinaKameraChange(TObject *Sender)
{
   if(jePokrenutaSimulacija){
			jePokrenutaSimulacija = false;
   }
   if(brzinaKamera->Text != ""){
		Timer1->Interval = StrToInt(brzinaKamera->Text);
   }
}
//---------------------------------------------------------------------------

void __fastcall TGlavna::ugaoRotacijeChange(TObject *Sender)
{
   if(jePokrenutaSimulacija){
			jePokrenutaSimulacija = false;
   }

   for(int i = 0; i< kamere.size();i++){
		kamere[i].ugaoRotacije =StrToInt(ugaoRotacije->Text);
   }
}
//---------------------------------------------------------------------------

