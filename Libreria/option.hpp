//###################################################################################################
//	
//	FILE NAME :			option.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Option
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/feb/11
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe astratta che rappresenta genericamente un’opzione. Ogni tipo di opzione verrá ovviamente derivata da questa,
//					implementando la funzione virtual pura definente il payoff.
//					L'unico metodo implementato è l'operatore di assegnamento per la classe figlia Eq_option, dichiarato virtual, 
//					necessario per permettere una maggiore elasticità del codice.
//
//
//	
//	
//	
//	
//	
//#######################################################################################################
#ifndef _OPTION_HPP
#define _OPTION_HPP

#include <iostream>

class Eq_option;

using namespace std;
//! Classe che rappresenta il generico concetto di opzione.
/*! Classe di livello 0. \n
Classe astratta che rappresenta genericamente un’opzione. Ogni tipo di opzione verrá ovviamente derivata da questa, implementando la funzione virtual pura definente il payoff. \n
L'unico metodo implementato è l'operatore di assegnamento per la classe figlia Eq_option, dichiarato virtual, necessario per permettere una maggiore elasticità del codice.
*/
class Option {

	public:
//! costruttore di default
		Option(){};
//! distruttore
		~Option(){};

		virtual Option &operator=(Eq_option &obj);

	private:
		
};

#endif
