#pragma once
#include <iostream>
#include<string>
#include <vector>
#include <sstream>

using namespace std;
class Person
{
public:
	Person(string firstname);
	void addFreeTime(string d, string s, string e);
	void addBusyTime(string d, string s, string e);
	int hourConverter(string time);
	int minuteConverter(string time);
	void daysfiller();
	void initiallizer();
	int getTimeSlot(string t);
	int getDaySlot(string d);
	string numberToString(int n);
	int stringToNumber(string c);
	string amchecker(int ch);
	string slotToHour(int slot);
	string slotToMinutes(int slot);
	void getAvailableTimesSlots();
	void printAvailableTimes();
	string getname();
	vector<vector<int>>getStartTime();
	vector<vector<int>>getEndTime();
	vector<string>getDays();

private:
	string name;
	vector<vector<bool>>schedule;
	int convertTimeToSlot(string time);
	int convertDayToSlot(string day);
	vector<string>days;
	vector<vector<int>>starttime;
	vector<vector<int>>endtime;

};
