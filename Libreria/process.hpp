//###################################################################################################
//	
//	FILE NAME :			process.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Process
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/feb/5
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' la classe madre dei processi che evolvono secondo funzioni dipendenti da una random variabile.
//					E' una classe completamente astratta; l'unico metodo implementato è l'overloading dell'operatore di assegnamento 
//					che permette di eguagliare un oggetto di questa classe ad un oggetto della classe figlia Eq_process. 
//					Questo è dichiarato virtual perchè possa essere ridefinito nella classe figlia. Questa operazione fa sì che, 
//					qualora ad un puntatore di tipo Process venga assegnato un oggetto di tipo Eq_process, venga richiamato l'operatore 
//					di assegnamento di tipo Eq_process nonostante il puntatore sia del tipo della classe madre.
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _PROCESS_HPP
#define _PROCESS_HPP

#include "eq_price.hpp"
#include "n_rand.hpp"
#include "rand_gen.hpp"
#include <iostream>

using namespace std;

class Eq_process;
//! Classe che rappresenta un generico processo.
/*! Classe di livello 0. \n
E' la classe madre dei processi che evolvono secondo funzioni dipendenti da una random variabile. \n
E' una classe completamente astratta; l'unico metodo implementato è l'overloading dell'operatore di assegnamento che permette di eguagliare un oggetto di questa classe ad un oggetto della classe figlia Eq_process. Questo è dichiarato virtual perchè possa essere ridefinito nella classe figlia. Questa operazione fa sì che, qualora ad un puntatore di tipo Process venga assegnato un oggetto di tipo Eq_process, venga richiamato l'operatore di assegnamento di tipo Eq_process nonostante il puntatore sia del tipo della classe madre.
*/
class Process {

	public:

//		COSTRUTTORE~DISTRUTTORE	
//! costruttore di default
		Process(){};
//! distruttore
		~Process(){};

//		METODI VIRTUAL
//! funzione che permette ad un'azione di evolvere temporalmente		
		virtual void Evol(Eq_price *A,Eq_price *B, N_rand *n) const=0;
//! funzione che restituisce il valore antitetico della random variabile che le viene passata 
		virtual N_rand *Anti_w(N_rand *w) const=0;
//! funzione che restituisce la random variabile usata per far evolvere l'azione
		virtual N_rand *Get_w() const=0;

//		OPERATORE ASSEGNAMENTO
		virtual Process &operator=(Eq_process &obj);
		
	private:

};

#endif
