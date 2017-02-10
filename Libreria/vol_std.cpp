//###################################################################################################
//	
//	FILE NAME :			vol_std.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Vol_std
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	FROM CLASS :		Volatility
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta una curva di volatilità piatta, ovvero costante nel tempo. Per questo motivo è sufficiente un double per impostare la curva.
//
//
//
//	
//	
//	
//	
//	
//###################################################################################################

#include "vol_std.hpp"
#include "errorlist.hpp"

//################################################################################################################
//COSTRUTTORI~DISTRUTTORE
//################################################################################################################

//! costruttore di default
Vol_std::Vol_std(): Volatility(){
	_vola=0.;
};


//! costruttore
Vol_std::Vol_std(double v){
	if(v<0){
		ErrorList::Get_errorlist()->Add_error("Vol_std::(constructor) volatility must be positive");
		v=0;
	}
	_vola=v;
};


//! costruttore di copia
Vol_std::Vol_std(const Vol_std &vo){
	_vola=vo._vola;
};


//! distruttore
Vol_std::~Vol_std(){};

//################################################################################################################
//FUNZIONI SET
//################################################################################################################

//! funzione che imposta il valore della volatilità
void Vol_std::Set_vol(double v){ 
	if(v<0){
		ErrorList::Get_errorlist()->Add_error("Vol_std::(Set_vol) error, volatility must be positive");
		v=0;
	}
	_vola=v;
};

//################################################################################################################
//METODI VIRTUAL
//################################################################################################################

//! funzione che restituisce la volatilità tra t1 e t2 
double Vol_std::Get_vol(const Time &t1, const Time &t2) const{
	return _vola ;
};

//################################################################################################################
//OPERATORE ASSEGNAMENTO
//################################################################################################################

//! overloading dell'operatore di assegnamento
Vol_std &Vol_std::operator=(Vol_std &obj){
	_vola=obj._vola;
	return (*this);
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

// overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Vol_std &dat) {
	os<<"La volatilità fissata è : "<<dat._vola<<std::endl;
	return os;
};

//################################################################################################################




