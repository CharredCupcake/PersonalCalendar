#include "Meeting.hpp"

Meeting::Meeting() :
	m_startTime(0),
	m_endTime(0),
	m_name(),
	m_note()
{
}

Meeting::Meeting(size_t startTime, size_t endTime, std::string name, std::string note) : 
	m_startTime(startTime),
	m_endTime(endTime),
	m_name(name),
	m_note(note)
{
}

size_t Meeting::getStartTime() const
{
	return m_startTime;
}

void Meeting::setStartTime(size_t startTime)
{
	m_startTime = startTime;
}

size_t Meeting::getEndTime() const
{
	return m_endTime;
}

void Meeting::setEndTime(size_t endTime)
{
	m_endTime = endTime;
}

std::string& Meeting::getName()
{
	return m_name;
}

void Meeting::setName(std::string name)
{
	m_name = name;
}

std::string& Meeting::getNote()
{
	return m_note;
}

void Meeting::setNote(std::string note)
{
	m_note = note;
}

size_t Meeting::meetingLength()
{
	size_t length = m_endTime - m_startTime;

	if (m_endTime % 100 < m_startTime % 100)
	{
		length -= 40;
	}
	return length;
}

size_t Meeting::cinTime(const char* timeType)
{
	std::string timeStr;
	std::string hoursStr;
	std::string minutesStr;
	std::cout << "Enter " << timeType << " in format HH:MM " << std::endl;
	std::cin >> timeStr;
	try
	{
		try
		{
			Validations::ValidateTimeFormat(timeStr);
		}
		catch (const char* message)
		{
			std::cerr << message << std::endl;
			return 0;
		}
		size_t colum = timeStr.find(':');
		hoursStr = timeStr.substr(0, colum);
		minutesStr = timeStr.substr(colum + 1);
		Validations::ValidateTime(hoursStr, minutesStr);
	}
	catch (const char* message)
	{
		std::cerr << message << std::endl;
		return 0;
	}
	return std::stoul(minutesStr) + std::stoul(hoursStr) * 100;
}

bool Meeting::operator==(const Meeting& other)
{
	if (m_startTime != other.m_startTime)
	{
		return false;
	}
	if (m_endTime != other.m_endTime)
	{
		return false;
	}
	if (m_name != other.m_name)
	{
		return false;
	}
	if (m_note != other.m_note)
	{
		return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& out, const Meeting& meeting)
{
	//out << "~Meeting~" << std::endl;
	//out << "Start time: ";
	if (meeting.m_startTime / 100 < 10)
	{
		out << '0' << meeting.m_startTime / 100 << ':';
	}
	else
	{
		out << meeting.m_startTime / 100 << ':';
	}
	if (meeting.m_startTime % 100 < 10)
	{
		out << '0' << meeting.m_startTime % 100 << std::endl;
	}
	else
	{
		out << meeting.m_startTime % 100 << std::endl;
	}
	//out << "End time: ";
	if (meeting.m_endTime / 100 < 10)
	{
		out << '0' << meeting.m_endTime / 100 << ':';
	}
	else
	{
		out << meeting.m_endTime / 100 << ':';
	}
	if (meeting.m_endTime % 100 < 10)
	{
		out << '0' << meeting.m_endTime % 100 << std::endl;
	}
	else
	{
		out << meeting.m_endTime % 100 << std::endl;
	}
	out << meeting.m_name << std::endl;
	out << meeting.m_note << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, Meeting& meeting)
{
	std::string startTimeStr;
	std::string endTimeStr;
	std::string hoursStr;
	std::string minutesStr;
	std::string name;
	std::string note;

	std::cout << "Enter starting time in format HH:MM " << std::endl;
	in >> startTimeStr;
	try
	{
		try
		{
			Validations::ValidateTimeFormat(startTimeStr);
		}
		catch (const char* message)
		{
			std::cerr << message << std::endl;
			return in;
		}
		size_t colum = startTimeStr.find(':');
		hoursStr = startTimeStr.substr(0, colum);
		minutesStr = startTimeStr.substr(colum + 1);
		Validations::ValidateTime(hoursStr, minutesStr);
	}
	catch (const char* message)
	{
		std::cerr << message << std::endl;
		return in;
	}
	meeting.m_startTime = std::stoul(minutesStr) + std::stoul(hoursStr) * 100;

	std::cout << "Enter ending time in format HH:MM " << std::endl;
	in >> endTimeStr;
	try
	{
		try
		{
			Validations::ValidateTimeFormat(endTimeStr);
		}
		catch (const char* message)
		{
			std::cerr << message << std::endl;
			return in;
		}
		size_t colum = endTimeStr.find(':');
		hoursStr = endTimeStr.substr(0, colum);
		minutesStr = endTimeStr.substr(colum + 1);
		Validations::ValidateTime(hoursStr, minutesStr);
	}
	catch (const char* message)
	{
		std::cerr << message << std::endl;
		return in;
	}
	meeting.m_endTime = std::stoul(minutesStr) + std::stoul(hoursStr) * 100;

	std::cout << "Enter name " << std::endl;
	std::cin >> name;
	std::cin.ignore();
	meeting.m_name = name;

	std::cout << "Enter note " << std::endl;
	std::getline(std::cin, note);
	meeting.m_note = note;

	return in;
}
