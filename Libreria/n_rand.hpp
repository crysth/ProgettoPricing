//###################################################################################################
//	
//	FILE NAME :			n_rand.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class N_rand
//	
//	FIRST VERSION :		2010/jan/27
//	
//	LAST UPTIME : 		2010/apr/6
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Questa classe rappresenta un contenitore di numeri generati casualmente.
//	
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

#ifndef _N_RAND_HPP
#define _N_RAND_HPP

#include <iostream>
#include <string>

using namespace std;
//! Questa classe rappresenta un contenitore di numeri generati casualmente.
/*! Classe di livello 0. \n
Questa classe rappresenta un contenitore di numeri generati casualmente.
*/
class N_rand {

	public:

//		COSTRUTTORI~DISTRUTTORE
		N_rand();
		N_rand(double w);
		N_rand(const N_rand &w);
		~N_rand();

//		OPERATORE ASSEGNAMENTO		
		const N_rand &operator=(const N_rand &n);
		
//		FUNZIONI GET~SET
		void Set_rand(double w);
		double Get_rand() const;

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<" 
		friend ostream &operator<<(ostream &os, const N_rand &dat);	
	
//		OPERATORI
		N_rand operator-()const;
		double operator*(double a) const;
//! overloading dell'operatore di moltiplicazione di un double per un numero random
 		friend double operator*(double a, const N_rand &num);

	private:
		double _w;

};

#endif
