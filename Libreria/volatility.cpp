//###################################################################################################
//	
//	FILE NAME :			volatility.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Volatility
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	CLASS son :			Vol_std
//	
//	
//	DETAILED DESCRIPTION :	Classe astratta che traduce il concetto di volatilitá di un’azione, è quindi la classe madre delle curve di volatilità.
//					E' una classe puramente astratta in cui l'unico metodo implementato è l'overloading dell'operatore di assegnamento per la classe figlia.
//					La sua funzione principale (Get_vol) viene implementata a partire dal concetto temporale espresso dalla classe Time.
//
//	
//	
//	
//	
//	
//###################################################################################################
#include "volatility.hpp"

//###################################################################################################
//OPERATORE ASSEGNAMENTO
//###################################################################################################

//! operatore di assegnamento per la classe figlia: Vol_std
Volatility &Volatility::operator=(Vol_std &obj){
		cout<<"sono in = Volatility\n";
	return *this;
};

//###################################################################################################

