//###################################################################################################
//	
//	FILE NAME :			time.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Time
//	
//	FIRST VERSION :		2010/jan/5	
//	
//	LAST UPTIME : 		2010/feb/5
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe che rappresenta un istante temporale, quindi una data e un’orario.
//					Abbiamo trattato questa classe con particolare cura, implementando funzioni di controllo per gli anni bisestili, metodi e operatori
//					di interazione con le altri classi temporali (in particolare la Deltatime), prestando attenzione al differente numero di giorni dei 
//					mesi. La data è rappresentata come : anno, mese, giorno, ore, minuti, secondi. 
//					Possiede un membro statico "today" che indica il giorno di "oggi". Questo singleton ci permette di gestire al meglio alcune funzioni
//					all'interno della libreria:
//					se in una funzione è necessario conoscere una data si potrà anche passare un oggetto Deltatime che automaticamente, facendo riferimento 
//					a today, ricaverà la data in questione. 
//					Ecco il metodo per stabilire se l'anno sia o meno bisestile:
//					bisestile: if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0))
//					ovvero se l'anno è divisibile per 4, ma non per cento, oppure se è divisibile per 400.
//					non bisestile: if(_YYYY%400!=0){if((_YYYY%4!=0)||(_YYYY%100==0));}
//					ovvero se non è divisibile per 400 e, o non è divisibile per 4 o non è divisibile per 100.
//	
//###################################################################################################


//###################################################################################################
//INCLUDE
//###################################################################################################
#include "time.hpp"
#include <iostream>
#include <cmath>
#include <string>
//###################################################################################################
//COSTRUTTORI~DISTRUTTORE
//###################################################################################################

//! costruttore di default
Time::Time():_YYYY(0), _M(1), _D(1), _h(0), _m(0), _s(0){};


//! costruttore
Time::Time(int YYYY, int M, int D, int h, int m, int s): _YYYY((YYYY>0)?YYYY:0),_M((M>0 && M<13)?M:1),_D((D>0 && D<32)?D:1), _h((h>0 && h<24)?h:0), _m((m>0 && m<60)?m:0), _s((s>0 && s<60)?s:0){
	bool check=true;
	//controlli sui numeri passati al costruttore
	if(YYYY<0) check=false;
	if(M<0 || M>12) check=false;
	if(D<0 || D>31) check=false;
	if(h<0 || h>23) check=false;
	if(m<0 || m>59) check=false;
	if(s<0 || s>59) check=false;
	//controlli sul numero di giorni del mese
	if(_D==31){
		if(_M==4 or _M==6 or _M==9 or _M==11) {
			_D=30;
			check=false;
		}
	}
	if(_M==2 and _D>=29) {
		if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0)) _D=29;
		else {
			_D=28;
			check=false;
		}
	} 
	if(check==false) ErrorList::Get_errorlist()->Add_error("Time::(constructor) one or more errors here");
};


//! costruttore di copia
Time::Time(const Time &copia){
	_YYYY=copia._YYYY;
	_M=copia._M;
	_D=copia._D;
	_h=copia._h;
	_m=copia._m;
	_s=copia._s;
};


//! distruttore
Time::~Time(){};

//###################################################################################################
//funzioni
// bisestile se if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0))
// non bisestile se if(_YYYY%400!=0){if((_YYYY%4!=0)||(_YYYY%100==0))non bisestile;}
//###################################################################################################
//FUNZIONI GET
//###################################################################################################

//! funzione che restituisce l'anno
int Time::Get_year()const {
	return _YYYY;
};


//! funzione che restituisce il mese
int Time::Get_month()const {
	return _M;
};


//! funzione che restituisce il giorno
int Time::Get_day()const {
	return _D;
};


//! funzione che restituisce le ore 
int Time::Get_hour()const {
	return _h;
};


//! funzione che restituisce i minuti
int Time::Get_minute()const {
	return _m;
};


//! funzione che restituisce i secondi
int Time::Get_second()const {
	return _s;
};


//###################################################################################################
//FUNZIONI TODAY
//###################################################################################################


//! funzioine che crea il link statico all'oggetto today
Time* Time::Get_today() {
	if(_today==NULL){
		_today = new Time();
	}
	return _today;
};


//! funzione che imposta l'oggetto statico today
void Time::Set_today(int Y=0,int M=1,int D=1,int h=0, int m=0, int s=0){
	bool check=true;
	//controlli sui numeri passati al metodo
	if(Y<0) {
		Y=0;
		check=false;
	}
	if(M<0 || M>13) {
		M=1;
		check=false;
	}
	if(D<0 || D>31) {
		D=1;
		check=false;
	}
	if(D==31) {
		if(M==4 or M==6 or M==9 or M==11) {
			D=30;
			check=false;
		}
	}
	if(M==2 and D>=29) {
			if((Y%4==0 && Y%100!=0)||(Y%400==0)) D=29;
			else {
				D=28;
				check=false;
			}
	} 
	if(h<0 || h>23) {
		h=0;
		check=false;
	}
	if(m<0 || m>59) {
		m=0;
		check=false;
	}
	if(s<0 || s>59) {
		s=0;
		check=false;
	}
	//setto l'istante
	(Get_today())->_YYYY=Y;
	(Get_today())->_M=M;
	(Get_today())->_D=D;
	(Get_today())->_h=h;
	(Get_today())->_m=m;
	(Get_today())->_s=s;
	if(check==false) ErrorList::Get_errorlist()->Add_error("Time::(set today) one or more errors here");
};


//! funzione che imposta l'oggeto today come copia di un oggetto Time passatogli
void Time::Set_today(const Time &today){
	*(Get_today())=today;
};


//! funzione che stampa a video l'oggetto today
void Time::Print_today() {
	std::cout<<Get_today()->Get_year()<<"/"<<Get_today()->Get_month()<<"/"<<Get_today()->Get_day()<<endl;
	std::cout<<Get_today()->Get_hour()<<":"<<Get_today()->Get_minute()<<":"<<Get_today()->Get_second()<<endl;
};


//###################################################################################################
//FUNZIONI SET
//###################################################################################################


//! funzione che imposta l'anno ( se 29/2 e anno non bisestile -> 28//2)
void Time::Set_year(int YYYY){
	if(YYYY>=0) {
		_YYYY=YYYY;
		if(_M==2 and _D==29){
			if(_YYYY%400!=0){
				if((_YYYY%4!=0)||(_YYYY%100==0)) _D=28;
			}
		}
	}
	else ErrorList::Get_errorlist()->Add_error("Time::(set year) one or more errors here");
};


//! funzione che imposta il mese ( se il giorno preimpostato non è presente nel nuovo mese, viene impostato di default l'ultimo giorno possibile)
void Time::Set_month(int M){
	if(M>=1 && M<=12) {
		_M=M;
		if(_M==2 and _D>=29){
			if(_D>29) _D=29;
			if(_YYYY%400!=0){
				if((_YYYY%4!=0)||(_YYYY%100==0)) _D=28;
			}
		}
	}
	else ErrorList::Get_errorlist()->Add_error("Time::(set month) one or more errors here");
};


//! funzione che imposta il giorno
void Time::Set_day(int D){
	if(D>=1 && D<=31){
	_D=D;
		switch (_M){
			case 4: case 6: case 9: case 11:
				if(_D==31) _D=30; break;
			case 2:
				if(_D>=29){
					if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0)) _D=29;
					else _D=28; break;
				}
		else break;
		}
	}
	else ErrorList::Get_errorlist()->Add_error("Time::(set day) one or more errors here");
};


//! funzione che imposta le ore
void Time::Set_hour(int h){
	if(h>=0&&h<23) _h=h;
	else ErrorList::Get_errorlist()->Add_error("Time::(set hour) one or more errors here");
};


//! funzione che imposta i minuti
void Time::Set_minute(int m){
	if(m>=0&&m<59) _m=m;
	else ErrorList::Get_errorlist()->Add_error("Time::(set minute) one or more errors here");
};


//! funzione che imposta i secondi
void Time::Set_second(int s){
	if(s>=0&&s<59) _s=s;
	else ErrorList::Get_errorlist()->Add_error("Time::(set second) one or more errors here");
};


//###################################################################################################
//GIORNI DEL MESE
//###################################################################################################


//! funzione che restituisce il numero di giorni del mese passato al metodo
int Time::Num_days_M(int mese) const{
	int ris=0;
	switch (mese){
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			ris=31; break;
		case 4: case 6: case 9: case 11:
			ris=30; break;
		case 2:
			if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0)) ris=29;
			else ris=28; break;
	}
	if(mese>12 || mese<1) ErrorList::Get_errorlist()->Add_error("Time::(numdaysM) one or more errors here");
	return ris;
};


//###################################################################################################
//CONTEGGIO GIORNI
//###################################################################################################


//! funzione che restituisce i giorni dal primo gennaio dell'anno impostato nell'oggetto chiamante
int Time::Delta_days_1() const{
	int sum=0;
	if(_M>1) {
		for(int i=1;i<_M;i++) {			
			sum+=Num_days_M(i);
		}
	}
	sum+=_D;
	return sum;
};


//! funzione che restituisce i giorni dal primo gennaio dell'anno 0
int Time::Delta_days_0() const{
	int sum=0;
	sum+=_YYYY*365 + (floor(_YYYY/4)-(floor(_YYYY/100)-floor(_YYYY/400)));
	sum+=Delta_days_1();
	return sum;
};


//###################################################################################################
//DIFFERENZE DI TIME
//###################################################################################################


//! funzione che restituisce la differenza di 2 time in giorni 
int Time::Delta_days(const Time &da) const {
	return fabs(da.Delta_days_0() - Delta_days_0());
};


//! funzione che restituisce la differenza di 2 time in frazione di mesi
double Time::Delta_months(const Time &da) const {
	return ((Delta_days(da))/30.5);
};


//! funzione che restituisce la differenza di 2 time in frazione di anni
double Time::Delta_years(const Time &da) const {
	return ((Delta_days(da))/365.25);
};


//###################################################################################################
//SOMMARE GIORNI MESI ANNI ORE MINUTI SECONDI 
//###################################################################################################


//funzione che permette di sommare ad un time secondi, minuti, ore, giorni, mesi o anni in base a quanto specificato nella stringa
void Time::Plus(int pl, const std::string &a){
	if(a=="days") (*this)=(*this)+pl;
	if(a=="months") (*this)=(*this)+(pl*30);
	if(a=="years") (*this)=(*this)+(pl*365);
	if(a=="hours"){
		pl=pl+(Get_hour());
		if(pl<24) Set_hour(pl);
		else{
			int d=_D,M=_M,y=_YYYY;
			while (pl>=24) {
				pl-=24;		
				d++;
				if(d==Num_days_M(M)){
					M++;
					d=1;
					if(M==13){
						y++;
						M=1;
					}		
				}
			}
		Set_year(y);
		Set_month(M);
		Set_day(d);
		Set_hour(pl);
		}
	}
	if(a=="minutes"){
		pl+=Get_minute();
		if(pl<60) Set_minute(pl);
		else{
			int h=(_h), d=(_D),M=(_M),y=(_YYYY);
			while (pl>=60) {
				pl-=60;		
				h++;
				if(h==24){
					d++;
					h=0;
					if(d==Num_days_M(M)){
						M++;
						d=1;
						if(M==13){
							y++;
							M=1;
						}		
					}
				}
			}
		Set_year(y);
		Set_month(M);
		Set_day(d);
		Set_hour(h);
		Set_minute(pl);
		}
	}
	if(a=="seconds"){
		pl+=Get_second();
		if(pl<60) Set_second(pl);
		else{
			int m=_m, h=_h, d=_D,M=_M,y=_YYYY;
			while (pl>=60) {
				pl-=60;		
				m++;
				if(m==60){
					h++;
					m=0;
					if(h==24){
						d++;
						h=0;
						if(d==Num_days_M(M)){
							M++;
							d=1;
							if(M==13){
								y++;
								M=1;
							}		
						}
					}
				}
			}
		Set_year(y);
		Set_month(M);
		Set_day(d);
		Set_hour(h);
		Set_minute(m);
		Set_second(pl);
		}
	}
};


// funzione che permette di sottrarre a un time secondi, minuti, ore, giorni, mesi o anni in base a quanto specificato nella string
void Time::Minus(int pl, const std::string &a){
	if(a=="days") (*this)=(*this)-pl;
	if(a=="months") (*this)=(*this)-(pl*30);
	if(a=="years") (*this)=(*this)-(pl*365);
	if(a=="hours"){
		int h=(_h)-pl, d=(_D), M=(_M), y=(_YYYY);
		while (h<0) {
			d--;
			h+=23;		
			if(d==0){
				M--;
				d=Num_days_M(M);
				if(M==0){
					y--;
					M=12;
				}
			}	
		}
	Set_year(y);
	Set_month(M);
	Set_day(d);
	Set_hour(h);
	}
	if(a=="minutes"){
		int  m=_m-pl, h=_h, d=_D, M=_M, y=_YYYY;
		while (m<0) {
			h--;
			m+=59;		
			if(h==-1){
				d--;
				h=23;
				if(d==0){
					M--;
					d=Num_days_M(M);
					if(M==0){
						y--;
						M=12;
					}
				}	
			}
		}
	Set_year(y);
	Set_month(M);
	Set_day(d);
	Set_hour(h);
	Set_minute(m);
	}
	if(a=="seconds"){
		int s=_s-pl, m=_m, h=_h, d=_D, M=_M, y=_YYYY;
		while (s<0) {
			m--;
			s+=59;		
			if(m==-1){
				h--;
				m=59;
				if(h==-1){
					d--;
					h=23;
					if(d==0){
						M--;
						d=Num_days_M(M);
						if(M==0){
							y--;
							M=12;
						}
					}	
				}
			}
		}
	Set_year(y);
	Set_month(M);
	Set_day(d);
	Set_hour(h);
	Set_minute(m);
	Set_second(s);
	}
};


//###################################################################################################
//operatori
//###################################################################################################
//OPERATORI MATEMATICI
//###################################################################################################


//! overloading dell'operatore di sottrazione per numero intero di giorni
Time Time::operator-(int days) const{
	int d=_D-days, m=_M, y=_YYYY;
	while (d<=0) {
		m--;
		d+=Num_days_M(m);		
		if(m==0){
			y--;
			m=13;
		}		
	}
	Time ris(*this);
	ris._YYYY=y;
	ris._M=m;
	ris._D=d;
	return ris;
};


//! overloading dell'operatore di somma per numero intero di giorni
Time Time::operator+(int days) const{
	int d=_D+days, m=_M, y=_YYYY;
	while (d>=Num_days_M(m)) {
		d-=Num_days_M(m);		
		m++;
		if(m==13){
			y++;
			m=1;
		}		
	}
	Time ris(*this);
	ris._YYYY=y;
	ris._M=m;
	ris._D=d;
	return ris;
};


//! overloading dell'operatore iterativo di somma "+="
Time &Time::operator+=(int days){
	(*this)=(*this)+days;
	return (*this);
};


//! overloading dell'operatore iterativo di sottrazione "-="
Time &Time::operator-=(int days){
	(*this)=(*this)-days;
	return (*this);
};


//###################################################################################################
//OPERATORE DI ASSEGNAMENTO
//###################################################################################################


//! overloading dell'operatore di assegnamento 
const Time & Time::operator=(const Time &data){
	_YYYY=data._YYYY; _M=data._M;_D=data._D;_h=data._h;_m=data._m;_s=data._s;
	return (*this);
};


//###################################################################################################
//OPERATORI MATEMATICI CON DELTATIME
//###################################################################################################


//! overloading dell'operatore di sottrazione tra 2 Time
Deltatime Time::operator-(const Time &da) const {
	int y=((_YYYY)-da._YYYY);
	int M=((_M)-da._M);
	int d=((_D)-da._D);
	int h=((_h)-da._h);
	int m=((_m)-da._m);
	int s=((_s)-da._s);
	while (s<0){
		s=s+60;
		m--;
	}
	while (m<0){
		m=m+60;
		h--;
	}
	while (h<0){
		h=h+24;
		d--;
	}
	while (d<0){
		d=d+31;
		M--;
	}
	while (M<0){
		M=M+12;
		y--;
	}
	Deltatime delta(y,M,d,h,m,s);
	return delta;
};


//! overloading dell'operatore di sottrazione per un oggetto Deltatime
Time Time::operator-(const Deltatime &c) const{
	int anno=_YYYY-c.Get_y();
	int mese=_M-c.Get_M();
	int giorno=_D-c.Get_d();
	int ora=_h-c.Get_h();
	int minuto=_m-c.Get_m();
	int secondo=_s-c.Get_s();
	if(anno<0 || mese<=0 || giorno<=0 || ora<=0 || minuto<0 || secondo<0){
		if(anno<0){
			ErrorList::Get_errorlist()->Add_error("Time::(operator -) time must be positive or zero");
		}
		else {
			while(secondo<0){
				secondo+=60;
				minuto--;
			}
			while(minuto<0){
				minuto+=60;
				ora--;
			}
			while(ora<0){
				ora+=24;
				giorno--;
			}
			while(giorno<0){
				giorno+=30;
				mese--;
			}
			while(mese<=0){
				mese+=12;
				anno--;
			}
			if(giorno>Num_days_M(mese)){
				giorno=Num_days_M(mese);
			}
			if(anno<0){
				ErrorList::Get_errorlist()->Add_error("Time::(operator-) time must be positive");
			}
		}
	}
	Time ris(anno,mese,giorno,ora,minuto,secondo);
	return ris;
};


//! overloading dell'operatore di somma per un Deltatime
Time Time::operator+(const Deltatime &delta) const{
	//secondi di time + secondi di deltatime	
	int s = _s + delta.Get_s();
	//minuti di time + secondi di deltatime	
	int m = _m + delta.Get_m();
	//ore di time + secondi di deltatime	
	int h = _h + delta.Get_h();
	//giorni di time + secondi di deltatime	
	int d = _D + delta.Get_d();
	//mesi di time + secondi di deltatime	
	int M = _M + delta.Get_M();
	//anni di time + secondi di deltatime	
	int y = _YYYY + delta.Get_y();
	while (s>=60) {
		s-=60;		
		m++;
	}
	while (m>=60) {
		m-=60;		
		h++;
	}
	while (h>=24) {
		h-=24;		
		d++;
	}
	while (d>31) {
		d-=31;		
		M++;
	}
	while (M>12) {
		M-=12;		
		y++;
	}
	if(d>Num_days_M(M)){
		d-=Num_days_M(M);
		M++;
	}
	Time ris(y,M,d,h,m,s);
	return ris;
};


//! overloading dell'operatore iterativo di somma "+=" ( per Deltatime)
Time &Time::operator+=(const Deltatime &delta){
	int anno=_YYYY+delta.Get_y();
	int mese=_M+delta.Get_M();
	int giorno=_D+delta.Get_d();
	int ora=_h+delta.Get_h();
	int minuto=_m+delta.Get_m();
	int secondo=_s+delta.Get_s();

	if(secondo>=60||minuto>=60||ora>24||giorno>Num_days_M(mese)||mese>12){
		while(secondo>=60){
			secondo-=60;
			minuto++;
		}
		while(minuto>=60){
			minuto-=60;
			ora++;
		}
		while(ora>24){
			ora-=24;
			giorno++;
		}
		while(giorno>Num_days_M(mese)){
			giorno-=Num_days_M(mese);
			mese++;
		}
		while(mese>12){
			mese-=12;
			anno++;
		}
	}
	_YYYY=anno;
	_M=mese;
	_D=giorno;
	_h=ora;
	_m=minuto;
	_s=secondo;
	return (*this);
};


//! overloading dell'operatore iterativo di sottrazione "-=" ( per Deltatime)
Time &Time::operator-=(const Deltatime &delta){
	int anno=_YYYY-delta.Get_y();
	int mese=_M-delta.Get_M();
	int giorno=_D-delta.Get_d();
	int ora=_h-delta.Get_h();
	int minuto=_m-delta.Get_m();
	int secondo=_s-delta.Get_s();

	if(anno<0 || mese<=0 || giorno<=0 || ora<=0 || minuto<0 || secondo<0){
		if(anno<0){
			ErrorList::Get_errorlist()->Add_error("Time::(operator -=) time must be positive or zero");
		}
		else {
			while(secondo<0){
				secondo+=60;
				minuto--;
			}
			while(minuto<0){
				minuto+=60;
				ora--;
			}
			while(ora<0){
				ora+=24;
				giorno--;
			}
			while(giorno<0){
				giorno+=Num_days_M(mese);
				mese--;
			}
			while(mese<=0){
				mese+=12;
				anno--;
			}
			if(anno<0){
				ErrorList::Get_errorlist()->Add_error("Time::(operator -=) time must be positive");
			}
		}
	}
	_YYYY=anno;
	_M=mese;
	_D=giorno;
	_h=ora;
	_m=minuto;
	_s=secondo;
	return (*this);
};


//###################################################################################################
//OPERATORI BOOL
//###################################################################################################


//! overloading dell'operatore logico di uguaglianza
bool Time::operator==(const Time &dat) const{
	if(_YYYY==dat._YYYY && _M==dat._M && _D==dat._D && _h==dat._h && _m==dat._m && _s==dat._s) return true;
	else return false;
};


//! overloading dell'operatore logico di disuguaglianza
bool Time::operator!=(const Time &dat) const{
	if(_YYYY!=dat._YYYY || _M!=dat._M || _D!=dat._D || _h!=dat._h || _m!=dat._m || _s!=dat._s) return true;
	else return false;
}


//! overloading dell'operatore logico <
bool Time::operator<(const Time &dat) const{
	if(_YYYY<dat._YYYY) return true;
	if(_YYYY>dat._YYYY) return false;
	else {
		if(_M<dat._M) return true;
		if(_M>dat._M) return false;
		else {
			if(_D<dat._D) return true;
			if(_D>dat._D) return false;
			else{
				if(_h<dat._h) return true;
				if(_h>dat._h) return false;
				else{
					if(_m<dat._m) return true;
					if(_m>dat._m) return false;
						else{
							if(_s<dat._s) return true;
							else return false;
						}
				}
			}
		}
	}
};


//! overloading dell'operatore logico >
bool Time::operator>(const Time &dat) const{
	if(_YYYY>dat._YYYY) return true;
	if(_YYYY<dat._YYYY) return false;
	else {
		if(_M>dat._M) return true;
		if(_M<dat._M) return false;
		else {
			if(_D>dat._D) return true;
			if(_D<dat._D) return false;
			else{
				if(_h>dat._h) return true;
				if(_h<dat._h) return false;
				else{
					if(_m>dat._m) return true;
					if(_m<dat._m) return false;
						else{
							if(_s>dat._s) return true;
							else return false;
						}
				}
			}
		}
	}
};


//! overloading dell'operatore logico <=
bool Time::operator<=(const Time &dat) const{
	if((*this)<dat || (*this)==dat) return true;
	else return false;
};


//! overloading dell'operatore logico >=
bool Time::operator>=(const Time &dat) const{
	if((*this)>dat || (*this)==dat) return true;
	else return false;
};


//###################################################################################################
//FRIEND
//###################################################################################################


// overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Time &dat) {
	os<<dat._YYYY<<"/"<<dat._M<<"/"<<dat._D<<"  "<<dat._h<<":"<<dat._m<<":"<<dat._s;
	return os;
};

//###################################################################################################


