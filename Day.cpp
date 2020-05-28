#include "Day.hpp"

void Day::swapMeetings(Meeting& first, Meeting& second)
{
	Meeting temp;
	temp = first;
	first = second;
	second = temp;
}

Day::Day() :
	m_date(),
	m_meetingSize(0),
	m_meetings(nullptr),
	m_isWeekend(false)
{
}

Day::Day(const Day& other) :
	m_date(other.m_date),
	m_meetingSize(other.m_meetingSize),
	m_meetings(nullptr),
	m_isWeekend(other.m_isWeekend)
{
	for (size_t i = 0; i < other.m_meetingSize; i++)
	{
		pushMeeting(other.m_meetings[i]);
	}
}

Day::Day(const Date& date, const Meeting& meeting) :
	m_date(date),
	m_meetingSize(0),
	m_meetings(nullptr),
	m_isWeekend(false)
{
	pushMeeting(meeting);
}

Day::~Day()
{
	delete[] m_meetings;
}

Day& Day::operator=(const Day& other)
{
	if (this != &other)
	{
		m_date = other.m_date;
		m_meetingSize = other.m_meetingSize;
		if (m_meetings != nullptr)
		{
			delete[] m_meetings;
		}
		m_meetings = new Meeting[m_meetingSize];
		for (size_t i = 0; i < m_meetingSize; i++)
		{
			m_meetings[i] = other.m_meetings[i];
		}
		m_isWeekend = other.m_isWeekend;
	}
	return *this;
}

Date& Day::getDate()
{
	return m_date;
}

size_t Day::getMeetingSize()
{
	return m_meetingSize;
}

Meeting& Day::getMeeting(size_t position)
{
	return m_meetings[position];
}

void Day::removeMeeting(size_t position)
{
	if (m_meetingSize == 1)
	{
		m_meetingSize = 0;
		delete[] m_meetings;
		m_meetings = nullptr;
		return;
	}
	Meeting* newMeetings = new Meeting[m_meetingSize - 1];
	for (size_t i = 0; i < position; i++)
	{
		newMeetings[i] = m_meetings[i];
	}
	for (size_t i = position + 1; i < m_meetingSize; i++)
	{
		newMeetings[i - 1] = m_meetings[i];
	}
	m_meetingSize--;
	delete[] m_meetings;
	m_meetings = newMeetings;
}

void Day::pushMeeting(const Meeting& meeting)
{
	if (m_meetings == nullptr)
	{
		m_meetingSize = 1;
		m_meetings = new Meeting[m_meetingSize];
		m_meetings[0] = meeting;
	}
	else
	{
		Meeting* newMeetings = new Meeting[m_meetingSize + 1];
		for (size_t i = 0; i < m_meetingSize; i++)
		{
			newMeetings[i] = m_meetings[i];
		}
		newMeetings[m_meetingSize] = meeting;
		m_meetingSize++;
		if (m_meetings != nullptr)
		{
			delete[] m_meetings;
		}
		m_meetings = newMeetings;
	}
}

void Day::sortMeetings()
{
	for (size_t i = 0; i < m_meetingSize - 1; i++)
	{
		for (size_t j = 0; j < m_meetingSize - i - 1; j++)
		{
			if (m_meetings[j].getStartTime() / 100 > m_meetings[j + 1].getStartTime() / 100)
			{
				swapMeetings(m_meetings[j], m_meetings[j + 1]);
				continue;
			}
			if (m_meetings[j].getStartTime() / 100 == m_meetings[j + 1].getStartTime() / 100)
			{
				if (m_meetings[j].getStartTime() % 100 > m_meetings[j + 1].getStartTime() % 100)
				{
					swapMeetings(m_meetings[j], m_meetings[j + 1]);
				}
			}
		}
	}
}

void Day::setIsWeekend(bool isWeekend)
{
	m_isWeekend = isWeekend;
}

bool Day::getIsWeekend()
{
	return m_isWeekend;
}

void Day::setDate(const Date& date)
{
	m_date = date;
}

size_t Day::findFreeTime(size_t length)
{
	sortMeetings();
	size_t startTime = 800;
	if (m_meetingSize > 0)
	{
		if (startTime + length <= getMeeting(0).getStartTime())
		{
			return startTime;
		}
		for (size_t i = 0; i < m_meetingSize - 1; i++)
		{
			startTime = m_meetings[i].getEndTime();
			if ( startTime <= 1700)
			{
				if (startTime + length <= m_meetings[i + 1].getStartTime())
				{
					return startTime;
				}
			}
		}
		startTime = m_meetings[m_meetingSize - 1].getEndTime();
		if (startTime + length <= 1700)
		{
			return startTime;
		}
	}
	else
	{
		return startTime;
	}
	return 0xffffffff;
}

bool Day::checkMeeting(size_t startTime, size_t length)
{
	sortMeetings();
	if (m_meetingSize > 0)
	{
		if (startTime + length <= m_meetings[0].getStartTime())
		{
			return true;
		}
		for (size_t i = 0; i < m_meetingSize - 1; i++)
		{
			if (startTime >= m_meetings[i].getEndTime())
			{
				if (startTime + length <= m_meetings[i + 1].getStartTime())
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		if (startTime >= m_meetings[m_meetingSize - 1].getEndTime())
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const Day& day)
{
	if (day.m_meetingSize > 0)
	{
		for (size_t i = 0; i < day.m_meetingSize; i++)
		{
			out << day.m_date;
			out << day.m_isWeekend << std::endl;
			out << day.m_meetings[i];
		}
	}
	else
	{
		out << day.m_date;
		out << day.m_isWeekend << std::endl;
	}

	return out;
}
