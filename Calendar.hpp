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
	void removeDay(size_t position);
	size_t findDay(const Date& date);
	void swapDays(Day& first, Day& second);
	void sortDays();
	void getLine(std::string& str, std::ifstream& in);
	void mergeDays(size_t dayPos, Day& otherDay);

public:

	Calendar();
	Calendar(const char* fileName);
	~Calendar();

	void open(std::string& fileName);
	void close(std::string& fileName);
	void save(std::string& fileName);
	void saveAs();
	static void help();
	void exit(std::string& fileName, bool fileIsOpen);

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

};

