#include "polinom.h"
#include <iostream>
#include <string>

using namespace std;

char menu()
{
	char choice;
	cout<<"Choose a operation"<<endl;
	cout<<"1. p1 + p2"<<endl;
	cout<<"2. p1 - p2"<<endl; 
	cout<<"3. p1*p2"<<endl;
	cout<<"4. c*p1"<<endl;
	cout<<"5. Exit"<<endl;

	cout << "Your choice: ";
	cin >> choice;
	return choice;
}

int main()          
{
	string s1,s2;
	TPolinome p1, p2;
	double c;
	char number;

	do
	{
		number = menu();
		switch(number)
		{
		case '1':
			{
				cout << "Enter polinom p1: ";
				cin >> s1;
				p1 = s1;
				cout << "Enter polinom p2: ";
				cin >> s2;
				p2 = s2;
				cout << "Result of operation: " << p1 + p2 << endl << endl;
				break;
			}
		case '2':
			{
				cout << "Enter polinom p1: ";
				cin >> s1;
				p1 = s1;
				cout << "Enter polinom p2: ";
				cin >> s2;
				p2 = s2;
				cout << "Result of operation: " << p1 - p2 << endl << endl;
				break;
			}
		case '3':
			{
				cout << "Enter polinom p1: ";
				cin >> s1;
				p1 = s1;
				cout << "Enter polinom p2: ";
				cin >> s2;
				p2 = s2;
				cout << "Result of operation: " << p1 * p2 << endl << endl;
				break;
			}
		case '4':
			{
				cout << "Enter polinom p1: ";
				cin >> s1;
				p1 = s1;
				cout << "Enter const c: ";
				cin >> c;
				cout << "Result of operation: " << p1*c << endl << endl;
				break;
			}
		case '5':
			{
				break;
			}
		}
	}
	while (number != '5');
	return 0;
}