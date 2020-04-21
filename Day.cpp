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
		for (size_t j = i; j < m_meetingSize - 1; j++)
		{
			if (m_meetings[j].getStartTime() / 100 > m_meetings[j + 1].getStartTime() / 100)
			{
				swapMeetings(m_meetings[j], m_meetings[j + 1]);
				continue;
			}
			if(m_meetings[j].getStartTime() / 100 == m_meetings[j + 1].getStartTime() / 100)
			{
				if (m_meetings[j].getStartTime() % 100 > m_meetings[j + 1].getStartTime() % 100)
				{
					swapMeetings(m_meetings[j], m_meetings[j + 1]);
				}
			}
		}
	}
}
