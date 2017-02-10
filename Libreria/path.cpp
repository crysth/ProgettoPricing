//###################################################################################################
//	
//	FILE NAME :			path.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Path
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/mar/26
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta il cammino di evoluzione di un'azione, ovvero i diversi valori che l'azione assume durante un certo lasso di tempo, 
//					controlati con una certa periodicità.
//					Richiamando le classi Process permette di costrutire un cammino, dato un vettore di Deltatime ( una Timestruct da cui ricaviamo 
//					anche la dimensione), a partire da un'azione a prezzo e tempo fissati.
//					Permette inoltre di salvare i numeri random utilizzati per generare ogni passo del cammino, e di generare l'anticammino.  
//
//
//	
//	
//	
//	
//	
//#######################################################################################################
#include "path.hpp"

#include "errorlist.hpp"

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Path::Path(){
	_dim=0;
	_process=NULL;			//imposto a NULL tutti i puntatori
	_eq_prices=NULL;
	_num_rand=NULL;
};


//! costruttore
Path::Path(const Eq_price &start_price, Timestruct *times, Process *process) {		
	//controlli sui puntatori
	if(times==NULL || process==NULL){
 		ErrorList *err=ErrorList::Get_errorlist();
		if(times==NULL)
			err->Add_error("Path::(constructor) invalid Timestruct pointer");
		if(process==NULL)
			err->Add_error("Path::(constructor) invalid process pointer");
	}
	else {
		//ottengo la dimensione dalla timestruct
		 _dim=(times->Get_dim())+1;
		//creo il vettore di puntatori a eqprice
		_eq_prices = new Eq_price*[_dim];
			for(int i=0;i<_dim;i++){
				_eq_prices[i]=new Eq_price;
			}
		//copio il punto iniziale
		*_eq_prices[0]=start_price;
		//setto tempi e eqdescription negli eq_price
		Time start_time=start_price.Get_time();
			for(int i=1;i<_dim;i++){
				_eq_prices[i]->Set_time(start_time+times->Get_deltatime(i-1));
				_eq_prices[i]->Set_eq(start_price.Get_eq());
				start_time=start_time+times->Get_deltatime(i-1);
			}
		//creo il vettore di puntatori a numeri rand
		_num_rand = new N_rand*[_dim-1];
		//copio i puntatori al processo e ai tempi
		_process=process;
		//genero numeri casuali e faccio evolvere gli eqprice
		for(int i=0;i<(_dim-1);i++){
			_num_rand[i]=(process->Get_w());
			process->Evol(_eq_prices[i], _eq_prices[i+1], _num_rand[i]);
		}
	}
};


//! costruttore di copia
Path::Path(const Path &copy){
	//ottengo la dimensione dalla timestruct
	_dim = copy._dim;
	//copio i puntatori al processo e ai tempi
	_process=copy._process;
	//creo un vettore di puntatori a eqprice
	_eq_prices = new Eq_price*[_dim];
	for(int i=0;i<_dim;i++){
		_eq_prices[i]=new Eq_price;
	}
	//creo il vettore di numeri casuali
	_num_rand = new N_rand*[_dim-1];
	for(int i=0;i<_dim-1;i++){
		_num_rand[i]=new N_rand;
	}
	//copio eqprices e numrand
	*(_eq_prices[0])=*(copy._eq_prices[0]);
	for(int i=0;i<(_dim-1);i++){
		*_num_rand[i]=*copy._num_rand[i];
		*(_eq_prices[i+1])=*(copy._eq_prices[i+1]);
	}
};


//! distruttore
Path::~Path(){
	if(_eq_prices!=NULL && _num_rand!=NULL){
		for(int i=0;i<(_dim-1);i++)
			delete _num_rand[i];
		for(int i=0;i<_dim;i++)
			delete _eq_prices[i];
		
			delete[] _eq_prices;
			delete[] _num_rand;
	}
};

//##############################################################################################################
//METODI
//##############################################################################################################

//! funzione che rigenera il cammino secondo nuovi numeri casuali, utile nella simulazione dove non è necessario salvare i path
void Path::Refresh(){
	//pulisco il vettore di numeri casuali
	for(int i=0;i<_dim-1;i++){
		delete _num_rand[i];
	}
	//ottengo nuovi numeri casuali e rigenero il cammino
	for(int i=0;i<_dim-1;i++){
		_num_rand[i]=_process->Get_w();
		_process->Evol(_eq_prices[i], _eq_prices[i+1], _num_rand[i]);
	}
};


//! funzione che trasforma il cammino nel suo anticammino
void Path::Reverse(){
	*this=-*this;
};


//! funzione che imposta l'oggetto chiamante come anticammino dell'oggetto passato alla funzione
void Path::Reverse(Path *cammino){
	*this=-*cammino;
};

//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
const Path &Path::operator=(const Path &cammino){
	//controlli dimensionali
	if(_dim!=cammino._dim){
		//se il vettore di eqprices non è null, lo pulisco
		if(_eq_prices!=NULL){
			for(int i=0;i<_dim;i++){
				delete _eq_prices[i];
			}
			delete[] _eq_prices;
		}
		//genero il vettore di eqprices secondo la giusta dimensione
		_eq_prices = new Eq_price*[cammino._dim];
		for(int i=0;i<cammino._dim;i++){
			_eq_prices[i]=new Eq_price;
		}
		//pulisco il vettore di numeri casuali (se non è null)
		if(_num_rand!=NULL){
			for(int i=0;i<_dim-1;i++){
				delete _num_rand[i];
			}
			delete[] _num_rand;
		}
		//genero il vettore di numeri casuali secondo la giusta dimensione
		_num_rand = new N_rand*[_dim-1];
		for(int i=0;i<(cammino._dim-1);i++){
			_num_rand[i]=new N_rand;
		}
	}
	//copio il puntatore a process
	_process=cammino._process;
	//copio eqprices e numrand (hanno dimensioni diverse)
	*(_eq_prices[0])=*(cammino._eq_prices[0]);
	for(int i=1;i<(cammino._dim);i++){
		*(_eq_prices[i])=*(cammino._eq_prices[i]);
		*(_num_rand[i-1])=*(cammino._num_rand[i-1]);
	}
	return (*this);
};

//##############################################################################################################
//OPERATORE ANTICAMMINO
//##############################################################################################################

//! overloading dell'operatore unario per ottenere un anticammino
Path Path::operator-() const{
	int dim=_dim-1;
	Path copy(*this);
	//inverto i numeri random
	for(int i=0;i<dim;i++){
		*(copy._num_rand[i])=-(*(copy._num_rand[i]));
	}
	//rievolvo secondo i nuovi numeri
	for(int i=0;i<dim;i++){
		_process->Evol(copy._eq_prices[i], copy._eq_prices[i+1], copy._num_rand[i]);
	}
	return copy;
};

//##############################################################################################################
//FUNZIONI GET
//##############################################################################################################

//! funzione che restiruisce l'azione i-esima 
Eq_price *Path::Get_eqprice(int i){
	if(i>_dim||i<0){
		ErrorList::Get_errorlist()->Add_error("Path::(get_eqprice) this eqprice doesn't exist");
		return _eq_prices[0];
	}
	else { 
		return _eq_prices[i];
	}
};


//! funzione che restituisce il vettore di tempi
int Path::Get_dim() const{ 
	return _dim;
};


//! funzione che restituisce l'i-esimo numero casuale utilizzato per creare il cammino
N_rand *Path::Get_nrand(int i) const{
	if(_num_rand==NULL){
		ErrorList::Get_errorlist()->Add_error("Path::(get_nrand) invalid pointer");
		return _num_rand[0];
	}
	if(i>_dim-1||i<0){
		ErrorList::Get_errorlist()->Add_error("Path::(get_nrand) this eqprice doesn't exist");
		return _num_rand[0];
	}
	else { 
		return _num_rand[i];
	}
};

//##############################################################################################################

