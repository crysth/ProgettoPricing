//###################################################################################################
//	
//	FILE NAME :			yield_curve.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Yield_curve
//	
//	FIRST VERSION :		2009/dec/13
//	
//	LAST UPTime : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' la classe madre delle curve del tasso e per questo contiene gli overloading delle funzioni di assegnamento delle classi figlie,
//					dichiarati virtual.
//					Le funzioni che restituiscono lo spot-rate ovvero il tasso ad un tempo ben preciso sono chiaramente virtual pure, poichè saranno
//					implementate diversamente in ogni classe figlia.
//					Sono già implementate le funzioni Get_forward_rate e Get_discount_factor che prescindono dalla struttura delle calssi derivate 
//					poichè necessitano delle generiche funzioni Get_spot_rate .
//	
//	
//	
//	
//	
//###################################################################################################



#ifndef _YIELD_CURVE_HPP
#define _YIELD_CURVE_HPP

#include "time.hpp"
#include <iostream>

class Yield_curve_flat;
class Yield_curve_term_struct;

using namespace std;
//! Classe che rappresenta una generica curva dei tassi.
/*! Classe di livello 2. \n
E' la classe madre delle curve del tasso e per questo contiene gli overloading delle funzioni di assegnamento delle classi figlie, dichiarati virtual. \n
Le funzioni che restituiscono lo spot-rate ovvero il tasso ad un tempo ben preciso sono chiaramente virtual pure, poichè saranno implementate diversamente in ogni classe figlia. \n
Sono già implementate le funzioni Get_forward_rate e Get_discount_factor che prescindono dalla struttura delle calssi derivate poichè necessitano delle generiche funzioni Get_spot_rate. 
*/
class Yield_curve {

	public:
//		METODI VIRTUAL
//! restitisce il tasso ad un tempo t ( è virtual pura)
		virtual double Get_spot_rate(const Time &t) const=0;
//! restitisce il tasso dopo un intervallo di tempo t ( è virtual pura)
		virtual double Get_spot_rate(const Deltatime &t) const=0;

//		FUNZIONI GET
		double Get_discount_factor(const Time &t) const;
		double Get_discount_factor(const Time &t1, const Time &t2) const;
		double Get_discount_factor(const Deltatime &delta) const;

		double Get_forward_rate(const Time &t1, const Time &t2) const;
		double Get_forward_rate(const Time &t, const Deltatime &delta) const;

//		OPERATORI ASSEGNAMENTO
		virtual Yield_curve &operator=(Yield_curve_flat &obj);
		virtual Yield_curve &operator=(Yield_curve_term_struct &obj);

	private:

};

#endif
