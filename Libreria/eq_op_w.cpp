//###################################################################################################
//	
//	FILE NAME :			eq_op_w.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat, Marco Antonelli (poco)
//	
//	DESCRIPTION : 		Implementation of class Eq_op_w
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
#include "eq_op_w.hpp"
#include "errorlist.hpp"

//#######################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#######################################################################################################

//! costruttore di default
Eq_op_w::Eq_op_w() {};


//! costruttore
Eq_op_w::Eq_op_w(Eq_price eq_price, Timestruct times){
	Set_Eq_price(eq_price);
	Set_times(times);
};


//! costruttore di copia
Eq_op_w::Eq_op_w(const Eq_op_w &copy){
	Set_Eq_price(copy.Get_Eq_price());
	Set_times(copy.Get_times());
};


//! distruttore
Eq_op_w::~Eq_op_w(){};

//#######################################################################################################
//PAYOFF
//#######################################################################################################

//! funzione che restituisce il payoff dell'opzione dato un cammino
Price Eq_op_w::Pay_off(Path *cammino){
	double P=0.;
	for(int i=0;i<Get_times().Get_dim();i++){
		P+=pow(cammino->Get_nrand(i)->Get_rand(),2);
	}
	//creo il price
	Currency *currency=cammino->Get_eqprice(0)->Get_currency();
	Price payoff(P,currency);
	return payoff;
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

std::ostream &operator<<(std::ostream &os, const Eq_op_w &dat) {
	os<<dat.Get_Eq_price()<<endl<<dat.Get_times()<<endl;
	return os;
};

//################################################################################################################
//OPERATORE ASSEGNAMENTO
//################################################################################################################

//! overloading dell'operatore di assegnamento
Eq_op_w &Eq_op_w::operator=(Eq_op_w &obj){
		cout<<"sono in = Eq_op_w\n";
	Set_times(obj.Get_times());
	Set_Eq_price(obj.Get_Eq_price());
	return *this;
};

//################################################################################################################

