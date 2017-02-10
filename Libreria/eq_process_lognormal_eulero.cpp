//###################################################################################################
//	
//	FILE NAME :			eq_process_lognormal_eulero.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_process_lognormal_eulero
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/28
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta i processi che regolano l'evoluzione temporale di una azione che segua un processo lognormale secondo funzioni 
//					che dipendono da una random variabile gaussiana con media nulla e varianza unitaria. Il processo qui implementato permette 
//					la valutazione con formula approssiamta di Eulero: 
//					P = Po +   (r*(t2-t1) + s*(sqrt( t2 - t1 )) * w) * Po  
//					dove P è il prezzo finale al tempo t2, Po il prezzo iniziale al tempo t1, r il tasso forward tra i tempi t1 e t2, s rappresenta 
//					la volatilità e w è la variabile estratta dalla gaussiana.    
//	
//	
//
//	
//	
//#######################################################################################################

#include "eq_process_lognormal_eulero.hpp"

#include <cmath>
#include <iostream>

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Eq_process_lognormal_eulero::Eq_process_lognormal_eulero(): Eq_process(){
	Set_rand_gen();
};


//! costruttore
Eq_process_lognormal_eulero::Eq_process_lognormal_eulero(Rand_gen *ra): Eq_process(){
	Set_rand_gen(ra);
};


//! distruttore
Eq_process_lognormal_eulero::~Eq_process_lognormal_eulero(){};

//##############################################################################################################
//EVOLUZIONE
//#############################################################################################################		

//! funzione che fa evolvere un eqprice in un altro
void Eq_process_lognormal_eulero::Evol(Eq_price *A,Eq_price *B, N_rand *w) const {
	//ottengo i dati da inserire nella formula
	/*startprice*/
	double Po = A->Get_Eq_price().Get_price();
	/* T1 */
	Time t1	= A->Get_time();
	/* T2 */
	Time t2	= B->Get_time();
	/* T2-T1 */
	Deltatime delta=t2-t1;
	double deltanumerico=delta.Value();
	/*fwr rate*/
	double r = A->Get_eq()->Get_curve()->Get_forward_rate(t1,delta);
	/*volatility*/
	double sigma = A->Get_eq()->Get_vol()->Get_vol(t1,t2);
	//Evolvo con la formula
	/*formula eulero*/
	double P = Po + Po*( (r*deltanumerico) + sigma*(sqrt(deltanumerico)) * (*w) ) ;
	//imposto la currency 
	Price ris(P,A->Get_currency());
	/*set price*/	
	B->Set_price(ris);
	/*set equity*/	
	B->Set_eq(A->Get_eq());
};


//! funzione che restituisce il numero casuale estratto da una distribuzione gaussiana di media nulla e varianza unitaria
N_rand *Eq_process_lognormal_eulero::Get_w() const{
	return Get_rand_gen()->Get_gauss(0,1);
};

//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
Eq_process_lognormal_eulero &Eq_process_lognormal_eulero::operator=(Eq_process_lognormal_eulero &obj){
		cout<<"sono in = Eq_process_lognormal_eulero \n";
	Set_rand_gen(obj.Get_rand_gen());
	return *this;
};

//##############################################################################################################






