#include<iostream>
#include<string>
#include<chrono>
#include<ctime>
#include<regex>
#include<array>
#include<utility>
#include<cstdlib>

// Month Enum which starts with 1.
enum Month
{
	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

// Datastructure for string to num conversion in month(.i.e."Mar" Month to 3)
const std::array<std::pair<std::string, Month>, 12> monthinfo = {
	std::make_pair(std::string("Jan"), Month::Jan),
	std::make_pair(std::string("Feb"), Month::Feb),
	std::make_pair(std::string("Mar"), Month::Mar),
	std::make_pair(std::string("Apr"), Month::Apr),
	std::make_pair(std::string("May"), Month::May),
	std::make_pair(std::string("Jun"), Month::Jun),
	std::make_pair(std::string("Jul"), Month::Jul),
	std::make_pair(std::string("Aug"), Month::Aug),
	std::make_pair(std::string("Sep"), Month::Sep),
	std::make_pair(std::string("Oct"), Month::Oct),
	std::make_pair(std::string("Nov"), Month::Nov),
	std::make_pair(std::string("Dec"), Month::Dec)
};

// concrete daytime structure to store the data
template<typename T1, typename T2 = std::string>
struct DayTime
{
	T1 day = T1();
	T1 month = T1();
	T1 year = T1();
	T1 hour = T1();
	T1 min = T1();
	T1 second = T1();
	T2 daystr = T2();
	T2 dtstring = T2();
};


// Main class which would fetech/parse the current time and provide to the client
class CurrentDateTime
{
public:
	CurrentDateTime();
	int GetDay()            const { return dt.day; }
	int GetMonth()          const { return dt.month; }
	int GetYear()           const { return dt.year; }
	int GetHour()           const { return dt.hour; }
	int GetMin()            const { return dt.min; }
	int GetSecond()         const { return dt.second; }
	std::string GetDayStr() const { return dt.daystr; }
private:
	DayTime<std::string> ParseDateTime(const std::string&);
	void StrToNumber(const DayTime<std::string>&);
	void GetMonthFromStr(int&, const std::string&);

	DayTime<int>  dt;
};




