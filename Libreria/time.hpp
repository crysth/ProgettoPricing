//###################################################################################################
//	
//	FILE NAME :			time.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Time
//	
//	FIRST VERSION :		2010/jan/5
//	
//	LAST UPTIME : 		2010/feb/5
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Classe che rappresenta un istante temporale, quindi una data e un’orario.
//					Abbiamo trattato questa classe con particolare cura, implementando funzioni di controllo per gli anni bisestili, metodi e operatori
//					di interazione con le altri classi temporali (in particolare la Deltatime), prestando attenzione al differente numero di giorni dei 
//					mesi. La data è rappresentata come : anno, mese, giorno, ore, minuti, secondi. 
//					Possiede un membro statico "today" che indica il giorno di "oggi". Questo singleton ci permette di gestire al meglio alcune funzioni
//					all'interno della libreria:
//					se in una funzione è necessario conoscere una data si potrà anche passare un oggetto Deltatime che automaticamente, facendo riferimento 
//					a today, ricaverà la data in questione. 
//					Ecco il metodo per stabilire se l'anno sia o meno bisestile:
//					bisestile: if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0))
//					ovvero se l'anno è divisibile per 4, ma non per cento, oppure se è divisibile per 400.
//					non bisestile: if(_YYYY%400!=0){if((_YYYY%4!=0)||(_YYYY%100==0));}
//					ovvero se non è divisibile per 400 e, o non è divisibile per 4 o non è divisibile per 100.
//	
//###################################################################################################


//###################################################################################################
//INCLUDE
//###################################################################################################

#ifndef _TIME_HPP
#define _TIME_HPP

#include <iostream>
#include <string>
#include <cstdlib>

#include "errorlist.hpp"
#include "deltatime.hpp"

using namespace std;
//! Classe che rappresenta un istante temporale.
/*! Classe di livello 1.  \n
Classe che rappresenta un istante temporale, quindi una data e un’orario. \n
Abbiamo trattato questa classe con particolare cura, implementando funzioni di controllo per gli anni bisestili, metodi e operatori di interazione con le altri classi temporali (in particolare la Deltatime), prestando attenzione al differente numero di giorni dei mesi.  \n
La data è rappresentata come : anno, mese, giorno, ore, minuti, secondi. \n
Possiede un membro statico "today" che indica il giorno di "oggi". Questo singleton ci permette di gestire al meglio alcune funzioni all'interno della libreria: \n
se in una funzione è necessario conoscere una data si potrà anche passare un oggetto Deltatime che automaticamente, facendo riferimento a today, ricaverà la data in questione. \n
Ecco il metodo per stabilire se l'anno sia o meno bisestile: \n
bisestile: if((_YYYY%4==0 && _YYYY%100!=0)||(_YYYY%400==0)) \n
ovvero se l'anno è divisibile per 4, ma non per cento, oppure se è divisibile per 400. \n
non bisestile: if(_YYYY%400!=0){if((_YYYY%4!=0)||(_YYYY%100==0));} \n
ovvero se non è divisibile per 400 e, o non è divisibile per 4 o non è divisibile per 100. 
*/
class Time {

	public:
		Time();
		Time(int YYYY, int M, int D, int h, int m, int s);
		Time(const Time &copia);
		~Time();

//		FUNZIONI GET
		int Get_year()const;
		int Get_month()const;
		int Get_day()const;
		int Get_hour()const;
		int Get_minute()const;
		int Get_second()const;

//		FUNZIONI SET
		void Set_year(int YYYY);
		void Set_month(int M);
		void Set_day(int D);
		void Set_hour(int h);
		void Set_minute(int m);
		void Set_second(int s);

//		FUNZIONI TODAY
		static void Set_today(const Time &today);
		static void Set_today(int Y,int M,int D,int h,int m,int s);
		static Time* Get_today() ;
		static void Print_today();

//		GIORNI DEL MESE
		int Num_days_M(int mese) const;

//		CONTEGGIO GIORNI
		int Delta_days_0() const;
		int Delta_days_1() const;

//		DIFFERENZE DI TIME
		int Delta_days(const Time &da) const;
		double Delta_months(const Time &da) const;
		double Delta_years(const Time &da) const;

//		METODI DI SOMMA E SOTTRAZIONE
//! funzione che permette di sommare ad un time secondi, minuti, ore, giorni, mesi o anni in base a quanto specificato nella stringa
		void Plus(int pl, const string &a);
//! funzione che permette di sottrarre a un time secondi, minuti, ore, giorni, mesi o anni in base a quanto specificato nella string
		void Minus(int pl, const string &a);

//		OPERATORI SOMMA-SOTTRAZIONE
		Time operator-(int days) const;
		Time operator+(int days) const;
		Time &operator+=(int days);
		Time &operator-=(int days);

//		OPERATORI SOMMA-SOTTRAZIONE CON DELTATIME
		Deltatime operator-(const Time &d1) const;
		Time operator-(const Deltatime &c) const;
		Time operator+(const Deltatime &delta) const;
		Time &operator+=(const Deltatime &delta);
		Time &operator-=(const Deltatime &delta);

//		OPERATORE DI ASSEGNAMENTO
		const Time &operator=(const Time &data);

//		OPERATORI LOGICI
		bool operator==(const Time &dat) const;
		bool operator!=(const Time &dat) const;
		bool operator<(const Time &dat) const;
		bool operator>(const Time &dat) const;
		bool operator<=(const Time &dat) const;
		bool operator>=(const Time &dat) const;

//		FRIEND
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Time &dat);

	private:
		int _YYYY, _M, _D;
		int _h, _m, _s;
		static Time *_today;

};

#endif
