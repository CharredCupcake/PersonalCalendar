#pragma once
#include <string>

class Meeting
{
private:

	size_t m_startTime;
	size_t m_endTime;
	std::string m_name;
	std::string m_note;

public:

	Meeting();
	Meeting(size_t startTime, size_t endTime, std::string name, std::string note);
	
	size_t getStartTime() const;
	void setStartTime(size_t startTime);
	size_t getEndTime() const;
	void setEndTime(size_t endTime);
	std::string& getName();
	void setName(std::string name);
	std::string& getNote();
	void setNote(std::string note);

};

