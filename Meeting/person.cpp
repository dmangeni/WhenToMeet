#include <iostream>
#include<string>
#include <vector>
#include <sstream>
#include "Person.h"

using namespace std;

Person::Person(string firstname)
{
	name = firstname;
	daysfiller();
	initiallizer();
}
void Person::addFreeTime(string d, string s, string e)
{
	//Set the stipulated time in a person's schedule free
	int start = getTimeSlot(s);
	int end = getTimeSlot(e);

	for (int i = start; i <= end; i++)
	{
		schedule[getDaySlot(d)][i] = true;
	}
}
void Person::addBusyTime(string d, string s, string e)
{
	//Set the specified times in a person's schedule to false
	int start = getTimeSlot(s);
	int end = getTimeSlot(e);

	//Excluding midnight to four am in the morning
	for (int i = 1; i < start; i++)
	{
		schedule[getDaySlot(d)][i] = true;
	}

	for (int i = (end + 1); i < getTimeSlot("12:00midnight"); i++)
	{
		schedule[getDaySlot(d)][i] = true;
	}
}
int Person::convertDayToSlot(string day)
{
	int slot = 0; //variable to store the slot for the day in the schedule
	for (int i = 0; i < days.size(); i++)
	{
		//Checking for the stated day
		if (day == days[i])
		{
			slot = i;
		}
	}
	return slot;
}
int Person::getDaySlot(string d)
{
	return convertDayToSlot(d);
}
int Person::convertTimeToSlot(string time)
{
	//Call the converter and check if the time is am or pm
	//
	int h;
	int m = (minuteConverter(time) / 15);
	int slot;
	if (time.find("pm") != string::npos || time == "12:00midnight")
	{
		h = ((hourConverter(time) + 12) * 60) / 15;
	}
	else if (time.substr(time.length() - 2, 2) == "am")
	{
		//Makes sure from twelve noon to one is displayed as 12 since I am working 
		//with military time
		if (hourConverter(time) == 12)
		{
			if (minuteConverter(time) > 0 || minuteConverter(time) < 60)
			{
				h = 0;
			}
			else
				slot = 0;
		}
		else
			h = (hourConverter(time) * 60) / 15;
	}
	else
		h = (hourConverter(time) * 60) / 15;
	slot = h + m;
	
	return slot;
}
int Person::getTimeSlot(string t)
{
	return convertTimeToSlot(t);
}
int Person::hourConverter(string time)
{
	//with 8:45 am, we only need 8
	int pos = time.find(":");
	string hour = time.substr(0, pos);

	return stringToNumber(hour);
}
int Person::minuteConverter(string time)
{
	//with 8:45am we only need 45 for conversion
	int pos = time.find(":");
	string minutes = time.substr(pos + 1, 2);

	return stringToNumber(minutes);
}
void Person::daysfiller()
{
	days.push_back("null");
	days.push_back("monday");
	days.push_back("tuesday");
	days.push_back("wednesday");
	days.push_back("thursday");
	days.push_back("friday");
}
void Person::initiallizer()
{
	//Assuming your times are initially set to false
	for (int day = 0; day <= 5; day++)
	{
		vector<bool>temp;
		schedule.push_back(temp);

		vector<int>temp1;
		starttime.push_back(temp1);
		endtime.push_back(temp1);

		for (int slot = 0; slot <= 96; slot++)
		{
			schedule[day].push_back(false);
		}
	}
}
string Person::amchecker(int ch)
{
	string amchecker;//for including am or pm
	//Check from twelve noon since we are using the twelve hour clock to print(48)
	if (ch == getTimeSlot("12:00"))
		amchecker = "noon";
	else if (ch == getTimeSlot("12:00midnight"))
		amchecker = "midnight";
	else if (ch > getTimeSlot("12:00"))
	{
		amchecker = "pm";
	}
	else
		amchecker = "am";
	return amchecker;
}
string Person::slotToHour(int slot)
{
	int h; //declare a variable to hold the hour
	//Checking from one pm afternoon since the schedule is on a twenty four hour clock(52)
	if (slot >= getTimeSlot("1:00pm"))
	{
		h = ((slot * 15) / 60) - 12;
	}
	else
	{
		h = (slot * 15) / 60;
	}
	//ensures a double digit for a uniform output
	string displayHour; //variable to hold how hour is displayed

	if (h > 0 && h < 10)
		displayHour = "0" + numberToString(h);
	else if (h == 0)
		displayHour = "12";
	else
		displayHour = numberToString(h);
	return displayHour;
}
string Person::slotToMinutes(int slot)
{
	int m = (slot * 15) % 60;
	string displayMinutes; //variable to hold how minutes are displayed
	if (m < 10)
		displayMinutes = "0" + numberToString(m);
	else
		displayMinutes = numberToString(m);
	return displayMinutes;
}
void Person::getAvailableTimesSlots()
{
	//Assuming the first slot will always be false, get the slots for available times
	for (int i = 0; i < schedule.size(); i++)
	{
		for (int j = 0; j < schedule[i].size() - 1; j++)
		{
			if (schedule[i][j] == false && schedule[i][j + 1] == true)
			{
				starttime[i].push_back(j + 1);
			}
			else if (schedule[i][j] == true && schedule[i][j + 1] == false)
			{
				endtime[i].push_back(j);
			}
		}
	}
}
void Person::printAvailableTimes()
{
	getAvailableTimesSlots();
	//The size of starttime will always be the same as endtime
	cout << getname() << " is available on the following times: \n" << endl;
	for (int i = 0; i < starttime.size(); i++)
	{
		if (!(starttime.empty() || starttime[i].empty()))
		{
			for (int j = 0; j < starttime[i].size(); j++)
			{
				//Print out the times that are available
				cout << days[i] << "  " << slotToHour(starttime[i][j]) << ":";
				cout << slotToMinutes(starttime[i][j]) << amchecker(starttime[i][j]) << " ";

				cout << "to" << "  " << slotToHour(endtime[i][j]) << ":";
				cout << slotToMinutes(endtime[i][j]) << amchecker(endtime[i][j]) << endl;
			}
		}
	}
}
int Person::stringToNumber(string c)
{
	int result; //number which will contain the 
	stringstream convert(c);
	convert >> result;
	return result;
}
string Person::numberToString(int n)
{
	string result; //will hold the result
	ostringstream convert;
	convert << n;
	result = convert.str();
	return result;
}
string Person::getname()
{
	return name;
}
vector<vector<int>>Person::getStartTime()
{
	return starttime;
}
vector<vector<int>>Person::getEndTime()
{
	return endtime;
}
vector<string>Person::getDays()
{
	return days;
}


