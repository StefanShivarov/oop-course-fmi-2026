#include <iostream>
#include <print>
#include <string>
using namespace std;

class Time
{
private:
	int hours;
	int minutes;
	int seconds;
public:
	void setHours(int h)
	{
		if (h > 23)
			println("Hours can't be more than 23!");
		else
			hours = h;
	}
	void setMinutes(int m)
	{
		if (m > 59)
			println("Minutes can't be more than 59!");
		else
			minutes = m;
	}
	void setSeconds(int s)
	{
		if (s > 59)
			println("Seconds can't be more than 59!");
		else
			seconds = s;
	}
	string getTimeAsString() const
	{
		string s = "00:00:00";
		s[0] = hours / 10 + '0';
		s[1] = hours % 10 + '0';
		s[3] = minutes / 10 + '0';
		s[4] = minutes % 10 + '0';
		s[6] = seconds / 10 + '0';
		s[7] = seconds % 10 + '0';
		return s;
	}
	int toSeconds() const
	{
		return hours * 3600 + minutes * 60 + seconds;
	}
	void addSeconds(int delta)
	{
		seconds += delta;
		if (seconds > 59)
		{
			minutes += seconds / 60;
			seconds = seconds % 60;
		}
		if (minutes > 59)
		{
			hours += minutes / 60;
			minutes = minutes % 60;
		}
		if (hours > 23)
		{
			hours = hours % 24;
		}
	}
	bool isBefore(const Time& other) const
	{
		return toSeconds() < other.toSeconds();
	}
	bool isAfter(const Time& other) const
	{
		return toSeconds() > other.toSeconds();
	}
	Time()
	{
		hours = 0;minutes = 0;seconds = 0;
	}
	Time(string t)
	{
		hours = (t[0] - '0') * 10 + t[1] - '0';
		minutes = (t[3] - '0') * 10 + t[4] - '0';
		seconds = (t[6] - '0') * 10 + t[7] - '0';
		if (seconds > 59)
		{
			println("Converting excess seconds to minutes");
			minutes += seconds / 60;
			seconds = seconds % 60;
		}
		if (minutes > 59)
		{
			println("Converting excess minutes to hours");
			hours += minutes / 60;
			minutes = minutes % 60;
		}
		if (hours > 23)
		{
			println("Going to the next day");
			hours = hours % 24;
		}
	}
};

enum Weekday
{
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};
enum class Subject
{
	OOP,
	DIS2,
	DSTR2,
	English,
	Geometry,
};
string weekdayToStr(Weekday day)
{
	switch (day)
	{
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	case 7:
		return "Sunday";
	default:
		return "Unknown day";
	}
}
Weekday intToWeekday(int x)
{
	switch (x)
	{
	case 1:
		return Monday;
	case 2:
		return Tuesday;
	case 3:
		return Wednesday;
	case 4:
		return Thursday;
	case 5:
		return Friday;
	case 6:
		return Saturday;
	case 7:
		return Sunday;
	default:
		println("Issue converting int to weekday!");
		return Monday;
	}
}
string subjectToStr(Subject sbj)
{
	switch (sbj) 
	{
	case Subject::OOP:
		return "OOP";
	case Subject::DIS2:
		return "DIS2";
	case Subject::DSTR2:
		return "DSTR2";
	case Subject::English:
		return "English";
	case Subject::Geometry:
		return "Geometry";
	default:
		return "Unknown sbj";
	}
}
Subject strToSubject(string s)
{
	if (s == "OOP") return Subject::OOP;
	if (s == "DIS2") return Subject::DIS2;
	if (s == "DSTR2") return Subject::DSTR2;
	if (s == "English") return Subject::English;
	if (s == "Geometry") return Subject::Geometry;
	return Subject::OOP;
}
struct StudySession
{
	Weekday day;
	Subject subj;
	string classroom;
	Time startTime;
	Time endTime;
	void printSession()
	{
		println("{} from:{} - to:{}, subject:{}, classroom:{}", weekdayToStr(day), startTime.getTimeAsString(), endTime.getTimeAsString(), subjectToStr(subj), classroom);
	}

	StudySession() = default;
	StudySession(Weekday d, string room, Subject s, Time start, Time end)
	{
		day = d;
		classroom = room;
		subj = s;
		startTime = start;
		endTime = end;
	}
};
class Schedule
{
private:
	StudySession* sessions = new StudySession[100];
	int count = 0;
public:
	~Schedule()
	{
		delete[] sessions;
	}
	bool addSession(StudySession s)
	{
		if (count >= 100)
		{
			println("Schedule is full!");
			return false;
		}
		for (int i = 0;i < count;i++)
		{
			if (s.day == sessions[i].day && s.classroom == sessions[i].classroom && s.startTime.isBefore(sessions[i].endTime) && sessions[i].startTime.isBefore(s.endTime))
			{
				println("Classes overlap can't add to schedule!");
				return false;
			}
		}
		sessions[count++] = s;
		println("Class successfully added to schedule!");
		return true;
	}
	void filterByClassroom(string crm) const
	{
		for (int i = 0;i < count;i++)
		{
			if (sessions[i].classroom == crm)
			{
				sessions[i].printSession();
			}
		}
	}
	void filterByDay(Weekday dayWanted) const
	{
		for (int i = 0;i < count;i++)
		{
			if (sessions[i].day == dayWanted)
			{
				sessions[i].printSession();
			}
		}
	}
};
int main()
{
	Schedule schedule;
	println("How many classes will you enter");
	int n;
	cin >> n;
	cin.ignore();
	string day, room, subj, start, end;
	for (int i = 0;i < n;i++)
	{
		println("Enter class {} (format: DayNum,Room,Subject,Start,End):", i + 1);
		getline(cin, day, ',');
		getline(cin, room, ',');
		getline(cin, subj, ',');
		getline(cin, start, ',');
		getline(cin, end);
		Weekday weekday = intToWeekday(day[0] - '0');
		Subject subject = strToSubject(subj);
		Time startTime(start);
		Time endTime(end);
		StudySession session(weekday, room, subject, startTime, endTime);
		schedule.addSession(session);
	}
	println("\n\nFilter by classroom\nEnter classroom name:");
	string clRoom;
	getline(cin, clRoom);
	schedule.filterByClassroom(clRoom);
	println("\n\nFilter by weekday\nEnter weekday number:");
	int x;
	cin >> x;
	Weekday dayForFilter = intToWeekday(x);
	schedule.filterByDay(dayForFilter);
}
