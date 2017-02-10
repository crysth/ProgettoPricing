//###################################################################################################
//	
//	FILE NAME :			eq_process.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_process
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/28
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' la classe madre dei processi che regolano l'evoluzione temporale (da uno stato A di partenza ad uno stato di arrivo B) 
//					di un'azione secondo funzioni dipendenti da una random variabile.
//					Pur rimanendo una classe prevalentemente astratta, permette di gestire i numeri casuali necessari alla funzione che regola l'evoluzione.
//					Permettere di scegliere il generatore di numeri casuali.   
//	
//	
//	
//	
//	
//	
//	
//#######################################################################################################

#include "eq_process.hpp"

#include <cmath>
#include <iostream>

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Eq_process::Eq_process(): Process(){
	_ra=NULL;
};


//! distruttore
Eq_process::~Eq_process(){};

//##############################################################################################################
//FUNZIONI GET
//##############################################################################################################

//! funzione che restituisce il  generatore di numeri casuali
Rand_gen *Eq_process::Get_rand_gen() const{
	return _ra;
};


//! funzione che restituisce l'antitetico del numero casuale
N_rand *Eq_process::Anti_w(N_rand *w) const{
		return new N_rand(-w->Get_rand());
};
//##############################################################################################################
//FUNZIONI SET
//##############################################################################################################

//! funzione che imposta il  generatore di numeri casuali
void Eq_process::Set_rand_gen(Rand_gen *ra){
	_ra=ra;
};


//! funzione che restituisce il  generatore di numeri casuali di default
void Eq_process::Set_rand_gen(void){
	_ra=NULL;
};

//##############################################################################################################
//OPERATORI ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento per la classe figlia: Eq_process_lognormal_eulero
Eq_process &Eq_process::operator=(Eq_process_lognormal_eulero &obj){
	return *this;
};


//! overloading dell'operatore di assegnamento per la classe figlia: Eq_process_lognormal_esatto
Eq_process &Eq_process::operator=(Eq_process_lognormal_esatto &obj){
	return *this;
};

//##############################################################################################################



