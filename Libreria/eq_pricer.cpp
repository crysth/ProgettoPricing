//###################################################################################################
//	
//	FILE NAME :			eq_pricer.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_pricer
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/mar/9
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' una classe astratta, madre delle simulazioni dei prezzi di un'opzione. Il metodo Compute_price è dichiarato virtual puro. 
//					Consente di impostare e ottenere il prezzo e i puntatori all'opzione considerata e al processo utilizzato.
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

#include "eq_pricer.hpp"
#include "errorlist.hpp"

//#################################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#################################################################################################################

//! costruttore di default
Eq_pricer::Eq_pricer(){
	_eq_option=NULL;
	_process=NULL;
};


//! distruttore
Eq_pricer::~Eq_pricer(){};

//#################################################################################################################
//FUNZIONI GET
//#################################################################################################################

//! funzione che restituisce il prezzo
Price Eq_pricer::Get_price() const{
	Price ris=_price;
	return ris;
};


//! funzione che restituisce l'opzione di riferimento
Eq_option *Eq_pricer::Get_Eq_option()const{
	if(_eq_option==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();			
		err->Add_error("Eq_pricer::(get_eq_option) invalid pointer returned");
	}
	return _eq_option;
};


//! funzione che restituisce il processo utilizzato
Process *Eq_pricer::Get_process() const{
	if(_process==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();			
		err->Add_error("Eq_pricer::(get_process) invalid pointer returned");
	}
	return _process;
};

//#################################################################################################################
//FUNZIONI SET
//#################################################################################################################

//! funzione che imposta l'opzione di riferimento
void Eq_pricer::Set_Eq_option(Eq_option *eq_option){
	if(eq_option==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();			
		err->Add_error("Eq_pricer::(set_eq_option) invalid pointer");
	}
	else { _eq_option=eq_option; }
};


//! funzione che imposta il prezzo
void Eq_pricer::Set_price(const Price &price){
	_price=price;
};


//! funzionie che imposta il processo da utilizzare
void Eq_pricer::Set_process(Process *process){
	if(process==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();			
		err->Add_error("Eq_pricer::(get_process) invalid pointer");
	}
	else{ _process=process;}
};

//#################################################################################################################
//OPERATORE ASSEGNAMENTO
//#################################################################################################################

//! overloading dell'operatore di assegnamento per la classe figlia: Eq_pricer_montecarlo
Eq_pricer &Eq_pricer::operator=(Eq_pricer_montecarlo &obj){
		cout<<"sono in = Eq_pricer\n";
	return *this;
};

//#################################################################################################################
