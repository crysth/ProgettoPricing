//###################################################################################################
//	
//	FILE NAME :			eq_process_lognormal_esatto.cpp
//	
//	FILE TYPE :			C++ file
//		
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_process_lognormal_esatto
//	
//	FIRST VERSION :		2010/mar/23
//	
//	LAST UPTIME : 		2010/apr/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta i processi che regolano l'evoluzione temporale di una azione che segua un processo lognormale secondo funzioni 
//					che dipendono da una random variabile gaussiana con media nulla e varianza unitaria. Il processo qui implementato permette 
//					la valutazione con formula integrale esatta:
//					P = Po*exp( (r - (s^2)/2)* dt  +  s * sqrt(dt) * w ) 
//					dove P è il prezzo finale al tempo t, Po il prezzo iniziale al tempo to, r il tasso forward tra i tempi to e t, 
//					s rappresenta la volatilità, w è la variabile estratta dalla gaussiana e dt = t - to.  
//	
//	
//
//	
//	
//#######################################################################################################

#include "eq_process_lognormal_esatto.hpp"

#include <cmath>
#include <iostream>

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Eq_process_lognormal_esatto::Eq_process_lognormal_esatto(): Eq_process(){
	Set_rand_gen();
};


//! costruttore
Eq_process_lognormal_esatto::Eq_process_lognormal_esatto(Rand_gen *ra): Eq_process(){
	Set_rand_gen(ra);
};


//! distruttore
Eq_process_lognormal_esatto::~Eq_process_lognormal_esatto(){};

//##############################################################################################################
//EVOLUZIONE
//#############################################################################################################	
	
//! funzione che fa evolvere un'azione al tempo t1 in un'altra al tempo t2 secondo la funzione integrale esatta
void Eq_process_lognormal_esatto::Evol(Eq_price *A,Eq_price *B, N_rand *w) const {
	//ottengo i dati da inserire nella formula
	/*startprice*/
	double Po = A->Get_Eq_price().Get_price();
	/* T1 */
	Time t1	= A->Get_time();
	/* T2 */
	Time t2	= B->Get_time();
	/* T2-T1 */
	Deltatime delta=t2-t1;
	/*fwr rate*/
	double r = A->Get_eq()->Get_curve()->Get_forward_rate(t1,delta);
	/*volatility*/
	double sigma = A->Get_eq()->Get_vol()->Get_vol(t1,t2);
	//Evolvo con la formula
	/*formula chiusa*/
	double P = Po*exp( (r - (0.5)*sigma*sigma)* delta.Value()  +  sigma * sqrt(delta.Value()) * (*w) );
	Price ris(P,A->Get_currency());
	/*set price*/	
	B->Set_price(ris);
	/*set equity*/	
	B->Set_eq(A->Get_eq());
};


//! funzione che restituisce il numero casuale estratto da una distribuzione gaussiana di media nulla e varianza unitaria
N_rand *Eq_process_lognormal_esatto::Get_w() const{
	return Get_rand_gen()->Get_gauss(0,1);
};

//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
Eq_process_lognormal_esatto &Eq_process_lognormal_esatto::operator=(Eq_process_lognormal_esatto &obj){
		cout<<"sono in = Eq_process_lognormale_esatto\n";
	Set_rand_gen(obj.Get_rand_gen());
	return *this;
};


//! overloading dell'operatore di assegnamento per la classe figlia: Eq_process_lognormal_binary
Eq_process_lognormal_esatto &Eq_process_lognormal_esatto::operator=(Eq_process_lognormal_binary &obj){
		cout<<"sono in = Eq_process\n";
	return *this;
};

//##############################################################################################################

