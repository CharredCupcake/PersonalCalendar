#pragma once
#include <iostream>
#include <fstream>
#include "Day.hpp"

static const char TEST_FILE[] = "Test.txt";

class Calendar
{
private:

	Day* m_days;
	size_t m_size;

	void pushHoliday(const Date& date);
	void pushDay(const Day& day);
	void pushMeeting(const Date& date, const Meeting& meeting);
	void removeDay(size_t position);
	size_t findDay(const Date& date);
	size_t findMeeting(size_t dayPos, size_t startTime, size_t endTime);
	size_t findMeeting(size_t dayPos, size_t startTime);
	size_t meetingLength(const Meeting& meeting);
	void swapDays(Day& first, Day& second);
	void sortDays();
	Date cinDate();
	bool ValidateDateFormat(const std::string& dateStr);
	bool ValidateDate(const std::string& yearStr, const std::string& monthStr, const std::string& dayStr);
	size_t cinTime(const char* startOrEnd);
	bool ValidateTimeFormat(const std::string& timeStr);
	bool ValidateTime(const std::string& hoursStr, const std::string& minutesStr);

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

	void print();//temporary for testing
};

