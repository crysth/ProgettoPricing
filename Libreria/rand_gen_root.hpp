//###################################################################################################
//	
//	FILE NAME :			rand_gen_root.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Rand_gen_root
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/mar/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' una classe in grado di generare numeri casuali secondo distribuzioni gaussiana, binaria, e uniforme basata 
//					sulla classe TRandom3 della libreria ROOT (CERN).
//					Abbiamo scelto di formulare anche questa classe come singleton, servendo nella pratica un unico generatore di 
//					numeri casuali, ottimizzando l’utilizzo della libreria.
//	
//	
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _RAND_GEN_ROOT_HPP
#define _RAND_GEN_ROOT_HPP

#include "TRandom3.h"
#include "rand_gen.hpp"
#include "n_rand.hpp"
#include "math.h"
#include <iostream>
using namespace std;
//! Generatore di numeri casuali basato sulla libreria ROOT (CERN).
/*! Classe di livello 1. \n
E' una classe in grado di generare numeri casuali secondo distribuzioni gaussiana, binaria, e uniforme basata sulla classe TRandom3 della libreria ROOT (CERN). \n
Abbiamo scelto di formulare anche questa classe come singleton, servendo nella pratica un unico generatore di numeri casuali, ottimizzando l’utilizzo della libreria.
*/
class Rand_gen_root: public Rand_gen {
	
	public:

//		CREA IL SINGLETON
		static Rand_gen_root* Get_rand_gen_root();

//		DISTRUTTORE
		~Rand_gen_root();
		
//		FUNZIONI
		virtual N_rand *Get_gauss(double m , double sig);
		virtual N_rand *Get_unif(double in, double en);
		virtual N_rand *Get_binary();


	private:
//		COSTRUTTORE
		Rand_gen_root();

		static Rand_gen_root *_single;
		TRandom *_gen;
};

#endif
