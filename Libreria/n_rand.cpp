//###################################################################################################
//	
//	FILE NAME :			n_rand.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class N_rand
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/apr/6
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Questa classe rappresenta un contenitore di numeri generati casualmente.
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

#include "n_rand.hpp"

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
N_rand::N_rand():_w(0.){};


//! costruttore
N_rand::N_rand(double w){
		_w=w;
};


//! costruttore di copia
N_rand::N_rand(const N_rand &r){
		_w=r._w;
};


//! distruttore
N_rand::~N_rand(){};

//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
const N_rand &N_rand::operator=(const N_rand &n){
	_w=n._w;
	return (*this);
};

//##############################################################################################################
//FUNZIONI GET~SET
//##############################################################################################################

//! funzione che imposta il  numero 
void N_rand::Set_rand(double w){
		_w=w;
	};


//! funzione che restituisce il numero		
double N_rand::Get_rand() const{
		return _w;
	};

//##############################################################################################################
//OPERATORI
//##############################################################################################################

//! overloading dell'operatore di moltiplicazione per un double
double N_rand::operator*(double a) const{
	return _w*a;
};


double operator*(double a, const N_rand &num){
	return ((num._w)*a);
};


//! overloading dell'operatore unario " - " che restituisce l'opposto additivo
N_rand N_rand::operator-()const{
	N_rand copy(*this);
	copy._w=-copy._w;
	return copy;
};

//###################################################################################################
//FRIEND
//###################################################################################################

std::ostream &operator<<(std::ostream &os, const N_rand &dat) {
	os<<dat._w;
	return os;
};

//###################################################################################################



