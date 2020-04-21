#include "Date.hpp"

Date::Date() : 
	m_year(0),
	m_month(0),
	m_day(0)
{
}

Date::Date(size_t year, size_t month, size_t day) :
	m_year(year),
	m_month(month),
	m_day(day)
{
}

size_t Date::getYear() const
{
	return m_year;
}

size_t Date::getMonth() const
{
	return m_month;
}

size_t Date::getDay() const
{
	return m_day;
}

bool Date::operator==(const Date& other)
{
	if (m_year == other.m_year && m_month == other.m_month && m_day == other.m_day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

