#pragma once
#include <iostream>
#include <string>
#include "Validations.hpp"

static const size_t DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:

	size_t m_year;
	size_t m_month;
	size_t m_day;

public:

	Date();
	Date(size_t year, size_t month, size_t day);
	Date& operator=(const Date& other);

	bool isLeapYear();
	size_t getYear() const;
	size_t getMonth() const;
	size_t getDay() const;
	void nextDay();

	bool operator==(const Date& other);
	bool operator>=(const Date& other);
	bool operator<=(const Date& other);

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);

};
