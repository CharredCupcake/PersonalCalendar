#include <iostream>
#include "Calendar.hpp"

int main()
{
	Calendar cal("Test.txt");
	cal.book();
	cal.book();
	cal.book();
	cal.change();

	cal.print();
}