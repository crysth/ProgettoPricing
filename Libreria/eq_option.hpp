//###################################################################################################
//	
//	FILE NAME :			eq_option.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Eq_option
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
//	DETAILED DESCRIPTION :	E' la classe madre delle opzioni su un'azione.
//					Rappresenta una generica opzione su un sottostante e quindi la funzione Pay_off(Path) è definita virtual pura.  
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
#ifndef _EQ_OPTION_HPP
#define _EQ_OPTION_HPP

#include "option.hpp"
#include "path.hpp"
#include "eq_price.hpp"
#include "timestruct.hpp"

#include <iostream>
#include <string>

class Eq_op_performance_with_corridor;
class Eq_op_plainvanilla;
class Eq_op_w;

using namespace std;
//! Classe che rappresenta il concetto di opzione.
/*! Classe di livello 7. \n
E' la classe madre delle opzioni su un'azione. \n
Rappresenta una generica opzione su un sottostante e quindi la funzione Pay_off(Path) è definita virtual pura.  
*/

class Eq_option : public Option {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Eq_option();
		Eq_option(const Eq_price &eq_price, const Timestruct &times);
		Eq_option(const Eq_option &copy);
		~Eq_option();

//		FUNZIONI VIRTUAL
//! funzione che restituisce il pay-off du un determinato cammino
		virtual Price Pay_off(Path *cammino)=0;

//		FUNZIONI GET
		const Eq_price &Get_Eq_price() const;
		const Timestruct &Get_times()const;

//		FUNZIONI SET
		void Set_Eq_price(const Eq_price &p);
		void Set_times(const Timestruct &t);

//		OPERATORE ASSEGNAMENTO
		virtual Eq_option &operator=(Eq_op_performance_with_corridor &obj);
		virtual Eq_option &operator=(Eq_op_plainvanilla &obj);
		virtual Eq_option &operator=(Eq_op_w &obj);


	private:
		Eq_price _eq_price;
		Timestruct _times;
};

#endif
