//###################################################################################################
//	
//	FILE NAME :			eq_process_lognormal_binary.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_process_lognormal_binary
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

#ifndef _EQ_PROCESS_LOGNORMAL_BINARY_HPP
#define _EQ_PROCESS_LOGNORMAL_BINARY_HPP

#include "eq_process_lognormal_esatto.hpp" 

#include <iostream>

using namespace std;
//! Classe che rappresenta un processo lognormale esatto la cui evoluzione dipende da una variabile stocastica binaria.
/*! Classe di livello 5. \n
Rappresenta un processo lognormale esatto la cui evoluzione dipende da una random variabile estratta da una distribuzione binaria che può quindi assumere i soli valori +1 o -1. Per questo motivo è stata derivata dalla classe Eq_process_lognormal_esatto da cui eredita la formula di evoluzione, con la sola differenza che la generazione di numeri
casuali viene reimplementata secondo un’estrazione binaria.
*/
class Eq_process_lognormal_binary : public Eq_process_lognormal_esatto {

	public:

//		COSTRUTTORI~DISTRUTTORE
		Eq_process_lognormal_binary();
		Eq_process_lognormal_binary(Rand_gen *ra);
		~Eq_process_lognormal_binary();

//		METODI		
		virtual N_rand *Get_w() const;

//		OPERATORE ASSEGNAMENTO
		virtual Eq_process_lognormal_binary &operator=(Eq_process_lognormal_binary &obj);
		
	private:

};

#endif
