//###################################################################################################
//	
//	FILE NAME :			eq_op_w.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_op_w
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
//	DETAILED DESCRIPTION :	Rappresenta un'opzione che usiamo per testare la nostra libreria in quanto ne conosciamo a priori il risultato, 
//					inoltre è anche un test per la classe che genera numeri casuali in quanto il Pay-off è definito come la sommatoria 
//					dei quadrati delle variabili casuali estratte durante il cammino passato alla funzione Pay_off.
//	
//	
//
//	
//	
//	
//	
//	
//#######################################################################################################
#ifndef _EQ_OP_W_HPP
#define _EQ_OP_W_HPP

#include "eq_option.hpp"

#include "yield_curve_flat.hpp"
#include "path.hpp"
#include "eq_price.hpp"
#include "timestruct.hpp"

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta un'opzione utilizzata per il controllo della libreria.
/*! Classe di livello 7. \n
Rappresenta un'opzione che usiamo per testare la nostra libreria in quanto ne conosciamo a priori il risultato, inoltre è anche un test per la classe che genera numeri casuali in quanto il Pay-off è definito come la sommatoria dei quadrati delle variabili casuali estratte durante il cammino passato alla funzione Pay_off.
*/
class Eq_op_w : public Eq_option {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_op_w();
		Eq_op_w(Eq_price eq_price, Timestruct times);
		Eq_op_w(const Eq_op_w &copy);
		~Eq_op_w();

//		FUNZIONI VIRTUAL
		virtual Price Pay_off(Path *cammino);

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Eq_op_w &dat);

//		OPERATORE ASSEGNAMENTO
		virtual Eq_op_w &operator=(Eq_op_w &obj);

	private:

};

#endif
