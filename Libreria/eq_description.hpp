//###################################################################################################
//	
//	FILE NAME :			Eq_description.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_description
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
//	DETAILED DESCRIPTION :  Rappresenta la descrizione di un'azione.
//					Le sue variabili private contengono il nome dell'azione, il suo codice e i puntatori alle curve dei tassi e della
//					volatilità a cui fa riferimento 
//	
//
//
//	
//	
//	
//	
//	
//#######################################################################################################
#ifndef _EQ_DESCRIPTION_HPP
#define _EQ_DESCRIPTION_HPP

#include "volatility.hpp"
#include "vol_std.hpp"
#include "yield_curve.hpp"
#include "yield_curve_flat.hpp"
#include "yield_curve_term_struct.hpp"
#include <string>
#include <iostream>

using namespace std;
//! Classe che rappresenta la descrizione di un'azione.
/*! Classe di livello 3.\n
Rappresenta la descrizione di un'azione.\n
Le sue variabili private contengono il nome dell'azione, il suo codice e i puntatori alle curve dei tassi e della volatilità a cui fa riferimento 
*/
class Eq_description {
	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_description();
  		Eq_description(const string &n, const string &c,Yield_curve *cu, Volatility *v);
		Eq_description(const Eq_description &copy);
  		~Eq_description();
  	
//		FUNZIONI SET
  		void Set_name(const string &n);
  		void Set_code(const string &c);
  		void Set_curve(Yield_curve *cu);
  		void Set_vol(Volatility *v);
  	
//		FUNZIONI GET
 		string Get_name() const;
  		string Get_code() const;
		Yield_curve *Get_curve() const;
		Volatility *Get_vol() const;
		
//		OPERATORE ASSEGNAMENTO
		const Eq_description &operator=(const Eq_description &eq);

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<" 
		friend std::ostream &operator<<(std::ostream &os, const Eq_description &dat);

	private:
		string _name;
		string _code;
		Volatility *_vol;
		Yield_curve *_curve;

};


#endif
