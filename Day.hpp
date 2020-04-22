#pragma once
#include "Date.hpp"
#include "Meeting.hpp"

class Day
{
private:

	Date m_date;
	Meeting* m_meetings;
	size_t m_meetingSize;
	bool m_isWeekend;

	void swapMeetings(Meeting& first, Meeting& second);

public:

	Day();
	Day(const Date& date, const Meeting& meeting);
	Day& operator=(const Day& other);

	Date& getDate();
	size_t getMeetingSize();
	Meeting& getMeeting(size_t position);
	void removeMeeting(size_t position);
	void pushMeeting(const Meeting& meeting);
	void sortMeetings();
	void setIsWeekend(bool isWeekend);
	bool getIsWeekend();
	void setDate(const Date& date);
};

