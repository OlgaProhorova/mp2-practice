#include "list.h"
#include <string>
#include <iostream>

using namespace std;

class TMonom
{
	public:
		double cf;
		unsigned int abc;
		TMonom(double c = 0, unsigned int a = 0);                       
		TMonom& operator =(const TMonom& m);                             
		bool operator <(const TMonom& m) const;		 
		bool operator >(const TMonom& m) const;		
		bool operator ==(const TMonom& m) const;
		bool operator !=(const TMonom& m) const;
};

class TPolinome
{
	private:
		TRingList<TMonom> monoms;
	public:
		TRingList<TMonom> similar_terms(TRingList<TMonom> sp); 
		TPolinome(string str="");
		TPolinome(const TPolinome &polinome);
		TPolinome operator +(const TPolinome &polinome) const;
		TPolinome operator *(const TPolinome &polinome) const;
		TPolinome operator *(const double &d) const;
		friend TPolinome operator*(const double d,const TPolinome& polinome) 
		{ return polinome*d; };
		TPolinome& operator =(const TPolinome &polinome);
		TPolinome operator -(const TPolinome& polinome) const;
		TPolinome operator -() const;                                                           
		friend ostream& operator<<(ostream &out, const TPolinome &polinome);	                                               
		bool operator==(const TPolinome& polinome) const;	
		bool operator!=(const TPolinome& polinome) const; 
		TPolinome(TRingList<TMonom> &list) : monoms(list) {};
};