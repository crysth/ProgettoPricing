//###################################################################################################
//	
//	FILE NAME :			eq_process_lognormal_binary.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_process_lognormal_binary
//	
//	FIRST VERSION :		2010/apr/10
//	
//	LAST UPTIME : 		2010/apr/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta un processo lognormale esatto la cui evoluzione dipende da una random variabile estratta da una distribuzione 
//					binaria che può quindi assumere i soli valori +1 o -1. Per questo motivo è stata derivata dalla classe Eq_process_lognormal_esatto 
//					da cui eredita la formula di evoluzione, con la sola differenza che la generazione di numeri casuali viene reimplementata secondo
//					un’estrazione binaria.
//	
//
//	
//	
//	
//	
//	
//#######################################################################################################

#include "eq_process_lognormal_binary.hpp"

#include <cmath>
#include <iostream>

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Eq_process_lognormal_binary::Eq_process_lognormal_binary(): Eq_process_lognormal_esatto(){
	Set_rand_gen();
};


//! costruttore
Eq_process_lognormal_binary::Eq_process_lognormal_binary(Rand_gen *ra): Eq_process_lognormal_esatto(){
	Set_rand_gen(ra);
};


//! distruttore
Eq_process_lognormal_binary::~Eq_process_lognormal_binary(){};

//##############################################################################################################
//GENERAZIONE NUMERI CASUALI
//##############################################################################################################

//! funzione che restituisce un numero casuale estratto da una distribuzione binaria -1 o +1
N_rand *Eq_process_lognormal_binary::Get_w() const{
		return Get_rand_gen()->Get_binary();
};


//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento 
Eq_process_lognormal_binary &Eq_process_lognormal_binary::operator=(Eq_process_lognormal_binary &obj){
		cout<<"sono in = Eq_process_lognormale_binary\n";
	Set_rand_gen(obj.Get_rand_gen());
	return *this;
};

//##############################################################################################################

