//###################################################################################################
//	
//	FILE NAME :			Errorlist.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Errorlist
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

#include "errorlist.hpp"

//####################################################################################################################
//COSTRUTTORE
//####################################################################################################################

//! costruttore: è un membro privato che crea il file lista_errori.dat
ErrorList::ErrorList(){
	_stampa.open("lista_errori.dat",ios::out);
	_stampa<<"\t\t==>ERRORI<=="<<endl<<endl;
};

//####################################################################################################################
//DISTRUTTORE
//####################################################################################################################

//! distruttore
ErrorList::~ErrorList(){
	_stampa.close();
};

//####################################################################################################################
//METODO GET
//####################################################################################################################

//! funzione che chiama il costruttore
ErrorList* ErrorList::Get_errorlist() {
	if(_list==NULL){
		_list = new ErrorList;
	}
	return _list;
};

//####################################################################################################################
//METODO ADD
//####################################################################################################################

//! funzione che consente l'aggiunta di un errore al file
void ErrorList::Add_error(string errore){
	_stampa<<errore<<endl<<endl;	
};

//####################################################################################################################



