

//###################################################################################################
//	
//	FILE NAME :			price.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Price
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/feb/5
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta un prezzo, pensato come un numero reale positivo, riferito ad un'opportuna valuta.
//	
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

#ifndef _PRICE_HPP
#define _PRICE_HPP

#include "currency.hpp"
#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta il prezzo.
/*! Classe di livello 1. \n
Rappresenta un prezzo, pensato come un numero reale positivo, riferito ad un'opportuna valuta.
*/
class Price {

	public:

//		COSTRUTTORI~DISTRUTTORE	
		Price();
		Price(double c);
		Price(double p, Currency *c);
  		~Price();
		
//		FUNZIONI SET~GET
		void Set_price(double p);
  		void Set_curr(Currency *c);

  		double Get_price() const;
		Currency *Get_currency() const;
  		
//		OPERATORE ASSEGNAMENTO
  		const Price &operator=(const Price &p);

//		OPERATORI
  		Price operator*(double p) const;
		Price operator+(double p) const;
  		const Price &operator+=(Price p );
  		Price operator/(double d) const;
  		Price operator/(int d) const;

//		FRIEND
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Price &pri);
//! overloading dell'operatore di divisione di un double per un un prezzo
		friend double operator/(double d, const Price &p) ;

	private:
		double _price;
		Currency *_val;
};


#endif
