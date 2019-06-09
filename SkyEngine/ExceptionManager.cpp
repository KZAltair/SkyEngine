#include "ExceptionManager.h"
#include <sstream>

ExceptionManager::ExceptionManager(int line, const char * file) noexcept
	:
	line(line),
	file(file)
{
}

const char * ExceptionManager::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char * ExceptionManager::GetType() const noexcept
{
	return "SkyEngine Exception Manager";
}

int ExceptionManager::GetLine() const noexcept
{
	return line;
}

const std::string & ExceptionManager::GetFile() const noexcept
{
	return file;
}

std::string ExceptionManager::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]" << file << std::endl
		<< "[Line]" << line;
	return oss.str();
}
