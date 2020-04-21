#pragma once

class Date
{
private:
	
	static const size_t EARLIEST_YEAR = 2020;

	size_t m_year;
	size_t m_month;
	size_t m_day;

public:

	Date();
	Date(size_t year, size_t month, size_t day);

	size_t getYear() const;
	size_t getMonth() const;
	size_t getDay() const;
	bool operator==(const Date& other);

};

