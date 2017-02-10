//###################################################################################################
//	
//	FILE NAME :			eq_option.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_option
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/mar/6
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
#include "eq_option.hpp"

#include "errorlist.hpp"

//#######################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#######################################################################################################

//! costruttore di default
Eq_option::Eq_option(): Option() {};


//! costruttore
Eq_option::Eq_option(const Eq_price &eq_price, const Timestruct &times): Option() {
	_eq_price=eq_price;
	_times=times;
};


//! costruttore di copia
Eq_option::Eq_option(const Eq_option &copy){
	_times=copy._times;
	_eq_price=copy._eq_price;
};


//! distruttore
Eq_option::~Eq_option(){};

//#######################################################################################################
//FUNZIONI GET
//#######################################################################################################

//! funzione che restituisce il punto iniziale dell'azione 
const Eq_price &Eq_option::Get_Eq_price() const{
	return _eq_price;
};


//! funzione che restituisce il vettore di tempi
const Timestruct &Eq_option::Get_times() const{
	return _times;
};


//#######################################################################################################
//FUNZIONI SET
//#######################################################################################################

//! funzione che imposta il punto iniziale dell'azione 
void Eq_option::Set_Eq_price(const Eq_price &eq_price){
	_eq_price=eq_price;
};


//! funzione che imposta il vettore di tempi 
void Eq_option::Set_times(const Timestruct &times){
	_times=times;
};

//#######################################################################################################
//OPERATORE ASSEGNAMENTO
//#######################################################################################################

//! overloading dell'operatore di assegnamento per la classe figlia: Eq_op_performance_with_corridor
Eq_option &Eq_option::operator=(Eq_op_performance_with_corridor &obj){
		cout<<"sono in = Eq_option\n";
	return *this;
};


//! overloading dell'operatore di assegnamento per la classe figlia: Eq_op_plainvanilla
Eq_option &Eq_option::operator=(Eq_op_plainvanilla &obj){
		cout<<"sono in = Eq_option\n";
	return *this;
};


//! overloading dell'operatore di assegnamento per la classe figlia: Eq_op_w
Eq_option &Eq_option::operator=(Eq_op_w &obj){
		cout<<"sono in = Eq_option\n";
	return *this;
};

//################################################################################################################

