//###################################################################################################
//	
//	FILE NAME :			volatility.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Volatility
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
#ifndef _VOLATILITY_HPP
#define _VOLATILITY_HPP

#include "time.hpp"

#include <iostream>

class Vol_std;

using namespace std;
//! Classe che rappresenta il concetto di curva di volatilità di un'azione.
/*! Classe di livello 2. \n
Classe astratta che traduce il concetto di volatilitá di un’azione, è quindi la classe madre delle curve di volatilità. \n
E' una classe puramente astratta in cui l'unico metodo implementato è l'overloading dell'operatore di assegnamento per la classe figlia. \n
La sua funzione principale (Get_vol) viene implementata a partire dal concetto temporale espresso dalla classe Time. 
*/
class Volatility {

	public:
//		COSTRUTTORE~DISTRUTTORE	
//! costruttore di default	
  		Volatility(){};
//! distruttore
  		~Volatility(){};
  
//		METODI VIRTUAL	
//! funzione che restituisce la volatilità tra i tempi t1 e t2 (virtual pura)
    		virtual double Get_vol(const Time &t1, const Time &t2) const = 0;

//		OPERATORE ASSEGNAMENTO
		virtual Volatility &operator=(Vol_std &obj);

	private:

};


#endif
