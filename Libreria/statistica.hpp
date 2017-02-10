//###################################################################################################
//	
//	FILE NAME :			statistica.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Statistica
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	DETAILED DESCRIPTION :	Questa classe rappresenta la statistica. Conserva la somma delle osservazioni, dei loro quadrati e conserva un counter interno 
//					per poterne poi fare la media e ottenere quindi informazioni sugli errori quali varianza, deviazione standard, errore assoluto
//					ed errore relativo.     
//
//
//	
//	
//	
//	
//###################################################################################################
#ifndef _STATISTICA_HPP
#define _STATISTICA_HPP

#include "math.h"
//! Classe che rappresenta la statistica.
/*! Classe di livello 0. \n
Questa classe rappresenta la statistica. Conserva la somma delle osservazioni, dei loro quadrati e conserva un counter interno per poterne poi fare la media e ottenere quindi informazioni sugli errori quali varianza, deviazione standard, errore assoluto ed errore relativo.     
*/
class Statistica {
	
	public:
//		COSTRUTTORI~DISTRUTTORE
		Statistica();
		Statistica(const Statistica &copy);
		~Statistica();

//		FUNZIONI GET
	      	double Get_media() const;
	      	double Get_media2() const;
		double Get_var2() const;
     		double Get_standard_deviation() const;
		double Get_errore() const;
		double Get_errore_percentuale() const;
 	
//		METODI
		void Add_observation(double x) ;

//		OPERATORE ASSEGNAMENTO
		const Statistica &operator=(const Statistica &copy);
		
	private:

		double _sum;
		double _sum2;
		int _cont;

};
#endif
