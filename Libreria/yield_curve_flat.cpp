//###################################################################################################
//	
//	FILE NAME :			yield_curve_flat.cpp
//		
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Yield_curve_flat
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
//	DETAILED DESCRIPTION :	Rappresenta una curva dei tassi piatta, ovvero costante nel tempo. Contiene un membro statico per la dichiarazione della curva risk-free.
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	
//###################################################################################################


//###################################################################################################
//INCLUDE
//###################################################################################################
#include "yield_curve_flat.hpp"
#include "errorlist.hpp"
//#################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#################################################################################################

//! costruttore di defalut
Yield_curve_flat::Yield_curve_flat():Yield_curve(), _rate(0){};


//! costruttore
Yield_curve_flat::Yield_curve_flat(double rate):Yield_curve(), _rate((rate>=0)?rate:0) {
	if(rate<0){
		ErrorList::Get_errorlist()->Add_error("Yield_curve_flat::(constructor) rate must be positive or zero");
	}
};


//! costruttore di copia
Yield_curve_flat::Yield_curve_flat(const Yield_curve_flat &fla): Yield_curve(),_rate(fla._rate) {};


//! distruttore
Yield_curve_flat::~Yield_curve_flat(){};


//###################################################################################################
//FUNCTIONS
//###################################################################################################

//! funzione che restituisce il valore del tasso al tempo t
double Yield_curve_flat::Get_spot_rate(const Time &t) const{
	if(t>=*(Time::Get_today())) return _rate;
	else{
		ErrorList::Get_errorlist()->Add_error("Yield_curve_flat::(Get_spot_rate) time must be in the future");
		return 0;
	}
};



//! funzione che restituisce il valore del tasso dopo un intervallo di tempo t
double Yield_curve_flat::Get_spot_rate(const Deltatime &t) const{
	return _rate;
};

//###################################################################################################
//FUNZIONI GET
//###################################################################################################

//! funzione che restituisce il tasso
double Yield_curve_flat::Get_rate() const{
	return _rate;
}

//###################################################################################################
//FUNZIONI SET
//###################################################################################################

//! funzione che imposta il tasso 
void Yield_curve_flat::Set_rate(double rate) {
	if(rate<0){
		ErrorList::Get_errorlist()->Add_error("Yield_curve_flat::(constructor) rate must be positive or zero");
	}
	else _rate=rate;
}

//#################################################################################################
//OPERATORI
//#################################################################################################

//overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Yield_curve_flat &fla) {
	os<<"il tasso è : "<<fla.Get_rate()<<std::endl;
	return os;
};

//#########################################################################################################
//FUNZIONI RISKFREE
//#########################################################################################################

//! funzione che restituisce il tasso risk-free (statico)
Yield_curve_flat* Yield_curve_flat::Get_riskfree() {
	if(_riskfree==NULL){
		_riskfree = new Yield_curve_flat();
	}
	return _riskfree;
};


//! funzione che imposta il tasso della curva risk-free (dato un double)
void Yield_curve_flat::Set_riskfree(double rate){
				(Get_riskfree())->_rate=rate;
};


//! funzione che imposta il tasso della curva risk-free (come copia di un altro oggetto Yield_curve_flat)
void Yield_curve_flat::Set_riskfree(Yield_curve_flat &y){
	*(Get_riskfree())=y;
};

//##########################################################################################################
//OPERATORE ASSEGNAMENTO
//##########################################################################################################

//! overloading dell'operatore di assegnamento
Yield_curve_flat &Yield_curve_flat::operator=(Yield_curve_flat &obj){
		cout<<"sono in = Yield_curve_flat\n";
	_rate=obj._rate;
	return *this;
};

//##########################################################################################################

