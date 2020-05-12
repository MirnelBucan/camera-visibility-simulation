//---------------------------------------------------------------------------

#pragma hdrstop

#include "pomocna.h"
#include <algorithm>


// 0 --> p, q ,r are kolinearne
// 1 --> cw
// 2 --> ccw
int Orijentacija(Tacka p, Tacka q, Tacka r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // kolinearne

	return (val > 0)? 1: 2; // cw or ccw
}


//provjera da li se tacka q nalazi na duzi pr
bool naSegmentu(Tacka p, Tacka q, Tacka r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
	   return true;

	return false;
}

//provjera da li se duzi p1q1 i p2q1 prosjecaju ili imaju tacku dodira
bool duziSePresjecaju(Tacka p1, Tacka q1, Tacka p2, Tacka q2)
{
	int o1 = Orijentacija(p1, q1, p2);
	int o2 = Orijentacija(p1, q1, q2);
	int o3 = Orijentacija(p2, q2, p1);
	int o4 = Orijentacija(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return true;

	// specijalni slucajevi
	// p1, q1 i p2 kolinearne i p2 lezi na p1q1
	if (o1 == 0 && naSegmentu(p1, p2, q1)) return true;

	// p1, q1 i q2 kolinearne i q2 lezi na p1q1
	if (o2 == 0 && naSegmentu(p1, q2, q1)) return true;

	// p2, q2 i p1  su kolinearne i p1 lezi na p2q2
	if (o3 == 0 && naSegmentu(p2, p1, q2)) return true;

	 // p2, q2 i q1 su kolineare i q1 lezi na p2q2
	if (o4 == 0 && naSegmentu(p2, q1, q2)) return true;

	return false;
}

//funkcija za vracanje duzinu izmedju 2 tacke
double udaljenost(Tacka A, Tacka B){
	return sqrt( pow(B.x - A.x, 2.0) + pow(B.y - A.y, 2.0) );
}

//funkcija za racunanje determinante 2x2
double determinanta(double a, double b, double c, double d){
	return a*d - c*b;
}

//racunanje tacke presjeka, 2 duzi
//detaljnije u linku
//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
Tacka tackaPresjeka(Tacka A, Tacka B, Tacka C, Tacka D) {
	int x1 = A.x,
		y1 = A.y,
		x2 = B.x,
		y2 = B.y,
		x3 = C.x,
		y3 = C.y,
		x4 = D.x,
		y4 = D.y;

	double subDet1 = determinanta(x1,y1,x2,y2),
		subDet2 = determinanta(x1,1,x2,1),
		subDet3 = determinanta(y1,1,y2,1),
		subDet4 = determinanta(x3,y3,x4,y4),
		subDet5 = determinanta(x3,1,x4,1),
		subDet6 = determinanta(y3,1,y4,1);

	double mainDet1 = determinanta(subDet1, subDet2, subDet4, subDet5),
		mainDet2 = determinanta(subDet2, subDet3, subDet5, subDet6),
		mainDet3 = determinanta(subDet1, subDet3, subDet4, subDet6),
		mainDet4 = determinanta(subDet2, subDet3, subDet5, subDet6);

	double X = mainDet1/mainDet2;
	double Y = mainDet3/mainDet4;

	return Tacka(X,Y);
}

// konvertovanje stepena u radijanima
double stepeniUradijanima(double stepeni){
	return stepeni * PI / 180.0;
}

// konvertovanje radijana u stepenima
double radijaniUstepenima(double radijani){
	return radijani * 180.0 / PI;
}

// projera da li se tacka nalazi unutar mnogougla
bool daLiJeUnutarProstogMnogougla(Tacka p, Tacka q, vector<Tacka>& tacke){
	int brojac = 0;

	for(int i=0;i<tacke.size()-1;i++) {
		if(duziSePresjecaju(p, q,tacke[i], tacke[i+1]))
			brojac++;
	}

	if(brojac%2 == 1)
		return true;

	return false;
}

void iscrtajPoligon(vector<Tacka> &poligon, TImage *image) {

  image->Canvas->MoveTo(poligon[poligon.size()-1].x,poligon[poligon.size()-1].y);
  for(int i=0;i<poligon.size();i++)
	image->Canvas->LineTo(poligon[i].x,poligon[i].y);
}

void Tacka::Crtaj(TImage *slika) const {
	slika->Canvas->Brush->Color = clBlue;
	slika->Canvas->Ellipse(x-3,y-3,x+3,y+3);
	slika->Canvas->Brush->Color = clWhite;
}


bool operator<(Tacka A, Tacka B) {
	if(A.x < B.x)
	  return true;
	if(A.x == B.x)
	  return A.y < B.y;
	return false;
}

bool operator==(Tacka A, Tacka B) {
  return A.x == B.x && A.y == B.y;
}

bool operator!=(Tacka A, Tacka B) {
  return A.x != B.x || A.y != B.y;
}


void Duz::Crtaj(TImage *slika) const {
	pocetna.Crtaj(slika);
	krajnja.Crtaj(slika);
	slika->Canvas->MoveTo(pocetna.x,pocetna.y);
	slika->Canvas->LineTo(krajnja.x,krajnja.y);
}

// pomocna funkcija
// rotiranje tacke oko polozaja kamere
// pomocu translacije i matrice rotacije
// za vise detalja https://en.wikipedia.org/wiki/Rotation_matrix
Tacka Kamera::rotirajTacku(Tacka t, double ugao){
	double sinUgla = sin(stepeniUradijanima(ugao));
	double cosUgla = cos(stepeniUradijanima(ugao));

	double novoX = (t.x - pozicija.x)*cosUgla - (t.y - pozicija.y)*sinUgla;
	double novoY = (t.x - pozicija.x)*sinUgla + (t.y - pozicija.y)*cosUgla;

	t.x = novoX + pozicija.x;
	t.y = novoY + pozicija.y;

	return t;
}

// iscrtavanje vidokruga od niza tacaka
// pomocu funkcije Polygon
void Kamera::iscrtajVidokrug(TImage* slika) {

	slika->Canvas->MoveTo(pozicija.x, pozicija.y);
	slika->Canvas->Pen->Color = clLime;
	slika->Canvas->LineTo(pocetakVidokruga.x, pocetakVidokruga.y);

	slika->Canvas->MoveTo(pozicija.x, pozicija.y);
	slika->Canvas->LineTo(krajVidokruga.x, krajVidokruga.y);

	TPoint points[vidokrug.size()];
	for(int i=0; i< vidokrug.size();i++){
		points[i] = Point(vidokrug[i].x, vidokrug[i].y);
	}
	slika->Canvas->Brush->Color = clLime;

	slika->Canvas->Polygon(points,vidokrug.size()-1);

	slika->Canvas->Brush->Color = clWhite;
}


void Kamera::crtaj(TImage* slika) const {
	slika->Canvas->Brush->Color = clRed;
	slika->Canvas->FillRect(Rect(pozicija.x-3, pozicija.y-3, pozicija.x+3, pozicija.y+3));
	slika->Canvas->Brush->Color = clWhite;
}

// rotiranje pocetka vidokruga i kraja vidokruga
// koristeci pomocne funkcije za rotiranje tacke oko pozicije kamere
void Kamera::rotirajKameru(){
	pocetakVidokruga =  rotirajTacku(pocetakVidokruga, ugaoRotacije);
	krajVidokruga = rotirajTacku(krajVidokruga, ugaoRotacije);
}

// funkcija za vracanje vidokruga na pocetne postavke
// tacnije vracanje vidokrug kamere na lijevu stranu
void Kamera::resetVidokrug(){
	Tacka pomocna = Tacka(0, pozicija.y);
	pocetakVidokruga =  rotirajTacku(pomocna, 330);
	krajVidokruga = rotirajTacku(pomocna, 30);
}

// funkcija za odredjivanje vidokruga kamere
void Kamera::odrediVidokrug(vector<Tacka> tacke,TImage *slika, TEdit *pVUgao, TEdit* kVUgao){

	vidokrug.clear();
//  tacke presjeka vidokruga sa poligonom
	Tacka pV, kV;
//  vector parova tacka i par rotacija duzi trenutne tacke i prethodne
	vector<pair<Tacka, pair<int,int> > > vidljive;



	int brojPresjeka = 0;
	float d = 0.0, r=0.0;
//  pronadjemo sve vidljive tacke ukljucujuci da pronadjemo orijentacije
//  za identifikovanje refleksni tacaka ( tacaka konkavnosti)
	for(int i=0; i < tacke.size()-1;i++){
		brojPresjeka = 0;
		for(int j = 0 ; j< tacke.size()-1;j++){
			if(duziSePresjecaju(tacke[j], tacke[j+1], pozicija, tacke[i])){
				brojPresjeka++;
			}
		}

//      provjerimo broj presjeka i da li priapda viokrugu kamere po uglu
//      tacka je vidljiva ako joj je broj presjeka 2
//      jednom ce biti pocetak neke stranice,a jednom kraj neke stranice
		if(brojPresjeka == 2 && pripadaVidokrugu(tacke[i])){

			if(i>0){
				vidljive.push_back(
					make_pair(
						tacke[i],
						make_pair(Orijentacija(pozicija, tacke[i], tacke[i+1]),
						 Orijentacija(pozicija, tacke[i-1], tacke[i])
						)
					)
				);
			} else {
			  vidljive.push_back(
					make_pair(
						tacke[i],
						make_pair(Orijentacija(pozicija, tacke[0], tacke[1]),
						 Orijentacija(pozicija, tacke[tacke.size()-2], tacke.back())
						)
					)
				);
			}

		}
	}

	brojPresjeka = 0;
//  pronadjemo tacku presjeka i pocetkavidokruga
//  pri cemo provjeravamo udaljenost
//  iz razloga sto vidokrug moze presjecat vise stranica
//  nama je potrebna najbliza, jer je ona jedina vidljiva
	for(int i=0; i < tacke.size()-1;i++){

	   if(duziSePresjecaju(tacke[i],tacke[i+1], pozicija, pocetakVidokruga)){

			 if( d == 0.0 || d > udaljenost(pozicija, tackaPresjeka(tacke[i], tacke[i+1], pozicija, pocetakVidokruga))){

				pV = tackaPresjeka(tacke[i], tacke[i+1], pozicija, pocetakVidokruga);
				d = udaljenost(pozicija,pV);
			}
	   }

	}
//  analogno za kraj vidokruga
	for(int i=0; i < tacke.size()-1;i++){

	   if(duziSePresjecaju(tacke[i],tacke[i+1], pozicija, krajVidokruga)){

			 if( r == 0.0 || r > udaljenost(pozicija, tackaPresjeka(tacke[i], tacke[i+1], pozicija, krajVidokruga))){

				kV = tackaPresjeka(tacke[i], tacke[i+1], pozicija, krajVidokruga);
				r = udaljenost(pozicija,kV);
			}
	   }

	}
//  prikaz na slici pocetak i kraj vidokruga
	pV.Crtaj(slika);
	kV.Crtaj(slika);

//  nalazenje vidokruga kao poligon
	vidokrug.push_back(pozicija);
	vidokrug.push_back(pV);
//  dodavanje vidljivi tacaka i sjenki refleksni tacaka

	for(int i=0; i < vidljive.size();i++){
		vidokrug.push_back(vidljive[i].first);
		if(vidljive[i].second.first != vidljive[i].second.second){
			vidokrug.push_back(sjenkaTacke(vidljive[i].first, tacke,
				vidljive[i].second.first > vidljive[i].second.second)
			);
		}
	}

	vidokrug.push_back(kV);

	Tacka p = vidokrug.front();
//  sortiranje tacaka za fin prikaz kao poligon
	sort( vidokrug.begin()+1, vidokrug.end(), [p] (Tacka A, Tacka B) {
		return Orijentacija(p,A,B) != 1;
	});


//  prikaz trenutnog ugla pocetka vidokruga i kraj vidokruga
	pVUgao->Text = round( ugaoIzmedjuDuzi( Tacka(0, pozicija.y), pozicija , pocetakVidokruga ));
	kVUgao->Text = round( ugaoIzmedjuDuzi( Tacka(0, pozicija.y), pozicija , krajVidokruga ));
}

/*       C
		/\
	   /  \
	  /    \
	 /      \
	/    Ugao\
   A----------B

   Ugao se mjeri u odnosu na AB, u smjeru kazaklje na satu

*/

double ugaoIzmedjuDuzi(Tacka A, Tacka B, Tacka C) {
	double ugao;
	double pocetnaX = A.x - B.x;
	double krajnjaX = C.x - B.x;

	double pocetnaY = A.y - B.y;
	double krajnjaY = C.y - B.y;

	double prvaDuzina = sqrt(pocetnaX*pocetnaX + pocetnaY*pocetnaY);
	double drugaDuzina = sqrt(krajnjaX*krajnjaX + krajnjaY*krajnjaY);

	ugao = acos(( pocetnaX*krajnjaX + pocetnaY*krajnjaY)/(prvaDuzina*drugaDuzina) );

	ugao = radijaniUstepenima(ugao);

	return Orijentacija(A, B, C) == 1 ? ugao : 360 - ugao ;
}
// provjera da li tacka pripada vidokrugu
// provjerimo da li je ugao koji zaklapa tacka u odnosu na poziciju kamere
//  veci od pocetka i manji od kraja, takodjer specijalni slucaj
// prilikom rotacije da je pocetni ugao veci od krajnje
bool Kamera::pripadaVidokrugu(Tacka trenutna){
	double ugaoSaKrajnjom,ugaoSaPocetnom, tekuciUgao;
	Tacka tmp(0,pozicija.y);

	ugaoSaPocetnom = ugaoIzmedjuDuzi( tmp, pozicija , pocetakVidokruga );
	ugaoSaKrajnjom = ugaoIzmedjuDuzi( tmp, pozicija, krajVidokruga );
	tekuciUgao = ugaoIzmedjuDuzi( tmp, pozicija, trenutna );

	if(
		ugaoSaPocetnom < ugaoSaKrajnjom &&
		tekuciUgao >= ugaoSaPocetnom &&
		tekuciUgao <= ugaoSaKrajnjom
	){
		return true;
	} else if(
		ugaoSaPocetnom > ugaoSaKrajnjom &&
		!(tekuciUgao <= ugaoSaPocetnom &&
		tekuciUgao >= ugaoSaKrajnjom)
	) {
		return true;
	}

	return false;
}


// odredjivanje sjenke refleksne tacke
Tacka Kamera::sjenkaTacke(Tacka tacka, vector<Tacka> tacke, int pomak){
	double fi, k, r;

//  odredimo ugao refleksne tacke i definisemo pravu pomocu koje trazimo sjenku
	fi = ugaoIzmedjuDuzi(Tacka(0, pozicija.y), pozicija, tacka);
//  pravimo pomak da izbjegnemo kolinearnost zbog sortiranja
	if(pomak == 0) {
		fi+=1;
	} else {
		fi-=1;
	}
	Tacka t(-900,pozicija.y);

	t = rotirajTacku(t, fi);
	k = udaljenost(tacka, pozicija);
	r = udaljenost(t, pozicija);

	Tacka tmp;

//  pronalazimo sjenku tako sto nadjemo sve presjeke stranica sa pravom
//  definisanom sa tackom pozicije kamere i refleksne tacke
//  i nadjemo drugu najmanju, jer prva podrazumijeva da je sama tacka refleksna sjenka
	for(int j=0; j < tacke.size()-1;j++) {
		if(tacka != tacke[j] && tacka != tacke[j+1] && duziSePresjecaju(tacke[j],tacke[j+1], pozicija, t)) {
			if( r > k &&
			r > udaljenost(tacka, tackaPresjeka(tacke[j], tacke[j+1], pozicija, t)) ) {

				tmp = tackaPresjeka(tacke[j], tacke[j+1], pozicija, t);
				r = udaljenost(tacka,tmp);
			}
		}
	}

	return tmp;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
