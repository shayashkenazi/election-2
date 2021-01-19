#pragma once
#include <stdexcept>

class CitizenAlreadyExistsException : public std::logic_error
{
public:
	CitizenAlreadyExistsException() :logic_error("this citizen's id already exist.") {}
};

class WrongCountyNumException : public std::logic_error
{
public:
	WrongCountyNumException() :logic_error("citizen's county num is invalid. ") {}
};
class WrongIdException : public std::logic_error
{
public:
	WrongIdException() :logic_error("citizen's id is invalid. ") {}
};
class WrongYearDateException : public std::logic_error
{
public:
    WrongYearDateException() :logic_error("invalid year.please select year bigger then 0") {}
};
class WrongMonthDateException : public std::logic_error
{
public:
    WrongMonthDateException() :logic_error("invalid month. please select month between 1-12") {}
};
class WrongDayDateException : public std::logic_error
{
public:
    WrongDayDateException() :logic_error("invalid day. please select day between the specific days of month") {}
};
class OpenFileException : public std::logic_error
{
public:
    OpenFileException() :logic_error("error opening file") {}
};

class WrongPartyIndexException : public std::logic_error
{
public:
    WrongPartyIndexException() :logic_error("invalid party index entered.") {}
};

class CitizenAleardyVotedException : public std::logic_error
{
public:
    CitizenAleardyVotedException() :logic_error("citizen is aleardy voted.") {}
};

class LeadCandAsRepException : public std::logic_error
{
public:
    LeadCandAsRepException() :logic_error("lead candidate can't be a represenative.") {}
};
class NumOfRepInvalidException : public std::logic_error
{
public:
    NumOfRepInvalidException() :logic_error("num of represenative's is invalid.") {}
};
class NoCountyInSimpleElectionException : public std::logic_error
{
public:
    NoCountyInSimpleElectionException() :logic_error("its not possible to add County At simple election.") {}
};

