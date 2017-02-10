//###################################################################################################
//	
//	FILE NAME :			eq_pricer_montecarlo.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Eq_pricer_montecarlo
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/apr/6
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Questa classe implementa il metodo Montecarlo per il pricing di un’opzione con un numero N di simulazioni passato al costruttore.
//					Prende come dati di input, oltre al numero di simulazioni, il tipo di opzione e il processo che si vuole utilizzare . Il metodo 
//					Compute_price avvia la simulazione, fa la stima del prezzo e lo attualizza. Utilizza la classe Statistica per fornire una stima 
//					degli errori commessi. Il membro Stima_montecarlo salva i risultati ottenuti.
//					Sia gli oggetti Statistica che Stima_montecarlo sono 3, per permettere all'utilizzatore di scegliere di utilizzare a scelta una 
//					stima condotta solo sui cammini standard, solo sugli anticammini o su cammini standard e anticammini.
//	
//	
//	
//	
//	
//#######################################################################################################

#include "eq_pricer_montecarlo.hpp"
#include "yield_curve.hpp"
#include "errorlist.hpp"

//##############################################################################################################
//COSTRUTTORI~DISTRUTTORE
//##############################################################################################################

//! costruttore di default
Eq_pricer_montecarlo::Eq_pricer_montecarlo(): Eq_pricer(), _N(0) {};


//! costruttore
Eq_pricer_montecarlo::Eq_pricer_montecarlo(Eq_option *opt, Process *pro, int N): Eq_pricer() {
	Set_Eq_option(opt);
	Set_process(pro);
	_N=N;
};


//! distruttore
Eq_pricer_montecarlo::~Eq_pricer_montecarlo(){};

//##############################################################################################################
//METODI
//##############################################################################################################

//! valutazione del prezzo dell'opzione
void Eq_pricer_montecarlo::Compute_price(){
	//->	dichiaro un puntatore per ogni variabile (per comodità e per controlli)
	Eq_option *eq_option=(Get_Eq_option());				//Eq_option da private della madre
	Timestruct *ptrtimes=new Timestruct(eq_option->Get_times());	//Timestruct dall'Eq_option
	int dim=(ptrtimes->Get_dim());					//dim dalla Timestruct
	Process *process=(Get_process());				//Process da private della madre
	//->	ottengo il discount_factor	
	Deltatime tot;
	for(int i=0;i<(dim);i++){
		(tot)+=(ptrtimes->Get_deltatime(i));
	}
	//ottengo il tasso r dalla curva riskfree
	Yield_curve_flat *rf=(Yield_curve_flat::Get_riskfree());			
	double discount_factor=rf->Get_discount_factor(tot);
	//->	copio il valore iniziale dell'azione
	Eq_price start_eq_price=(eq_option->Get_Eq_price());
	//->	creo cammino con gli Eq_price* la Timestruct e il processo
	Path *cammino;
	cammino=new Path(start_eq_price,ptrtimes,process);
	//->	creo il prezzo (per settarlo)
	double valore=0.;
	//->	setto il prezzo
	for (int j=0;j<_N;j++){

		//ottengo il payoff e lo attualizzo
		valore = eq_option->Pay_off(cammino).Get_price() * discount_factor;	
		//passo il valore alle classi statistiche
		_stat_std.Add_observation(valore);
		_stat_std_anti.Add_observation(valore);

		//inverto il cammino
		cammino->Reverse();

		//ottengo il payoff e lo attualizzo
		valore=(eq_option->Pay_off(cammino)).Get_price()*discount_factor;	
		//passo il valore alle classi statistiche
		_stat_anti.Add_observation(valore);
		_stat_std_anti.Add_observation(valore);

		//rigenero il cammino per l'iterazione successiva
		cammino->Refresh();
	
	}
	//salvo i valori nelle classi Stima_montecarlo
	//std
	_stima_std.Set(_stat_std);
	//anti
	_stima_anti.Set(_stat_anti);
	//std+anti
	_stima_std_anti.Set(_stat_std_anti);

	//ottengo la currency dalla prima Eq_price
	Currency *currency=(start_eq_price).Get_currency();

	//salvo il valore del price nella classe
	Price prezzo((_stat_std_anti.Get_media()),currency);
	Set_price(prezzo);

	//pulisco la memoria
	delete ptrtimes;
	delete cammino;
};

//##############################################################################################################
//FUNZIONI GET
//##############################################################################################################

//! funzione che restituisce la stima del prezzo dell'opzione
const Stima_montecarlo &Eq_pricer_montecarlo::Get_Stima(const string &type) const{
	if(type=="std"){
		return _stima_std;
	}
	if(type=="anti"){
		return _stima_anti;
	}
	else {
		return _stima_std_anti;
	}
};


//! funzione che restituisce la statistica del montecarlo 
const Statistica &Eq_pricer_montecarlo::Get_stat_std()const{
	return _stat_std;
};


//! funzione che restituisce la statistica del montecarlo per anticammini
const Statistica &Eq_pricer_montecarlo::Get_stat_anti()const{
	return _stat_anti;
};


//! funzione che restituisce ls statistica del montecarlo su cammini + anticammini
const Statistica &Eq_pricer_montecarlo::Get_stat_std_anti()const{
	return _stat_std_anti;
};


//! funzione che restituisce il prezzo valutato sui cammini standard
Price Eq_pricer_montecarlo::Get_price_std() const{
	Price price(_stima_std.Get_prezzo(),(Get_Eq_option()->Get_Eq_price()).Get_currency());
	return price;
};


//! funzione che restituisce il prezzo valutato sugli anticammini
Price Eq_pricer_montecarlo::Get_price_anti() const{
	Price price(_stima_anti.Get_prezzo(),(Get_Eq_option()->Get_Eq_price()).Get_currency());
	return price;
};

//##############################################################################################################
//OPERATORE ASSEGNAMENTO
//##############################################################################################################

//! overloading dell'operatore di assegnamento
Eq_pricer_montecarlo &Eq_pricer_montecarlo::operator=(Eq_pricer_montecarlo &obj){
		cout<<"sono in = Eq_pricer_montecarlo\n";
	_N=obj._N;
	Set_Eq_option(obj.Get_Eq_option());
	Set_process(obj.Get_process());
	return *this;
};

//##############################################################################################################
//OVERLOADING DEL << 
//##############################################################################################################

std::ostream &operator<<( std::ostream &os,  Eq_pricer_montecarlo &dat){
	os<<"--------STATISTICA_MONTECARLO--------"<<endl<<endl;
		os<<"numero di simulazioni : "<<dat._N<<endl<<endl;
	
		os<<"valutazione sui cammini\n\tmedia : "<<(dat._stat_std.Get_media())<<endl;
			os<<"\terrore  :  "<<dat._stat_std.Get_errore();
			os<<"\n\terrore %  :  "<<dat._stat_std.Get_errore_percentuale()<<endl;
		os<<"valutazione sugli anticammini\n\tmedia : "<<dat._stat_anti.Get_media()<<endl;
			os<<"\terrore  :  "<<dat._stat_anti.Get_errore();
			os<<"\n\terrore %  :  "<<dat._stat_anti.Get_errore_percentuale()<<endl;
		os<<"valutazione sulla media di cammini e anticammini\n\tmedia : ";
			os<<dat._stat_std_anti.Get_media()<<endl;
			os<<"\terrore  :  "<<dat._stat_std_anti.Get_errore();
			os<<"\n\terrore %  :  "<<dat._stat_std_anti.Get_errore_percentuale()<<endl;
	return os;
};

//##############################################################################################################




