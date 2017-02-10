//###################################################################################################
//	
//	FILE NAME :			rand_gen.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Rand_gen
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/feb/19
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' la classe madre delle classi generatrici di numeri casuali. 
//					E' una classe puramente astratta; l'unico metodo implementato è l'overloading dell'operatore di assegnamento per la 
//					classe figlia Rand_gen_root.
//					Possiede 3 diversi metodi per la generazione di numeri casuali, dichiarati virtual puri perchè possano essere implementati 
//					nelle diverse classi figlie:
//					Get_gauss restituisce un numero casuale estratto da una distribuzione gaussiana,
//					Get_unif che permette di estrarlo da una distribuzione uniforme,
//					Get_binary che permette di estrarlo da una distribuzione binaria.
//	
//	
//	
//#######################################################################################################

#ifndef _RAND_GEN_HPP
#define _RAND_GEN_HPP

#include "n_rand.hpp"
#include <iostream>

class Rand_gen_root;

using namespace std;
//! Classe che rappresenta un generico generatore di numeri casuali.
/*! Classe di livello 1. \n
E' la classe madre delle classi generatrici di numeri casuali. \n
E' una classe puramente astratta; l'unico metodo implementato è l'overloading dell'operatore di assegnamento per la classe figlia Rand_gen_root. \n
Possiede 3 diversi metodi per la generazione di numeri casuali, dichiarati virtual puri perchè possano essere implementati nelle diverse classi figlie: \n
Get_gauss restituisce un numero casuale estratto da una distribuzione gaussiana, \n
Get_unif che permette di estrarlo da una distribuzione uniforme, \n
Get_binary che permette di estrarlo da una distribuzione binaria.
*/
class Rand_gen {

	public:

//		COSTRUTTORE~DISTRUTTORE	
//! costruttore di default
		Rand_gen(){};
//! distruttore
		~Rand_gen(){};

//		METODI VIRTUAL
//! funzione che restituisce un numero random estratto da una distribuzione gaussiana con media m e deviazione standard var		
		virtual N_rand *Get_gauss(double m, double var)=0;
//! funzione che restituisce un numero random estratto da una distribuzione uniforme sull'intervallo di estremi in , en
		virtual N_rand *Get_unif(double in, double en)=0;
//! funzione che restituisce un numero random estratto da una distribuzione binaria 
		virtual N_rand *Get_binary()=0;

//		OPERATORE ASSEGNAMENTO
		virtual Rand_gen &operator=(Rand_gen_root &obj);


	private:

};

#endif
