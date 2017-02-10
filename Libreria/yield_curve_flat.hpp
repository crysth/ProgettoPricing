//###################################################################################################
//	
//	FILE NAME :			yield_curve_flat.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Yield_curve_flat
//	
//	FIRST VERSION :		2009/dec/13
//	
//	LAST UPDATE : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta una curva dei tassi piatta, ovvero costante nel tempo. Contiene un membro statico per la dichiarazione della curva risk-free.
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
//###################################################################################################


#ifndef _YIELD_CURVE_FLAT_HPP
#define _YIELD_CURVE_FLAT_HPP

#include "yield_curve.hpp"

#include <iostream>

#include "time.hpp"

using namespace std;
//! Classe che rappresenta una curva dei tassi costante.
/*! Classe di livello 2. \n
Rappresenta una curva dei tassi piatta, ovvero costante nel tempo. Contiene un membro statico per la dichiarazione della curva risk-free.
*/
class Yield_curve_flat: public Yield_curve {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Yield_curve_flat();
		Yield_curve_flat(double rate);
		Yield_curve_flat(const Yield_curve_flat &fla);
		~Yield_curve_flat();

//		FUNZIONI
		virtual double Get_spot_rate(const Time &t) const;
		virtual double Get_spot_rate(const Deltatime &t) const;

//		FUNZIONI GET
		double Get_rate() const;

//		FUNZIONI SET
		void Set_rate(double rate);		

//		OPERATORI
//! overloading dell'operatore "<<"
		friend std::ostream &operator<<(std::ostream &os, const Yield_curve_flat &fla);

//		OPERATORE ASSEGNAMENTO
		virtual Yield_curve_flat &operator=(Yield_curve_flat &obj);

//		FUNZIONI CURVERISKFREE
		static void Set_riskfree(Yield_curve_flat &y);
		static void Set_riskfree(double rate);
		static Yield_curve_flat* Get_riskfree();

	private:
		double _rate;
		static Yield_curve_flat *_riskfree;
};

#endif
