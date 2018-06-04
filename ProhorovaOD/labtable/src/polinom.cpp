#include "polinom.h"

using namespace std;
 
TMonom::TMonom(double c, unsigned int a)
{
	cf = c;
	abc = a;
};

TMonom& TMonom::operator =(const TMonom& m)
{
	cf = m.cf;
	abc = m.abc;
	return *this;
};

bool TMonom::operator <(const TMonom& m) const		 
{
	if (abc >= m.abc) return false;
	return true;
};

bool TMonom::operator >(const TMonom& m) const
{
	if (abc <= m.abc) return false;
	return true;
};

bool TMonom::operator ==(const TMonom& m) const
{
	if ((abc != m.abc)||(cf != m.cf)) return false;
	return true;
};

bool TMonom::operator !=(const TMonom& m) const
{
	return !(*this == m);
};

TRingList<TMonom> TPolinome::similar_terms(TRingList<TMonom> sp)
{
	TRingList<TMonom> res;
	res.Reset();
	sp.Reset();
	TLink<TMonom> mon(sp.GetCurr()->data.cf);
	while (sp.IsNotEnded())
	{
		mon.data.abc = sp.GetCurr()->data.abc;
		if (sp.GetCurr()->data.abc == sp.GetCurr()->next->data.abc &&(sp.GetCurr()->next->data.cf || sp.GetCurr()->next->data.abc))
			mon.data.cf += sp.GetCurr()->next->data.cf;
		else
		{
			if (mon.data.cf)
			{
				res.InsertTail(mon.data);
				res.GetNext();
			}
			mon.data.cf = sp.GetCurr()->next->data.cf;
		}
		sp.GetNext();
	} 	
	return res;
};

TPolinome::TPolinome(string str) 
{
	TRingList<TMonom> res;
	while (str.length())
	{
		string part;
		TMonom temp;
		int pos = 1; 
		while ((pos < str.length())&&(str[pos] != '+')&&(str[pos] != '-')) pos++;
		part = str.substr(0, pos);              
		str.erase(0, pos);                      
		pos = 0;
		while ((part[pos] != 'x')&&(part[pos] != 'y')&&(part[pos] != 'z')&&(pos < part.length())) pos++;
		string c = part.substr(0,pos);         
		if ((c == "+")||(c.length() == 0)) temp.cf = 1;
		else 
			if (c == "-") temp.cf = -1;
		else
			temp.cf = stod(c);                
		part.erase(0, pos);                       
		part += ' ';
		int a[3] = {100,10,1};
		for (int i = 0; i < 3; i++)
		{
			pos = part.find((char)(120 + i));   
			if (pos > -1)
			{
				if (part[pos + 1] != '^') part.insert(pos + 1, "^1");
				temp.abc += a[i] * stoi(part.substr(pos + 2, 1));      
				part.erase(pos, 3);
			}
		}
		monoms.Insert(temp);
	} 
	monoms = similar_terms(monoms);
};

TPolinome::TPolinome(const TPolinome &polinome)
{
	monoms = polinome.monoms;
};

TPolinome TPolinome::operator +(const TPolinome &polinome) const 
{
	TPolinome res;
	TPolinome pthis = *this;
	TPolinome p = polinome;

	pthis.monoms.Reset();
	p.monoms.Reset();
	res.monoms.Reset();

	while ((pthis.monoms.IsNotEnded()) && (p.monoms.IsNotEnded()))
	{
		if (pthis.monoms.GetCurr()->data > p.monoms.GetCurr()->data)
		{
			res.monoms.InsertTail(p.monoms.GetCurr()->data);            
			p.monoms.GetNext();
			res.monoms.GetNext();
		}
		else 
			if (pthis.monoms.GetCurr()->data < p.monoms.GetCurr()->data)
			{
				res.monoms.InsertTail(pthis.monoms.GetCurr()->data);
				pthis.monoms.GetNext();
				res.monoms.GetNext();
			}
			else
			{
				double newcf = pthis.monoms.GetCurr()->data.cf + p.monoms.GetCurr()->data.cf;
				if (newcf)
				{
					TMonom temp(newcf, pthis.monoms.GetCurr()->data.abc);
					res.monoms.InsertTail(temp);
					res.monoms.GetNext();
				}
				pthis.monoms.GetNext();
				p.monoms.GetNext();
			}
	}
	while (pthis.monoms.IsNotEnded())
	{
		res.monoms.InsertTail(pthis.monoms.GetCurr()->data);
		pthis.monoms.GetNext();
		res.monoms.GetNext();
	}
	while (p.monoms.IsNotEnded())
	{
		res.monoms.InsertTail(p.monoms.GetCurr()->data);
		p.monoms.GetNext();
		res.monoms.GetNext();
	}
	return res;
};

TPolinome TPolinome::operator *(const TPolinome &polinome) const 
{
	TPolinome res;
	TPolinome pthis = *this;
	TPolinome p =polinome;

	pthis.monoms.Reset();
	p.monoms.Reset();

	while (pthis.monoms.IsNotEnded())
	{
		double pthiscf = pthis.monoms.GetCurr()->data.cf;
		int pthisabc = pthis.monoms.GetCurr()->data.abc;
		TPolinome temp(polinome);
		temp.monoms.Reset();
		while (temp.monoms.IsNotEnded())
		{
			int tempabc = temp.monoms.GetCurr()->data.abc;
			if ((tempabc % 10 + pthisabc % 10) < 10 && (tempabc/10 % 10 + pthisabc/10 % 10) < 10 && (tempabc/100 + pthisabc/100) < 10)
			{
				temp.monoms.GetCurr()->data.abc += pthisabc;
				temp.monoms.GetCurr()->data.cf *= pthiscf;
			}
			else 
				throw "large index";
			temp.monoms.GetNext();
		}
		res = res + temp;
		pthis.monoms.GetNext();
	}
	return res;
};

TPolinome TPolinome::operator *(const double &d) const
{
	TPolinome res;
	if (d)
	{
		res = *this;
		res.monoms.Reset();
		while (res.monoms.IsNotEnded())
		{
			res.monoms.GetCurr()->data.cf *= d;
			res.monoms.GetNext();
		}
	}
	return res;
};

TPolinome TPolinome::operator -() const
{
	return (*this)*(-1.0);
};                                                                                                       

TPolinome& TPolinome::operator =(const TPolinome &polinome)
{
	monoms = polinome.monoms;
	return *this;
};

TPolinome TPolinome::operator -(const TPolinome& polinome) const
{
	return *this+polinome*(-1.0);
};
		
bool TPolinome::operator==(const TPolinome& polinome) const
{
	return (monoms == polinome.monoms);
};	
		
bool TPolinome::operator!=(const TPolinome& polinome) const
{
	return !(*this == polinome);
}; 

ostream& operator<<(ostream &out, const TPolinome &polinome)
{
	TPolinome p = polinome;
	p.monoms.Reset();

	while (p.monoms.IsNotEnded())
	{
		TMonom temp = p.monoms.GetCurr()->data;

		if (temp.cf > 0)
		{
			out << "+";
			if ((temp.cf == 1)&&(temp.abc != 0))
				out << "1";
			else 
				out << temp.cf;
		}
		else
			out << temp.cf;
		
		int a = temp.abc / 100;
		if (a>1)
			out << "x^" << a;
		else 
			if (a == 1) 
				out << "x";
		a = temp.abc / 10 % 10;
		if (a>1)
			out << "y^" << a;
		else 
			if (a == 1) 
				out << "y";
		a = temp.abc % 10;
		if (a>1)
			out<< "z^" << a;
		else
			if (a == 1) 
				out << "z";
		p.monoms.GetNext();  
	}
	return out;
};