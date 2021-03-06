//	v.22.01.27

#include <iostream>
#include <fstream>

using namespace std;

int SystemSelection()
{
	int a = 3;
	cout << "(1) Windows" << endl;
	cout << "(2) GNU/Linux or MacOS" << endl;
	cout << "(3) Unknown" << endl;
	cout << "    Select operating system: ";
	if (!(cin >> a)) a = 3;
	return a;
}

void TerminalClear(int a)
{
	switch (a)
	{
	case 1:
		cout << endl;
		system("cls"); // Windows
		break;
	case 2:
		cout << endl;
		system("clear"); // Unix
		break;
	default: cout << endl << "====================================================" << endl << endl; //unknown
		break;
	}
}

long double ErlangBFormula(long double A, unsigned long long int V)
{
	if (V == 0) return 1;
	else return (A * ErlangBFormula(A, V - 1) / (V + A * ErlangBFormula(A, V - 1)));
}

int main()
{
	ofstream output;

	output.open("output.txt", ios_base::app);

	int system = 3;
	char choice = 'x';

	long double A = 0;
	long double a_min = 0.2;
	long double a_max = 1.3;
	long double a_step = 0.1;
	unsigned long long int V = 20;

	system = SystemSelection();

	while (choice != 's' && choice != 'S')
	{
		TerminalClear(system);
		cout << "====================================================" << endl;
		cout << "(0) Operating system ..................... ";
		switch (system)
			{
			case 1: cout << "Windows" << endl;
			break;
			case 2: cout << "GNU/Linux or MacOS" << endl;
			break;
			default: cout << "unknown" << endl;
			break;
		}

		cout << "(1) System capacity: ..................... " << V << endl;
		cout << "(2) Minimum traffic offered: ............. " << a_min << endl;
		cout << "(3) Maximum traffic offered: ............. " << a_max << endl;
		cout << "(4) Calculation step: .................... " << a_step << endl;
		cout << endl;

		cout << "Choose number to edit, (S)tart or (E)xit ";

		cin >> choice;

		if (choice == 'e' || choice == 'E')
		{
			TerminalClear(system);
			cout << "Program ended...";
			exit(0);
		}

		if (choice != 's' && choice != 'S')
		{
			TerminalClear(0);
			switch (choice)
			{
			case '0':
				system = SystemSelection();
				break;
			case '1':
				cout << "System capacity: ";
				cin >> V;
				break;
			case '2':
				cout << "Minimum traffic offered: ";
				cin >> a_min;
				break;
			case '3':
				cout << "Maximum traffic offered: ";
				cin >> a_max;
				break;
			case '4':
				cout << "Calculation step: ";
				cin >> a_step;
				break;
			}
		}
	}

	double onePercent = ((a_max)-a_step) / 100;
	double detect = 0;
	float loadingStatus = 0;
	float lastLoadingStatus = -1;
	long double erlTemp = 0;
	double oneComplPerc = 100 / ( (a_max - a_min) / a_step );

	cout << endl << "Start of the calculation..." << endl;

	for (long double i = a_min; i <= a_max; i += a_step)
	{
		A = i * V;
		erlTemp = ErlangBFormula(A, V);
		
		if (static_cast<int>(loadingStatus) != lastLoadingStatus)
		{
			cout << static_cast<int>(loadingStatus) << "%" << endl;
			lastLoadingStatus = static_cast<int>(loadingStatus);
			loadingStatus += oneComplPerc;
		}
		output << i << "\t" << ErlangBFormula(A, V) << endl;
	}

	output.close();

	cout << endl << "...opus magnum, its done. Program ended...";
}
