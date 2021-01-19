#pragma once
#include <stdexcept>

class ExceptionCitizenAlreadyExists : public std::logic_error
{
public:
	ExceptionCitizenAlreadyExists() :logic_error("this citizen's id already exist.") {}
};

class ExceptionWrongCountyNum : public std::logic_error
{
public:
	ExceptionWrongCountyNum() :logic_error("citizen's county num is invalid. ") {}
};
class ExceptionWrongId : public std::logic_error
{
public:
	ExceptionWrongId() :logic_error("citizen's id is invalid. ") {}
};
class ExceptionwrnogYearDate : public std::logic_error
{
public:
    ExceptionwrnogYearDate() :logic_error("invalid year.please select year bigger then 0") {}
};
class ExceptionwrnogMonthDate : public std::logic_error
{
public:
    ExceptionwrnogMonthDate() :logic_error("invalid month. please select month between 1-12") {}
};
class ExceptionwrnogDayDate : public std::logic_error
{
public:
    ExceptionwrnogDayDate() :logic_error("invalid day. please select day between the specific days of month") {}
};
class ExceptionOpenFile : public std::logic_error
{
public:
    ExceptionOpenFile() :logic_error("error opening file") {}
};

