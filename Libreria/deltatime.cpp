//###################################################################################################
//	
//	FILE NAME :			deltatime.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Deltatime
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/apr/22
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe che rappresenta un intervallo temporale espresso in anni, mesi giorni, ore, minuti e secondi. 
//					Importante la ridefinizione degli operatori che permette di trattare un intervallo temporale come frazione di anni espressa da un double. 
//					Abbiamo ritenuto opportuno ridefinire in modo differente la divisione per un numero reale(double) e per un numero intero.
//					Mentre è più comodo trattare la prima come un double che rappresenti la frazione di anni, nel secondo caso abbiamo scelto di
//					mantenere un oggetto Deltatime.
//	
//	
//	
//	
//	
//	
//#######################################################################################################
#include "deltatime.hpp"

#include <string>
#include <iostream>
#include <cmath>

#include "errorlist.hpp"

//###################################################################################################
//COSTRUTTORI~DISTRUTTORE
//###################################################################################################

//! costruttore di default
Deltatime::Deltatime() : _y(0), _M(0), _d(0), _h(0), _m(0), _s(0) {};


//! costruttore
Deltatime::Deltatime(int y,int M=0,int d=0,int h=0, int m=0, int s=0): _y((y>0)?y:0),_M((M>0)?M:0),_d((d>0)?d:0), _h((h>0)?h:0), _m((m>0)?m:0), _s((s>0)?s:0){};


//! costruttore di copia
Deltatime::Deltatime(const Deltatime &copy){
	_y=copy._y;
	_M=copy._M;
	_d=copy._d;
	_h=copy._h;
	_m=copy._m;
	_s=copy._s;
};


//! distruttore
Deltatime::~Deltatime(){};

//###################################################################################################
//FUNZIONI GET
//###################################################################################################

//! funzione che restituisce l'anno
int Deltatime::Get_y()const {
	return _y;
};


//! funzione che restituisce il mese
int Deltatime::Get_M()const {
	return _M;
};


//! funzione che restituisce il giorno
int Deltatime::Get_d()const {
	return _d;
};


//! funzione che restituisce il ora
int Deltatime::Get_h()const {
	return _h;
};


//! funzione che restituisce il minuto
int Deltatime::Get_m()const {
	return _m;
};


//! funzione che restituisce il secondo
int Deltatime::Get_s()const {
	return _s;
};

//###################################################################################################
//FUNZIONI SET
//###################################################################################################

//! funzione che imposta l' anno
void Deltatime::Set_y(int YYYY){
	_y=YYYY;
};


//! funzone che imposta il  mese
void Deltatime::Set_M(int M){
	_M=M;
};


//! funzone che imposta il giorno
void Deltatime::Set_d(int D){
	_d=D;
};


//! funzone che imposta l'ora
void Deltatime::Set_h(int h){
	_h=h;
};


//! funzone che imposta i minuti
void Deltatime::Set_m(int m){
	_m=m;
};


//! funzone che imposta i secondi
void Deltatime::Set_s(int s){
	_s=s;
};

//###################################################################################################
//METODI
//###################################################################################################

//! valutazione del deltatime in frazione di anni
double Deltatime::Value()const{
	double ris=(((((((_s/60.)+_m)/60.)+_h)/24.)+_d)/365.25)+_y+(_M/12.);
	return ris;
};

//###################################################################################################
//OPERATORI MATEMATICI
//###################################################################################################

//! overloading dell'operatore di moltiplicazione: valuta l'oggetto in frazione di anni e lo moltiplica per un double. Restituisce il valore in frazione di anni 
double Deltatime::operator*(double c) const{
	return (((*this).Value())*c);
};


double operator*(double c, const Deltatime &del) {
	return (del*c);
};


//! overloading dell'operatore di divisione: valuta l'oggetto in frazione di anni e lo divide per un double. Restituisce il valore in frazione di anni 
double Deltatime::operator/(double c) const{
	return Value()/c ;
};


double operator/(double c, const Deltatime &del) {
	return (c/(del.Value()));
};


//! overloading dell'operatore di divisione per un intero
Deltatime Deltatime::operator/(int c){
	double tot = Value()/c;
	int y = floor(tot);
	tot = (tot - y)*12;
	int M = floor(tot);
	tot = (tot - M)*30.4375;
	int d = floor(tot); 
	tot = (tot-d)*24.;
	int h = floor(tot);
	tot = (tot-h)*60.;
	int m = floor(tot);
	tot = (tot-m)*60;
	int s = floor(tot+0.5);
	Deltatime ris(y,M,d,h,m,s);
	return ris;
}; 


//! overloading dell'operatore di sottrazione: valuta l'oggetto in frazione di anni e sottrae un double. Restituisce il valore in frazione di anni 
double Deltatime::operator-(double c) const{
	return ((*this).Value()-c);
};


double operator-(double c, const Deltatime &del) {
	return (c-(del.Value()));
};

//OPERATORI CON DELTATIME

//! overloading dell'operatore di sottrazione tra oggetti Deltatime
Deltatime Deltatime::operator-(const Deltatime &c) const{
	Deltatime ris(*this);
	ris._y=((ris._y)-(c._y));
	ris._M=((ris._M)-(c._M));
	ris._d=((ris._d)-(c._d));
	ris._h=((ris._h)-(c._h));
	ris._m=((ris._m)-(c._m));
	ris._s=((ris._s)-(c._s));

	if(ris._y<0 || ris._M<0 || ris._d<0 || ris._h<0 || ris._m<0 || ris._s<0){
		if((ris._y)<0){
			ErrorList *err=ErrorList::Get_errorlist();
			err->Add_error("Deltatime:: error, deltatime must be positive or zero");
		}
		else {
			while((ris._s)<0){
				ris._s+=60;
				ris._m--;
			}
			while((ris._m)<0){
				ris._m+=60;
				ris._h--;
			}
			while((ris._h)<0){
				ris._h+=24;
				ris._d--;
			}
			while((ris._d)<0){
				ris._d+=(365.25/12.);
				ris._M--;
			}
			while((ris._M)<0){
				ris._M+=12;
				ris._y--;
			}
			if((ris._y)<0){
			ErrorList *err=ErrorList::Get_errorlist();
			err->Add_error("Deltatime:: error, deltatime must be positive or zero");
			}
		}
	}
	return ris;
};


//! overloading dell'operatore di incremento
const Deltatime &Deltatime::operator+=(const Deltatime &d){
	((*this)._y)+=(d._y);
	((*this)._M)+=(d._M);
	((*this)._d)+=(d._d);
	((*this)._h)+=(d._h);
	((*this)._m)+=(d._m);
	((*this)._s)+=(d._s);
	return (*this);
}


//! overloading dell'operatore di divisione tra oggetti Deltatime: valuta i 2 oggetti e restituisce il valore in frazione di anni
double Deltatime::operator/(const Deltatime &c) const{
	return (((*this).Value())/(c.Value()));
};


//! overloading dell'operatore di somma 
Deltatime Deltatime::operator+(const Deltatime &c) const{
	Deltatime ris(*this);
	ris._y=((ris._y)+(c._y));
	ris._M=((ris._M)+(c._M));
	ris._d=((ris._d)+(c._d));
	ris._h=((ris._h)+(c._h));
	ris._m=((ris._m)+(c._m));
	ris._s=((ris._s)+(c._s));
	return ris;
};

//###################################################################################################
//OPERATORI LOGICI
//###################################################################################################

//! overloading dell'operatore logico "minore"
bool Deltatime::operator<(const Deltatime &d) const {
	if(_y<d._y) return true;
	if(_y>d._y) return false;
	else {
		if(_M<d._M) return true;
		if(_M>d._M) return false;
		else {
			if(_d<d._d) return true;
			if(_d>d._d) return false;
			else{
				if(_h<d._h) return true;
				if(_h>d._h) return false;
				else{
					if(_m<d._m) return true;
					if(_m>d._m) return false;
					else{
						if(_s<d._s) return true;
						else return false;
					}
				}
			}
		}
	}
};


//! overloading dell'operatore logico "maggiore"
bool Deltatime::operator>(const Deltatime &d) const {
	if(_y>d._y) return true;
	if(_y<d._y) return false;
	else {
		if(_M>d._M) return true;
		if(_M<d._M) return false;
		else {
			if(_d>d._d) return true;
			if(_d<d._d) return false;
			else{
				if(_h>d._h) return true;
				if(_h<d._h) return false;
				else{
					if(_m>d._m) return true;
					if(_m<d._m) return false;
						else{
							if(_s>d._s) return true;
							else return false;
						}
				}
			}
		}
	}
};


//! overloading dell'operatore logico "minore o uguale"
bool Deltatime::operator<=(const Deltatime &d) const {
	if((*this)<d || (*this)==d) return true;
	else return false;
};


//! overloading dell'operatore logico "maggiore o uguale"
bool Deltatime::operator>=(const Deltatime &d) const {
	if((*this)>d || (*this)==d) return true;
	else return false;
};


//! overloading dell'operatore logico di uguaglianza
bool Deltatime::operator==(const Deltatime &d) const {
	if(_y==d._y && _M==d._M && _d==d._d && _h==d._h && _m==d._m && _s==d._s) return true;
	else return false;
};


//! overloading dell'operatore logico di disuguaglianza
bool Deltatime::operator!=(const Deltatime &d) const {
	if(_y!=d._y || _M!=d._M || _d!=d._d || _h!=d._h || _m!=d._m || _s!=d._s) return true;
	else return false;
};

//###################################################################################################
//OVERLOADING DEL <<
//###################################################################################################

std::ostream &operator<<(std::ostream &os, const Deltatime &d) {
	os<<d._y<<" years "<<d._M<<" months "<<d._d<<" days "<<d._h<<" h "<<d._m<<" min "<<d._s<<" sec ";
	return os;
};
//###################################################################################################
//OPERATORE ASSEGNAMENTO
//###################################################################################################

//! overloading dell'operatore di assegnamento
const Deltatime &Deltatime::operator=(const Deltatime &copy){
	_y=copy._y;
	_M=copy._M;
	_d=copy._d;
	_h=copy._h;
	_m=copy._m;
	_s=copy._s;
	return (*this);
};

//###################################################################################################
