//###################################################################################################
//	
//	FILE NAME :			yield_curve_term_struct.cpp
//	
//	FILE TYPE :			C++ file
//		
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Yield_curve_term_struct
//	
//	FIRST VERSION :		2009/dec/13
//	
//	LAST UPDATE : 		2010/feb/20
//	
//	STATUS :			final
//		
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta una curva dei tassi complessa, costruita sull’interpolazione di dati.
//					Supponendo di essere a conoscenza del valore del tasso a certi tempi fissati si costrutisce una curva discreta. Nei metodi da noi 
//					implemntati abbiamo utilizzato una semplice interpolazione lineare per ricavare il valore del tasso a tempi diversi da quelli "conosciuti"
//					 dall'oggetto in esame. La formula utilizzata è:
//					 tax(t)=tax(t1)+ (tax(t2)-tax(t1)) * (t-t1) / (t2-t1); 
//					 dove t è il tempo a cui vogliamo trovare il tasso tax(t), t1 e t2 sono gli estremi dell'intervallo temporale a noi noto 
//					 che contiene t e tax(t1), tax(t2) sono i tassi( a noi noti) in tali istanti.
//					 Abbiamo considerato la curva come costante nel caso in cui t fosse compreso tra "today" e la prima data a nostra disposizione e 
//					 nel caso in cui t fosse superiore all'ultima data conosciuta. 
//					 Contiene un membro statico per la curva dei tassi risk-free.
//					 Il costruttore completo della classe accetta quindi il numero di punti conosciuti, un vettore di Deltatime( per le date di riferimento) 
//					 ed un vettore di double per i tassi.
//	
//###################################################################################################


//###################################################################################################
//INCLUDE
//###################################################################################################
#include "yield_curve_term_struct.hpp"
#include "time.hpp"
#include "errorlist.hpp"
//#########################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#########################################################################################################

//! costruttore di default
Yield_curve_term_struct::Yield_curve_term_struct(): Yield_curve(), _n(0){
	_time=NULL;
	_tax=NULL;
};


//! costruttore (lunghezza vettori, vettore Deltatime, vettore double (tassi))
Yield_curve_term_struct::Yield_curve_term_struct(int n, Deltatime *time, double *tax): Yield_curve(){
	//controllo sulla dimensione
	if(n<=0){
		if(n<0){
			ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(constructor) dimension must be positive");
		}
		_n=0;
		_time=NULL;
		_tax=NULL;
	}
	else{
		//costruisco vettori di deltatime e tassi e li riempio
		_time=new Deltatime[_n-1];
		for(int i=0;i<(_n-1);i++) _time[i]=time[i];
		_tax=new double[_n];
		for(int i=0;i<_n;i++) _tax[i]=tax[i];
	}
};


//! costruttore con il solo contatore
Yield_curve_term_struct::Yield_curve_term_struct(int n): Yield_curve(){
	//controllo sulla dimensione
	if(n<=0){
		if(n<0){
			ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(constructor) dimension must be positive");
		}
		_n=0;
		_time=NULL;
		_tax=NULL;
	}
	else{
		//costruisco vettori di deltatime e tassi
		_time=new Deltatime[_n-1];
		_tax=new double[_n];
		//pongo i tassi uguali a zero
		for(int i=0;i<_n;i++) _tax[i]=0;
	}
};


//! costruttore di copia
Yield_curve_term_struct::Yield_curve_term_struct(const Yield_curve_term_struct &nor):Yield_curve(){
	//copio la dimensione
	_n=nor._n;
	//creo i vettori di tempi e tassi e li copio
	_time=new Deltatime[_n-1];
	for(int i=0;i<(_n-1);i++) _time[i]=nor._time[i];
	_tax=new double[_n];
	for(int i=0;i<_n;i++) _tax[i]=nor._tax[i];
};


//! distruttore
Yield_curve_term_struct::~Yield_curve_term_struct(){
	if(_time!=NULL){
		delete[] _time;
	}
	if(_tax!=NULL){
		delete[] _tax;
	}
};

//###################################################################################################
//FUNCTIONS
//###################################################################################################

//###################################################################################################
//-----> Class :	Yield_curve_term_struct
//-----> Function name:	Get_spot_rate
//-----> Description :	restituisce il tasso corrispondente al tempo t interpolando linearmente
//###################################################################################################
//! funzione che restituisce il tasso corrispondente al tempo t interpolando linearmente
double Yield_curve_term_struct::Get_spot_rate(const Time &t) const{
	double ris=0;
	//ottengo l'istante attuale
	Time today=*(Time::Get_today());
	//controllo sull'istante passato (dev'essere nel futuro)
	if(t<today) {
		ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(Get_spot_rate) time must be in the future");
	}
	else {
		//se l'istante t sta tra adesso e il primo istante del vettore di tempi
		if(t<=today+(_time[0])){
				ris=_tax[0];
		}
		//se l'istante t è oltre l'ultimo istante del vettore di tempi
		if(t>=today+(_time[_n-1])){
				ris=_tax[_n-1];
		}
		else {
			//negli altri casi interpolo linearmente
			int cont=-1;
			Deltatime tot;
			//per trovare i 2 tempi tra i quali si trova il t passato al metodo
			for(int i=0;i<_n;i++){
				if(t>=today+tot) {
					cont++;
					tot+=_time[i];
				}
				else break;
			}
			//formula di interpolazione lineare
			ris=(_tax[cont]+ (_tax[cont+1]-_tax[cont]) * ((t-(today+tot))) / (_time[cont]));
		}
	}
	return ris;
};


//###################################################################################################
//-----> Class :	Yield_curve_term_struct
//-----> Function name:	Get_spot_rate
//-----> Description :	restituisce il tasso corrispondente al deltatime t interpolando linearmente
//###################################################################################################
//! funzione che restituisce il tasso corrispondente all'intervallo temporale t interpolando linearmente
double Yield_curve_term_struct::Get_spot_rate(const Deltatime &t) const{
	double ris=0;
	//se il deltatime t è più piccolo del primo deltatime del vettore di tempi
	if(t<=(_time[0])){
		ris=_tax[0];
	}
	//se il deltatime t è più grande dell'ultimo deltatime del vettore di tempi
	Deltatime all;
	for (int i=0;i<_n-1;i++) all+=_time[i];
	if(t>=all){
		ris=_tax[_n-1];
	}
	else {
		//negli altri casi interpolo linearmente
		int cont=-1;
		Deltatime tot;
		//per trovare i 2 deltatime tra i quali si trova il t passato al metodo
		for(int i=0;i<_n-1;i++){
			if(t>=tot) {
				cont++;
				tot+=_time[i];
			}
			else break;
		}
		//formula di interpolazione lineare
		ris=_tax[cont]+(_tax[cont+1]-_tax[cont])* ((t-tot) / (_time[cont]));
	}
	return ris;
};

//#########################################################################################################
//OPERATORE DI ASSEGNAMENTO
//#########################################################################################################

//! overloading dell'operatore di assegnamento
Yield_curve_term_struct &Yield_curve_term_struct::operator=(Yield_curve_term_struct &nor){
	//se le dimensioni sono diverse, pulisco i vettori e li ricreo
	if(_n!=nor._n) {
		delete[] _tax;
		delete[] _time;
		_n=nor._n;
		_tax=new double[_n];
		_time=new Deltatime[_n-1];
	}
	//li copio (hanno dimensioni diverse)
	_tax[_n]=nor._tax[_n];
	for(int i=0;i<(_n-1);i++){
		_tax[i]=nor._tax[i];
		_time[i]=nor._time[i];
	}
	return (*this);
};

//#########################################################################################################
//FUNZIONI GET
//#########################################################################################################

//! funzione che restituisce il numero di punti 
int Yield_curve_term_struct::Get_n() const{
	return _n;
};


//! funzione che restituisce l'iesimo tasso-spot ( tasso all'i-esimo tempo)
double Yield_curve_term_struct::Get_tax(int i) const{
	//controllo che i sia >0 e < della dimensione
	if(i<_n && i>=0) return _tax[i];
	else {
		ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(Get_tax)  this tax doesn't exist");
		return 0;
	}
};


//! funzione che restituisce l'iesimo intervallo temporale
Deltatime Yield_curve_term_struct::Get_time(int i) const{
	Deltatime ris;
	//controllo che i sia >0 e < della dimensione
	if(i<(_n-1) && i>=0) ris=_time[i];
	else {
		ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(Get_time) this time doesn't exist");
	}
	return ris;
};

//#########################################################################################################
//FUNZIONI SET
//#########################################################################################################

//! funzione che imposta la dimensione, ovvero il numero di punti
void Yield_curve_term_struct::Set_n(int n){
	if(n!=_n){
		//creo una nuova curva della giusta dimensione
		Yield_curve_term_struct ris(n);
		//copio tutti gli elementi che stanno nella nuova dimensione
		if(n>_n){
			for(int i=0;i<_n-1;i++) ris._time[i]=_time[i];
			for(int i=0;i<_n;i++) ris._tax[i]=_tax[i];
		}
		if(n<_n){
			for(int i=0;i<n-1;i++) ris._time[i]=_time[i];
			for(int i=0;i<n;i++) ris._tax[i]=_tax[i];

		}
		(*this)=ris;
	}
};


//! funzione che imposta il tasso all'i-esimo intervallo temporale
void Yield_curve_term_struct::Set_tax(int i, double tax){
	//controllo che i sia >0 e < della dimensione
	if(i<_n && i>=0) {
		_tax[i]=tax;
	}
	else {
		ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(Set_tax) this tax doesn't exist");
	}
};


//! funzione che imposta l'i-esimo intervallo temporale 
void Yield_curve_term_struct::Set_time(int i, const Deltatime &time){
	//controllo che i sia >0 e < della dimensione
	if(i<(_n-1) && i>=0) {
		_time[i]=time;
	}
	else {
		ErrorList::Get_errorlist()->Add_error("Yield_curve_term_struct::(Set_time) this time doesn't exist");
	}
};

//#########################################################################################################
//OVERLOADING DEL <<
//#########################################################################################################

// overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Yield_curve_term_struct &nor) {
	Time today=(*(Time::Get_today()));
	os<<"n\tdate\ttime\t\trate\t"<<std::endl;
	os<<(1)<<"\t"<<today<<"\t\t"<<nor.Get_tax(0)<<std::endl;
	for(int i=1;i<nor.Get_n();i++) {
		os<<(i+1)<<"\t"<<(today+nor.Get_time(i-1))<<"\t\t"<<nor.Get_tax(i)<<std::endl;
	}
	return os;
};

//#########################################################################################################
//FUNZIONI RISKFREE
//#########################################################################################################

//! funzione che restituisce un puntatore al membro statico risk-free (e di crearlo)
Yield_curve_term_struct* Yield_curve_term_struct::Get_riskfree() {
	static Yield_curve_term_struct *_riskfree = new Yield_curve_term_struct;
	return _riskfree;
};


//! permette di impostare la curva dei tassi risk-free (con vettori)
void Yield_curve_term_struct::Set_riskfree(int n, Deltatime *time, double *tax){
	//setta dimensione
	(Get_riskfree())->_n=n;
	//crea il vettore dei deltatime
	(Get_riskfree())->_time=new Deltatime[n-1];
	//copia il vettore dei deltatime
	for(int i=0;i<n-1;i++){
		(Get_riskfree())->_time[i]=time[i];
	}
	//crea il vettore dei tassi
	(Get_riskfree())->_tax=new double[n];
	//copia il vettore dei tassi
	for(int i=0;i<n;i++){
		(Get_riskfree())->_tax[i]=tax[i];
	}
};


//! permette di impostare la curva dei tassi risk-free ( come copia di un altro oggetto Yield_curve_term_struct)
void Yield_curve_term_struct::Set_riskfree(Yield_curve_term_struct &y){
	//l'oggetto puntato dal membro statico uguale all'oggetto passato al metodo
	*(Get_riskfree())=y;
};

//#########################################################################################################






