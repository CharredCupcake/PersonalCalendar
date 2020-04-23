#include <iostream>
#include "Calendar.hpp"

int main()
{
	Calendar cal;
	size_t option, dotPos;
	std::string fileName, otherFileName;
	do
	{
		do
		{	
			std::cout << "Choose an option." << std::endl;
			std::cout << "(1) Open." << std::endl;
			std::cout << "(2) Help." << std::endl;
			std::cout << "(3) Exit." << std::endl;
			std::cin >> option;

		} while (option < 1 || option > 3);
		switch (option)
		{
		case 1:
			cal.open(fileName);
			break;
		case 2:
			Calendar::help();
			continue;
		case 3:
			cal.exit(fileName, false);
			break;
		}
		do
		{
			std::cout << "Choose an option." << std::endl;
			std::cout << "(1) Close." << std::endl;
			std::cout << "(2) Exit." << std::endl;
			std::cout << "(3) Help." << std::endl;
			std::cout << "(4) Save." << std::endl;
			std::cout << "(5) Save as." << std::endl;
			std::cout << "(6) Book." << std::endl;
			std::cout << "(7) Unbook." << std::endl;
			std::cout << "(8) Agenda." << std::endl;
			std::cout << "(9) Change." << std::endl;
			std::cout << "(10) Find." << std::endl;
			std::cout << "(11) Holiday." << std::endl;
			std::cout << "(12) Busy days." << std::endl;
			std::cout << "(13) Find slot." << std::endl;
			std::cin >> option;
			if (option < 1 || option > 13)
			{
				continue;
			}
			switch (option)
			{
			case 1:
				cal.close(fileName);
				break;
			case 2:
				cal.exit(fileName, true);
				break;
			case 3:
				Calendar::help();
				continue;
			case 4:
				cal.save(fileName);
				break;
			case 5:
				std::cout << "Enter file name." << std::endl;
				std::cin >> otherFileName;
				dotPos = otherFileName.find('.');
				if (dotPos == std::string::npos)
				{
					otherFileName += ".txt";
				}
				else
				{
					if (otherFileName.find('txt', dotPos + 1) != dotPos + 1)
					{
						otherFileName += ".txt";
					}
				}
				cal.save(otherFileName);
				break;
			case 6:
				cal.book();
				break;
			case 7:
				cal.unbook();
				break;
			case 8:
				cal.agenda();
				break;
			case 9:
				cal.change();
				break;
			case 10:
				cal.find();
				break;
			case 11:
				cal.holiday();
				break;
			case 12:
				cal.busyDays();
				break;
			case 13:
				cal.findSlot();
				break;
			}
		} while (option != 1);

	} while (true);
}