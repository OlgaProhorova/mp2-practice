#pragma once
#include <string>
#include <iostream>
#define Cf 2

using namespace std;

template <typename type>
class TabRecord
{
	public:
		string name;
		type data;
		TabRecord() 
		{ 
			name = "emp";
		};
		TabRecord(const TabRecord& tr) 
		{ 
			name = tr.name; 
			data = tr.data; 
		};
		TabRecord& operator=(const TabRecord& tr) 
		{ 
			name = tr.name; 
			data = tr.data; 
		};
		TabRecord(const string& KEY, const type& DATA) 
		{ 
			name = KEY; 
			data = DATA; 
		};
};

template <typename type>
class Table
{
	protected:
		TabRecord<type>** Records;
		int Max;
		int CurrSize;
		int CurrIndex;
	public:
		Table(int i = 10)
		{
			Max = i;
			CurrSize = 0;
			CurrIndex = -1;
			Records = new TabRecord<type>*[Max];
		};
		Table(const Table<type>& Tab);
		virtual ~Table() 
		{ 
			delete[] Records; 
		};
		virtual void Realloc();
		virtual void Reset()
		{
			if (CurrSize) CurrIndex = 0;
			else CurrIndex = -1;
		};

		virtual int IsEnded() const 
		{ 
			return CurrIndex == -1 || ((CurrIndex + 1) == CurrSize); 
		};
		virtual type& GetCurr() const
		{
			if (CurrSize) return Records[CurrIndex]->data;
			else throw "Empty";
		};
		virtual void SetNext()
		{
			if (CurrSize) CurrIndex++;
			else throw "Empty";
			if (CurrIndex == CurrSize) Reset();
		};

		virtual type& Search(const string& KEY) const = 0;
		virtual void Insert(const string& KEY, const type& DATA) = 0;
		virtual void Delete(const string& KEY) = 0;

		template<class type> friend ostream& operator<< (std::ostream& os, const Table<type>& Tab);
};

template<typename type>
Table<type>::Table(const Table<type>& Tab)
{
	Max = Tab.Max;
	CurrSize = Tab.CurrSize;
	CurrIndex = Tab.CurrIndex;
	Records = new TabRecord<type>*[Max];
	for (int i = 0; i < CurrSize; i++)
		Records[i] = Tab.Records[i];
}

template<typename type>
void Table<type>::Realloc()
{
	int NewMax = Max * Cf;
	TabRecord<type>** temp = new TabRecord<type>*[NewMax];
	Reset();
	for (int i = 0; i < CurrSize; i++)
		temp[i] = Records[i];
	delete[] Records;
	Records = temp;
	Max = NewMax;
};

template <typename type>
ostream& operator<< (ostream& os, const Table<type>& Tab)
{
	if (Tab.CurrSize)
		for (int i = 0; i < Tab.CurrSize; i++)
			os << i << " | " << Tab.Records[i]->name << " | " << Tab.Records[i]->data << endl;
	else
		os << "Empty" << endl;
	return os;
}