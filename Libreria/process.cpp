//###################################################################################################
//	
//	FILE NAME :			process.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Process
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

#include "process.hpp"


//###################################################################################################
//OPERATORE ASSEGNAMENTO
//###################################################################################################

//! overloading dell'operatore di assegnamento della classe figlia: Eq_process
Process &Process::operator=(Eq_process &obj){
		cout<<"sono in = Process\n";
	return *this;
};

//###################################################################################################




