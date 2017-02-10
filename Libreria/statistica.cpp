//###################################################################################################
//	
//	FILE NAME :			statistica.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Statistica
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	DETAILED DESCRIPTION :	Questa classe rappresenta la statistica. Conserva la somma delle osservazioni, dei loro quadrati e conserva un counter interno 
//					per poterne poi fare la media e ottenere quindi informazioni sugli errori quali varianza, deviazione standard, errore assoluto
//					ed errore relativo.     
//
//	
//	
//	
//	
//	
//###################################################################################################
#include "statistica.hpp"

//##############################################################################################################
//COSTRUTTORI E DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Statistica::Statistica() {
	_sum=0.;
	_cont=0;
	_sum2=0.;
};


//! costruttore di copia
Statistica::Statistica(const Statistica &copy){
	_cont=copy._cont;
	_sum=copy._sum;
	_sum2=copy._sum2;
};


//! distruttore
Statistica::~Statistica(){};

//##############################################################################################################
//METODI
//##############################################################################################################

//! funzione che salva un'osservazione: salva la somma delle osservabili, la somma dei loro quadrati e incrementa il counter interno
void Statistica::Add_observation(double x){
	_cont++;
	_sum+=x;
	_sum2+=pow(x,2);
};

//##############################################################################################################
//FUNZIONI GET
//##############################################################################################################

//! funzione che restituisce la media
double Statistica::Get_media()const{
	return _sum/double(_cont);
};


//! funzione che restituisce la media dei quadrati 
double Statistica::Get_media2()const{
	return _sum2/double(_cont);
};


//! funzione che restituisce la varianza : media(x^2) - media(x)^2
double Statistica::Get_var2()const{
	//controllo per evitare di avere nan in return
	if((Get_media2() - pow(Get_media(),2))<0.000000000000001) return 0.;
	else return fabs(Get_media2() - pow(Get_media(),2));
};


//! funzione che restituisce la deviazione standard
double Statistica::Get_standard_deviation()const{
	return sqrt(Get_var2());
} ;


//funzione che restituisce l'errore assoluto
double Statistica::Get_errore(void)const{
	return Get_standard_deviation()/(sqrt(double(_cont)));
} ;


//! funzione che restituisce l'errore relativo
double Statistica::Get_errore_percentuale(void)const{
	return (100.*Get_errore()/Get_media());
} ;

//##############################################################################################################
//OPERATORE DI ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
const Statistica &Statistica::operator=(const Statistica &copy){
	_cont=copy._cont;
	_sum=copy._sum;
	_sum2=copy._sum2;
	return (*this);
};

//##############################################################################################################



