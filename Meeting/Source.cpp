#include <iostream>
#include<string>
#include <vector>
#include <sstream>
#include"Person.h"
#include"Meetings.h"
using namespace std;

void loadData(Meeting &m);

int main()
{
	Meeting m("Sure", 45);
	loadData(m);
	m.printTimes();

	system("pause");
	return 0;
}
void loadData(Meeting &m)
{
	//For efficiency purposes use either addBusyTime or addFreeTime per day but not 
	//both on the same day
	//The program is case sensitive. please enter in lowercase. To get the available times
	//as you add. Load one at a time and run

	Person f("Ashley");
	f.addBusyTime("monday", "5:00am", "8:45am");
	f.addBusyTime("wednesday", "9:45pm", "10:30pm");
	f.addFreeTime("tuesday", "1:00pm", "5:00pm");
	f.addFreeTime("friday", "2:00pm", "5:00pm");
	m.addPerson(f);
	
	Person s("Mark");
	s.addFreeTime("monday", "8:00am", "10:00am");
	s.addBusyTime("wednesday", "9:00am", "12:00");
	s.addBusyTime("tuesday", "3:00pm", "5:00pm");
	s.addBusyTime("friday", "1:00pm", "2:00pm");
	m.addPerson(s);
	
	Person t("Lindsay");
	t.addFreeTime("thursday", "8:00am", "9:45am");
	t.addBusyTime("monday", "8:00pm", "12:00midnight");
	t.addFreeTime("tuesday", "2:00pm", "4:15pm");
	t.addFreeTime("friday", "1:00pm", "2:00pm");
	m.addPerson(t);
}