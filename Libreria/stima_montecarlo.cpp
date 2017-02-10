//###################################################################################################
//	
//	FILE NAME :			stima_montecarlo.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Stima_montecarlo
//	
//	FIRST VERSION :		2010/mar/26
//	
//	LAST UPTIME : 		2010/mar/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta la stima ottenuta da N simulazioni di montecarlo. Salva i dati del prezzo e dell'errore assoluto in modo 
//					che siano facilmente accessibili al termine di una simulazione.
//
//
//
//	
//	
//	
//	
//	
//#######################################################################################################

#include "stima_montecarlo.hpp"

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Stima_montecarlo::Stima_montecarlo():_prezzo(0.),_err_assoluto(0.){};


//! costruttore
Stima_montecarlo::Stima_montecarlo(double prezzo, double err_assoluto):_prezzo(prezzo),_err_assoluto(err_assoluto){};


//! distruttore
Stima_montecarlo::~Stima_montecarlo(){};

//##############################################################################################################
//FUNZIONI GET
//##############################################################################################################

//! funzione che restituisce il prezzo calcolato
double Stima_montecarlo::Get_prezzo() const{
	return _prezzo;
};


//! funzione che restituisce l'errore assoluto
double Stima_montecarlo::Get_errore_assoluto() const{
	return _err_assoluto;
};


//! funzione che restituisce l'errore relativo
double Stima_montecarlo::Get_errore_relativo() const{
	return _err_assoluto/_prezzo;
};

//##############################################################################################################
//FUNZIONI SET
//##############################################################################################################

//! funzione che imposta il prezzo 
void Stima_montecarlo::Set_prezzo(double prezzo) {
	_prezzo=prezzo;
};


//! funzione che imposta l'errore assoluto
void Stima_montecarlo::Set_errore_assoluto(double err_assoluto) {
	_err_assoluto=err_assoluto;
};


//! funzione che imposta prezzo ed errore, a partire da un oggetto di tipo Statistica
void Stima_montecarlo::Set(const Statistica &stat){
	_prezzo = stat.Get_media();
	_err_assoluto = stat.Get_errore();
};

//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
Stima_montecarlo &Stima_montecarlo::operator=(Stima_montecarlo &obj){
	_prezzo=obj._prezzo;
	_err_assoluto=obj._err_assoluto;
	return *this;
};

//##############################################################################################################
//OVERLOADING DEL <<
//##############################################################################################################

// overloading dell'operatore "<<"
ostream &operator<<(ostream &os, Stima_montecarlo &dat){
	os<<"STIMA MONTECARLO :\nPrezzo : "<<dat._prezzo;
	os<<" +- "<<dat._err_assoluto<<"  ("<<(100.*dat._err_assoluto/dat._prezzo)<<"%)"<<endl;
	return os;
};

//##############################################################################################################

