#include"DateTime.h"

CurrentDateTime::CurrentDateTime()
{
	//fetch/store current local-daytime information
	auto tp = std::chrono::system_clock::now();
	time_t cstyle_t = std::chrono::system_clock::to_time_t(tp);
	char* cstyleinfo = std::ctime(&cstyle_t);
	// copy(deep) the data into the std::string as ::ctime() provides static data 
	// which might be overwritten in case someone call it again.
	std::string currentinfo{ cstyleinfo };

	//parse/store  the information
	auto dtstr = ParseDateTime(currentinfo);
	StrToNumber(dtstr);
}


DayTime<std::string> CurrentDateTime::ParseDateTime(const std::string& information)
{
	DayTime<std::string> info;
	std::regex dtimeregex{ R"(^(\w{3}) (\w{3}) (\d{2}) (\d{2}):(\d{2}):(\d{2}) (\d{4})$)" };
	std::smatch match;

	if (std::regex_search(information, match, dtimeregex)) {
		// Match the group and subgroups by regex parser.
		auto index = 0;
		info.dtstring = match[index++];
		info.daystr = match[index++];
		info.month = match[index++];
		info.day = match[index++];
		info.hour = match[index++];
		info.min = match[index++];
		info.second = match[index++];
		info.year = match[index++];
	}
	return info;
}


void CurrentDateTime::StrToNumber(const DayTime<std::string>& information)
{
	dt.dtstring = information.dtstring;
	dt.daystr = information.daystr;
	dt.day = std::stoi(information.day);
	dt.hour = std::stoi(information.hour);
	dt.min = std::stoi(information.min);
	dt.second = std::stoi(information.second);
	dt.year = std::stoi(information.year);

	GetMonthFromStr(dt.month, information.month);
}


void CurrentDateTime::GetMonthFromStr(int& m, const std::string& input) {
	for (const auto& itr : monthinfo) {
		if (itr.first == input)
			m = itr.second;
	}
}

