//###################################################################################################
//	
//	FILE NAME :			timestruct.hpp
//	
//	FILE TYPE :			C++ file
//	
//	AUTHORS :			Mariacristina Romano, Gianmaria Enea Roat
//	
//	DESCRIPTION : 		Declaration of class Timestruct
//	
//	FIRST VERSION :		2010/feb/9
//	
//	LAST UPTIME : 		2010/feb/15
//	
//	STATUS :			final
//	
//	COPYRIGHT :			none
//	
//	
//	DETAILED DESCRIPTION :	Questa classe gestisce vettori di intervalli temporali Deltatime, per cui contiene un membro che rappresenta la lunghezza di tali vettori.
//					Rappresenta una struttura temporale, permette una migliore e piú sicura gestione dei vettori di intervalli di tempi che verranno 
//					ampliamente usati all’interno della libreria. 
//					Abbiamo implementato un costruttore che permetta di creare un oggetto Timestruct composto da intervalli di eguale durata passando
//					semplicemente un Deltatime e la lughezza del vettore.
//					Un altro costruttore permette di passare istanti temporali: gli intervalli cengono ricavati dalla differenza di tali date e , più
//					precisamente, il primo intervallo corrisponde alla differenza tra il primo istante passato alla funzione e "today".
//	
//	
//	
//	
//	
//#######################################################################################################

#ifndef _TIMESTRUCT_HPP
#define _TIMESTRUCT_HPP

#include "time.hpp"
#include "deltatime.hpp"

#include <iostream>
#include <string>

using namespace std;
//! Classe che rappresenta un vettore di intervalli temporali.
/*! Classe di livello 2. \n
Questa classe gestisce vettori di intervalli temporali Deltatime, per cui contiene un membro che rappresenta la lunghezza di tali vettori. \n
Rappresenta una struttura temporale, permette una migliore e piú sicura gestione dei vettori di intervalli di tempi che verranno ampliamente usati all’interno della libreria. \n
Abbiamo implementato un costruttore che permetta di creare un oggetto Timestruct composto da intervalli di eguale durata passando semplicemente un Deltatime e la lughezza del vettore. \n
Un altro costruttore permette di passare istanti temporali: gli intervalli cengono ricavati dalla differenza di tali date e , più precisamente, il primo intervallo corrisponde alla differenza tra il primo istante passato alla funzione e "today".
*/
class Timestruct {
	public:
//		COSTRUTTORI~DISTRUTTORE
		Timestruct();
		Timestruct(int dim);
		Timestruct(Deltatime *delta_tempi,int dim);
		Timestruct(Deltatime **delta_tempi,int dim);
		Timestruct(const Deltatime &delta,int dim);
		Timestruct(Time *tempi,int dim);
		Timestruct(const Timestruct &copy);
		~Timestruct();

//		FUNZIONI GET
		const Deltatime &Get_deltatime(int i);
		int Get_dim() const;

//		FUNZIONI SET
		void Set_deltatime(const Deltatime &delta, int i);

//		OPERATORE ASSEGNAMENTO
		const Timestruct &operator=(const Timestruct &copy);

//		OPERATORI LOGICI
		bool operator==(const Timestruct &dat) const;
		bool operator!=(const Timestruct &dat) const;

//		OVERLOAD DEL COUT
//! overloading dell'operatore "<<"
		friend ostream &operator<<(ostream &os, const Timestruct &dat);

	private:
		Deltatime *_delta_tempi;
		int _dim;

};

#endif
