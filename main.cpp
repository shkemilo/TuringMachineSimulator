#include <iostream>
#include "TuringGraph.h"
#include "TuringMachine.h"
#include "TuringParser.h"

using namespace std;

int main()
{
	try
	{
		TuringParser tp; TuringGraph* tg = nullptr; vector<char>* tape = nullptr; int position = -1; bool finished = false;
		while (!finished)
		{
			system("cls");
			cout << "Turing Machine Simulator 2019, Mateja Milosevic" << endl
				<< "1. Compile program" << endl
				<< "2. Load input" << endl
				<< "3. Show program" << endl
				<< "4. Show input" << endl
				<< "5. Execute program" << endl
				<< "6. Exit" << endl << endl;

			cout << "Please enter your choice: ";
			int choice;
			cin >> choice;
			system("cls");

			switch (choice)
			{
			case 1:
			{
				string fileName;
				bool loaded = false;
				while (!loaded)
				{
					cout << "Enter program file name: ";
					cin >> fileName;

					loaded = true;
					try
					{
						tg = &tp.Compile(fileName);
					}
					catch (InvalidNameException & e)
					{
						loaded = false;
						cout << e << endl;
					}
				}
				cout << "Program successfully loaded!" << endl;
				break;
			}
			case 2:
			{
				string inputName;
				delete tape;

				bool loaded = false;
				while (!loaded)
				{
					cout << "Enter input file name: ";
					cin >> inputName;
					loaded = true;
					try
					{
						tape = &tp.GetInput(inputName);
						position = tp.GetPosition(inputName);
					}
					catch (InvalidNameException & e)
					{
						loaded = false;
						cout << e << endl;
					}
				}

				cout << "Input successfully loaded!" << endl;
				break;
			}
			case 3:
				if (tg == nullptr)
				{
					cout << "Program not loaded yet!" << endl;
					system("pause");
					continue;
				}

				cout << *tg << endl;
				break;
			case 4:
				if (tape == nullptr || position == -1)
				{
					cout << "Input not loaded yet!" << endl;
					system("pause");
					continue;
				}

				for (unsigned i = 0; i < tape->size(); i++)
					if (i == position)
						cout << '|' << (*tape)[i] << '|';
					else
						cout << ' ' << (*tape)[i] << ' ';
				cout << endl;
				break;
			case 5:
			{
				if (tg == nullptr)
				{
					cout << "Program not loaded yet" << endl;
					system("pause");
					continue;
				}
				if (tape == nullptr || position == -1)
				{
					cout << "Input not loaded yet!" << endl;
					system("pause");
					continue;
				}

				TuringMachine tm(*tg, *tape, position);
				bool succ = tm.ExecuteProgram();
				if (succ)
					cout << "Program exited with positive state!" << endl;
				else
					cout << "Program exited with negative state!" << endl;
				break;
			}
			case 6:
				delete tape;
				cout << "Goodbye!" << endl;
				finished = true;
				break;
			default:
				cout << "Invalid choice: Please enter a number from the menu!" << endl;
				break;
			}

			system("pause");
		}
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
		system("pause");
	}
	
	return 0;
}