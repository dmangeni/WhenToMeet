#include <iostream>
#include<string>
#include <vector>
#include <sstream>
#include "Person.h"
#include"Meetings.h"

using namespace std;
Meeting::Meeting(string n, int d)
{
	//duration is in minutes
	name = n;
	duration = d;
	scheduleFiller();
	setTimeLimits("8:00am", "5:00pm");
}
void Meeting::setTimeLimits(string s, string e)
{
	startLimit = s;
	endLimit = e;
}
void Meeting::addPerson(Person &p)
{
	members.push_back(p);
}
void Meeting::scheduleFiller()
{
	//Assuming the masterschedule times are initially set to true
	//Vector of time slots is also
	for (int day = 0; day <= 5; day++)
	{
		vector<bool>temp;
		meetingSchedule.push_back(temp);

		vector<int>counter;
		timeSlots.push_back(counter);

		startTimeSlots.push_back(counter); //These will store the available time slots for everyone
		endTimeSlots.push_back(counter);

		for (int slot = 0; slot <= 96; slot++)
		{
			meetingSchedule[day].push_back(false);
			timeSlots[day].push_back(0);
		}
	}
}
void Meeting::getMeetingTimeSlots()
{
	//Using the two vectors which has slots for each person's
	//available times we can get the times they can all meet
	for (int i = 0; i < members.size(); i++)
	{
		//loop through each members available time slots
		members[i].getAvailableTimesSlots();
		for (int j = 0; j < members[i].getStartTime().size(); j++)
		{
			for (int k = 0; k < members[i].getStartTime()[j].size(); k++)
			{
				//pushback the starttimes and endtimes of each member's available time
				int s = members[i].getStartTime()[j][k]; //a member's available starting time slot
				int e = members[i].getEndTime()[j][k];
				//Loop through the timeSlots to update the  number of times a particular time slot appears
				//for example if member one's time is from slot one to 19 increase the counter
				for (int l = s; l <= e; l++)
				{
					timeSlots[j][l]++;
				}
			}
		}
	}
	//Update the meeting schedule to the times that all members can meet
	for (int i = 0; i < timeSlots.size(); i++)
	{
		for (int j = 0; j < timeSlots[i].size(); j++)
		{
			if (timeSlots[i][j] == members.size())
			{
				meetingSchedule[i][j] = true;
			}
		}
	}
}
void Meeting::getSlotsForAllMembers()
{
	getMeetingTimeSlots();
	//Assuming the first slot will always be false, get the slots for available times
	for (int i = 0; i < meetingSchedule.size(); i++)
	{
		for (int j = 0; j < meetingSchedule[i].size() - 1; j++)
		{
			if (meetingSchedule[i][j] == false && meetingSchedule[i][j + 1] == true)
			{
				startTimeSlots[i].push_back(j + 1);
			}
			else if (meetingSchedule[i][j] == true && meetingSchedule[i][j + 1] == false)
			{
				endTimeSlots[i].push_back(j);
			}
		}
	}
}
void Meeting::checkLimits()
{
	getSlotsForAllMembers();
	//Get the slot for the meeting start and endlimits.
	int f = members[0].getTimeSlot(getStartLimit());//32
	int l = members[0].getTimeSlot(getEndLimit());//68

	//Check whether the available times are within the meeting start and end limits
	for (int i = 0; i < startTimeSlots.size(); i++)
	{
		if (!(startTimeSlots.empty() || endTimeSlots[i].empty()))
		{
			for (int j = 0; j < startTimeSlots[i].size(); j++)
			{
				//A meeting cant start earlier or later than the stated times
				if (startTimeSlots[i][j] < f)
				{
					startTimeSlots[i][j] = f;
				}
				else if (startTimeSlots[i][j] >= l)
				{
					startTimeSlots[i][j] = 0;
					endTimeSlots[i][j] = 0;
				}
				if (endTimeSlots[i][j] <= f)
				{
					startTimeSlots[i][j] = 0;
					endTimeSlots[i][j] = 0;
				}
				else if (endTimeSlots[i][j] >= l)
				{
					endTimeSlots[i][j] = l;
				}
				
			}
		}
	}
}
void Meeting::printMembers()
{
	cout << "The following are the members:" << endl;
	for (int i = 0; i < members.size(); i++)
	{
		cout << members[i].getname() << endl;
	}
	cout << "\n\n";
}
void Meeting::checkDuration()
{
	checkLimits();
	printMembers();
	cout << duration << " minutes meeting with time limits starting from ";
	cout << getStartLimit() << " to " << getEndLimit() << endl;
	cout << "has the following times:\n\n";
	
	int timeslots = duration / 15;
	Person k("UsingYouToaccessThePersonsMethods");
	if (startTimeSlots.empty() && endTimeSlots.empty())
	{
		cout << "There are no available meeting times on all days";
	}
	else
	{
		for (int i = 1; i < startTimeSlots.size(); i++)
		{
			if (!(startTimeSlots[i].empty() && endTimeSlots[i].empty()))
			{
				for (int j = 0; j < startTimeSlots[i].size(); j++)
				{
					//Check only the days and slots where there are available slots and it is not zero
					if (!(startTimeSlots[i][j] == 0 && endTimeSlots[i][j] == 0))
					{
						int times = endTimeSlots[i][j] - startTimeSlots[i][j];//4
						if (times < timeslots)
						{
							cout << "There are no available meeting times for all members on: " << k.getDays()[i] << endl;
							cout << "\n";
							//Set the particular slot to zero
							startTimeSlots[i][j] = 0;
							endTimeSlots[i][j] = 0;
						}
					}
				}
			}
			else
			{
				cout << "There are no available meeting times on: " << k.getDays()[i] << endl;
			}
		}
	}
}
void Meeting::printTimes()
{
	checkDuration();
	cout << "There are available meeting times on :\n" << endl;
	for (int i = 0; i < startTimeSlots.size(); i++)
	{
		if (!(startTimeSlots[i].empty()))
		{
			for (int j = 0; j < startTimeSlots[i].size(); j++)
			{
				//Print out the times the available slots that are not zeroed
				if (startTimeSlots[i][j] == 0 && endTimeSlots[i][j] == 0)
					continue;
				else
				{
					cout << members[0].getDays()[i] << "  " << members[0].slotToHour(startTimeSlots[i][j]) << ":";
					cout << members[0].slotToMinutes(startTimeSlots[i][j]) << members[0].amchecker(startTimeSlots[i][j]) << " ";

					cout << "to" << "  " << members[0].slotToHour(endTimeSlots[i][j]) << ":";
					cout << members[0].slotToMinutes(endTimeSlots[i][j]) << members[0].amchecker(endTimeSlots[i][j]) << endl;
				}
			}
		}
	}
}
string Meeting::getStartLimit()
{
	return startLimit;
}
string Meeting::getEndLimit()
{
	return endLimit;
}

