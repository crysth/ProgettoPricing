//###################################################################################################################
//	
//	FILE NAME :		pricing.hpp
//	
//	FILE TYPE :		C++ file
//	
//	AUTHORS :		Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Pricing
//	
//	FIRST VERSION :		2010/apr/11
//	
//	LAST UPTIME : 		2010/apr/12
//	
//	STATUS :		final
//	
//	COPYRIGHT :		none
//	
//	
//	DETAILED DESCRIPTION :	Classe ad hoc per la risoluzione del tema d'esame. Grazie a questa classe è possibile ottenere 
//				un file di testo (passatone il nome al costruttore) nel quale vengono stampati direttamente dalla 
//				classe i risultati della simulazione. Al costruttore vengono passati tutti i parametri fissati (in double 
//				o int) e tutti i parametri che si vogliono far variare (come vettori di double, int o deltatime); al 
//				costruttore viene passato anche il tipo di processo (come string) che si vuole utilizzare per l'evoluzione
//				dell'azione. Ogni costruttore rappresenta una delle simulazioni richieste dal tema d'esame.
//				1. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di maturity time. 
//					La simulazione viene eseguita per ogni valore di m.
//				2. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di lambda. 
//					La simulazione viene eseguita per ogni valore di m.
//				3. Costruttore che permette di studiare l'andamento dell'errore in dipendenza dal numero di simulazioni N.
//				4. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di volatilità. 
//					La simulazione viene eseguita per ogni valore di m.
//				5. Costruttore che permette di studiare la variazione del prezzo di un'opzione plain-vanilla. 
//					La simulazione viene eseguita per ogni valore di m.
//				6. Costruttore che permette di effettuare un test della libreria e del generatore di numeri casuali tramite l'opzione 
//					Eq_op_w.La simulazione viene eseguita per ogni valore di m.
//				Questa classe permette un utilizzo rapido e pratico di tutta la libreria.
//				Abbiamo volutamente evitato l'implementazione di un costruttore generico, implementando invece costruttori mirati ai
//				problemi del tema d'esame, per ottimizzare l'esecuzione di ogni simulazione. 	
//	
//###################################################################################################################


//###################################################################################################################
//INCLUDE
//###################################################################################################################

#ifndef _PRICING_HPP
#define _PRICING_HPP

#include <iostream>
#include <string>
#include <cstdlib>

#include "timestruct.hpp"
#include "deltatime.hpp"
#include "time.hpp"
#include "yield_curve_term_struct.hpp"
#include "yield_curve_flat.hpp"
#include "currency.hpp"
#include "price.hpp"
#include "eq_price.hpp"
#include "vol_std.hpp"
#include "process.hpp"
#include "eq_process.hpp"
#include "eq_process_lognormal_eulero.hpp"
#include "eq_process_lognormal_esatto.hpp"
#include "eq_option.hpp"
#include "eq_description.hpp"
#include "eq_pricer_montecarlo.hpp"
#include "rand_gen_root.hpp"
#include "errorlist.hpp"
#include "eq_op_performance_with_corridor.hpp"
#include "eq_process_lognormal_binary.hpp"
#include "eq_op_plainvanilla.hpp"
#include "eq_op_w.hpp"

using namespace std;
//! Classe ad hoc per la risoluzione del tema d'esame. 
/*! Classe di livello 9. \n 
Classe ad hoc per la risoluzione del tema d'esame. Grazie a questa classe è possibile ottenere un file di testo (passatone il nome al costruttore) nel quale vengono stampati direttamente dalla classe i risultati della simulazione. Al costruttore vengono passati tutti i parametri fissati (in double o int) e tutti i parametri che si vogliono far variare (come vettori di double, int o deltatime); al costruttore viene passato anche il tipo di processo (come string) che si vuole utilizzare per l'evoluzione dell'azione. Ogni costruttore rappresenta una delle simulazioni richieste dal tema d'esame. \n
1. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di maturity time. La simulazione viene eseguita per ogni valore di m. \n
2. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di lambda. La simulazione viene eseguita per ogni valore di m. \n
3. Costruttore che permette di studiare l'andamento dell'errore in dipendenza dal numero di simulazioni N. \n
4. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di volatilità. La simulazione viene eseguita per ogni valore di m. \n
5. Costruttore che permette di studiare la variazione del prezzo di un'opzione plain-vanilla. La simulazione viene eseguita per ogni valore di m. \n
6. Costruttore che permette di effettuare un test della libreria e del generatore di numeri casuali tramite l'opzione Eq_op_w.La simulazione viene eseguita per ogni valore di m. \n
Questa classe permette un utilizzo rapido e pratico di tutta la libreria. \n
Abbiamo volutamente evitato l'implementazione di un costruttore generico, implementando invece costruttori mirati ai problemi del tema d'esame, per ottimizzare l'esecuzione di ogni simulazione. 
*/
class Pricing {

	public:
//		COSTRUTTORI~DISTRUTTORE

		Pricing();
		//COSTRUTTORE 1 (variazione del price per maturity time)
		Pricing(int N, double S_O, double strikeprice, double rate, double volatility, Timestruct T_maturity, double lambda, int *m, int dim_m, string name_process, const char *nome_file_out);
		//COSTRUTTORE 2 (variazione del price per lambda)
		Pricing(int N, double S_O, double strikeprice, double rate, double volatility, const Deltatime &T_maturity, double *lambda, int dim_lambda, int *m, int dim_m, string name_process, const char *nome_file_out);
		//COSTRUTTORE 3 (controllo errori su N simulazioni variabile)
		Pricing(int *N, int dim_N, double S_O, double strikeprice, double rate, double volatility, const Deltatime &T_maturity, double lambda, int m, string name_process, const char *nome_file_out);
		//COSTRUTTORE 4 (variazione del price per la volatilità)
		Pricing(int N, double S_O, double strikeprice, double rate, double *volatility, int dim_vol, const Deltatime &T_maturity, double lambda, int *m, int dim_m, string name_process, const char *nome_file_out);
		//COSTRUTTORE 5 (PLAINVANILLA)
		Pricing(int N, double S_O, double strikeprice, double rate, double volatility, Timestruct T_maturity, int *m, int dim_m, const char *nome_file_out);
		//COSTRUTTORE 6 (opzione W - test sul generatore di numeri casuali e sull'implementazione)
		Pricing(int N, double S_O, double rate, double volatility, const Deltatime &T_maturity, int *m, int dim_m, const char *nome_file_out);

		~Pricing();



	private:
		
};

#endif
