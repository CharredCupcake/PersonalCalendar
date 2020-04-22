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

bool Date::isLeapYear()
{
	if (((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
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

void Date::nextDay()
{
	if (m_month == 12 && m_day == DAYS_IN_MONTH[11])
	{
		m_year++;
		m_month = 1;
		m_day = 1;
		return;
	}
	else
	{
		if (!isLeapYear())
		{
			if (m_day == DAYS_IN_MONTH[m_month - 1])
			{
				m_month++;
				m_day = 1;
				return;
			}
		}
		else
		{
			if (m_month == 2)
			{
				if (m_day == DAYS_IN_MONTH[1] + 1)
				{
					m_month++;
					m_day = 1;
					return;
				}
			}
			else
			{
				if (m_day == DAYS_IN_MONTH[m_month - 1])
				{
					m_month++;
					m_day = 1;
					return;
				}
			}
		}
	}
	m_day++;
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

bool Date::operator>=(const Date& other)
{
	if (m_year >= other.m_year && m_month >= other.m_month && m_day >= other.m_day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::operator<=(const Date& other)
{
	if (m_year <= other.m_year && m_month <= other.m_month && m_day <= other.m_day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.m_year << '.' << date.m_month << '.' << date.m_day;
	return out;
}
