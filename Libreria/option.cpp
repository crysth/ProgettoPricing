//###################################################################################################
//	
//	FILE NAME :			option.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Option
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

#include "option.hpp"

//########################################################################################################################
//OPERATORE ASSEGNAMENTO
//########################################################################################################################

//! overloading dell'operatore di assegnamento per la classe figlia: Eq_option.
Option &Option::operator=(Eq_option &obj){
		cout<<"sono in = Option\n";
	return *this;
};

//########################################################################################################################

