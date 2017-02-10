//###################################################################################################
//	
//	FILE NAME :			Errorlist.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Errorlist
//	
//	FIRST VERSION :		2010/feb/10
//	
//	LAST UPTIME : 		2010/mar/15
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe che rappresenta la coda di stampa degli errori di scorretto utilizzo della libreria.
//					Ogni volta che la libreria viene utilizzata erroneamente, viene inviato un messaggio di errore alla classe Errorlist
//					che stamperá sul file lista_errori.dat l’elenco degli errori. Essendo un singleton, il costruttore é privato. 
//					Si evita in tal modo che venga costruito piú di un oggetto di tipo Errorlist, che sarebbe evidentemente un inutile spreco di memoria,
//					 e tutti i messaggi di errori vengono quindi gestiti da un unico oggetto.
//
//
//
//	
//#######################################################################################################

#ifndef _ERRORLIST_HPP
#define _ERRORLIST_HPP
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
//! Classe che rappresenta la coda di stampa degli errori.
/*! Classe di livello 0. \n
Classe che rappresenta la coda di stampa degli errori di scorretto utilizzo della libreria. \n
Ogni volta che la libreria viene utilizzata erroneamente, viene inviato un messaggio di errore alla classe Errorlist che stamperá sul file lista_errori.dat l’elenco degli errori. Essendo un singleton, il costruttore é privato. Si evita in tal modo che venga costruito piú di un oggetto di tipo Errorlist, che sarebbe evidentemente un inutile spreco di memoria, e tutti i messaggi di errori vengono quindi gestiti da un unico oggetto.
*/
class ErrorList {

	public:

//		CREA IL SINGLETON
		static ErrorList* Get_errorlist() ;

//		PER AGGIUNGERE GLI ERRORI AL FILE
		void Add_error(string errore);

//		DISTRUTTORE
		~ErrorList();
	
	private:

//		COSTRUTTORE
		ErrorList();

//		INSTANCE
		static ErrorList *_list;

//		MEMBRO PRIVATO
		fstream _stampa; 	
	
};

#endif
