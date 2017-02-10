//#################################################################################################################
//	
//	FILE NAME :			currency.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Currency
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/25
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	 Classe che rappresenta la valuta. Contiene tra i membri privati un intero al quale 
//				corrisponde una valuta predefinita.	La valuta impostata di default è l'euro (EUR).
//	
//
//
//
//	
//	
//	
//	
//	
//#################################################################################################################
#include "currency.hpp"

//#################################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#################################################################################################################

//! costruttore di default
Currency::Currency(){
	_curr=1;
};


//! costruttore
Currency::Currency(const string &c){
	if(c=="EUR") _curr=1;
	if(c=="USD") _curr=2;
	else _curr=0;
};


//! distruttore
Currency::~Currency(){};

//#################################################################################################################
//FUNZIONI GET~SET
//#################################################################################################################

//! funzione per impostare la valuta.
void Currency::Set_currency(const string &c){
	if(c=="EUR")	_curr=1;
	if(c=="USD") _curr=2;
	else _curr=0;
};


//! funzione per ottenere la valuta.
string Currency::Get_currency() const {
	if(_curr==1) return "EUR";
	if(_curr==2) return "USD";
	else return "invalid currency";
};

//#################################################################################################################
//OPERATORE ASSEGNAMENTO
//#################################################################################################################

//! operatore di assegnamento.
const Currency &Currency::operator=(const Currency &p){
	_curr=p._curr;
	return (*this);
};

//#################################################################################################################
//OPERATORI LOGICI
//#################################################################################################################

//! operatore logico di uguaglianza.
bool Currency::operator==(const Currency &dat) const{
	if(dat._curr==_curr) return true;
	else return false;
};


//! operatore logico di disuguaglianza.
bool Currency::operator!=(const Currency &dat) const{
	if(dat._curr!=_curr) return true;
	else return false;
};

//#################################################################################################################
//OVERLOAD DEL <<
//#################################################################################################################

std::ostream &operator<<(std::ostream &os, const Currency &cu) {
	if(cu._curr==1) {
		os<<"EUR";
	}
	if(cu._curr==2) {
		os<<"USD";
	}
	else {
		os<<"invalid currency";
	}
	return os;
};

//#################################################################################################################

