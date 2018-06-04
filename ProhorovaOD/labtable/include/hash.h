#pragma once
#include "table.h"

template<typename type>
class HashTable :public Table<type>
{
	protected:
		int* H;
		int Hash(const string& KEY) const;
		virtual void Realloc();
	public:
		HashTable(int i = 10);
		HashTable(const HashTable& Tab);
		~HashTable() 
		{ 
			delete[] H; 
		};
	
		virtual void Reset();
		virtual type& GetCurr() const;
		virtual void SetNext();

		virtual type& Search(const string& KEY) const;
		virtual void Insert(const string& KEY, const type& DATA);
		virtual void Delete(const string& KEY);

		template<class type> friend ostream& operator<< (std::ostream& os, const HashTable<type>& Tab);
};

template<typename type>
HashTable<type>::HashTable(int i = 10) : Table(i) 
{ 
	H = new int[i]; 
	for (int j = 0; j < Max; j++) H[j] = 0;
};

template<typename type>
int HashTable<type>::Hash(const string& KEY) const
{
	int seed = 0;
	for (int i = 0; i < KEY.length(); i++)
		seed = seed + int(KEY[i]);
	return  seed % Max;
}

template<typename type>
void HashTable<type>::Realloc() 
{
	int NewMax = Max * Cf;
	TabRecord<type>** temp = new TabRecord<type>*[NewMax];
	int* tempH = new int[NewMax];
	int i = 0;
	for (i; i < Max; i++)
	{
		temp[i] = Records[i];
		tempH[i] = H[i];
	}
	delete [] Records;
	delete [] H;
	Records = temp;
	H = tempH;
	Max = NewMax;
}

template<typename type>
HashTable<type>::HashTable(const HashTable& Tab)
{
	Max = Tab.Max;
	CurrSize = Tab.CurrSize;
	CurrIndex = Tab.CurrIndex;
	Records = new TabRecord<type>*[Max];
	H = new int[Max];
	for (int i = 0; i < Max; i++)
	{
		H[i] = Tab.H[i];
		Records[i] = Tab.Records[i];
	}
}

template<typename type>
void HashTable<type>::Reset()
{
	if (CurrSize)
	{
		CurrIndex = 0;
		while (H[CurrIndex] != 1)
			CurrIndex++;
	}
	else
		CurrIndex = -1;
}

template<typename type>
type& HashTable<type>::GetCurr() const
{
	if (CurrSize)
		return Records[CurrIndex]->data;
	else
		throw "Empty";
}

template<typename type>
void HashTable<type>::SetNext()
{
	if (CurrSize)
	{
		CurrIndex++;
		while (H[CurrIndex] != 1)
			CurrIndex = (CurrIndex + 1) % Max;
	}
	else
		throw "Empty";
}

template<typename type>
type& HashTable<type>::Search(const string& KEY) const
{
	HashTable<type> Temp(*this);
	Temp.Reset();
	if (Temp.CurrSize)
	{
		Temp.CurrIndex = Temp.Hash(KEY);
		int l = Temp.CurrIndex;
		if (Temp.Records[Temp.CurrIndex]->name == KEY)
			return Temp.Records[Temp.CurrIndex]->data;
		else
		{
			while (Temp.H[Temp.CurrIndex] && ((Temp.CurrIndex + 1) != l) && (Temp.Records[Temp.CurrIndex]->name != KEY))
				Temp.CurrIndex = (Temp.CurrIndex + 1) % Temp.Max;
			if(Temp.Records[Temp.CurrIndex]->name == KEY)
				return Temp.Records[Temp.CurrIndex]->data;
			else throw "Key isn't exist";
		}
	}
	else throw "Empty";
}

template<typename type>
void HashTable<type>::Insert(const string& KEY, const type& DATA)
{
	if (CurrSize == Max) Realloc();
	CurrIndex = Hash(KEY);
	if (!H[CurrIndex])
	{
		Records[CurrIndex] = new TabRecord<type>(KEY, DATA);
		CurrSize++;
		H[CurrIndex] = 1;
	}
	else
		if (Records[CurrIndex]->name != KEY)
		{
			int l = CurrIndex;
			while (H[CurrIndex] && ((CurrIndex + 1) != l))
				CurrIndex = (CurrIndex + 1) % Max;
			Records[CurrIndex] = new TabRecord<type>(KEY, DATA);
			CurrSize++;
			H[CurrIndex] = 1;
		}
		else throw "key already exists";
}

template<typename type>
void HashTable<type>::Delete(const string& KEY)
{
	Reset();
	if (CurrSize)
	{
		CurrIndex = Hash(KEY);
		int l = CurrIndex;
		if((!H[CurrIndex])&&(Records[CurrIndex]->name != "emp")) throw "Key isn't exist";
			if (Records[CurrIndex]->name != KEY)
			{
				while (((CurrIndex + 1) != l) && (Records[CurrIndex]->name != KEY))
					CurrIndex = (CurrIndex + 1) % Max;
				if (Records[CurrIndex]->name != KEY)
					throw "Key isn't exist";
				else
				{
					Records[CurrIndex] = new TabRecord<type>;
					H[CurrIndex] = 0;
					CurrSize--;
				}
			}
			else
			{
				Records[CurrIndex] = new TabRecord<type>;
				H[CurrIndex] = 0;
				CurrSize--;
			}
	}
	else throw "Empty";
}

template <typename type>
ostream& operator<< (ostream& os, const HashTable<type>& Tab)
{
	if (Tab.CurrSize)
	{
		for (int i = 0; i < Tab.Max; i++)
			if (Tab.H[i])
				os << i << " | " << Tab.Records[i]->name << " | " << Tab.Records[i]->data << endl;
	}
	else
		os << "Empty" << endl;
	return os;
}