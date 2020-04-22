#include <iostream>
#include "Calendar.hpp"

int main()
{
	Calendar cal("Test.txt");
	cal.book();
	cal.book();
	cal.holiday();
	cal.book();
	cal.busyDays();

	cal.print();
}