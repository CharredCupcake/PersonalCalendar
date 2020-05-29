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
		delete[] m_days;
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
		delete[] m_days;
	}
	m_days = newDays;
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

size_t Calendar::findDay(const Date& date)
{
	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getDate() == date)
		{
			return i;
		}
	}
	return 0xffffffff;
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

void Calendar::getLine(std::string& str, std::ifstream& in)
{
	char tempChar = 0;
	while ((tempChar = in.get()) != '\n')
	{
		str.push_back(tempChar);
	}
}

void Calendar::mergeDays(size_t dayPos, Day& otherDay)
{
	m_days[dayPos].sortMeetings();
	otherDay.sortMeetings();

	size_t meetingSize = m_days[dayPos].getMeetingSize();
	size_t otherMeetingPos = 0;
	size_t thisStart, thisEnd;
	size_t otherStart, otherEnd;
	size_t choice = 0;
	for (size_t i = 0; i < meetingSize; i++)
	{
		for (otherMeetingPos; otherMeetingPos < otherDay.getMeetingSize(); otherMeetingPos++)
		{
			thisStart = m_days[dayPos].getMeeting(i).getStartTime();
			thisEnd = m_days[dayPos].getMeeting(i).getEndTime();
			otherStart = otherDay.getMeeting(otherMeetingPos).getStartTime();
			otherEnd = otherDay.getMeeting(otherMeetingPos).getEndTime();

			if ((otherStart >= thisStart && otherStart <= thisEnd) || (otherEnd >= thisStart && otherEnd <= thisEnd))
			{
				std::cout << "Meetings overlap! Choose meeting to save" << std::endl;
				std::cout << "Meeting (1) " << std::endl;
				std::cout << m_days[dayPos].getMeeting(i);
				std::cout << "Meeting (2) " << std::endl;
				std::cout << otherDay.getMeeting(otherMeetingPos);
				std::cout << "Your choice: ";
				std::cin >> choice;
				while (choice < 1 || choice > 2)
				{
					std::cout << "Invalid choice. Please choose again." << std::endl;
					std::cin >> choice;
				}
				switch (choice)
				{
				case 1:
					break;
				case 2:
					m_days[dayPos].getMeeting(i) = otherDay.getMeeting(otherMeetingPos);
					break;
				}
			}
			else
			{
				if (otherStart < thisStart)
				{
					m_days[dayPos].pushMeeting(otherDay.getMeeting(otherMeetingPos));
				}
				else
				{
					break;
				}
			}
		}
	}
	for (otherMeetingPos; otherMeetingPos < otherDay.getMeetingSize(); otherMeetingPos++)
	{
		m_days[dayPos].pushMeeting(otherDay.getMeeting(otherMeetingPos));
	}
}

Calendar::Calendar() :
	m_days(nullptr),
	m_size(0)
{
}

Calendar::Calendar(const char* fileName) :
	m_days(nullptr),
	m_size(0)
{
	std::ofstream outStream;
	do
	{
		outStream.open(fileName, std::ios::app);
	} while (!outStream.is_open());
	outStream.close();

	std::ifstream inStream;
	do
	{
		inStream.open(fileName);
	} while (!inStream.is_open());

	if (inStream.peek() == EOF)
	{
	}
	else
	{
		do
		{
			std::string dateStr;
			bool isWeekend;

			getLine(dateStr, inStream);
			isWeekend = bool(inStream.get() - '0');
			inStream.ignore();

			size_t firstDot = dateStr.find('.'), secondDot = dateStr.rfind('.');
			std::string yearStr = dateStr.substr(0, firstDot), monthStr = dateStr.substr(firstDot + 1, secondDot - firstDot - 1), dayStr = dateStr.substr(secondDot + 1);
			Date date(std::stoul(yearStr), std::stoul(monthStr), std::stoul(dayStr));

			if (isWeekend)
			{
				pushHoliday(date);
			}
			else
			{
				size_t startTime = 0, endTime = 0;
				std::string name, note;

				startTime += size_t(inStream.get() - '0') * 1000 + size_t(inStream.get() - '0') * 100;
				inStream.ignore();
				startTime += size_t(inStream.get() - '0') * 10 + size_t(inStream.get() - '0');
				inStream.ignore();
				endTime += size_t(inStream.get() - '0') * 1000 + size_t(inStream.get() - '0') * 100;
				inStream.ignore();
				endTime += size_t(inStream.get() - '0') * 10 + size_t(inStream.get() - '0');
				inStream.ignore();

				getLine(name, inStream);
				getLine(note, inStream);

				size_t dayPos = findDay(date);
				if (dayPos == 0xffffffff)
				{
					pushDay(Day(date, Meeting(startTime, endTime, name, note)));
				}
				else
				{
					m_days[dayPos].pushMeeting(Meeting(startTime, endTime, name, note));
				}
			}
		} while (inStream.peek() != EOF);
	}
	inStream.close();
}

Calendar::~Calendar()
{
	delete[] m_days;
}

void Calendar::open(std::string& fileName)
{
	std::cout << "Enter file name." << std::endl;
	std::cin >> fileName;
	Validations::ValidateFileName(fileName);

	this->Calendar::Calendar(fileName.c_str());
}

void Calendar::close(std::string& fileName)
{
	std::cout << "Close without saving?" << std::endl;
	size_t option = 0;
	do
	{
		std::cout << "(1) Save." << std::endl;
		std::cout << "(2) Save As." << std::endl;
		std::cout << "(3) Cancel." << std::endl;
		std::cout << "(4) Close." << std::endl;
		std::cin >> option;

	} while (option < 1 || option > 4);

	switch (option)
	{
	case 1:
		this->save(fileName);
		break;
	case 2:
		this->saveAs();
		break;
	case 3:
		break;
	case 4:
		this->~Calendar();
		break;
	}
}

void Calendar::save(std::string& fileName)
{
	sortDays();
	for (size_t i = 0; i < m_size; i++)
	{
		if (!m_days[i].getIsWeekend())
		{
			m_days[i].sortMeetings();
		}
	}
	std::ofstream outStream;
	do
	{
		outStream.open(fileName, std::ofstream::trunc);
	} while (!outStream.is_open());

	for (size_t i = 0; i < m_size; i++)
	{
		outStream << m_days[i];
	}
	outStream.close();
}

void Calendar::saveAs()
{
	std::string otherFileName;
	size_t dotPos = 0;
	std::cout << "Enter file name." << std::endl;
	std::cin >> otherFileName;
	Validations::ValidateFileName(otherFileName);
	save(otherFileName);
}

void Calendar::help()
{
	std::cout << "Commands: " << std::endl;
	std::cout << "Open - Open new calendar." << std::endl;
	std::cout << "Close - Close currently open calendar." << std::endl;
	std::cout << "Save - Save calendar in the same file." << std::endl;
	std::cout << "Save as - Save calendar in a different file." << std::endl;
	std::cout << "Help - List of all commands." << std::endl;
	std::cout << "Exit - Exit the aplication." << std::endl;
	std::cout << "Book <date> <start time> <end time> <name> <note> - Create a new meeting." << std::endl;
	std::cout << "Unbook <date> <start time> <end time> - Delete existing meeting." << std::endl;
	std::cout << "Agenda <date> - Show all meetings on this date." << std::endl;
	std::cout << "Change <date> <start time> - Change meeting at this date." << std::endl;
	std::cout << "Find <key word> - List all meetings with the key word either in their name or note." << std::endl;
	std::cout << "Holiday <date> - Make this date a holiday." << std::endl;
	std::cout << "Busy days <start date> <end date> - List all days from start date to end date ordered descending by work hours." << std::endl;
	std::cout << "Find slot <date> <hours> - Finds and books the first possible meeting from date with hours length." << std::endl;
	std::cout << "Find slot <date> <hours> <calendar> - Finds and books the first possible meeting from date with hours length synced with other calendar." << std::endl;
	std::cout << "Merge <calendar> - Merges the current calendar with another one." << std::endl;
}

void Calendar::exit(std::string& fileName, bool fileIsOpen)
{
	if (fileIsOpen)
	{
		std::cout << "Exit without saving?" << std::endl;
		size_t option = 0;
		do
		{
			std::cout << "(1) Save." << std::endl;
			std::cout << "(2) Save As." << std::endl;
			std::cout << "(3) Cancel." << std::endl;
			std::cout << "(4) Exit." << std::endl;
			std::cin >> option;

		} while (option < 1 || option > 4);

		switch (option)
		{
		case 1:
			this->save(fileName);
			break;
		case 2:
			this->saveAs();
			break;
		case 3:
			return;
		case 4:
			break;
		}
	}

	std::exit(0);
}

void Calendar::book()
{
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	Meeting meeting;
	std::cin >> meeting;
	try
	{
		if (meeting == Meeting())
		{
			throw std::invalid_argument("Couldn't initialize meeting.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t dayPos = findDay(date);
	if (dayPos == 0xffffffff)
	{
		pushDay(Day(date, meeting));
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
			m_days[dayPos].pushMeeting(meeting);
		}
	}
}

void Calendar::unbook()
{
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception &)
	{
		return;
	}

	size_t startTime = Meeting::cinTime("start");
	try
	{
		if (startTime == 0)
		{
			throw std::invalid_argument("Couldn't initialize time.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t endTime = Meeting::cinTime("end");
	try
	{
		if (startTime == 0)
		{
			throw std::invalid_argument("Couldn't initialize time.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t dayPos = findDay(date);
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
			size_t meetingPos = m_days[dayPos].findMeeting(startTime, endTime);
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
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t dayPos = findDay(date);
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
			for (size_t i = 0; i < meetingSize; i++)
			{
				std::cout << m_days[dayPos].getMeeting(i);
			}
		}
	}
}

void Calendar::change()
{
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t startTime = Meeting::cinTime("start");
	try
	{
		if (startTime == 0)
		{
			throw std::invalid_argument("Couldn't initialize time.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t option;

	size_t meetingPos;
	size_t dayPos = findDay(date);
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
			meetingPos = m_days[dayPos].findMeeting(startTime);
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

	Meeting savedMeeting = m_days[dayPos].getMeeting(meetingPos);
	std::string name;

	size_t duration = 0;
	size_t endTime;
	switch (option)
	{
	case 1:
		std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
		std::cin >> date;
		try
		{
			if (date == Date())
			{
				throw std::invalid_argument("Couldn't initialize date.");
			}
		}
		catch (const std::exception&)
		{
			return;
		}
		m_days[dayPos].removeMeeting(meetingPos);
		dayPos = findDay(date);
		if (dayPos == 0xffffffff)
		{
			pushDay(Day(date, savedMeeting));
		}
		else
		{
			m_days[dayPos].pushMeeting(savedMeeting);
		}
		break;
	case 2:
		startTime = Meeting::cinTime("new start");
		try
		{
			if (startTime == 0)
			{
				throw std::invalid_argument("Couldn't initialize time.");
			}
		}
		catch (const std::exception&)
		{
			return;
		}
		m_days[dayPos].removeMeeting(meetingPos);
		duration = savedMeeting.meetingLength();
		savedMeeting.setStartTime(startTime);
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
		endTime = Meeting::cinTime("new end");
		try
		{
			if (startTime == 0)
			{
				throw std::invalid_argument("Couldn't initialize time.");
			}
		}
		catch (const std::exception&)
		{
			return;
		}
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
					std::cout << "Date: " << m_days[i].getDate() << std::endl;
					std::cout << m_days[i].getMeeting(j);
				}
			}
		}
	}
}

void Calendar::holiday()
{
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t dayPos = findDay(date);
	if (dayPos == 0xffffffff)
	{
		pushHoliday(date);
	}
	else
	{
		m_days[dayPos].setIsWeekend(true);
	}
	
}

void Calendar::busyDays()
{
	std::cout << "From when to start the search?" << std::endl;
	Date fromDate;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> fromDate;
	try
	{
		if (fromDate == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	std::cout << "When to stop the search?" << std::endl;
	Date toDate;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> toDate;
	try
	{
		if (toDate == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t* busyHours = new size_t[m_size]{ 0 };

	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getIsWeekend())
		{
			continue;
		}
		else
		{
			if ((m_days[i].getDate() >= fromDate)
				&& (m_days[i].getDate() <= toDate))
			{
				size_t meetingSize = m_days[i].getMeetingSize();
				for (size_t j = 0; j < meetingSize; j++)
				{
					busyHours[i] += m_days[i].getMeeting(j).meetingLength();
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
			std::cout << "Date: " << m_days[i].getDate() << std::endl;
			size_t meetingSize = m_days[i].getMeetingSize();
			for (size_t j = 0; j < meetingSize; j++)
			{
				std::cout << m_days[i].getMeeting(j);
			}
		}
	}
	delete[] busyHours;
}

void Calendar::findSlot()
{
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t meetingLength = Meeting::cinTime("meeting length");
	try
	{
		try
		{
			if (meetingLength == 0)
			{
				throw std::invalid_argument("Couldn't initialize time.");
			}
		}
		catch (const std::exception&)
		{
			return;
		}
		if (meetingLength > 900)
		{
			throw std::invalid_argument("Meeting too long.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	std::string name, note;
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cin.ignore();
	std::cout << "Enter note: ";
	std::getline(std::cin, note);

	size_t startTime = 800;
	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getIsWeekend())
		{
			continue;
		}
		if (m_days[i].getDate() >= date)
		{
			startTime = m_days[i].findFreeTime(meetingLength);
			if (startTime != 0xffffffff)
			{
				m_days[i].pushMeeting(Meeting(startTime, startTime + meetingLength, name, note));
				return;
			}
		}
	}
	startTime = 800;
	sortDays();
	date = m_days[m_size - 1].getDate();
	date.nextDay();
	pushDay(Day(date, Meeting(startTime, startTime + meetingLength, name, note)));
}

void Calendar::findSlotWith()
{
	Date date;
	std::cout << "Enter date in format YYYY.MM.DD " << std::endl;
	std::cin >> date;
	try
	{
		if (date == Date())
		{
			throw std::invalid_argument("Couldn't initialize date.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	size_t meetingLength = Meeting::cinTime("meeting length");
	try
	{
		try
		{
			if (meetingLength == 0)
			{
				throw std::invalid_argument("Couldn't initialize time.");
			}
		}
		catch (const std::exception&)
		{
			return;
		}
		if (meetingLength > 900)
		{
			throw std::invalid_argument("Meeting too long.");
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	std::string name, note;
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cin.ignore();
	std::cout << "Enter note: ";
	std::getline(std::cin, note);

	Calendar otherCal;
	std::string otherFile;
	otherCal.open(otherFile);
	size_t otherDayPos;
	size_t startTime = 800;

	for (size_t i = 0; i < m_size; i++)
	{
		if (m_days[i].getIsWeekend() || otherCal.m_days[i].getIsWeekend())
		{
			continue;
		}
		if (m_days[i].getDate() >= date)
		{

			startTime = m_days[i].findFreeTime(meetingLength);
			if (startTime != 0xffffffff)
			{
				otherDayPos = otherCal.findDay(m_days[i].getDate());
				if (otherDayPos == 0xffffffff)
				{
					m_days[i].pushMeeting(Meeting(startTime, startTime + meetingLength, name, note));
					otherCal.pushDay(Day(m_days[i].getDate(), Meeting(startTime, startTime + meetingLength, name, note)));
					otherCal.save(otherFile);
					return;
				}
				else
				{
					if (otherCal.m_days[otherDayPos].checkMeeting(startTime, meetingLength))
					{
						m_days[i].pushMeeting(Meeting(startTime, startTime + meetingLength, name, note));
						otherCal.m_days[otherDayPos].pushMeeting(Meeting(startTime, startTime + meetingLength, name, note));
						otherCal.save(otherFile);
						return;
					}
				}
			}
		}
	}
	sortDays();
	otherCal.sortDays();
	Date newDate = m_days[m_size - 1].getDate();
	newDate.nextDay();
	startTime = 800;
	otherDayPos = otherCal.findDay(newDate);
	while (otherDayPos != 0xffffffff && otherCal.m_days[otherDayPos].checkMeeting(startTime, meetingLength) == false)
	{
		newDate.nextDay();
		otherDayPos = otherCal.findDay(newDate);
	}
	if (otherDayPos == 0xffffffff)
	{
		pushDay(Day(newDate, Meeting(startTime, startTime + meetingLength, name, note)));
		otherCal.pushDay(Day(newDate, Meeting(startTime, startTime + meetingLength, name, note)));
		otherCal.save(otherFile);
	}
	else
	{
		pushDay(Day(newDate, Meeting(startTime, startTime + meetingLength, name, note)));
		otherCal.m_days[otherDayPos].pushMeeting(Meeting(startTime, startTime + meetingLength, name, note));
		otherCal.save(otherFile);
	}
}

void Calendar::merge()
{
	Calendar otherCal;
	std::string otherFile;
	otherCal.open(otherFile);

	sortDays();
	otherCal.sortDays();

	size_t thisCalSize = m_size;
	size_t otherDayPos = 0;
	size_t choice = 0;
	for (size_t i = 0; i < thisCalSize; i++)
	{
		for (otherDayPos; otherDayPos < otherCal.m_size; otherDayPos++)
		{
			if (m_days[i].getDate() >= otherCal.m_days[otherDayPos].getDate())
			{
				if (m_days[i].getDate() == otherCal.m_days[otherDayPos].getDate())
				{
					if (m_days[i].getIsWeekend())
					{
						m_days[i] = otherCal.m_days[otherDayPos];
					}
					else
					{
						if (!otherCal.m_days[otherDayPos].getIsWeekend())
						{
							mergeDays(i, otherCal.m_days[otherDayPos]);
						}
					}
				}
				else
				{
					pushDay(otherCal.m_days[otherDayPos]);
				}
			}
			else
			{
				break;
			}
		}
	}
	for (otherDayPos; otherDayPos < otherCal.m_size; otherDayPos++)
	{
		pushDay(otherCal.m_days[otherDayPos]);
	}
}
