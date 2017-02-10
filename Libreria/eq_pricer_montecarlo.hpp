//###################################################################################################
//	
//	FILE NAME :			eq_pricer_montecarlo.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_pricer_montecarlo
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/apr/6
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Questa classe implementa il metodo Montecarlo per il pricing di un’opzione con un numero N di simulazioni passato al costruttore.
//					Prende come dati di input, oltre al numero di simulazioni, il tipo di opzione e il processo che si vuole utilizzare . Il metodo 
//					Compute_price avvia la simulazione, fa la stima del prezzo e lo attualizza. Utilizza la classe Statistica per fornire una stima 
//					degli errori commessi. Il membro Stima_montecarlo salva i risultati ottenuti.
//					Sia gli oggetti Statistica che Stima_montecarlo sono 3, per permettere all'utilizzatore di scegliere di utilizzare a scelta una 
//					stima condotta solo sui cammini standard, solo sugli anticammini o su cammini standard e anticammini.
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _EQ_PRICER_MONTECARLO_HPP
#define _EQ_PRICER_MONTECARLO_HPP

#include "eq_pricer.hpp"
#include "eq_option.hpp"
#include "eq_process.hpp"
#include "path.hpp"
#include "timestruct.hpp"
#include "process.hpp"
#include "statistica.hpp"
#include "stima_montecarlo.hpp"

#include <iostream>
#include <cmath>
#include <string>

using namespace std;
//! Classe che rappresenta il metodo di montecarlo per il pricing di un'opzione.
/*! Classe di livello 8.\n
Questa classe implementa il metodo Montecarlo per il pricing di un’opzione con un numero N di simulazioni passato al costruttore.\n
Prende come dati di input, oltre al numero di simulazioni, il tipo di opzione e il processo che si vuole utilizzare . Il metodo Compute_price avvia la simulazione, fa la stima del prezzo e lo attualizza. Utilizza la classe Statistica per fornire una stima degli errori commessi. Il membro Stima_montecarlo salva i risultati ottenuti.\n
Sia gli oggetti Statistica che Stima_montecarlo sono 3, per permettere all'utilizzatore di scegliere di utilizzare a scelta una stima condotta solo sui cammini standard, solo sugli anticammini o su cammini standard e anticammini.
*/
class Eq_pricer_montecarlo: public Eq_pricer {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_pricer_montecarlo();
		Eq_pricer_montecarlo(Eq_option *opt, Process *pro, int N);
		~Eq_pricer_montecarlo();

//		METODI
		virtual void Compute_price();
		
//		FUNZIONI GET
		const Stima_montecarlo &Get_Stima(const string &type) const;
		
		const Statistica &Get_stat_std() const;
		const Statistica &Get_stat_anti() const;
		const Statistica &Get_stat_std_anti() const;

		Price Get_price_std() const;
		Price Get_price_anti() const;
		
//		OPERATORE ASSEGNAMENTO
		virtual Eq_pricer_montecarlo &operator=(Eq_pricer_montecarlo &obj);

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, Eq_pricer_montecarlo &dat);

	private:
		int _N;
		Statistica _stat_std, _stat_anti, _stat_std_anti;
		Stima_montecarlo _stima_std,_stima_anti,_stima_std_anti;
};

#endif
