//###################################################################################################
//	
//	FILE NAME :			eq_op_plainvanilla.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_op_plainvanilla
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/mar/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta un'opzione plainvanilla con strike-price E e Pay-off definito come 
//					Pay-off = Max[P-E,0] 
//					dove P è il prezzo del sottostante al tempo T di maturità. 
//					Questo tipo di contratto può essere usato per fare un test della libreria in quanto per opzioni di questo tipo conosciamo 
//					le soluzioni in formula chiusa.
//
//	
//	
//	
//	
//	
//#######################################################################################################
#ifndef _EQ_OP_PLAINVANILLA_HPP
#define _EQ_OP_PLAINVANILLA_HPP

#include "eq_option.hpp"

#include "yield_curve_flat.hpp"
#include "path.hpp"
#include "eq_price.hpp"
#include "timestruct.hpp"

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta un'opzione call di tipo plain-vanilla.
/*! Classe di livello 7. \n
Rappresenta un'opzione plainvanilla con strike-price E e Pay-off definito come \n
Pay-off = Max[P-E,0] \n
dove P è il prezzo del sottostante al tempo T di maturità. \n
Questo tipo di contratto può essere usato per fare un test della libreria in quanto per opzioni di questo tipo conosciamo le soluzioni in formula chiusa.
*/
class Eq_op_plainvanilla : public Eq_option {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_op_plainvanilla();
		Eq_op_plainvanilla(Eq_price eq_price, Timestruct times, double strikeprice);
		Eq_op_plainvanilla(const Eq_op_plainvanilla &copy);
		~Eq_op_plainvanilla();

//		FUNZIONI VIRTUAL
		virtual Price Pay_off(Path *cammino);

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Eq_op_plainvanilla &dat);

//		OPERATORE ASSEGNAMENTO
		virtual Eq_op_plainvanilla &operator=(Eq_op_plainvanilla &obj);

	private:
		double _strikeprice;

};

#endif
