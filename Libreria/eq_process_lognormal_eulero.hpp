//###################################################################################################
//	
//	FILE NAME :			eq_process.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_process
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
//	DETAILED DESCRIPTION :	Rappresenta i processi che regolano l'evoluzione temporale di una azione che segua un processo lognormale secondo funzioni 
//					che dipendono da una random variabile gaussiana con media nulla e varianza unitaria. Il processo qui implementato permette 
//					la valutazione con formula approssiamta di Eulero: 
//					P = Po +   (r*(t2-t1) + s*(sqrt( t2 - t1 )) * w) * Po  
//					dove P è il prezzo finale al tempo t2, Po il prezzo iniziale al tempo t1, r il tasso forward tra i tempi t1 e t2, s rappresenta 
//					la volatilità e w è la variabile estratta dalla gaussiana.    
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _EQ_PROCESS_LOGNORMAL_EULERO_HPP
#define _EQ_PROCESS_LOGNORMAL_EULERO_HPP

#include "eq_process.hpp" 

#include <iostream>

using namespace std;
//! Classe che rappresenta un processo lognormale valutato con la formula approssimata di Eulero. 
/*! Classe di livello 5. \n
Rappresenta i processi che regolano l'evoluzione temporale di una azione che segua un processo lognormale secondo funzioni che dipendono da una random variabile gaussiana con media nulla e varianza unitaria. Il processo qui implementato permette la valutazione con formula approssiamta di Eulero: \n
P = Po +   (r*(t2-t1) + s*(sqrt( t2 - t1 )) * w) * Po  \n
dove P è il prezzo finale al tempo t2, Po il prezzo iniziale al tempo t1, r il tasso forward tra i tempi t1 e t2, s rappresenta la volatilità e w è la variabile estratta dalla gaussiana.    
*/
class Eq_process_lognormal_eulero : public Eq_process {

	public:
		
//		COSTRUTTORI~DISTRUTTORE
		Eq_process_lognormal_eulero ();
		Eq_process_lognormal_eulero (Rand_gen *ra);
		~Eq_process_lognormal_eulero ();

//		METODI		
		virtual void Evol(Eq_price *A,Eq_price *B, N_rand *w) const;
		virtual N_rand *Get_w() const;

//		OPERATORE ASSEGNAMENTO
		virtual Eq_process_lognormal_eulero &operator=(Eq_process_lognormal_eulero &obj);

		
	private:

};

#endif
