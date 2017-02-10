//###################################################################################################
//	
//	FILE NAME :			deltatime.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Deltatime
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/apr/22
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe che rappresenta un intervallo temporale espresso in anni, mesi giorni, ore, minuti e secondi. 
//					Importante la ridefinizione degli operatori che permette di trattare un intervallo temporale come frazione di anni espressa da un double. 
//					Abbiamo ritenuto opportuno ridefinire in modo differente la divisione per un numero reale(double) e per un numero intero.
//					Mentre è più comodo trattare la prima come un double che rappresenti la frazione di anni, nel secondo caso abbiamo scelto di
//					mantenere un oggetto Deltatime.
//						
//	
//	
//	
//	
//	
//###################################################################################################
#ifndef _DELTATIME_HPP
#define _DELTATIME_HPP

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta un intervallo temporale.
/*! Classe di livello 1. \n
Classe che rappresenta un intervallo temporale espresso in anni, mesi giorni, ore, minuti e secondi. Importante la ridefinizione degli operatori che permette di trattare un intervallo temporale come frazione di anni espressa da un double. Abbiamo ritenuto opportuno ridefinire in modo differente la divisione per un numero reale(double) e per un numero intero. Mentre è più comodo trattare la prima come un double che rappresenti la frazione di anni, nel secondo caso abbiamo scelto di mantenere un oggetto Deltatime.
*/
class Deltatime {
	public:
		Deltatime();
		Deltatime(int y,int M,int d,int h, int m, int s);
		Deltatime(const Deltatime &copy);
		~Deltatime();

//		FUNZIONI GET
		int Get_y()const;
		int Get_M()const;
		int Get_d()const;
		int Get_h()const;
		int Get_m()const;
		int Get_s()const;

//		FUNZIONI SET
		void Set_y(int YYYY);
		void Set_M(int M);
		void Set_d(int D);
		void Set_h(int h);
		void Set_m(int m);
		void Set_s(int s);

//		METODI
		double Value()const;

//		OPERATORI MATEMATICI
		double operator*(double c) const;
//! overloading dell'operatore di moltiplicazione: moltiplica un double per l'oggetto valutato in frazione di anni. Restituisce il valore in frazione di anni 
		friend double operator*(double c, const Deltatime &del);
		double operator/(double c) const;
//! overloading dell'operatore di divisione: divide un double per l'oggetto valutato in frazione di anni. Restituisce il valore in frazione di anni	
		friend double operator/(double c, const Deltatime &del);
		Deltatime operator/(int c);
		double operator-(double c) const;
//! overloading dell'operatore di sottrazione: sottrae a un double l'oggetto valutato in frazione di anni. Restituisce il valore in frazione di anni 
		friend double operator-(double c, const Deltatime &del);
		Deltatime operator-(const Deltatime &c) const;
		const Deltatime &operator+=(const Deltatime &d);
		double operator/(const Deltatime &c) const;
		Deltatime operator+(const Deltatime &c) const;

//		OPERATORI LOGICI
		bool operator<=(const Deltatime &d) const;
		bool operator>=(const Deltatime &d) const;
		bool operator<(const Deltatime &d) const;
		bool operator>(const Deltatime &d) const;
		bool operator==(const Deltatime &d) const;
		bool operator!=(const Deltatime &d) const;

//		OPERATORE ASSEGNAMENTO
		const Deltatime &operator=(const Deltatime &copy);

//		OVERLOADING DEL <<
//! overloading dell'operatore "<<" 
		friend ostream &operator<<(ostream &os, const Deltatime &d);

	private:
		int _y,_M,_d,_h,_m,_s;
};

#endif
