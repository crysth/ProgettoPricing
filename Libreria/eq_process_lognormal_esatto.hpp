//###################################################################################################
//	
//	FILE NAME :			eq_process_lognormal_esatto.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_process_lognormal_esatto
//	
//	FIRST VERSION :		2010/mar/23
//	
//	LAST UPTIME : 		2010/apr/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta i processi che regolano l'evoluzione temporale di una azione che segua un processo lognormale secondo funzioni 
//					che dipendono da una random variabile gaussiana con media nulla e varianza unitaria. Il processo qui implementato permette 
//					la valutazione con formula integrale esatta:
//					P = Po*exp( (r - (s^2)/2)* dt  +  s * sqrt(dt) * w ) 
//					dove P è il prezzo finale al tempo t, Po il prezzo iniziale al tempo to, r il tasso forward tra i tempi to e t, 
//					s rappresenta la volatilità, w è la variabile estratta dalla gaussiana e dt = t - to.  
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _EQ_PROCESS_LOGNORMAL_ESATTO_HPP
#define _EQ_PROCESS_LOGNORMAL_ESATTO_HPP

#include "eq_process.hpp"

#include <iostream>

class Eq_process_lognormal_binary;

using namespace std;
//! Classe che rappresenta un processo lognormale esatto dipendente da una random variabile gaussiana.
/*! Classe di livello 5. \n
Rappresenta i processi che regolano l'evoluzione temporale di una azione che segua un processo lognormale secondo funzioni che dipendono da una random variabile gaussiana con media nulla e varianza unitaria. Il processo qui implementato permette la valutazione con formula integrale esatta:\n
P = Po*exp( (r - (s^2)/2)* dt  +  s * sqrt(dt) * w ) \n
dove P è il prezzo finale al tempo t, Po il prezzo iniziale al tempo to, r il tasso forward tra i tempi to e t, s rappresenta la volatilità, w è la variabile estratta dalla gaussiana e dt = t - to.    
*/
class Eq_process_lognormal_esatto : public Eq_process {

	public:

//		COSTRUTTORI~DISTRUTTORE
		Eq_process_lognormal_esatto();
		Eq_process_lognormal_esatto(Rand_gen *ra);
		~Eq_process_lognormal_esatto();

//		METODI		
		virtual void Evol(Eq_price *A,Eq_price *B, N_rand *w) const;
		virtual N_rand *Get_w() const;
//		OPERATORE ASSEGNAMENTO
		virtual Eq_process_lognormal_esatto &operator=(Eq_process_lognormal_esatto &obj);
		virtual Eq_process_lognormal_esatto &operator=(Eq_process_lognormal_binary &obj);
		
	private:

};

#endif
