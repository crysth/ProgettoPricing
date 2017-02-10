//###################################################################################################
//	
//	FILE NAME :			vol_std.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Vol_std
//	
//	FIRST VERSION :		2010/feb/3
//	
//	LAST UPTIME : 		2010/feb/20
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	FROM CLASS :		Volatility
//	
//	
//	DETAILED DESCRIPTION :	Rappresenta una curva di volatilità piatta, ovvero costante nel tempo. Per questo motivo è sufficiente un double per impostare la curva.
//
//
//
//	
//	
//	
//	
//	
//###################################################################################################
#ifndef _VOL_STD_HPP
#define _VOL_STD_HPP

#include "volatility.hpp"

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta una curva di volatilità costante.
/*! Classe di livello 2. \n
Rappresenta una curva di volatilità piatta, ovvero costante nel tempo. Per questo motivo è sufficiente un double per impostare la curva.
*/
class Vol_std : public Volatility {
	public:
//		COSTRUTTORI~DISTRUTTORE
		Vol_std();
  		Vol_std(double v);
  		Vol_std(const Vol_std &vo);
  		~Vol_std();

//		FUNZIONI SET
     		void Set_vol(double v);

//		METODI VIRTUAL    	
    		virtual double Get_vol(const Time &t1, const Time &t2) const;

//		OVERLOAD DEL <<
//! overloading dell'operatore "<<"
		friend std::ostream &operator<<(std::ostream &os, const Vol_std &dat);

//		OPERATORE ASSEGNAMENTO
		virtual Vol_std &operator=(Vol_std &obj);

    	
	private:
		double _vola;
};


#endif
