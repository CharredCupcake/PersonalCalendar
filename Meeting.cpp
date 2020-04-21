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

