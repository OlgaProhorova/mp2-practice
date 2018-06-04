#pragma once
#include "table.h"

template<typename type>
class SortedTable : public Table<type>
{
	public:
		SortedTable(int i = 10) : Table(i) {};
		SortedTable(const SortedTable<type>& Tab) : Table(Tab) {};
		~SortedTable() { };

		int BinarySearch(const string& KEY) const;
		virtual type& Search(const string& KEY) const;
		virtual void Insert(const string& KEY, const type& DATA);
		virtual void Delete(const string& KEY);
};

template<typename type>
int SortedTable<type>::BinarySearch(const string& KEY) const
{
	int i = 0, j = CurrSize - 1;
	int mid;
	while (i <= j)
	{
		mid = (i + j) / 2;
		if (KEY > Records[mid]->name)
			i = mid + 1;
		else
			j = mid - 1;
	}
	return i;
}

template<typename type>
type& SortedTable<type>::Search(const string& KEY) const
{
	SortedTable<type> Temp(*this);
	Temp.Reset();
	if (CurrIndex > -1)
	{
		int k = Temp.BinarySearch(KEY);
		if (Temp.Records[k]->name == KEY)
			return Temp.Records[k]->data;
		else
			throw "Key isn't exist";
	}
	else
		throw "Empty";
}

template<typename type>
void SortedTable<type>::Insert(const string& KEY, const type& DATA)
{
	if (CurrSize == Max) Realloc();
	Reset();
	if (CurrSize)
	{
		int k = BinarySearch(KEY);
		if (k != CurrSize)
		{
			if (Records[k]->name != KEY)
			{
				for (int i = CurrSize; i > k; i--)
					Records[i] = Records[i - 1];
				Records[k] = new TabRecord<type>(KEY, DATA);
				CurrSize++;
			}
			else
				throw "Key already exists";
		}
		else
		{
			Records[k] = new TabRecord<type>(KEY, DATA);
			CurrSize++;
		}
	}
	else
	{
		CurrIndex++;
		Records[CurrIndex] = new TabRecord<type>(KEY, DATA);
		CurrSize++;
	}
}

template<typename type>
void SortedTable<type>::Delete(const string& KEY)
{
	Reset();
	if (CurrSize)
	{
		int k = BinarySearch(KEY);
		if (Records[k]->name == KEY)
		{
				for (int i = k; i < CurrSize - 1; i++)
					Records[i] = Records[i + 1];
				CurrSize--;
		}
		else throw "Key isn't exist";
	}
	else throw "Empty";
}

