//---------------------------------------------------------------------------

#ifndef pomocnaH
#define pomocnaH
#include <vector>
#include <algorithm>
#define PI 3.14159265

using namespace std;

struct Tacka {
	int x;
	int y;
	Tacka():x(0),y(0) {}
	Tacka(int X, int Y):x(X),y(Y) {}
	Tacka(const Tacka &t){ x = t.x; y = t.y; }
	void Crtaj(TImage*) const;
};

bool operator==(Tacka,Tacka);
bool operator!=(Tacka,Tacka);
bool operator<(Tacka,Tacka);

struct Duz {
	Tacka pocetna;
	Tacka krajnja;
	Duz(Tacka A,Tacka B):pocetna(A),krajnja(B) {}
	void Crtaj(TImage*) const;
};

struct Kamera {
	Tacka pozicija;
	Tacka pocetakVidokruga;
	Tacka krajVidokruga;
	vector<Tacka> vidokrug;

	int ugaoRotacije = 1;
	Kamera(Tacka t) {
		Tacka pomocna = Tacka(-90000, t.y);
		pozicija = Tacka(t);
		pocetakVidokruga =  rotirajTacku(pomocna, 330);
		krajVidokruga = rotirajTacku(pomocna, 30);
	}

	void rotirajKameru();
	void iscrtajVidokrug(TImage*);
	void crtaj(TImage*) const;
	void resetVidokrug();
	void odrediVidokrug(vector<Tacka>, TImage*, TEdit*, TEdit*);

private:
	Tacka rotirajTacku(Tacka, double);
	Tacka rubnaTacka(Duz);
	bool pripadaVidokrugu(Tacka);
	Tacka sjenkaTacke(Tacka,vector<Tacka>,int);
};

double ugaoIzmedjuDuzi(Tacka, Tacka, Tacka);
void iscrtajPoligon(vector<Tacka> &poligon, TImage *image);

bool daLiJeUnutarProstogMnogougla(Tacka, Tacka, vector<Tacka>&);
double stepeniURadijanima(double);

double radijaniUstepenima(double);
Tacka tackaPresjeka(Tacka, Tacka, Tacka, Tacka);

double determinanta(double a, double b, double c, double d);
double udaljenost(Tacka, Tacka);

bool naSegmentu(Tacka p, Tacka q, Tacka r);
int Orijentacija(Tacka,Tacka,Tacka);

bool duziSePresjecaju(Tacka p1, Tacka q1, Tacka p2, Tacka q2);
//---------------------------------------------------------------------------
#endif
