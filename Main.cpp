#include <iostream>
#include "Calendar.hpp"

int main()
{
	Calendar cal(TEST_FILE);
	cal.book();
	cal.book();

	cal.print();
}