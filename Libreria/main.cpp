#include <iostream>
#include <string>

#include "timestruct.hpp"
#include "deltatime.hpp"
#include "time.hpp"
#include "yield_curve_term_struct.hpp"
#include "yield_curve_flat.hpp"
#include "currency.hpp"
#include "price.hpp"
#include "eq_price.hpp"
#include "vol_std.hpp"
#include "process.hpp"
#include "eq_process.hpp"
#include "eq_process_lognormal_eulero.hpp"
#include "eq_process_lognormal_esatto.hpp"
#include "eq_option.hpp"
#include "eq_description.hpp"
#include "eq_pricer_montecarlo.hpp"
#include "rand_gen_root.hpp"
#include "errorlist.hpp"
#include "eq_op_performance_with_corridor.hpp"
#include "eq_process_lognormal_binary.hpp"
#include "pricing.hpp"

#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TLegend.h"


using namespace std;

//singleton a NULL
ErrorList *ErrorList::_list=NULL;
Rand_gen_root *Rand_gen_root::_single=NULL;
Time *Time::_today=NULL;
Yield_curve_flat *Yield_curve_flat::_riskfree=NULL;


int main(){


//_________________________________________Dati inizialI_________________________________________//

//NUMERO SIMULAZIONI
	//dimensione del vettore di simulazioni
	//(ATTENZIONE! se si modifica qui, va modificato anche il punto successivo!)
	int dim_N=15;
	//=num simulazioni
	//(ATTENZIONE! devono essere esattamente dim_N!)
	int N[dim_N];
		N[0]=500;
		N[1]=1000;
		N[2]=3000;
		N[3]=5000;
		N[4]=10000;
		N[5]=12000;
		N[6]=16000;
		N[7]=20000;
		N[8]=23000;
		N[9]=26000;
		N[10]=30000;
		N[11]=32000;
		N[12]=35000;
		N[13]=37000;
		N[14]=40000;


//VALORE INIZIALE DELL'AZIONE
	//=valore iniziale dell'azione = Eq_price[0]
	double S_O=100.;	

//STRIKEPRICE
	//=strikeprice %
	double strikeprice=0.02;	

//VALORE DEL TASSO RISKFREE
	//=riskfree flat
	double rate=0.02;	
	
//VOLATILITA
	//dimensione del vettore di volatilità
	//(ATTENZIONE! se si modifica qui, va modificato anche il punto successivo!)
	int dim_vol=4;
	//volatilità in %
	//(ATTENZIONE! devono essere esattamente dim_vol!)
	double volatilita[dim_vol];
		volatilita[0]=0.;
		volatilita[1]=0.15;	
		volatilita[2]=0.30;	
		volatilita[3]=0.60;	

//NUMERO INTERVALLI
	//numero di m intervalli
	//(ATTENZIONE! se si modifica qui, va modificato anche il punto successivo!)
	int dim_m=8;
	//num intervalli=> deltatime=T/n (ATTENZIONE! devono essere esattamente dim_m!)
	int m[dim_m];
		m[0]= 2;
		m[1]= 5;
		m[2]= 10;
		m[3]= 20;
		m[4]= 50;
		m[5]= 100;
		m[6]= 150;
		m[7]= 200;

//LAMBDA
	//numero dati di Lambda
	//(ATTENZIONE! se si modifica qui, va modificato anche il punto successivo)
	int dim_lambda=5;
	//valori di lambda
	//(ATTENZIONE! devono essere esattamente dim_lambda!)
	double lambda[dim_lambda];
		lambda[0]=0.;
		lambda[1]=0.15;
		lambda[2]=0.30;
		lambda[3]=0.60;
		lambda[4]=1.20;

//TIME MATURITY
	//numero dati di TimeMaturity
	//(ATTENZIONE! se si modifica qui, va modificato anche il punto successivo)
	int dim_time=9;
	//Time maturity
	//(ATTENZIONE! devono essere esattamente dim_time!)
	Deltatime *intervallo_temporale[dim_time];
		intervallo_temporale[0]= new Deltatime(0,6,0,0,0,0);	//tempo totale
		intervallo_temporale[1]= new Deltatime(1,0,0,0,0,0);	//tempo totale
		intervallo_temporale[2]= new Deltatime(1,6,0,0,0,0);	//tempo totale
		intervallo_temporale[3]= new Deltatime(2,0,0,0,0,0);	//tempo totale
		intervallo_temporale[4]= new Deltatime(2,6,0,0,0,0);	//tempo totale
		intervallo_temporale[5]= new Deltatime(3,0,0,0,0,0);	//tempo totale
		intervallo_temporale[6]= new Deltatime(3,6,0,0,0,0);	//tempo totale
		intervallo_temporale[7]= new Deltatime(6,6,0,0,0,0);	//tempo totale
		intervallo_temporale[8]= new Deltatime(10,6,0,0,0,0);	//tempo totale
	Timestruct maturity(intervallo_temporale , dim_time);




//_________________________________________Setto i membri staticI_________________________________________//

	//today
	Time::Set_today(1,3,15,10,11,10);
		cout<<endl<<"istante iniziale :"<<endl;
		Time::Print_today();
		cout<<endl<<endl;

	//riskfree
	Yield_curve_flat::Set_riskfree(rate);


//_________________________________________Stampa a video dei datI_________________________________________//

	cout<<"Dati iniziali :  "<<endl;
	cout<<"numero simulazioni  "<<"\t";
		for(int i=0;i<dim_N;i++) cout<<N[i]<<"\t";
		cout<<endl;
	cout<<"valore iniziale dell'azione  "<<S_O<<endl;
	cout<<"strikeprice  "<<strikeprice<<endl;
	cout<<"tasso riskfree  "<<rate<<endl;
	cout<<"volatilità  "<<"\t";
		for(int i=0;i<dim_vol;i++) cout<<volatilita[i]<<"\t";
		cout<<endl;
	cout<<"numero m di intervalli  ";
		for(int i=0;i<dim_m;i++) cout<<m[i]<<"\t";
		cout<<endl;
	cout<<"lambda  ";
		for(int i=0;i<dim_lambda;i++) cout<<lambda[i]<<"\t";
		cout<<endl;
	cout<<"valori di maturity time T\n";
		for(int i=0;i<dim_time;i++) cout<<"\t"<<(*intervallo_temporale[i])<<"\n";
		cout<<endl;


//_________________________________________Computazione dei datI_________________________________________//


//VARIABILI TIME MATURITY E m
	Pricing p1(N[7], S_O, strikeprice, rate, volatilita[2], maturity, lambda[1], m, dim_m, "esatto" , "datiTime.dat");

//VARIABILI LAMBDA E m
//	Pricing p2(N[7], S_O, strikeprice, rate, volatilita[2], *intervallo_temporale[2], lambda, dim_lambda, m, dim_m, "binary", "datiLambda.dat");

//VARIABILE N
//	Pricing p3(N, dim_N, S_O, strikeprice, rate, volatilita[2], *intervallo_temporale[4], lambda[1], m[2], "esatto", "datiN.dat");

//VARIABILE N ( OPZIONE W )
//	Pricing p7(N[7], S_O, rate, volatilita[2], *intervallo_temporale[5], m, dim_m, "datiOpzionew.dat");

//VARIABILE VOLATILITY
//	Pricing p4(N[7], S_O, strikeprice, rate, volatilita, dim_vol, *intervallo_temporale[2], lambda[1], m, dim_m, "esatto", "datiVol.dat"); 

//VOLATILITA A ZERO
//	Pricing p5(N[1], S_O, strikeprice, rate, volatilita[0], maturity, lambda[1], m, 1, "esatto" , "datiLambdazero.dat");

//PLAINVANILLA
//	Pricing p8(N[1], S_O, 0., rate, volatilita[2], maturity, m, dim_m, "datiPlainvanilla.dat");


return 0;
}



