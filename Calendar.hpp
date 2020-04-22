#pragma once
#include <iostream>
#include <fstream>
#include "Day.hpp"

class Calendar
{
private:

	Day* m_days;
	size_t m_size;

	void pushHoliday(const Date& date);
	void pushDay(const Day& day);
	void pushMeeting(const Date& date, const Meeting& meeting);
	void removeDay(size_t position);
	size_t findDay(size_t year, size_t month, size_t day);
	size_t findMeeting(size_t dayPos, size_t startTime, size_t endTime);
	size_t findMeeting(size_t dayPos, size_t startTime);
	size_t meetingLength(const Meeting& meeting);
	void swapDays(Day& first, Day& second);
	void sortDays();

public:

	Calendar(const char* fileName);
	~Calendar();

	void book();
	void unbook();
	void agenda();
	void change();
	void find();
	void holiday();
	void busyDays();
	void findSlot();
	void findSlotWith();
	void merge();

	//temp for testing
	void print();
};

