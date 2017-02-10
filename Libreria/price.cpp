//###################################################################################################
//	
//	FILE NAME :			price.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Price
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/feb/5
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta un prezzo, pensato come un numero reale positivo, riferito ad un'opportuna valuta.
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

#include "price.hpp"

#include <string>
#include <iostream>
#include "errorlist.hpp"

using namespace std;

//#######################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#######################################################################################################

//! costruttore di default
Price::Price(): _price(0.){
	_val=NULL;
};


//! costruttore senza curruncy
Price::Price(double c) {
	if(c<0.) {
		ErrorList::Get_errorlist()->Add_error("Price::(constructor1) error, price must be positive");
		c=0.;
	}
	else{
		_price=c;
	}
	_val=NULL;
};


//! costruttore
Price::Price(double p,Currency *c){
	if(p<0.) {
		ErrorList::Get_errorlist()->Add_error("Price::(constructor2) error, price must be positive");
		p=0.;
	}
	else{
		_price=p;
	}
	if(c==NULL) {
		ErrorList::Get_errorlist()->Add_error("Price::(constructor2) error, invalid currency pointer");
	}
	_val=c;
};


//! distruttore
Price::~Price(){};

//#######################################################################################################
//SET~GET
//#######################################################################################################

//! funzione che imposta il prezzo
void  Price::Set_price(double p){
	if(p<0) {
		ErrorList::Get_errorlist()->Add_error("Price::(set price) error, price must be positive");
		p=0.;
	}
	else{
		_price=p;
	}
};


//! funzione che imposta la valuta
void Price::Set_curr(Currency *c){
	if(c==NULL) {
		ErrorList::Get_errorlist()->Add_error("Price::(set_curr) error, invalid currency pointer");
	}
	_val=c;
};


//! funzione che restituisce il prezzo
double Price::Get_price() const {
	return _price;
};


//! funzione che restituisce la valuta
Currency *Price::Get_currency() const{
	return _val;
};


//###################################################################################################
//OPERATORE ASSEGNAMENTO
//###################################################################################################

//! overloading dell'operatore di assegnamento 
const Price & Price::operator=(const Price &p){
	_val=p._val;
	_price=p._price;
	return (*this);
};

//###################################################################################################
//OPERATORI
//###################################################################################################

//! overloading dell'operatore iterativo " += "
const Price &Price::operator+=(Price p){
	_price=(_price + p._price);
	return (*this);
};


//! overloading dell'operatore di divisione per un double
Price Price::operator/(double d)const {
	Price ris((_price/d),_val);
	return ris;
};


//! overloading dell'operatore di divisione per un int
Price Price::operator/(int d)const {
	Price ris((_price/d),_val);
	return ris;
};


//! overloading dell'operatore di moltiplicazione per un double
Price Price::operator*(double p) const{
	Price ris((_price*p),_val);
	return ris;
};


//! overloading dell'operatore di somma per un double
Price Price::operator+(double p) const{
	Price ris((_price+p),_val);
	return ris;
};

//###################################################################################################
//FRIEND
//###################################################################################################

// overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Price &pri) {
	os<<(pri._price)<<" ";
	if(pri._val==NULL){
		os<<"valuta non disponibile";
	}
	else os<<(pri._val->Get_currency());
	return os;
};


//overloading dell'operatore di divisione di un double per un un prezzo
double operator/(double d, const Price &p) {
	return (d/p._price);
};

//###################################################################################################

