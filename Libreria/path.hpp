//###################################################################################################
//	
//	FILE NAME :			path.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Path
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta il cammino di evoluzione di un'azione, ovvero i diversi valori che l'azione assume durante un certo lasso di tempo, 
//					controlati con una certa periodicità.
//					Richiamando le classi Process permette di costrutire un cammino, dato un vettore di Deltatime ( una Timestruct da cui ricaviamo 
//					anche la dimensione), a partire da un'azione a prezzo e tempo fissati.
//					Permette inoltre di salvare i numeri random utilizzati per generare ogni passo del cammino, e di generare l'anticammino.  
//	
//	
//
//
//	
//	
//	
//#######################################################################################################

#ifndef _PATH_HPP
#define _PATH_HPP

#include "eq_price.hpp"
#include "eq_process.hpp"
#include "process.hpp"
#include "time.hpp"
#include "n_rand.hpp"
#include "timestruct.hpp"
//! Classe che rappresenta il cammino di un'azione.
/*! Classe di livello 6.\n
Rappresenta il cammino di evoluzione di un'azione, ovvero i diversi valori che l'azione assume durante un certo lasso di tempo, controlati con una certa periodicità.\n
Richiamando le classi Process permette di costrutire un cammino, dato un vettore di Deltatime ( una Timestruct da cui ricaviamo anche la dimensione), a partire da un'azione a prezzo e tempo fissati.\n
Permette inoltre di salvare i numeri random utilizzati per generare ogni passo del cammino, e di generare l'anticammino.  
*/
class Path {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Path();
		Path(const Eq_price &start_price, Timestruct *times, Process *process);
		Path(const Path &copy);
		~Path();

//		METODI
		void Refresh();
		void Reverse();
		void Reverse(Path *cammino);

//		FUNZIONI GET
		Eq_price *Get_eqprice(int i);
		int Get_dim() const;
		N_rand *Get_nrand(int i) const;

//		OPERATORI
		const Path &operator=(const Path &cammino);
		Path operator-()const;

	private:
		Eq_price **_eq_prices;
		N_rand **_num_rand;

		int _dim;
		Process *_process;

};

#endif
