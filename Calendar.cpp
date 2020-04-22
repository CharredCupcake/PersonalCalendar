#include "Calendar.hpp"

void Calendar::pushHoliday(const Date& date)
{
	if (m_size == 0)
	{
		m_size++;
		m_days = new Day[m_size];
		m_days[0].setDate(date);
		m_days[0].setIsWeekend(true);
		return;
	}
	Day* newDays = new Day[m_size + 1];
	for (size_t i = 0; i < m_size; i++)
	{
		newDays[i] = m_days[i];
	}
	newDays[m_size].setDate(date);
	newDays[m_size].setIsWeekend(true);
	m_size++;
	if (m_days != nullptr)
	{
		delete m_days;
	}
	m_days = newDays;
}

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

void Calendar::swapDays(Day& first, Day& second)
{
	Day temp(first);
	first = second;
	second = temp;
}

void Calendar::sortDays()
{
	for (size_t i = 0; i < m_size - 1; i++)
	{
		for (size_t j = 0; j < m_size - i - 1; j++)
		{
			if (m_days[j].getDate().getYear() > m_days[j + 1].getDate().getYear())
			{
				swapDays(m_days[j], m_days[j + 1]);
				continue;
			}
			else
			{
				if (m_days[j].getDate().getYear() == m_days[j + 1].getDate().getYear() && m_days[j].getDate().getMonth() > m_days[j + 1].getDate().getMonth())
				{
					swapDays(m_days[j], m_days[j + 1]);
					continue;
				}
				else
				{
					if (m_days[j].getDate().getMonth() == m_days[j + 1].getDate().getMonth() && m_days[j].getDate().getDay() > m_days[j + 1].getDate().getDay())
					{
						swapDays(m_days[j], m_days[j + 1]);
						continue;
					}
				}
			}
		}
	}
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
		if (m_days[dayPos].getIsWeekend())
		{
			std::cout << "This is a holiday." << std::endl;
			return;
		}
		else
		{
			m_days[dayPos].pushMeeting(Meeting(startTime, endTime, name, note));
		}
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
		if (m_days[dayPos].getIsWeekend())
		{
			std::cout << "This is a holiday." << std::endl;
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
		if (m_days[dayPos].getIsWeekend())
		{
			std::cout << "This is a holiday." << std::endl;
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
		if (m_days[dayPos].getIsWeekend())
		{
			std::cout << "This is a holiday." << std::endl;
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

void Calendar::find()
{
	//string
	std::string subStr;
	std::cout << "Enter word to search for: ";
	std::cin >> subStr;

	size_t meetingSize;
	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getIsWeekend())
		{
			continue;
		}
		else
		{
			meetingSize = m_days[i].getMeetingSize();
			for (size_t j = 0; j < meetingSize; j++)
			{
				if (m_days[i].getMeeting(j).getName().find(subStr) != std::string::npos || m_days[i].getMeeting(j).getNote().find(subStr) != std::string::npos)
				{
					std::cout << "Date: " << m_days[i].getDate().getYear() << '.' << m_days[i].getDate().getMonth() << '.' << m_days[i].getDate().getDay() << std::endl;
					std::cout << "Meeting: " << std::endl
						<< "Start time: " << m_days[i].getMeeting(j).getStartTime() << std::endl
						<< "Start end: " << m_days[i].getMeeting(j).getEndTime() << std::endl
						<< "Name: " << m_days[i].getMeeting(j).getName() << std::endl
						<< "Note: " << m_days[i].getMeeting(j).getNote() << std::endl;
				}
			}
		}
	}
}

void Calendar::holiday()
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
		pushHoliday(Date(year, month, day));
	}
	else
	{
		m_days[dayPos].setIsWeekend(true);
	}
	
}

void Calendar::busyDays()
{
	//From
	size_t fromYear, fromMonth, fromDay;
	//to
	size_t toYear, toMonth, toDay;

	std::cout << "Enter starting year: ";
	std::cin >> fromYear;
	//todo validate year
	std::cout << "Enter startng month: ";
	std::cin >> fromMonth;
	//todo validate month
	std::cout << "Enter starting day: ";
	std::cin >> fromDay;
	//todo validate day

	std::cout << "Enter end year: ";
	std::cin >> toYear;
	//todo validate year
	std::cout << "Enter end month: ";
	std::cin >> toMonth;
	//todo validate month
	std::cout << "Enter end day: ";
	std::cin >> toDay;
	//todo validate day

	size_t* busyHours = new size_t[m_size]{ 0 };

	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getIsWeekend())
		{
			continue;
		}
		else
		{
			if ((m_days[i].getDate().getYear() >= fromYear && m_days[i].getDate().getMonth() >= fromMonth && m_days[i].getDate().getDay() >= fromDay)
				&& (m_days[i].getDate().getYear() <= toYear && m_days[i].getDate().getMonth() <= toMonth && m_days[i].getDate().getDay() <= toDay))
			{
				size_t meetingSize = m_days[i].getMeetingSize();
				for (size_t j = 0; j < meetingSize; j++)
				{
					busyHours[i] += meetingLength(m_days[i].getMeeting(j));
				}
			}
		}
	}

	for (size_t i = 0; i < m_size - 1; i++)
	{
		for (size_t j = 0; j < m_size - i - 1; j++)
		{
			if (busyHours[j] < busyHours[j + 1])
			{
				size_t temp = busyHours[j];
				busyHours[j] = busyHours[j + 1];
				busyHours[j + 1] = temp;

				swapDays(m_days[j], m_days[j + 1]);
			}
		}
	}

	for (size_t i = 0; i < m_size; i++)
	{
		if (busyHours[i] == 0)
		{
			break;
		}
		else
		{
			std::cout << "Date: " << m_days[i].getDate().getYear() << '.' << m_days[i].getDate().getMonth() << '.' << m_days[i].getDate().getDay() << std::endl;
			size_t meetingSize = m_days[i].getMeetingSize();
			for (size_t j = 0; j < meetingSize; j++)
			{
				std::cout << "Meeting: " << std::endl;
				std::cout << "Start time: " << m_days[i].getMeeting(j).getStartTime() << std::endl;
				std::cout << "End time: " << m_days[i].getMeeting(j).getEndTime() << std::endl;
				std::cout << "Name: " << m_days[i].getMeeting(j).getName() << std::endl;
				std::cout << "Note: " << m_days[i].getMeeting(j).getNote() << std::endl;
			}
		}
	}
	delete[] busyHours;
}

void Calendar::findSlot()
{
	//Date
	size_t year, month, day;
	//hours
	size_t meetingLength;
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

	std::cout << "Enter meeting length: ";
	std::cin >> meetingLength;
	//todo validate meetingLength
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cin.ignore();
	std::cout << "Enter note: ";
	std::getline(std::cin, note);


	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getIsWeekend())
		{
			continue;
		}
		if (m_days[i].getDate().getYear() >= year && m_days[i].getDate().getMonth() >= month && m_days[i].getDate().getDay() >= day)
		{
			m_days[i].sortMeetings();
			size_t meetingSize = m_days[i].getMeetingSize();
			if (meetingSize > 0)
			{
				if (800 + meetingLength <= m_days[i].getMeeting(0).getStartTime())
				{
					m_days[i].pushMeeting(Meeting(800, 800 + meetingLength, name, note));
					return;
				}
			}
			for (size_t j = 0; j < meetingSize - 1; j++)
			{
				if (m_days[i].getMeeting(j).getEndTime() <= 1700)
				{
					if (m_days[i].getMeeting(j).getEndTime() + meetingLength <= m_days[i].getMeeting(j + 1).getStartTime())
					{
						m_days[i].pushMeeting(Meeting(m_days[i].getMeeting(j).getEndTime(), m_days[i].getMeeting(j).getEndTime() + meetingLength, name, note));
						return;
					}
				}
			}
		}
	}
	sortDays();
	Date lastDate = m_days[m_size - 1].getDate();
	lastDate.nextDay();
	pushDay(Day(lastDate, Meeting(800, 800 + meetingLength, name, note)));
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
