//###################################################################################################
//	
//	FILE NAME :			eq_op_plainvanilla.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_op_plainvanilla
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
#include "eq_op_plainvanilla.hpp"
#include "errorlist.hpp"

//#######################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#######################################################################################################

//! costruttore di default
Eq_op_plainvanilla::Eq_op_plainvanilla(): _strikeprice(0){};


//! costruttore
Eq_op_plainvanilla::Eq_op_plainvanilla(Eq_price eq_price, Timestruct times, double strikeprice){
	Set_Eq_price(eq_price);
	Set_times(times);
	_strikeprice=strikeprice;
};


//! costruttore di copia
Eq_op_plainvanilla::Eq_op_plainvanilla(const Eq_op_plainvanilla &copy){
	Set_Eq_price(copy.Get_Eq_price());
	Set_times(copy.Get_times());
	_strikeprice=copy._strikeprice;
};


//! distruttore
Eq_op_plainvanilla::~Eq_op_plainvanilla(){};

//#######################################################################################################
//PAYOFF
//#######################################################################################################

//! funzione che restituisce il payoff dell'opzione dato un cammino
Price Eq_op_plainvanilla::Pay_off(Path *cammino){

	double P=(cammino->Get_eqprice((Get_times().Get_dim()))->Get_Eq_price().Get_price());

	//creo il price
	Currency *currency=cammino->Get_eqprice(0)->Get_currency();
	Price payoff(0.,currency);
	cerr<<"P "<<P<<endl;
	//setto nel caso il valore di P-E sia positivo
	if((P-_strikeprice)>0)	payoff.Set_price((P-_strikeprice));
//std::cerr<<"Payoff "<<payoff<<endl;
	return payoff;
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

// overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Eq_op_plainvanilla &dat) {
	os<<dat.Get_Eq_price()<<endl<<dat.Get_times()<<endl;
	os<<"strikeprice = "<<dat._strikeprice<<endl;
	return os;
};

//################################################################################################################
//OPERATORE ASSEGNAMENTO
//################################################################################################################

//! overloading dell'operatore di assegnamento
Eq_op_plainvanilla &Eq_op_plainvanilla::operator=(Eq_op_plainvanilla &obj){
		cout<<"sono in = Eq_op_plainvanilla\n";
	Set_times(obj.Get_times());
	Set_Eq_price(obj.Get_Eq_price());
	_strikeprice=obj._strikeprice;
	return *this;
};

//################################################################################################################

