//###################################################################################################
//	
//	FILE NAME :			stima_montecarlo.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Stima_montecarlo
//	
//	FIRST VERSION :		2010/mar/26
//	
//	LAST UPTIME : 		2010/mar/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta la stima ottenuta da N simulazioni di montecarlo. Salva i dati del prezzo e dell'errore assoluto in modo 
//					che siano facilmente accessibili al termine di una simulazione.
//	
//
//
//
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _STIMA_MONTECARLO_HPP
#define _STIMA_MONTECARLO_HPP

#include <iostream>

#include "statistica.hpp"

using namespace std;
//! Classe che rappresenta la stima ottenuta da N simulazioni di montecarlo.
/*! Classe di livello 1. \n
Rappresenta la stima ottenuta da N simulazioni di montecarlo. Salva i dati del prezzo e dell'errore assoluto in modo che siano facilmente accessibili al termine di una simulazione.
*/
class Stima_montecarlo {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Stima_montecarlo();
		Stima_montecarlo(double prezzo, double err_assoluto);
		~Stima_montecarlo();

//		FUNZIONI GET
		double Get_prezzo() const;
		double Get_errore_assoluto() const;
		double Get_errore_relativo() const;
		
//		FUNZIONI SET
		void Set_prezzo(double prezzo);
		void Set_errore_assoluto(double err_assoluto);
		void Set(const Statistica &stat);
		
//		OPERATORE ASSEGNAMENTO
		Stima_montecarlo &operator=(Stima_montecarlo &obj);

//		OVERLOAD DEL COUT
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, Stima_montecarlo &dat);

	private:
		double _prezzo;
		double _err_assoluto;
};

#endif
