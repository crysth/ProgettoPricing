//###################################################################################################
//	
//	FILE NAME :			eq_op_performance_with_corridor.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_op_performance_with_corridor
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
#include "eq_op_performance_with_corridor.hpp"
#include "errorlist.hpp"

//#######################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#######################################################################################################

//! costruttore di default
Eq_op_performance_with_corridor::Eq_op_performance_with_corridor(): _strikeprice(0), _lambda(0){};


//! costruttore 
Eq_op_performance_with_corridor::Eq_op_performance_with_corridor(Eq_price eq_price, Timestruct times, double strikeprice, double lambda){
	Set_Eq_price(eq_price);
	Set_times(times);
	_strikeprice=strikeprice;
	_lambda=lambda;
};


//! costruttore di copia
Eq_op_performance_with_corridor::Eq_op_performance_with_corridor(const Eq_op_performance_with_corridor &copy){
	Set_Eq_price(copy.Get_Eq_price());
	Set_times(copy.Get_times());
	_strikeprice=copy._strikeprice;
	_lambda=copy._lambda;
};


//! distruttore
Eq_op_performance_with_corridor::~Eq_op_performance_with_corridor(){};

//#######################################################################################################
//PAYOFF
//#######################################################################################################

//! funzione che restituisce il payoff dell'opzione ( come definito nel commento della classe) dato un cammino
Price Eq_op_performance_with_corridor::Pay_off(Path *cammino){
	// price in double settato a zero
	double P = 0.;	
	//ottengo il deltatime (frazione di anni)
		Timestruct appo1=Get_times();
	double dtime =  (appo1.Get_deltatime(0).Value());
	//dichiaro k
	double k = 1.+_lambda*sqrt(dtime);
	//dichiaro L
	double L = (exp((Yield_curve_flat::Get_riskfree()->Get_rate())*dtime)/k) - 1.;
	//dichiaro U
	double U = k*(exp((Yield_curve_flat::Get_riskfree()->Get_rate())*dtime)) - 1. ;
	//valore dell'azione S(t1) e S(t0)
	double St1,St0;
	//Utilizzo la formula [ P+=(min(max(S(ti+1)/S(ti)-1,L),U)) ] aggiungendo alla Po i valori ottenuti
	for(int i=0;i<(Get_times().Get_dim());i++){
		//setto S(t1) e S(t2)
		St1=(cammino->Get_eqprice(i+1)->Get_Eq_price().Get_price());
		St0=((cammino->Get_eqprice(i)->Get_Eq_price().Get_price()));
		/*sommo*/
		P+=min(max((St1/St0)-1.,L),U);
	}
	//creo il price
	Currency *currency=cammino->Get_eqprice(0)->Get_currency();
	Price payoff(0.,currency);
	//setto nel caso il valore di P-E sia positivo
	if((P-_strikeprice)>0)	payoff.Set_price((P-_strikeprice));
	return payoff;
};

//#######################################################################################################
//FUNZIONI GET
//#######################################################################################################

//! funzione che restituisce il valore della costante lambda
double Eq_op_performance_with_corridor::Get_lambda() const{
	return _lambda;
};


//! funzione che restituisce lo strikeprice
double Eq_op_performance_with_corridor::Get_strikeprice() const{
	return _strikeprice;
};

//#######################################################################################################
//FUNZIONI SET
//#######################################################################################################

//! funzione che imposta il valore della costante lambda
void Eq_op_performance_with_corridor::Set_lambda(double lambda){
	if(lambda>=0.) {
		_lambda=lambda;
	}
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_op_performance_with_corridor::(Set_lambda) error, Lambda must be positive");
	}
};


//! funzione che imposta lo strikeprice
void Eq_op_performance_with_corridor::Set_strikeprice(double strikeprice){
	_strikeprice=strikeprice;
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

std::ostream &operator<<(std::ostream &os, const Eq_op_performance_with_corridor &dat) {
	os<<dat.Get_Eq_price()<<endl<<dat.Get_times()<<endl;
	os<<"lambda = "<<dat._lambda<<endl<<"strikeprice = "<<dat._strikeprice<<endl;
	return os;
};

//################################################################################################################
//OPERATORE ASSEGNAMENTO
//################################################################################################################

//! overloading dell'operatore di assegnamento 
Eq_op_performance_with_corridor &Eq_op_performance_with_corridor::operator=(Eq_op_performance_with_corridor &obj){
		cout<<"sono in = Eq_op_performance_with_corridor\n";
	Set_times(obj.Get_times());
	Set_Eq_price(obj.Get_Eq_price());
	_strikeprice=obj._strikeprice;
	_lambda=obj._lambda;
	return *this;
};

//################################################################################################################

