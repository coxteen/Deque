#include <iostream>
#include "Deque.h"

int main() {

	Deque<int> dq;

	bool isRunning = true;
	while (isRunning) {

		std::cout << "\n\n\n";
		std::cout << "  |-------------------------------------------|\n";
		std::cout << "  |                                           |\n";
		std::cout << "  |                    Deque                  |\n";
		std::cout << "  |                                           |\n";
		std::cout << "  |   1. push_back                            |\n";
		std::cout << "  |   2. push_front                           |\n";
		std::cout << "  |   3. pop_back                             |\n";
		std::cout << "  |   4. pop_front                            |\n";
		std::cout << "  |   5. front()                              |\n";
		std::cout << "  |   6. back()                               |\n";
		std::cout << "  |   7. empty()                              |\n";
		std::cout << "  |   8. clear()                              |\n";
		std::cout << "  |   9. size()                               |\n";
		std::cout << "  |   10. acces prin pozitie                  |\n";
		std::cout << "  |   11. insert                              |\n";
		std::cout << "  |   12. erase                               |\n";
		std::cout << "  |   13. print                               |\n";
		std::cout << "  |   0. EXIT                                 |\n";
		std::cout << "  |                                           |\n";
		std::cout << "  |-------------------------------------------|\n";

		int input;
		std::cout << "\n  Alegeti o optiune : ";
		std::cin >> input;

		int insertValue, index;

		switch (input)
		{
		case 1:
			std::cout << "\n  Alegeti valoarea pe care doriti sa o adaugati la sfarsit : ";
			std::cin >> insertValue;
			dq.push_back(insertValue);
			break;
		case 2:
			std::cout << "\n  Alegeti valoarea pe care doriti sa o adaugati la inceput : ";
			std::cin >> insertValue;
			dq.push_front(insertValue);
			break;
		case 3:
			if (dq.empty()) 
				std::cout << "\n Structura nu are elemente!\n";
			else {
				std::cout << "\n  Valoarea " << dq.back() << " a fost stearsa (valoarea de la sfarsit).";
				dq.pop_back();
			}
			break;
		case 4:
			if(dq.empty()) 
				std::cout << "\n Structura nu are elemente!\n";
			else {
				std::cout << "\n  Valoarea " << dq.front() << " a fost stearsa (valoarea de la inceput).";
				dq.pop_front();
			}
			break;
		case 5:
			std::cout << "\n  Valoarea de la inceput este " << dq.front();
			break;
		case 6:
			std::cout << "\n  Valoarea de la sfarsit este " << dq.back();
			break;
		case 7:
			if (dq.empty())
				std::cout << "\n  Structura nu contine elemente.";
			else
				std::cout << "\n  Structura contine elemente.";
			break;
		case 8:
			if(!dq.empty())
				dq.clear();
			std::cout << "\n  Structura a fost golita.";
			break;
		case 9:
			std::cout << "\n  Dimensiunea structurii (numarul de elemente din structura) este " << dq.size();
			break;
		case 10:
			std::cout << "\n  Pozitia : ";
			std::cin >> index;
			if (index < dq.size() - 1)
				std::cout << "\n  La pozitia : " << index << " se afla elementul " << dq[index];
			else
				std::cout << "\n  Index-ul depaseste dimensiunea structurii.";
			break;
		case 11:
			std::cout << "\n  Valoarea pe care doriti sa o introduceti : ";
			std::cin >> insertValue;
			std::cout << "\n  Pozitia unde doriti sa introduceti elementul : ";
			std::cin >> index;
			if (index > dq.size())
				std::cout << "\n  Locatia este invalida!";
			else {
				dq.insert(insertValue, index);
			}
			break;
		case 12:
			std::cout << "\n  Pozitia de unde doriti sa stergeti elementul : ";
			std::cin >> index;
			if (index > dq.size())
				std::cout << "\n  Locatia este invalida!";
			else {
				dq.erase(index);
			}
			break;
		case 13:
			dq.print();
			break;
		case 0:
			isRunning = false;
			break;

		default:
			break;
		}
	}

	return 0;
}