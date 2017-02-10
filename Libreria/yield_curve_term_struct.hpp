//###################################################################################################
//	
//	FILE NAME :			yield_curve_term_struct.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Yield_curve_term_struct
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
//	DETAILED DESCRIPTION :	Rappresenta una curva dei tassi complessa, costruita sull’interpolazione di dati.
//					Supponendo di essere a conoscenza del valore del tasso a certi tempi fissati si costrutisce una curva discreta. Nei metodi da noi 
//					implemntati abbiamo utilizzato una semplice interpolazione lineare per ricavare il valore del tasso a tempi diversi da quelli "conosciuti"
//					 dall'oggetto in esame. La formula utilizzata è:
//					 tax(t)=tax(t1)+ (tax(t2)-tax(t1)) * (t-t1) / (t2-t1); 
//					 dove t è il tempo a cui vogliamo trovare il tasso tax(t), t1 e t2 sono gli estremi dell'intervallo temporale a noi noto 
//					 che contiene t e tax(t1), tax(t2) sono i tassi( a noi noti) in tali istanti.
//					 Abbiamo considerato la curva come costante nel caso in cui t fosse compreso tra "today" e la prima data a nostra disposizione e 
//					 nel caso in cui t fosse superiore all'ultima data conosciuta. 
//					 Contiene un membro statico per la curva dei tassi risk-free.
//					 Il costruttore completo della classe accetta quindi il numero di punti conosciuti, un vettore di Deltatime( per le date di riferimento) 
//					 ed un vettore di double per i tassi.
//	
//###################################################################################################



#ifndef _YIELD_CURVE_TERM_STRUCT_HPP
#define _YIELD_CURVE_TERM_STRUCT_HPP

#include "yield_curve.hpp"
#include <iostream>

#include "time.hpp"
//! Classe che rappresenta una curva dei tassi complessa, costruita sull’interpolazione di dati. 
/*! Classe di livello 2. \n
Rappresenta una curva dei tassi complessa, costruita sull’interpolazione di dati. \n
Supponendo di essere a conoscenza del valore del tasso a certi tempi fissati si costrutisce una curva discreta. Nei metodi da noi implemntati abbiamo utilizzato una semplice interpolazione lineare per ricavare il valore del tasso a tempi diversi da quelli "conosciuti" dall'oggetto in esame. La formula utilizzata è: \n
tax(t)=tax(t1)+ (tax(t2)-tax(t1)) * (t-t1) / (t2-t1) \n
dove t è il tempo a cui vogliamo trovare il tasso tax(t), t1 e t2 sono gli estremi dell'intervallo temporale a noi noto che contiene t e tax(t1), tax(t2) sono i tassi( a noi noti) in tali istanti. \n
Abbiamo considerato la curva come costante nel caso in cui t fosse compreso tra "today" e la prima data a nostra disposizione e nel caso in cui t fosse superiore all'ultima data conosciuta. \n
Contiene un membro statico per la curva dei tassi risk-free. \n
Il costruttore completo della classe accetta quindi il numero di punti conosciuti, un vettore di Deltatime( per le date di riferimento) ed un vettore di double per i tassi.
*/
class Yield_curve_term_struct: public Yield_curve {

	public:
//		COSTRUTTORI~DISTRUTTORE
		Yield_curve_term_struct();
		Yield_curve_term_struct(int n, Deltatime *time, double *tax);
		Yield_curve_term_struct(int n);
		Yield_curve_term_struct(const Yield_curve_term_struct &nor);
		~Yield_curve_term_struct();

//		OPERATORE DI ASSEGNAMENTO
		virtual Yield_curve_term_struct &operator=(Yield_curve_term_struct &nor);

//		FUNZIONI
		virtual double Get_spot_rate(const Time &t) const;
		virtual double Get_spot_rate(const Deltatime &t) const;

//		FUNZIONI GET
		int Get_n() const;
		double Get_tax(int i) const;
		Deltatime Get_time(int i) const;

//		FUNZIONI SET
		void Set_n(int n);
		void Set_tax(int i, double tax);
		void Set_time(int i, const Deltatime &time);

//		OPERATORI
//! overloading dell'operatore "<<"
		friend std::ostream &operator<<(std::ostream &os, const Yield_curve_term_struct &nor);

//		FUNZIONI CURVERISKFREE
		static void Set_riskfree(Yield_curve_term_struct &y);
		static void Set_riskfree(int n, Deltatime *time, double *tax);
		static Yield_curve_term_struct* Get_riskfree();

	private:
		int _n;
		Deltatime *_time;
		double *_tax;
		static Yield_curve_term_struct *_riskfree;

};

#endif
