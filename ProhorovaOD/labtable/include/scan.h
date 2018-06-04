#pragma once
#include "table.h"

template<typename type>
class ScanTable :public Table<type>
{
	public:
		ScanTable(int i = 10) : Table(i) {};
		ScanTable(const ScanTable<type>& Tab) : Table(Tab) {};
		~ScanTable() {};
	
		virtual type& Search(const string& KEY) const;
		virtual void Insert(const string& KEY, const type& DATA);
		virtual void Delete(const string& KEY);
};

template<typename type>
type& ScanTable<type>::Search(const string& KEY) const
{	
	ScanTable<type> Temp(*this);
	Temp.Reset();
	if (Temp.CurrIndex > -1)
	{
		while ((Temp.CurrIndex > -1) && (Temp.Records[Temp.CurrIndex]->name != KEY) && (Temp.CurrIndex < Temp.CurrSize))
			Temp.SetNext();
		if (Temp.CurrIndex < Temp.CurrSize)
			return Temp.Records[Temp.CurrIndex]->data;
		else
			throw "key isn't exist";
	}
	else throw "Empty";
}

template<typename type>
void ScanTable<type>::Insert(const string& KEY, const type& DATA)
{
	if (CurrSize == Max)
		Realloc();
	Reset();
	if (CurrSize)
	{
		while ((CurrIndex < CurrSize) && (Records[CurrIndex]->name != KEY))
			CurrIndex++;
		if (CurrIndex == CurrSize)
		{
			Records[CurrIndex] = new TabRecord<type>(KEY, DATA);
			CurrSize++;
		}
		else throw "Key already exists";
	}
	else
	{
		CurrIndex++;
		Records[CurrIndex] = new TabRecord<type>(KEY, DATA);
		CurrSize++;
	}
}

template<typename type>
void ScanTable<type>::Delete(const string& KEY)
{
	Reset();
	while ((CurrIndex > -1) && (Records[CurrIndex]->name != KEY) && (CurrIndex < CurrSize))
		CurrIndex++;
	if (CurrSize && (CurrIndex < CurrSize))
	{
		if (CurrSize > 1)
			Records[CurrIndex] = Records[--CurrSize];
		else
			CurrSize = 0;
	}
	else
		throw "Key isn't exist";
}