//###################################################################################################################
//	
//	FILE NAME :		pricing.cpp
//	
//	FILE TYPE :		C++ file
//	
//	AUTHORS :		Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Pricing
//	
//	FIRST VERSION :		2010/apr/11
//	
//	LAST UPTIME : 		2010/apr/12
//	
//	STATUS :		final
//	
//	COPYRIGHT :		none
//	
//	
//	DETAILED DESCRIPTION :	Classe ad hoc per la risoluzione del tema d'esame. Grazie a questa classe è possibile ottenere 
//				un file di testo (passatone il nome al costruttore) nel quale vengono stampati direttamente dalla 
//				classe i risultati della simulazione. Al costruttore vengono passati tutti i parametri fissati (in double 
//				o int) e tutti i parametri che si vogliono far variare (come vettori di double, int o deltatime); al 
//				costruttore viene passato anche il tipo di processo (come string) che si vuole utilizzare per l'evoluzione
//				dell'azione. Ogni costruttore rappresenta una delle simulazioni richieste dal tema d'esame.
//				1. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di maturity time. 
//					La simulazione viene eseguita per ogni valore di m.
//				2. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di lambda. 
//					La simulazione viene eseguita per ogni valore di m.
//				3. Costruttore che permette di studiare l'andamento dell'errore in dipendenza dal numero di simulazioni N.
//				4. Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di volatilità. 
//					La simulazione viene eseguita per ogni valore di m.
//				5. Costruttore che permette di studiare la variazione del prezzo di un'opzione plain-vanilla. 
//					La simulazione viene eseguita per ogni valore di m.
//				6. Costruttore che permette di effettuare un test della libreria e del generatore di numeri casuali tramite l'opzione 
//					Eq_op_w.La simulazione viene eseguita per ogni valore di m.
//				Questa classe permette un utilizzo rapido e pratico di tutta la libreria.
//				Abbiamo volutamente evitato l'implementazione di un costruttore generico, implementando invece costruttori mirati ai
//				problemi del tema d'esame, per ottimizzare l'esecuzione di ogni simulazione. 	
//	
//###################################################################################################################


//###################################################################################################################
//INCLUDE
//###################################################################################################################
#include "pricing.hpp"

//###################################################################################################################
//COSTRUTTORI~DISTRUTTORE
//###################################################################################################################

//! costruttore di default
Pricing::Pricing(){};

//###################################################################################################################
//COSTRUTTORE 1 (variazione del price per maturity time)
//permette di creare dati partendo dalla timestruct (un punto per ogni deltatime presente nella timestruct)
//i dati si ripetono dim_m volte secondo gli m passati nel vettore
//###################################################################################################################
//! Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di maturity time. La simulazione viene eseguita per ogni valore di m
Pricing::Pricing(int N, double S_O, double strikeprice, double rate, double volatility, Timestruct T_maturity, double lambda, int *m, int dim_m, string name_process, const char *nome_file_out) {
	fstream _out;
	//file di output dati	
	_out.open(nome_file_out,ios::out);
	_out<<"#opzione PERFORMANCE WITH CORRIDOR"<<endl;
	_out<<"#N simulazioni "<<N<<endl;
	_out<<"#S_O "<<S_O<<endl;
	_out<<"#strikeprice "<<strikeprice<<endl;
	_out<<"#rate "<<rate<<endl;
	_out<<"#volatility "<<volatility<<endl;
	_out<<"#lambda "<<lambda<<endl;
	_out<<"#processo "<<name_process<<endl;
	_out<<"#Maturity Time "<<T_maturity<<endl;
	_out<<"#m "; for(int i=0;i<dim_m;i++) _out<<m[i]<<"\t"; _out<<endl<<endl<<endl;
	_out<<"#deltatime\t\tprice\t\t\t\terr%"<<endl;
	//curva dei tassi
	Yield_curve_flat *ptrcurve=new Yield_curve_flat(rate);
	//volatilità
	Volatility *ptrvolatility=new Vol_std(volatility);
	//anagrafica dell'azione
	Eq_description *ptreqdescr=new Eq_description("enel","jkflu3i743gigt",ptrcurve,ptrvolatility);
	//istante iniziale
	Time now=*(Time::Get_today());
	//currency
	Currency *ptrcurrency=new Currency;
	//prezzo iniziale
	Price price(S_O,ptrcurrency);
	//classe per prezzo dell'azione all'istante time
	Eq_price eqprice(ptreqdescr,now,price);
	//generatore numeri casuali
	Rand_gen_root *ptrrandgenroot=Rand_gen_root::Get_rand_gen_root();
	//classe per l'evoluzione dell'azione
	Eq_process *ptreqprocess;
	if(name_process=="binary"){
		ptreqprocess = new Eq_process_lognormal_binary(ptrrandgenroot);
	}
	if(name_process=="eulero"){
		ptreqprocess = new Eq_process_lognormal_eulero(ptrrandgenroot);
	}
	else {
		ptreqprocess=new Eq_process_lognormal_esatto(ptrrandgenroot);
	}
	//oggetti e puntatori che verranno refreshati più volte nel ciclo
	Deltatime deltatime;
	Deltatime deltatime1;
	Timestruct *timestruct;
	Eq_option *ptreqoption;
	Eq_pricer_montecarlo *pricer;
	//primo ciclo che permette di ripetere i dati per diversi valori di m
	for(int j=0;j<dim_m;j++){
		//ciclo che computa i dati per diversi valori di Maturity time
		for(int i=0;i<T_maturity.Get_dim();i++){
			//deltatime (T/n)
			deltatime1 = (T_maturity.Get_deltatime(i));
			deltatime=deltatime1 / m[j];
			//struttura temporale
			timestruct= new Timestruct(deltatime,m[j]);
			//contratto dell'opzione
			ptreqoption=new Eq_op_performance_with_corridor(eqprice,*timestruct,strikeprice,lambda);
				//il pricer (montecarlo)
				pricer = new Eq_pricer_montecarlo(ptreqoption,ptreqprocess,N);
					pricer->Compute_price();
			// stampo i dati
			_out<<(T_maturity.Get_deltatime(i).Value())<<"\t\t\t"<<(pricer->Get_price().Get_price());
			_out<<"\t\t\t"<<pricer->Get_stat_std_anti().Get_errore_percentuale()<<endl;
			//pulisco i vettori
			delete pricer;
			delete ptreqoption;
			delete timestruct;
		}
		_out<<endl;
	}
	//pulisco la memoria
	delete ptreqprocess;
	delete ptrcurrency;
	delete ptreqdescr;
	delete ptrvolatility;
	delete ptrcurve;
	_out.close();
};


//###################################################################################################################
//COSTRUTTORE 2 (variazione del price per lambda)
//permette di creare dati facendo variare lambda (quindi dim_lambda dati)
//i dati si ripetono dim_m volte secondo gli m passati nel vettore
//###################################################################################################################
//! Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di lambda. La simulazione viene eseguita per ogni valore di m
Pricing::Pricing(int N, double S_O, double strikeprice, double rate, double volatility, const Deltatime &T_maturity, double *lambda, int dim_lambda, int *m, int dim_m, string name_process, const char *nome_file_out){
	fstream _out;
	//file di output dati	
	_out.open(nome_file_out,ios::out);
	_out<<"#opzione PERFORMANCE WITH CORRIDOR"<<endl;
	_out<<"#N simulazioni "<<N<<endl;
	_out<<"#S_O "<<S_O<<endl;
	_out<<"#strikeprice "<<strikeprice<<endl;
	_out<<"#rate "<<rate<<endl;
	_out<<"#volatility "<<volatility<<endl;
	_out<<"#processo "<<name_process<<endl;
	_out<<"#Maturity Time "<<T_maturity<<endl;
	_out<<"#lambda "; for(int i=0;i<dim_lambda;i++) _out<<lambda[i]<<"\t"; _out<<endl;
	_out<<"#m "; for(int i=0;i<dim_m;i++) _out<<m[i]<<"\t"; _out<<endl<<endl<<endl;
	_out<<"#lambda\t\tprice\t\terr%"<<endl;
	//curva dei tassi
	Yield_curve_flat *ptrcurve=new Yield_curve_flat(rate);
	//volatilità
	Volatility *ptrvolatility=new Vol_std(volatility);
	//anagrafica dell'azione
	Eq_description *ptreqdescr=new Eq_description("enel","jkflu3i743gigt",ptrcurve,ptrvolatility);
	//istante iniziale
	Time now=*(Time::Get_today());
	//currency
	Currency *ptrcurrency=new Currency;
	//prezzo iniziale
	Price price(S_O,ptrcurrency);
	//classe per prezzo dell'azione all'istante time
	Eq_price eqprice(ptreqdescr,now,price);
	//generatore numeri casuali
	Rand_gen_root *ptrrandgenroot=Rand_gen_root::Get_rand_gen_root();
	//classe per l'evoluzione dell'azione
	Eq_process *ptreqprocess;
	if(name_process=="binary"){
		ptreqprocess=new Eq_process_lognormal_binary(ptrrandgenroot);
	}
	if(name_process=="eulero"){
		ptreqprocess=new Eq_process_lognormal_eulero(ptrrandgenroot);
	}
	else {
		ptreqprocess=new Eq_process_lognormal_esatto(ptrrandgenroot);
	}
	//oggetti e puntatori che verranno refreshati più volte nel ciclo
	Deltatime deltatime1=T_maturity;
	Deltatime deltatime;
	Timestruct *timestruct;
	Eq_option *ptreqoption;
	Eq_pricer_montecarlo *pricer;
	//primo ciclo che permette di ripetere i dati per diversi valori di m
	for(int j=0;j<dim_m;j++){
			//deltatime (T/n)
			deltatime=(deltatime1/m[j]);
			//struttura temporale
			timestruct = new Timestruct(deltatime,m[j]);
		//ciclo che computa i dati per diversi valori di lambda
		for(int i=0;i<dim_lambda;i++){
			//contratto dell'opzione
			ptreqoption=new Eq_op_performance_with_corridor(eqprice,*timestruct,strikeprice,lambda[i]);
			//il pricer (montecarlo)
			pricer = new Eq_pricer_montecarlo(ptreqoption,ptreqprocess,N);
				pricer->Compute_price();
			//stampa i dati
			_out<<lambda[i]<<"\t"<<pricer->Get_price().Get_price();
			_out<<"\t\t"<<pricer->Get_stat_std_anti().Get_errore_percentuale()<<endl;
			//pulisco i puntatori
			delete pricer;
			delete ptreqoption;
			}
			_out<<endl;
			delete timestruct;
	}
	//pulisco la memoria
	delete ptreqprocess;
	delete ptrcurrency;
	delete ptreqdescr;
	delete ptrvolatility;
	delete ptrcurve;
	_out.close();
};


//###################################################################################################################
//COSTRUTTORE 3 (controllo errori su N simulazioni variabile)
//permette di creare dati facendo variare il numero di simulazioni (quindi dim_N dati)
//###################################################################################################################
//! Costruttore che permette di studiare l'andamento dell'errore in dipendenza dal numero di simulazioni N
Pricing::Pricing(int *N, int dim_N, double S_O, double strikeprice, double rate, double volatility, const Deltatime &T_maturity, double lambda, int m, string name_process, const char *nome_file_out){
	//file di output dati	
	fstream _out;
	_out.open(nome_file_out,ios::out);
	_out<<"#opzione PERFORMANCE WITH CORRIDOR"<<endl;
	_out<<"#S_O "<<S_O<<endl;
	_out<<"#strikeprice "<<strikeprice<<endl;
	_out<<"#rate "<<rate<<endl;
	_out<<"#volatility "<<volatility<<endl;
	_out<<"#processo "<<name_process<<endl;
	_out<<"#Maturity Time "<<T_maturity<<endl;
	_out<<"#lambda "<<lambda<<endl;
	_out<<"#N simulazioni "; for(int i=0;i<dim_N;i++) _out<<N[i]<<"\t"; _out<<endl<<endl<<endl;
	_out<<"#N\t\terr%"<<endl;
	//curva dei tassi
	Yield_curve_flat *ptrcurve=new Yield_curve_flat(rate);
	//volatilità
	Volatility *ptrvolatility=new Vol_std(volatility);
	//anagrafica dell'azione
	Eq_description *ptreqdescr=new Eq_description("enel","jkflu3i743gigt",ptrcurve,ptrvolatility);
	//istante iniziale
	Time now=*(Time::Get_today());
	//currency
	Currency *ptrcurrency=new Currency;
	//prezzo iniziale
	Price price(S_O,ptrcurrency);
	//classe per prezzo dell'azione all'istante time
	Eq_price eqprice(ptreqdescr,now,price);
	//generatore numeri casuali
	Rand_gen_root *ptrrandgenroot=Rand_gen_root::Get_rand_gen_root();
	//classe per l'evoluzione dell'azione
	Eq_process *ptreqprocess;
	if(name_process=="binary"){
		ptreqprocess=new Eq_process_lognormal_binary(ptrrandgenroot);
	}
	if(name_process=="eulero"){
		ptreqprocess=new Eq_process_lognormal_eulero(ptrrandgenroot);
	}
	else {
		ptreqprocess=new Eq_process_lognormal_esatto(ptrrandgenroot);
	}
	//puntatori che verranno allocati più volte nel ciclo
	Timestruct *timestruct;
	Eq_option *ptreqoption;
	Eq_pricer_montecarlo *pricer;
	//deltatime (T/n)
	Deltatime deltatime1(T_maturity);
	Deltatime deltatime=deltatime1/m;
	//struttura temporale
	timestruct = new Timestruct(deltatime,m);
	//contratto dell'opzione
	ptreqoption=new Eq_op_performance_with_corridor(eqprice,*timestruct,strikeprice,lambda);
	//ciclo che computa i dati
	for(int i=0;i<dim_N;i++){
		//il pricer (montecarlo)
		pricer = new Eq_pricer_montecarlo(ptreqoption,ptreqprocess,N[i]);
			pricer->Compute_price();
		// stampo gli errori
		_out<<N[i]<<"\t\t"<<pricer->Get_stat_std_anti().Get_errore_percentuale()<<endl;
		//pulisco il puntatore
		delete pricer;
	}
	//pulisco la memoria
	delete ptreqoption;
	delete timestruct;
	delete ptreqprocess;
	delete ptrcurrency;
	delete ptreqdescr;
	delete ptrvolatility;
	delete ptrcurve;
	_out.close();
};


//###################################################################################################################
//COSTRUTTORE 4 (variazione del price per la volatilità)
//permette di creare dati partendo dalla volatilità (quindi dim_vol punti)
//i dati si ripetono dim_m volte secondo gli m passati nel vettore
//###################################################################################################################
//! Costruttore che permette di studiare la variazione del prezzo dell'opzione per diversi valori di volatilità. La simulazione viene eseguita per ogni valore di m
Pricing::Pricing(int N, double S_O, double strikeprice, double rate, double *volatility, int dim_vol, const Deltatime &T_maturity, double lambda, int *m, int dim_m, string name_process, const char *nome_file_out) {
	fstream _out;
	//file di output dati	
	_out.open(nome_file_out,ios::out);
	_out<<"#opzione PERFORMANCE WITH CORRIDOR"<<endl;
	_out<<"#N simulazioni "<<N<<endl;
	_out<<"#S_O "<<S_O<<endl;
	_out<<"#strikeprice "<<strikeprice<<endl;
	_out<<"#rate "<<rate<<endl;
	_out<<"#lambda "<<lambda<<endl;
	_out<<"#processo "<<name_process<<endl;
	_out<<"#Maturity Time "<<T_maturity<<endl;
	_out<<"#volatilità "; for(int i=0;i<dim_vol;i++) _out<<volatility[i]<<"\t"; _out<<endl;
	_out<<"#m "; for(int i=0;i<dim_m;i++) _out<<m[i]<<"\t"; _out<<endl<<endl<<endl;
	_out<<"#Volatility\t\tprice\t\terr%"<<endl;
	//curva dei tassi
	Yield_curve_flat *ptrcurve=new Yield_curve_flat(rate);
	//volatilità
	Volatility *ptrvolatility=new Vol_std(volatility[0]);
	//anagrafica dell'azione
	Eq_description *ptreqdescr=new Eq_description("enel","jkflu3i743gigt",ptrcurve,ptrvolatility);
	//istante iniziale
	Time now=*(Time::Get_today());
	//currency
	Currency *ptrcurrency=new Currency;
	//prezzo iniziale
	Price price(S_O,ptrcurrency);
	//classe per prezzo dell'azione all'istante time
	Eq_price eqprice(ptreqdescr,now,price);
	//generatore numeri casuali
	Rand_gen_root *ptrrandgenroot=Rand_gen_root::Get_rand_gen_root();
	//classe per l'evoluzione dell'azione
	Eq_process *ptreqprocess;
	if(name_process=="binary"){
		ptreqprocess = new Eq_process_lognormal_binary(ptrrandgenroot);
	}
	if(name_process=="eulero"){
		ptreqprocess = new Eq_process_lognormal_eulero(ptrrandgenroot);
	}
	else {
		ptreqprocess=new Eq_process_lognormal_esatto(ptrrandgenroot);
	}
	//deltatime (T/n)
	Deltatime deltatime1=T_maturity;
	//struttura temporale
	Timestruct *timestruct;
	//puntatori che verranno allocati più volte nel ciclo
	Eq_option *ptreqoption;
	Eq_pricer_montecarlo *pricer;
	//primo ciclo che permettere di ripetere i dati per tutti i valori di m
	for(int j=0;j<dim_m;j++){
		Deltatime deltatime=deltatime1/m[j];
		timestruct= new Timestruct(deltatime,m[j]);
		//ciclo che computa i dati per ogni valore di volatilità
		for(int i=0;i<dim_vol;i++){
			//setto la volatilità secondo il valore iesimo del vettore
			delete ptrvolatility;
			ptrvolatility=new Vol_std(volatility[i]);
			ptreqdescr->Set_vol(ptrvolatility);
			//contratto dell'opzione
			ptreqoption=new Eq_op_performance_with_corridor(eqprice,*timestruct,strikeprice,lambda);
				//il pricer (montecarlo)
				pricer = new Eq_pricer_montecarlo(ptreqoption,ptreqprocess,N);
					pricer->Compute_price();
			// stampo i dati
			_out<<volatility[i]<<"\t"<<(pricer->Get_price().Get_price());
			_out<<"\t\t"<<pricer->Get_stat_std_anti().Get_errore_percentuale()<<endl;
			//pulisco i puntatori
			delete pricer;
			delete ptreqoption;
		}
		delete timestruct;
		_out<<endl;
	}
	//pulisco la memoria
	delete ptreqprocess;
	delete ptrcurrency;
	delete ptreqdescr;
	delete ptrvolatility;
	delete ptrcurve;
	_out.close();
};


//###################################################################################################################
//COSTRUTTORE 5 (PLAINVANILLA)
//permette di creare dati partendo dal time maturity
//i dati si ripetono dim_m volte secondo gli m passati nel vettore
//###################################################################################################################
//! Costruttore che permette di studiare la variazione del prezzo di un'opzione plain-vanilla. La simulazione viene eseguita per ogni valore di m
Pricing::Pricing(int N, double S_O, double strikeprice, double rate, double volatility, Timestruct T_maturity, int *m, int dim_m, const char *nome_file_out) {
	fstream _out;
	//file di output dati	
	_out.open(nome_file_out,ios::out);
	_out<<"#opzione PLAINVANILLA"<<endl;
	_out<<"#N simulazioni "<<N<<endl;
	_out<<"#S_O "<<S_O<<endl;
	_out<<"#strikeprice "<<strikeprice<<endl;
	_out<<"#rate "<<rate<<endl;
	_out<<"#Maturity Time "<<T_maturity<<endl;
	_out<<"#volatilità "<<volatility<<endl;
	_out<<"#m "; for(int i=0;i<dim_m;i++) _out<<m[i]<<"\t"; _out<<endl<<endl<<endl;
	//curva dei tassi
	Yield_curve_flat *ptrcurve=new Yield_curve_flat(rate);
	//volatilità
	Volatility *ptrvolatility=new Vol_std(volatility);
	//anagrafica dell'azione
	Eq_description *ptreqdescr=new Eq_description("enel","jkflu3i743gigt",ptrcurve,ptrvolatility);
	//istante iniziale
	Time now=*(Time::Get_today());
	//currency
	Currency *ptrcurrency=new Currency;
	//prezzo iniziale
	Price price(S_O,ptrcurrency);
	//classe per prezzo dell'azione all'istante time
	Eq_price eqprice(ptreqdescr,now,price);
	//generatore numeri casuali
	Rand_gen_root *ptrrandgenroot=Rand_gen_root::Get_rand_gen_root();
	//classe per l'evoluzione dell'azione
	Eq_process *ptreqprocess=new Eq_process_lognormal_esatto(ptrrandgenroot);
	//oggetti e puntatori che verranno refreshati più volte nel ciclo
	Deltatime deltatime;
	Deltatime deltatime1;
	Timestruct *timestruct;
	Eq_option *ptreqoption;
	Eq_pricer_montecarlo *pricer;
	//primo ciclo che permette di ripetere i dati per diversi valori di m
	for(int j=0;j<dim_m;j++){
		//ciclo che computa i dati per diversi valori di Maturity time
		for(int i=0;i<T_maturity.Get_dim();i++){
			//deltatime (T/n)
			deltatime1 = (T_maturity.Get_deltatime(i));
			deltatime=deltatime1 / m[j];
			//struttura temporale
			timestruct= new Timestruct(deltatime,m[j]);
			//contratto dell'opzione
			ptreqoption = new Eq_op_plainvanilla(eqprice,*timestruct,strikeprice);
				//il pricer (montecarlo)
				pricer = new Eq_pricer_montecarlo(ptreqoption,ptreqprocess,N);
					pricer->Compute_price();
			// stampo i dati
			_out<<(T_maturity.Get_deltatime(i).Value())<<"\t"<<(pricer->Get_price().Get_price());
			_out<<"\t\t"<<pricer->Get_stat_std_anti().Get_errore()<<endl;
			//pulisco i vettori
			delete pricer;
			delete ptreqoption;
			delete timestruct;
		}
		_out<<endl;
	}
	//pulisco la memoria
	delete ptreqprocess;
	delete ptrcurrency;
	delete ptreqdescr;
	delete ptrvolatility;
	delete ptrcurve;
	_out.close();
};


//###################################################################################################################
//COSTRUTTORE 6 (opzione W - test sul generatore di numeri casuali e sull'implementazione)
//permette di creare dati facendo variare il numero di simulazioni (quindi dim_N dati)
//###################################################################################################################
//! Costruttore che permette di effettuare un test della libreria e del generatore di numeri casuali tramite l'opzione Eq_op_w.La simulazione viene eseguita per ogni valore di m.
Pricing::Pricing(int N, double S_O, double rate, double volatility, const Deltatime &T_maturity, int *m, int dim_m, const char *nome_file_out){
	//file di output dati	
	fstream _out;
	_out.open(nome_file_out,ios::out);
	_out<<"#opzione W"<<endl;
	_out<<"#N simulazioni "<<N<<endl;
	_out<<"#S_O "<<S_O<<endl;
	_out<<"#rate "<<rate<<endl;
	_out<<"#Maturity Time "<<T_maturity<<endl;
	_out<<"#m "; for(int i=0;i<dim_m;i++) _out<<m[i]<<"\t"; _out<<endl<<endl;
	_out<<"#m\t\t<m>\t\terr%"<<endl;
	//curva dei tassi
	Yield_curve_flat *ptrcurve=new Yield_curve_flat(rate);
	//volatilità
	Volatility *ptrvolatility=new Vol_std(volatility);
	//anagrafica dell'azione
	Eq_description *ptreqdescr=new Eq_description("enel","jkflu3i743gigt",ptrcurve,ptrvolatility);
	//istante iniziale
	Time now=*(Time::Get_today());
	//currency
	Currency *ptrcurrency=new Currency;
	//prezzo iniziale
	Price price(S_O,ptrcurrency);
	//classe per prezzo dell'azione all'istante time
	Eq_price eqprice(ptreqdescr,now,price);
	//generatore numeri casuali
	Rand_gen_root *ptrrandgenroot=Rand_gen_root::Get_rand_gen_root();
	//classe per l'evoluzione dell'azione
	Eq_process *ptreqprocess=new Eq_process_lognormal_esatto(ptrrandgenroot);
	//puntatori che verranno allocati più volte nel ciclo
	Timestruct *timestruct;
	Eq_pricer_montecarlo *pricer;
	//contratto dell'opzione
	Eq_option *ptreqoption;
	//deltatime (T/n)
	Deltatime deltatime1(T_maturity);
	Deltatime deltatime;
	//ciclo che computa i dati
	for(int i=0;i<dim_m;i++){
		deltatime=deltatime1/m[i];
		//struttura temporale
		timestruct = new Timestruct(deltatime,m[i]);
		//contratto dell'opzione
		ptreqoption = new Eq_op_w(eqprice,*timestruct);
		//il pricer (montecarlo)
		pricer = new Eq_pricer_montecarlo(ptreqoption,ptreqprocess,N);
			pricer->Compute_price();
		// stampo gli errori
		_out<<m[i]<<"\t"<<(pricer->Get_price().Get_price())*exp(0.02*T_maturity.Value());
		_out<<"\t\t"<<pricer->Get_stat_std_anti().Get_errore()*exp(0.02*T_maturity.Value())<<endl;
		//pulisco i puntatori
		delete pricer;
		delete ptreqoption;
		delete timestruct;
	}
	//pulisco la memoria
	delete ptreqprocess;
	delete ptrcurrency;
	delete ptreqdescr;
	delete ptrvolatility;
	delete ptrcurve;
	_out.close();
};


//###################################################################################################################
//DISTRUTTORE
//###################################################################################################################
//! distruttore
Pricing::~Pricing(){};
//###################################################################################################################




