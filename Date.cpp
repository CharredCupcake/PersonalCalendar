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

Date& Date::operator=(const Date& other)
{
	m_year = other.m_year;
	m_month = other.m_month;
	m_day = other.m_day;
	return *this;
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
	if (m_year > other.m_year)
	{
		return true;
	}
	else
	{
		if (m_year == other.m_year)
		{
			if (m_month > other.m_month)
			{
				return true;
			}
			else
			{
				if (m_month == other.m_month)
				{
					if (m_day >= other.m_day)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
}

bool Date::operator<=(const Date& other)
{
	if (m_year < other.m_year)
	{
		return true;
	}
	else
	{
		if (m_year == other.m_year)
		{
			if (m_month < other.m_month)
			{
				return true;
			}
			else
			{
				if (m_month == other.m_month)
				{
					if (m_day <= other.m_day)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.m_year << '.';
	if (date.m_month < 10)
	{
		out << '0' << date.m_month << '.';
	}
	else
	{
		out << date.m_month << '.';
	}
	if (date.m_day < 10)
	{
		out << '0' <<date.m_day << '\n';
	}
	else
	{
		out << date.m_day << '\n';
	}
	return out;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	std::string dateStr;
	std::string yearStr;
	std::string monthStr;
	std::string dayStr;
	in >> dateStr;
	try
	{
		try
		{
			Validations::ValidateDateFormat(dateStr);
		}
		catch (const char* message)
		{
			std::cerr << message << std::endl;
			return in;
		}
		size_t firstDot = dateStr.find('.');
		size_t secondDot = dateStr.rfind('.');
		yearStr = dateStr.substr(0, firstDot);
		monthStr = dateStr.substr(firstDot + 1, secondDot - firstDot - 1);
		dayStr = dateStr.substr(secondDot + 1);

		Validations::ValidateDate(yearStr, monthStr, dayStr);
	}
	catch (const char* message)
	{
		std::cerr << message << std::endl;
		return in;
	}
	date = Date(std::stoul(yearStr), std::stoul(monthStr), std::stoul(dayStr));
	return in;
}
