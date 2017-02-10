//###################################################################################################
//	
//	FILE NAME :			rand_gen.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Rand_gen
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
#include "rand_gen.hpp"


//###################################################################################################
//OPERATORE ASSEGNAMENTO
//###################################################################################################

//! overloading dell'operatore di assegnamento per la classe figlia: Rand_gen_root 
Rand_gen &Rand_gen::operator=(Rand_gen_root &obj){
		cout<<"sono in = Rand_gen\n";
	return *this;
};

//###################################################################################################

