//###################################################################################################
//	
//	FILE NAME :			yield_curve.cpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Implementation of class Yield_curve
//	
//	FIRST VERSION :		2009/dec/13
//	
//	LAST UPDATE : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	E' la classe madre delle curve del tasso e per questo contiene gli overloading delle funzioni di assegnamento delle classi figlie,
//					dichiarati virtual.
//					Le funzioni che restituiscono lo spot-rate ovvero il tasso ad un tempo ben preciso sono chiaramente virtual pure, poichè saranno
//					implementate diversamente in ogni classe figlia.
//					Sono già implementate le funzioni Get_forward_rate e Get_discount_factor che prescindono dalla struttura delle calssi derivate 
//					poichè necessitano delle generiche funzioni Get_spot_rate .
//	
//	
//	
//	
//	
//###################################################################################################


//###################################################################################################
//INCLUDE
//###################################################################################################
#include "yield_curve.hpp"
#include <cmath>
#include <iostream>
#include "deltatime.hpp"
#include "errorlist.hpp"

//###################################################################################################
//FUNCTIONS
//###################################################################################################

//###################################################################################################
//----> Class :		yield_curve
//----> Function name:	Get_discount_factor
//----> Description :	this function returns the discount factor(double) at a specified time t(double)
// 				time must be positive
//###################################################################################################
//! funzione che restituisce il fattore di sconto ad un tempo t fissato. Il tempo deve essere positivo(= maggiore di oggi)
double Yield_curve::Get_discount_factor(const Time &t) const{
	if(t<*(Time::Get_today())) {
		ErrorList::Get_errorlist()->Add_error("Yield_curve::(Get_discount_factor) time must be in the future");
		return -1;
	}
	else return (exp(-(Get_spot_rate(t)*(t-*(Time::Get_today())))));
};


//###################################################################################################
//----> Class :		yield_curve
//----> Function name:	Get_discount_factor
//----> Description :	this function returns the discount factor(double) between 2 specified times 
//				t1(double), t2(double). t1,t2 must be positive, t2 must be > t1
//###################################################################################################
//! funzione che restituisce il fattore di sconto tra 2 tempi t1 e t2
double Yield_curve::Get_discount_factor(const Time &t1, const Time &t2) const{
	if(t1>*(Time::Get_today())) {
		ErrorList::Get_errorlist()->Add_error("Yield_curve::(Get_discount_factor) time must be in the future");
		return -1;
	} 
	else {
		if(t2>t1) return (exp(-Get_forward_rate(t1,t2)*(t2-t1)));
		else {
			ErrorList *err=ErrorList::Get_errorlist();
			err->Add_error("Yield_curve::(Get_discount_factor) t2 must be > than t1");
			return -1;
		}
	}
};


//###################################################################################################
//----> Class :		yield_curve
//----> Function name:	Get_discount_factor
//----> Description :	this function returns the discount factor(double) at a specified time t(double)
// 				time must be positive
//###################################################################################################
//! funzione che restituisce il fattore di sconto su un intervallo temporale delta
double Yield_curve::Get_discount_factor(const Deltatime &delta) const{
	return (exp(-(Get_spot_rate(delta)*(delta))));
};


//###################################################################################################
//----> Class :		yield_curve
//----> Function name:	Get_forward_rate
//----> Description :	this function returns the rate(double) between 2 specified times
//###################################################################################################
//! funzione che restituisce il tasso forward tra i tempi t1 e t2
double Yield_curve::Get_forward_rate(const Time &t1, const Time &t2) const{
	if(t1<*(Time::Get_today())) {
		ErrorList::Get_errorlist()->Add_error("Yield_curve::(Get_forward_rate) time must be in the future");
		return -1;
	} 
	if(t1>t2){
		ErrorList::Get_errorlist()->Add_error("Yield_curve::(Get_forward_rate) t2 must be > than t1");
		return -1;
	}
	return ((Get_spot_rate(t2) * (t2 -*Time::Get_today()) - (Get_spot_rate(t1)*(t1 -*Time::Get_today())))/(t2-t1));
};


//###################################################################################################
//----> Class :		yield_curve
//----> Function name:	Get_forward_rate
//----> Description :	this function returns the rate(double) between 2 specified times
//###################################################################################################
//! funzione che restituisce il tasso forward su un intervallo delta che parte dal tempo t1
double Yield_curve::Get_forward_rate(const Time &t1, const Deltatime &delta) const{
	if(t1<*(Time::Get_today())) {
		ErrorList::Get_errorlist()->Add_error("Yield_curve::(Get_forward_rate) time must be in the future");
		return -1;
	}
	double r1=Get_spot_rate(t1);
	double r2=Get_spot_rate(t1+delta);
	double t_1=(t1- *Time::Get_today()).Value();
	double t_2=(t1+delta - *Time::Get_today()).Value();
	// forward_rate = (r2 * t2 - r1 * t1) / t2-t1
	return ( (r2*t_2) - (r1*t_1) )/ (delta.Value());
};

//###################################################################################################
//OPERATORI ASSEGNAMENTO
//###################################################################################################

//! overloading dell'operatore di assegnamento per la classe figlia: Yield_curve_flat
Yield_curve &Yield_curve::operator=(Yield_curve_flat &obj){
		cout<<"sono in = Yield_curve\n";
	return *this;
};


//! overloading dell'operatore di assegnamento per la classe figlia: Yield_curve_term_struct
Yield_curve &Yield_curve::operator=(Yield_curve_term_struct &obj){
		cout<<"sono in = Yield_curve\n";
	return *this;
};

//###################################################################################################

