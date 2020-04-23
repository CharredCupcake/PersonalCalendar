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
