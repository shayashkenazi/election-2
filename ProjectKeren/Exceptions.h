#pragma once
#include <stdexcept>


class ExceptionCitizenAlreadyExists : public std::logic_error
{
public:
	ExceptionCitizenAlreadyExists() :logic_error("this citizen's id already exist.") {}
};

class ExceptionWringCountyNum : public std::logic_error
{
public:
	ExceptionWringCountyNum() :logic_error("citizen's county num is invalid. ") {}
};
class ExceptionWrongId : public std::logic_error
{
public:
	ExceptionWrongId() :logic_error("citizen's id is invalid. ") {}
};
