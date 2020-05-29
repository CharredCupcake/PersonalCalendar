#include "Validations.hpp"

void Validations::ValidateDateFormat(const std::string& dateStr)
{
	size_t firstDot = dateStr.find('.');
	size_t secondDot = dateStr.rfind('.');
	if (firstDot == std::string::npos)
	{
		throw "Invalid date format";
	}
	if (secondDot == firstDot + 1)
	{
		throw "Invalid date format";
	}
	if (firstDot == 0)
	{
		throw "Invalid date format";
	}
	if (secondDot == dateStr.length() - 1)
	{
		throw "Invalid date format";
	}
	if (firstDot == secondDot)
	{
		throw "Invalid date format";
	}
	if (dateStr.find('.', firstDot + 1) != secondDot)
	{
		throw "Invalid date format";
	}
}

void Validations::ValidateDate(const std::string& yearStr, const std::string& monthStr, const std::string& dayStr)
{
	if (yearStr.find_first_not_of("0123456789") != std::string::npos)
	{
		throw "Invalid Year.";
	}
	if (monthStr.find_first_not_of("0123456789") != std::string::npos)
	{
		throw "Invalid Month.";
	}
	if (dayStr.find_first_not_of("0123456789") != std::string::npos)
	{
		throw "Invalid Day.";
	}
	size_t year = std::stoul(yearStr), month = std::stoul(monthStr), day = std::stoul(dayStr);
	if (month < 1 || month > 12)
	{
		throw "Invalid Month.";
	}
	if (Date(year, month, day).isLeapYear())
	{
		if (month == 2)
		{
			if (DAYS_IN_MONTH[1] + 1 < day)
			{
				throw "Invalid Day.";
			}
			else
			{
				return;
			}
		}
		else
		{
			if (DAYS_IN_MONTH[month - 1] < day)
			{
				throw "Invalid Day.";
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		if (DAYS_IN_MONTH[month - 1] < day)
		{
			throw "Invalid Day.";
		}
		else
		{
			return;
		}
	}
}

void Validations::ValidateTimeFormat(const std::string& timeStr)
{
	size_t colum = timeStr.find(':');
	size_t otherColum = timeStr.rfind(':');
	if (colum == std::string::npos)
	{
		throw "Invalid time format";
	}
	if (otherColum != colum)
	{
		throw "Invalid time format";
	}
	if (colum == 0)
	{
		throw "Invalid time format";
	}
	if (colum == timeStr.length() - 1)
	{
		throw "Invalid time format";
	}
}

void Validations::ValidateTime(const std::string& hoursStr, const std::string& minutesStr)
{
	if (hoursStr.find_first_not_of("0123456789") != std::string::npos)
	{
		throw "Invalid Hours";
	}
	if (minutesStr.find_first_not_of("0123456789") != std::string::npos)
	{
		throw "Invalid Minutes";
	}
	size_t hours = std::stoul(hoursStr), minutes = std::stoul(minutesStr);
	if (hours > 24)
	{
		throw "Invalid Hours";
	}
	if (minutes > 59)
	{
		throw "Invalid Minutes";
	}
}

void Validations::ValidateFileName(std::string& fileName)
{
	size_t dotPos = fileName.find('.');
	try
	{
		if (dotPos == std::string::npos)
		{
			throw "Missing extension.";
		}
	}
	catch (const char* message)
	{
		fileName += ".txt";
		return;
	}
	try
	{
		if (fileName.find('txt', dotPos + 1) != dotPos + 1)
		{
			throw "Wrong extension.";
		}
	}
	catch (const char* message)
	{
		fileName.resize(dotPos);
		fileName += ".txt";
	}
}