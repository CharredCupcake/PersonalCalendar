#include "Calendar.hpp"

void Calendar::pushDay(const Day& day)
{
	if (m_size == 0)
	{
		m_size++;
		m_days = new Day[m_size];
		m_days[0] = day;
		return;
	}
	Day* newDays = new Day[m_size + 1];
	for (size_t i = 0; i < m_size; i++)
	{
		newDays[i] = m_days[i];
	}
	newDays[m_size] = day;
	m_size++;
	if (m_days != nullptr)
	{
		delete m_days;
	}
	m_days = newDays;
}

void Calendar::pushMeeting(const Date& date, const Meeting& meeting)
{
	size_t dayPos = findDay(date.getYear(), date.getMonth(), date.getDay());
	if (dayPos == 0xffffffff)
	{
		pushDay(Day(date, meeting));
	}
	else
	{
		m_days[dayPos].pushMeeting(meeting);
	}

}

void Calendar::removeDay(size_t position)
{
	if (m_size == 1)
	{
		m_size = 0;
		delete[] m_days;
		m_days = nullptr;
		return;
	}
	Day* newDays = new Day[m_size - 1];
	for (size_t i = 0; i < position; i++)
	{
		newDays[i] = m_days[i];
	}
	for (size_t i = position + 1; i < m_size; i++)
	{
		newDays[i - 1] = m_days[i];
	}
	m_size--;
	delete[] m_days;
	m_days = newDays;
}

size_t Calendar::findDay(size_t year, size_t month, size_t day)
{
	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getDate().getYear() == year && m_days[i].getDate().getMonth() == month && m_days[i].getDate().getDay() == day)
		{
			return i;
		}
	}
	return 0xffffffff;
}

size_t Calendar::findMeeting(size_t dayPos, size_t startTime, size_t endTime)
{
	size_t meetingsSize = m_days->getMeetingSize();
	for (size_t j = 0; j < meetingsSize ; j++)
	{
		if (m_days[dayPos].getMeeting(j).getStartTime() == startTime && m_days[dayPos].getMeeting(j).getEndTime() == endTime)
		{
			return j;
		}
	}
	return 0xffffffff;
}

size_t Calendar::findMeeting(size_t dayPos, size_t startTime)
{
	size_t meetingsSize = m_days->getMeetingSize();
	for (size_t j = 0; j < meetingsSize; j++)
	{
		if (m_days[dayPos].getMeeting(j).getStartTime() == startTime)
		{
			return j;
		}
	}
	return 0xffffffff;
}

size_t Calendar::meetingLength(const Meeting& meeting)
{
	size_t length = meeting.getEndTime() - meeting.getStartTime();

	if (meeting.getEndTime() % 100 < meeting.getStartTime() % 100)
	{
		length -= 40;
	}
	return length;
}

Calendar::Calendar(const char* fileName) :
	m_days(nullptr),
	m_size(0)
{
	std::ofstream outStream;
	outStream.open(fileName);
	outStream.close();
	std::ifstream inStream;
	inStream.open(fileName);
	if (inStream.peek() == EOF)
	{
		std::cout << "Empty" << std::endl;// do nothing.
	}
	else
	{
		std::cout << "Not empty" << std::endl;// load calendar from file
	}
	inStream.close();
}

Calendar::~Calendar()
{
	delete[] m_days;
}

void Calendar::book()
{
	//Date
	size_t year, month, day;
	//Meeting
	size_t startTime, endTime;
	std::string name, note;

	std::cout << "Enter year: ";
	std::cin >> year;
	//todo validate year
	std::cout << "Enter month: ";
	std::cin >> month;
	//todo validate month
	std::cout << "Enter day: ";
	std::cin >> day;
	//todo validate day
	std::cout << "Enter start time: ";
	std::cin >> startTime;
	//todo validate startTime
	std::cout << "Enter end time: ";
	std::cin >> endTime;
	//todo validate endTime
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cin.ignore();
	std::cout << "Enter note: ";
	std::getline(std::cin, note);

	size_t dayPos = findDay(year, month, day);
	if (dayPos == 0xffffffff)
	{
		pushDay(Day(Date(year, month, day), Meeting(startTime, endTime, name, note)));
	}
	else
	{
		m_days[dayPos].pushMeeting(Meeting(startTime, endTime, name, note));
	}
	
}

void Calendar::unbook()
{
	//Date
	size_t year, month, day;
	//startTime
	size_t startTime;
	//endTime
	size_t endTime;

	std::cout << "Enter year: ";
	std::cin >> year;
	//todo validate year
	std::cout << "Enter month: ";
	std::cin >> month;
	//todo validate month
	std::cout << "Enter day: ";
	std::cin >> day;
	//todo validate day
	std::cout << "Enter start time: ";
	std::cin >> startTime;
	//todo validate startTime
	std::cout << "Enter end time: ";
	std::cin >> endTime;
	//todo validate endTime

	size_t dayPos = findDay(year, month, day);
	if (dayPos == 0xffffffff)
	{
		std::cout << "Day not found." << std::endl;
		return;
	}
	else
	{
		size_t meetingPos = findMeeting(dayPos, startTime, endTime);
		if (meetingPos == 0xffffffff)
		{
			std::cout << "Meeting not found." << std::endl;
			return;
		}
		else
		{
			m_days[dayPos].removeMeeting(meetingPos);
			if (m_days[dayPos].getMeetingSize() == 0)
			{
				removeDay(dayPos);
			}
		}
	}

}

void Calendar::agenda()
{
	//Date
	size_t year, month, day;

	std::cout << "Enter year: ";
	std::cin >> year;
	//todo validate year
	std::cout << "Enter month: ";
	std::cin >> month;
	//todo validate month
	std::cout << "Enter day: ";
	std::cin >> day;
	//todo validate day

	size_t dayPos = findDay(year, month, day);
	if (dayPos == 0xffffffff)
	{
		std::cout << "Day not found." << std::endl;
		return;
	}
	else
	{
		m_days[dayPos].sortMeetings();
		size_t meetingSize = m_days[dayPos].getMeetingSize();
		std::cout << "Meetings: " << std::endl;
		for (size_t i = 0; i < meetingSize; i++)
		{
			std::cout << "Start time: " << m_days[dayPos].getMeeting(i).getStartTime() << std::endl
					  << "End time: " << m_days[dayPos].getMeeting(i).getEndTime() << std::endl
					  << "Name: " << m_days[dayPos].getMeeting(i).getName() << std::endl
					  << "Note: " << m_days[dayPos].getMeeting(i).getNote() << std::endl << std::endl;
		}
	}
}

void Calendar::change()
{
	//Date
	size_t year, month, day;
	//startTime
	size_t startTime;
	//option
	size_t option;

	std::cout << "Enter year: ";
	std::cin >> year;
	//todo validate year
	std::cout << "Enter month: ";
	std::cin >> month;
	//todo validate month
	std::cout << "Enter day: ";
	std::cin >> day;
	//todo validate day
	std::cout << "Enter start time: ";
	std::cin >> startTime;
	//todo validate startTime

	size_t dayPos = findDay(year, month, day);
	size_t meetingPos;
	if (dayPos == 0xffffffff)
	{
		std::cout << "Day not found." << std::endl;
		return;
	}
	else
	{
		meetingPos = findMeeting(dayPos, startTime);
		if (meetingPos == 0xffffffff)
		{
			std::cout << "Meeting not found." << std::endl;
			return;
		}
	}

	do
	{
		std::cout << "Choose what to change. " << std::endl;
		std::cout << "(1) Date." << std::endl;
		std::cout << "(2) Start time." << std::endl;
		std::cout << "(3) End time." << std::endl;
		std::cout << "(4) Name." << std::endl;
		std::cout << "(5) Note." << std::endl;
		std::cout << "Your choice: " << std::endl;
		std::cin >> option;

	} while (option < 1 || option>5);

	//newValue
	Meeting savedMeeting = m_days[dayPos].getMeeting(meetingPos);
	std::string name;
	size_t duration = 0;//meeting duration
	switch (option)
	{
	case 1:
		std::cout << "Enter new year: ";
		std::cin >> year;
		//todo validate year
		std::cout << "Enter new month: ";
		std::cin >> month;
		//todo validate month
		std::cout << "Enter new day: ";
		std::cin >> day;
		//todo validate day
		m_days[dayPos].removeMeeting(meetingPos);
		pushMeeting(Date(year, month, day), savedMeeting);
		break;
	case 2:
		std::cout << "Enter new start time: ";
		std::cin >> startTime;
		//todo validate startTime
		m_days[dayPos].removeMeeting(meetingPos);
		duration = meetingLength(savedMeeting);
		savedMeeting.setStartTime(startTime);
		//todo check if end time is valid after adding duration
		if (startTime >= savedMeeting.getEndTime())
		{
			if ((savedMeeting.getStartTime() % 100 + duration % 100) > 59)
			{
				savedMeeting.setEndTime(startTime + duration + 40);
			}
			else
			{
				savedMeeting.setEndTime(startTime + duration);
			}
		}
		m_days[dayPos].pushMeeting(savedMeeting);
		break;
	case 3:
		std::cout << "Enter new end time: ";
		std::cin >> startTime;
		//todo validate startTime
		m_days[dayPos].removeMeeting(meetingPos);
		savedMeeting.setEndTime(startTime);
		m_days[dayPos].pushMeeting(savedMeeting);
		break;
	case 4:
		std::cout << "Enter new name: ";
		std::cin >> name;
		m_days[dayPos].removeMeeting(meetingPos);
		savedMeeting.setName(name);
		m_days[dayPos].pushMeeting(savedMeeting);
		break;
	case 5:
		std::cout << "Enter new note: ";
		std::cin.ignore();
		std::getline(std::cin, name);
		m_days[dayPos].removeMeeting(meetingPos);
		savedMeeting.setNote(name);
		m_days[dayPos].pushMeeting(savedMeeting);
		break;
	}


}

void Calendar::print()
{
	for (size_t i = 0; i < m_size; i++)
	{
		std::cout << "Date: " << m_days[i].getDate().getYear() << "." << m_days[i].getDate().getMonth() << "." << m_days[i].getDate().getDay() << std::endl;
		size_t meetingSize = m_days[i].getMeetingSize();
		for (size_t j = 0; j < meetingSize; j++)
		{
			std::cout << "Meeting: " << std::endl
			<< m_days[i].getMeeting(j).getStartTime() << std::endl
			<< m_days[i].getMeeting(j).getEndTime() << std::endl
			<< m_days[i].getMeeting(j).getName() << std::endl
			<< m_days[i].getMeeting(j).getNote() << std::endl;
		}
	}
}
