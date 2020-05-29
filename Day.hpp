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
	Day(const Day& other);
	Day(const Date& date, const Meeting& meeting);
	~Day();
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
	size_t findFreeTime(size_t length);
	bool checkMeeting(size_t startTime, size_t length);
	size_t findMeeting(size_t startTime, size_t endTime);
	size_t findMeeting(size_t startTime);

	friend std::ostream& operator<<(std::ostream& out, const Day& day);
};

