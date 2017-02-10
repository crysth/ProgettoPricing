//###################################################################################################
//	
//	FILE NAME :			rand_gen_root.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Rand_gen_root
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/mar/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' una classe in grado di generare numeri casuali secondo distribuzioni gaussiana, binaria, e uniforme basata 
//					sulla classe TRandom3 della libreria ROOT (CERN).
//					Abbiamo scelto di formulare anche questa classe come singleton, servendo nella pratica un unico generatore di 
//					numeri casuali, ottimizzando l’utilizzo della libreria.
//
//
//	
//	
//	
//	
//	
//#######################################################################################################

#include "rand_gen_root.hpp"


//#######################################################################################################
//METODO PUBBLICO PER CREARE IL SINGLETON E OTTENERLO
//#######################################################################################################

//! funzione che consente di generare e ottenere il membro statico
Rand_gen_root* Rand_gen_root::Get_rand_gen_root() {
	if(_single==NULL){
		_single = new Rand_gen_root;
	}
	return _single;
};

//#######################################################################################################
//COSTRUTTORE
//#######################################################################################################

//! costruttore di default
Rand_gen_root::Rand_gen_root() : Rand_gen() {
	_gen= new TRandom3(0);
};

//#######################################################################################################
//DISTRUTTORE
//#######################################################################################################

//! distruttore
Rand_gen_root::~Rand_gen_root(){
	delete _gen;
};

//#######################################################################################################
//GAUSSIAN
//#######################################################################################################

//! funzione che permette di ottenere un numero casuale estratto da una distribuzione gaussiana con media m e deviazione standard sig
N_rand *Rand_gen_root::Get_gauss(double m=0 , double sig=1){
	return new N_rand(_gen->Gaus(m,sig)); 
};

//#######################################################################################################
//UNIFORM
//#######################################################################################################

//! funzione che permette di ottenere un numero casuale estratto da una distribuzione uniforme nell'intervallo [in , en]
N_rand  *Rand_gen_root::Get_unif(double in=0, double en=1){
	return new N_rand(_gen->Uniform(in,en)); 
};

//#######################################################################################################
//BINARY
//#######################################################################################################

//! funzione che permette di ottenere un numero casuale che può assumere con la stessa probabilità i valori -1 o +1
N_rand  *Rand_gen_root::Get_binary(){
	
	return new N_rand(floor(_gen->Uniform(0.5,1.5))*2 -1); 
};

//#######################################################################################################


