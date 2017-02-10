//###################################################################################################
//	
//	FILE NAME :			eq_price.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_price
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe per la gestione del valore di un’azione ad un determinato istante Time. 
//					Contiene quindi un puntatore alla classe Eq_description che permette di identificare a quale azione fa riferimento, 
//					un membro price che contiene il valore del prezzo ed un membro Time, che indica il momento in cui l'azione assume tale prezzo.
//					Per comodità abbiamo implementato un metodo che restituisca direttamente il valore del prezzo in double.
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
//	
//#######################################################################################################
#include "eq_price.hpp"
#include "errorlist.hpp"

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Eq_price::Eq_price(){
	_equity=NULL;
};


//! costruttore con solo puntatore a equity description
Eq_price::Eq_price(Eq_description *eq){
	if (eq==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_price::(constructor) invalid Eq_description pointer");
	}
	_equity=eq;
};


//! costruttore 
Eq_price::Eq_price(Eq_description *eq,Time t, Price p){
	if (eq==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_price::(constructor) invalid Eq_description pointer");
	}
	_equity=eq;
	_time=t;
	_price=p;
};


//! costruttore di copia
Eq_price::Eq_price(const Eq_price &copy){		//costruttore di copia
	_equity=copy._equity;
	_time=copy._time;
	_price=copy._price;
};


//! distruttore
Eq_price::~Eq_price(){};

//##############################################################################################################
//FUNZIONI SET
//##############################################################################################################

//! funzione che imposta il prezzo
void  Eq_price::Set_price(const Price &p){
	_price=p;
};


//! funzione che imposta l'anagrafica dell'azione
void  Eq_price::Set_eq( Eq_description *eq){
	if (eq==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_price::(Set_eq) invalid Eq_description pointer");
	}
	_equity = eq;
};


//! funzione che imposta l'istante temporale 
void  Eq_price::Set_time(const Time &t){
	_time=t;
};

//##############################################################################################################
//FUNZIONI GET
//##############################################################################################################

//! funzione che restituisce il prezzo
Price Eq_price::Get_Eq_price() const {
	Price ris(_price);
	return ris;
};


//! funzione che restituisce l'anagrafica dell'azione
Eq_description *Eq_price::Get_eq() const {
	if (_equity==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_price::(Get_eq) invalid Eq_description pointer");
	}
	return _equity;
};


//! funzione che restituisce l'istante temporale
Time Eq_price::Get_time() const {
	Time ris(_time);
	return ris;
};


//! funzione che restituisce il valore del prezzo in double
double Eq_price::Get_price_double() const {
	return _price.Get_price();
};


//! funzione che restituisce la valuta a cui fa riferimento il prezzo
Currency *Eq_price::Get_currency() const{
	return _price.Get_currency();
};

//##############################################################################################################
//OPERATORE DI ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
const Eq_price & Eq_price::operator=(const Eq_price &p ){
	_equity=p._equity;
	_time=p._time;
	_price=p._price;
	return (*this);
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

std::ostream &operator<<(std::ostream &os, const Eq_price &dat) {
	if(dat._equity!=NULL) os<<"equity : "<<dat._equity->Get_name()<<endl;
	else os<<"invalid equity description pointer"<<endl;
	os<<dat._time<<"\t"<<dat._price;
	return os;
};

//################################################################################################################



