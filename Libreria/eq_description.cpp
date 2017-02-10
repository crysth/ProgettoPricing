//###################################################################################################
//	
//	FILE NAME :			eq_description.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_description
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
//	DETAILED DESCRIPTION :	Rappresenta la descrizione di un'azione.
//					Le sue variabili private contengono il nome dell'azione, il suo codice e i puntatori alle curve dei tassi e della
//					volatilità a cui fa riferimento 
//	
//	
//
//	
//	
//	
//	
//	
//#######################################################################################################
#include "eq_description.hpp"
#include "errorlist.hpp"

//#########################################################################################################
//COSTRUTTORI~DISTRUTTORE
//#########################################################################################################

//! costruttore di default
Eq_description::Eq_description(){
	_name="none";
	_code="none";
	_vol=NULL;
	_curve=NULL;
};


//! costruttore
Eq_description::Eq_description(const string &n,const string &c,Yield_curve *cu, Volatility *v){
	_name=n;
	_code=c;
	if(cu!=NULL) {_curve=cu;}
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_description::(Constructor) error, curve is NULL");
	}
	if(v!=NULL) {_vol= v;}
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_description::(Constructor) error, Volatility is NULL");
	}
};


//! costruttore di copia
Eq_description::Eq_description(const Eq_description &copy){
	_name=copy._name;
	_code=copy._code;
	_vol=copy._vol;
	_curve=copy._curve;
};


//! distruttore
Eq_description::~Eq_description(){};

//#########################################################################################################
//FUNZIONI SET
//#########################################################################################################  	

//! funzione che imposta il nome dell'azione
void Eq_description::Set_name(const string &n){
	_name=n;
};


//! funzione che imposta il codice dell'azione
void Eq_description::Set_code(const string &c){
	_code=c;
};


//! funzione che imposta la curva dei tassi a cui fa riferimento l'azione
void Eq_description::Set_curve(Yield_curve *cu){
	if(cu!=NULL) {_curve=cu;}
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_description::(Set_curve) error, curve is NULL");
	}
};


//! funzione che imposta la curva di volatilità a cui fa riferimento l'azione
void Eq_description::Set_vol(Volatility *v){
	if(v!=NULL) {_vol= v;}
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_description::(Set_vol) error, Volatility is NULL");
	}
};

//#########################################################################################################
//FUNZIONI GET
//######################################################################################################### 	

//! funzione che restituisce il nome dell'azione
string Eq_description::Get_name() const{
	string ris(_name);
	return ris;
};


//! funzione che restituisce il codice dell'azione
string Eq_description::Get_code() const{
	string ris(_code);
	return ris;
};


//! funzione che restituisce il puntatore alla curva dei tassi a cui fa riferimento l'azione
Yield_curve *Eq_description::Get_curve() const{
	if(_curve!=NULL) {return _curve;}
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_description::(Get_curve) error, curve isn't declared");
		return _curve;
	}
};


//! funzione che restituisce il puntatore alla curva di volatilità a cui fa riferimento l'azione
Volatility *Eq_description::Get_vol() const{
	if(_vol!=NULL) return _vol;
	else {
		ErrorList *err=ErrorList::Get_errorlist();
		err->Add_error("Eq_description::(Get_vol) error, volatility isn't declared");
		return _vol;
	}
};


//#########################################################################################################
//OPERATORE ASSEGNAMENTO
//#########################################################################################################

//! overloading dell'operatore di assegnamento
const Eq_description &Eq_description::operator=(const Eq_description &eq){
	_name = eq._name;
	_code = eq._code;
	_vol = eq._vol;
	_curve = eq._curve;
	return (*this);
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

std::ostream &operator<<(std::ostream &os, const Eq_description &dat) {
	os<<"Nome dell'azione : "<<dat._name<<std::endl;
	os<<"Codice dell'azione : "<<dat._code<<std::endl;
	return os;
};

//#########################################################################################################

