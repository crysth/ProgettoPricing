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

#ifndef _EQ_PROCESS_HPP
#define _EQ_PROCESS_HPP

#include "process.hpp" 

#include "eq_price.hpp"
#include "n_rand.hpp"
#include "rand_gen.hpp"
#include "rand_gen_root.hpp"
#include <iostream>

using namespace std;

class Eq_process_lognormal_eulero;
class Eq_process_lognormal_esatto;
//! Classe che rappresenta il generico concetto di processo relativo ad un'azione.
/*! Classe di livello 5.\n
E' la classe madre dei processi che regolano l'evoluzione temporale (da uno stato A di partenza ad uno stato di arrivo B) di un'azione secondo funzioni dipendenti da una random variabile.\n
Pur rimanendo una classe prevalentemente astratta, permette di gestire i numeri casuali necessari alla funzione che regola l'evoluzione.\n
Permettere di scegliere il generatore di numeri casuali.   
*/
class Eq_process : public Process {

	public:
		
//		COSTRUTTORI~DISTRUTTORE
		Eq_process();
		~Eq_process();

//		FUNZIONI
//! funzione che fa evolvere un'azione al tempo t1 in un'altra al tempo t2 ( virtual pura)
		virtual void Evol(Eq_price *A,Eq_price *B, N_rand *w) const=0;
//! funzione che restituisce il numero casuale estratto da una distribuzione ( virtual pura, l'implementazione è lasciata alle figlie)
		virtual N_rand *Get_w() const=0;
		virtual N_rand *Anti_w(N_rand *w) const;

//		FUNZIONI GET~SET
		Rand_gen *Get_rand_gen() const;
		void Set_rand_gen(Rand_gen *ra);
		void Set_rand_gen(void);

//		OPERATORI ASSEGNAMENTO
		virtual Eq_process &operator=(Eq_process_lognormal_eulero &obj);
		virtual Eq_process &operator=(Eq_process_lognormal_esatto &obj);

	private:
		Rand_gen *_ra;

};

#endif
