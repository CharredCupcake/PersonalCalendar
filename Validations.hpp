#pragma once
#include <string>
#include <exception>
#include "Date.hpp"

class Validations
{
public:

	static void ValidateDateFormat(const std::string& dateStr);
	static void ValidateDate(const std::string& yearStr, const std::string& monthStr, const std::string& dayStr);
	static void ValidateTimeFormat(const std::string& timeStr);
	static void ValidateTime(const std::string& hoursStr, const std::string& minutesStr);
	static void ValidateFileName(std::string& fileName);
};

