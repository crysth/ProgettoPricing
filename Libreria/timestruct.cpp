//###################################################################################################
//	
//	FILE NAME :			timestruct.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Timestruct
//	
//	FIRST VERSION :		2010/feb/9
//	
//	LAST UPTIME : 		2010/feb/15
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Questa classe gestisce vettori di intervalli temporali Deltatime, per cui contiene un membro che rappresenta la lunghezza di tali vettori.
//					Rappresenta una struttura temporale, permette una migliore e piú sicura gestione dei vettori di intervalli di tempi che verranno 
//					ampliamente usati all’interno della libreria. 
//					Abbiamo implementato un costruttore che permetta di creare un oggetto Timestruct composto da intervalli di eguale durata passando
//					semplicemente un Deltatime e la lughezza del vettore.
//					Un altro costruttore permette di passare istanti temporali: gli intervalli cengono ricavati dalla differenza di tali date e , più
//					precisamente, il primo intervallo corrisponde alla differenza tra il primo istante passato alla funzione e "today".
//	
//	
//	
//	
//#######################################################################################################

#include "timestruct.hpp"
#include "errorlist.hpp"

//################################################################################################################
//COSTRUTTORI~DISTRUTTORE
//################################################################################################################

//! costruttore di default
Timestruct::Timestruct(): _dim(0){
	_delta_tempi=NULL;
};


//! costruttore con la sola dimensione
Timestruct::Timestruct(int dim): _dim((dim>0)?dim:0){
	if(dim<0) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) the dimension must be positive");
	}
	_delta_tempi=new Deltatime[_dim];
};


//! costruttore con un solo deltatime (vettore di intervalli di eguale durata)
Timestruct::Timestruct(const Deltatime &delta,int dim): _dim((dim>0)?dim:0){
	if(dim<0) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) the dimension must be positive");
	}
	_delta_tempi=new Deltatime[_dim];
	for(int i=0;i<_dim;i++){
		_delta_tempi[i]=delta;
	}
};


//! costruttore con vettore di deltatime
Timestruct::Timestruct(Deltatime *delta_tempi,int dim): _dim((dim>0)?dim:0){
	if(dim<0) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) the dimension must be positive");
	}
	if(delta_tempi==NULL) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) invalid deltatime pointer");
	}
	_delta_tempi=new Deltatime[_dim];
	for(int i=0;i<_dim;i++){
		_delta_tempi[i]=delta_tempi[i];
	}
};


//! costruttore con vettore di puntatori di deltatime
Timestruct::Timestruct(Deltatime **delta_tempi,int dim): _dim((dim>0)?dim:0){
	if(dim<0) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) the dimension must be positive");
	}
	if(delta_tempi==NULL) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) invalid deltatime pointer");
	}
	_delta_tempi=new Deltatime[_dim];
	for(int i=0;i<_dim;i++){
		_delta_tempi[i]=*delta_tempi[i];
	}
};


//! costruttore con vettore di istanti (il deltatime sarà la differenza di istanti a partire da "today")
Timestruct::Timestruct(Time *tempi,int dim): _dim((dim>0)?dim:0){
	if(dim<0) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) the dimension must be positive");
	}
	if(tempi==NULL) {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(constructor) invalid time pointer");
	}
	_delta_tempi=new Deltatime[_dim];
	Time today=*(Time::Get_today());
	_delta_tempi[0]=(tempi[0]-today);
	for(int i=0;i<_dim-1;i++){
		_delta_tempi[i+1]=tempi[i+1]-tempi[i];
	}
};


//! costruttore di copia
Timestruct::Timestruct(const Timestruct &copy){
	_dim=copy._dim;
	_delta_tempi=new Deltatime[_dim];
	for(int i=0;i<_dim;i++){
		_delta_tempi[i]=copy._delta_tempi[i];
	}
};


//! distruttore
Timestruct::~Timestruct(){
	delete[] _delta_tempi;
};

//################################################################################################################
//FUNZIONI GET
//################################################################################################################

//! funzione che restituisce l'i-esimo intervallo
const Deltatime &Timestruct::Get_deltatime(int i) {
	if(i<_dim && i>=0) return _delta_tempi[i];
	else {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(Get_deltatime)  this deltatime doesn't exist");
		if(_dim!=0) return _delta_tempi[0];
		else{
			_dim=1;
			_delta_tempi= new Deltatime[1];
			return _delta_tempi[0];
		}
	}
};


//! funzione che restituisce la dimensione del vettore
int Timestruct::Get_dim() const{
	return _dim;
};

//################################################################################################################
//FUNZIONI SET
//################################################################################################################

//! funzione che imposta l'i-esimo intervallo 
void Timestruct::Set_deltatime(const Deltatime &delta, int i){
	if(i<_dim) _delta_tempi[i]=delta;
	else {
		ErrorList::Get_errorlist()->Add_error("Timestruct::(set_deltatime)  this deltatime doesn't exist");
	}
};

//################################################################################################################
//OPERATORE ASSEGNAMENTO
//################################################################################################################

//! overloading dell'operatore di assegnamento
const Timestruct &Timestruct::operator=(const Timestruct &copy){
	if(_dim!=copy._dim){
		if(_dim!=0) delete[] _delta_tempi;
		_delta_tempi=new Deltatime[copy._dim];
		_dim=copy._dim;
	}
	for(int i=0;i<_dim;i++){
		_delta_tempi[i]=copy._delta_tempi[i];
	}
	return *this;
};

//################################################################################################################
//OPERATORI LOGICI
//################################################################################################################

//! overloading dell'operatore logico di eguaglianza " == "
bool Timestruct::operator==(const Timestruct &dat) const{
	if(_dim!=dat._dim) return false;
	else {
		bool check=true;
		for(int i=0;i<_dim;i++){
			if(_delta_tempi[i]!=dat._delta_tempi[i]){
				check=false;
			}
		}
		return check;
	}
};


//! overloading dell'operatore logico di diseguaglianza " != "
bool Timestruct::operator!=(const Timestruct &dat) const{
	if(_dim!=dat._dim) return true;
	else {
		bool check=false;
		for(int i=0;i<_dim;i++){
			if(_delta_tempi[i]!=dat._delta_tempi[i]){
				check=true;
			}
		}
		return check;
	}
};

//################################################################################################################
//OVERLOADING DEL <<
//################################################################################################################

// overloading dell'operatore "<<"
std::ostream &operator<<(std::ostream &os, const Timestruct &dat) {
	for(int i=0;i<dat._dim;i++){
		os<<"#"<<(i+1)<<"\t"<<dat._delta_tempi[i]<<endl;
	}
	return os;
};

//################################################################################################################


