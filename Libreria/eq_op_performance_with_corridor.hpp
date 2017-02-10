//###################################################################################################
//	
//	FILE NAME :			eq_op_performance_with_corridor.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_op_performance_with_corridor
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/apr/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta un particolare tipo di opzione di tipo europeo, path dependent secondo questo contratto:
//					Sia T la data di maturità e t=0 la data attuale, indichiamo con S(t) il prezzo del sottostante al tempo t.
//					Definiamo il  Pay-off = 1 * valuta * Max[P-E,0], dove E è una sorta di strike-price dell'opzione e P è definito come la sommatoria 
//					su "i" da 1 a m dei P(i) così definiti: 
//					P(i) = Min[ Max[ S(t+1)/S(t) - 1 , l], u]
//					m rappresenta il numero di intervalli regolari in cui viene suddiviso l' intervallo temporale (0,T) 
//					e definiamo dt = T / m .( (T - t(0))/m ). Definiamo l e u come:
//					l = EXP(r * dt)/k - 1 
//					u = EXP(r * dt)*k -1
//					dove k è una costante che dipende dalla grandezza dt : k = 1 + lambda * sqrt(dt).
//	
//	
//	
//#######################################################################################################
#ifndef _EQ_OP_PERFORMANCE_WITH_CORRIDOR_HPP
#define _EQ_OP_PERFORMANCE_WITH_CORRIDOR_HPP

#include "eq_option.hpp"

#include "yield_curve_flat.hpp"
#include "path.hpp"
#include "eq_price.hpp"
#include "timestruct.hpp"

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta il contratto dell'opzione in esame.
/*! Classe di livello 7. \n
Rappresenta un particolare tipo di opzione di tipo europeo, path dependent secondo questo contratto: \n
	Sia T la data di maturità e t=0 la data attuale, indichiamo con S(t) il prezzo del sottostante al tempo t. \n
	Definiamo il  Pay-off = 1 * valuta * Max[P-E,0], dove E è una sorta di strike-price dell'opzione e P è definito come la sommatoria su "i" da 1 a m dei P(i) così definiti: \n
	P(i) = Min[ Max[ S(t+1)/S(t) - 1 , l], u] \n
	m rappresenta il numero di intervalli regolari in cui viene suddiviso l' intervallo temporale (0,T) e definiamo dt = T / m .( (T - t(0))/m ). Definiamo l e u come: \n
	l = EXP(r * dt)/k - 1 \n
	u = EXP(r * dt)*k -1 \n
	dove k è una costante che dipende dalla grandezza dt : k = 1 + lambda * sqrt(dt).

*/
class Eq_op_performance_with_corridor : public Eq_option {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_op_performance_with_corridor();
		Eq_op_performance_with_corridor(Eq_price eq_price, Timestruct times, double strikeprice, double lambda);
		Eq_op_performance_with_corridor(const Eq_op_performance_with_corridor &copy);
		~Eq_op_performance_with_corridor();

//		FUNZIONI VIRTUAL
		virtual Price Pay_off(Path *cammino);

//		FUNZIONI GET
		double Get_lambda() const;
		double Get_strikeprice() const;

//		FUNZIONI GET
		void Set_lambda(double lambda);
		void Set_strikeprice(double strikeprice);

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Eq_op_performance_with_corridor &dat);

//		OPERATORE ASSEGNAMENTO
		virtual Eq_op_performance_with_corridor &operator=(Eq_op_performance_with_corridor &obj);

	private:
		double _strikeprice;	
		double _lambda;
};

#endif
