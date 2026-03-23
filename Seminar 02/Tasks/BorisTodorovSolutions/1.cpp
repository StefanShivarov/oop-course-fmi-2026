#include <iostream>
#include <fstream>
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
			minutes+= seconds / 60;
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

void swapTimes(Time& t1,Time& t2)
{
	Time temp = t1;
	t1 = t2;
	t2 = temp;
}
void sortFile(string fileName)
{
	ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		println("Error opening file!");
		return;
	}
	int n = 0;
	string currLine;
	while (getline(inFile, currLine))
	{
		n++;
	}
	inFile.close();
	if (n == 0)
	{
		cout << "The file is empty!";
		return;
	}
	else if (n == 1)
	{
		cout << "Only one time in file!";
		return;
	}
	Time* times = new Time[n];
	inFile.open(fileName);
	int currentIndex = 0;
	while (getline(inFile, currLine))
	{
		times[currentIndex] = Time(currLine);
		currentIndex++;
	}
	inFile.close();
	bool swapped;
	for (int i = 0;i < n - 1;i++)
	{
		swapped = false;
		for (int j = 0;j < n - i - 1;j++)
		{
			if (times[j].isAfter(times[j + 1]))
			{
				swapTimes(times[j], times[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
	ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		println("Error opening file for writing!");
		return;
	}
	for (int i = 0;i < n;i++)
	{
		outFile << times[i].getTimeAsString() << "\n";
	}
	outFile.close();
	delete[] times;
}
int main()
{
	sortFile("times.txt");
}