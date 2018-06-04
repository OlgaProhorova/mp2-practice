#include "polinom.h"
#include <conio.h>
#include "scan.h"
#include "sorted.h"
#include "hash.h"

void main()
{
	cout << "Input correct polinoms" << endl;
	cout << "You can insert/delete and find in tables" << endl;
	char c = 0, str;
	ScanTable<TPolinome> Tab1;
	SortedTable<TPolinome> Tab2;
	HashTable<TPolinome> Tab3;
	string key;
	TPolinome P;

	while (!c || (c == ' '))
	{
		cout << "ScanTable: " << endl << Tab1 << endl;
		cout << "-------------------------" << endl;
		cout << "SortedTable:" << endl << Tab2 << endl;
		cout << "-------------------------" << endl;
		cout << "HashTable:" << endl << Tab3 << endl << endl;
		cout << "-------------------------" << endl;
		cout << "1. Insert   2. Delete   3. Search" << endl;
		cin >> str;
		switch (str)
		{
			case '1':
			{
				cout << "Enter polinom:" << endl;
				getline(cin, key);
				if (key == "")
					getline(cin, key);
				P = TPolinome(key);
				Tab1.Insert(key, P);
				Tab2.Insert(key, P);
				Tab3.Insert(key, P);
				cout << "ScanTable: " << endl << Tab1 << endl;
				cout << "-------------------------" << endl;
				cout << "SortedTable:" << endl << Tab2 << endl;
				cout << "-------------------------" << endl;
				cout << "HashTable:" << endl << Tab3 << endl << endl;
				cout << "-------------------------" << endl;
				break;
			}
			case '2':
			{
				cout << "Enter polinom:" << endl;
				getline(cin, key);
				if (key == "")
					getline(cin, key);
				Tab1.Delete(key);
				Tab2.Delete(key);
				Tab3.Delete(key);
				cout << "ScanTable: " << endl << Tab1 << endl;
				cout << "-------------------------" << endl;
				cout << "SortedTable:" << endl << Tab2 << endl;
				cout << "-------------------------" << endl;
				cout << "HashTable:" << endl << Tab3 << endl << endl;
				cout << "-------------------------" << endl;
				break;
			}
			case '3':
			{
				cout << "Enter polinom:" << endl;
				getline(cin, key);
				if (key == "")
					getline(cin, key);
				Tab1.Search(key);
				Tab2.Search(key);
				Tab3.Search(key);
				cout << "ScanTable: " << endl << Tab1 << endl;
				cout << "-------------------------" << endl;
				cout << "Search in ScanTable: " << Tab1.Search(key) << endl;
				cout << "-------------------------" << endl;
				cout << "SortedTable:" << endl << Tab2 << endl;
				cout << "-------------------------" << endl;
				cout << "Search in SortedTable: " << Tab2.Search(key) << endl;
				cout << "-------------------------" << endl;
				cout << "HashTable:" << endl << Tab3 << endl << endl;
				cout << "-------------------------" << endl;
				cout << "Search in HashTable: " << Tab3.Search(key) << endl;
				cout << "-------------------------" << endl;
				break;
			}
			default:
				cout << "try again" << endl;
		}
		cout << "Press SPACE to retry" << endl;
		cout << "Press any key to exit" << endl;

		c = _getch();
	}
}