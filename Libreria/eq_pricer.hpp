//###################################################################################################
//	
//	FILE NAME :			eq_pricer.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_pricer
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/mar/9
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' una classe astratta, madre delle simulazioni dei prezzi di un'opzione. Il metodo Compute_price è dichiarato virtual puro. 
//					Consente di impostare e ottenere il prezzo e i puntatori all'opzione considerata e al processo utilizzato.
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
#ifndef _EQ_PRICER_HPP
#define _EQ_PRICER_HPP

#include "option.hpp"
#include "price.hpp"
#include "eq_option.hpp"
#include "eq_process.hpp"
#include "process.hpp"

#include <iostream>

class Eq_pricer_montecarlo;

using namespace std;
//! Classe che rappresenta un generico metodo di simulazione, per ottenere i prezzi di un'opzione. 
/*! Classe di livello 8. \n
E' una classe astratta, madre delle simulazioni dei prezzi di un'opzione. Il metodo Compute_price è dichiarato virtual puro. \n
Consente di impostare e ottenere il prezzo e i puntatori all'opzione considerata e al processo utilizzato.
*/
class Eq_pricer {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_pricer();
		~Eq_pricer();

//		FUNZIONI VIRTUAL
//! funzione che valuta il prezzo dell'opzione ( virtual pura)
		virtual void Compute_price()=0;

//		FUNZIONI GET
		Price Get_price() const;
		Eq_option *Get_Eq_option() const;
		Process *Get_process() const;

//		FUNZIONI SET
		void Set_Eq_option(Eq_option *eq_option);
		void Set_price(const Price &price);
		void Set_process(Process* process);

//		OPERATORE ASSEGNAMENTO
		virtual Eq_pricer &operator=(Eq_pricer_montecarlo &obj);


	private:
		Eq_option *_eq_option;
		Process *_process;
		Price _price;
};

#endif
