//###################################################################################################
//		
//	FILE NAME :			eq_price.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_price
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe per la gestione del valore di un’azione ad un determinato istante Time. 
//					Contiene quindi un puntatore alla classe Eq_description che permette di identificare a quale azione fa riferimento, 
//					un membro price che contiene il valore del prezzo ed un membro Time, che indica il momento in cui l'azione assume tale prezzo.
//					Per comodità abbiamo implementato un metodo che restituisca direttamente il valore del prezzo in double.
//
//
//	
//	
//	
//	
//	
//#######################################################################################################
#ifndef _EQ_PRICE_HPP
#define _EQ_PRICE_HPP

#include "eq_description.hpp"
#include "price.hpp"
#include "time.hpp"

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta il prezzo di un'azione in un istante fissato.
/*! Classe di livello 4. \n
Classe per la gestione del valore di un’azione ad un determinato istante Time.  \n
Contiene quindi un puntatore alla classe Eq_description che permette di identificare a quale azione fa riferimento, un membro price che contiene il valore del prezzo ed un membro Time, che indica il momento in cui l'azione assume tale prezzo. \n
Per comodità abbiamo implementato un metodo che restituisca direttamente il valore del prezzo in double.
*/

class Eq_price {
	public:
//		COSTRUTTORI~DISTRUTTORE	
		Eq_price();
		Eq_price(Eq_description *eq , Time t , Price p);
		Eq_price(Eq_description *eq);
		Eq_price(const Eq_price &copy);
		~Eq_price();
  	
//		FUNZIONI SET
	  	void Set_price(const Price &p);
	  	void Set_eq(Eq_description *eq);
  		void Set_time(const Time &t);
  	
//		FUNZIONI GET
  		Price Get_Eq_price() const;
		Eq_description *Get_eq() const;
		Time Get_time() const;
		Currency *Get_currency() const;

//		METODI
		double Get_price_double() const;

//		OPERATORE DI ASSEGNAMENTO
		const Eq_price &operator=(const Eq_price &p ); 

//		OVERLOAD DEL COUT
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Eq_price &dat);


	private:
		Eq_description *_equity;
		Price _price;
		Time _time;
};


#endif
