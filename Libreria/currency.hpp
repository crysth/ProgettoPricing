//###################################################################################################
//	
//	FILE NAME :			currency.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Currency
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/25
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	 Classe che rappresenta la valuta. Contiene tra i membri privati un intero al quale corrisponde una valuta predefinita.
//					 La valuta impostata di default è l'euro (EUR).
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
#ifndef _CURRENCY_HPP
#define _CURRENCY_HPP

#include <string>
#include <iostream>

using namespace std;
//! Classe che rappresenta la valuta.
/*! Classe di livello 0. \n
 Classe che rappresenta la valuta. Contiene tra i membri privati un intero al quale corrisponde una valuta predefinita. \n
La valuta impostata di default è l'euro (EUR).
*/
class Currency{
	
	public:
//		COSTRUTTORI~DISTRUTTORE
	  	Currency();
		Currency(const string &c);	 
		~Currency();

//		FUNZIONI SET~GET
		void Set_currency(const string &c);
		string Get_currency() const;

//		OPERATORE ASSEGNAMENTO
 		const Currency &operator=(const Currency &p);

//		OPERATORI LOGICI
		bool operator==(const Currency &dat) const;
		bool operator!=(const Currency &dat) const;

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Currency &cu);


	private:
	  	int _curr;

};

#endif
