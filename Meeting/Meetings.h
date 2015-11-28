#pragma once
#include <iostream>
#include<string>
#include <vector>
#include <sstream>
#include "Person.h"

using namespace std;

class Meeting
{
public:
	Meeting(string n, int d);
	void setTimeLimits(string s, string e);
	void addPerson(Person &p);
	void scheduleFiller();
	void getMeetingTimeSlots();
	void getSlotsForAllMembers();
	void checkLimits();
	void checkDuration();
	void printMembers();
	void printTimes();
	string getStartLimit();
	string getEndLimit();


private:
	vector<Person>members;
	vector<vector<bool>>meetingSchedule;
	vector<vector<int>>timeSlots;

	vector<vector<int>>startTimeSlots; //Stores the slots for all members possible meeting times
	vector<vector<int>>endTimeSlots;

	string name;
	string startLimit;
	string endLimit;
	int duration;

};