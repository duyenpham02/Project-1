// BloodSugar.cpp
// Duyen Pham
// COSC 2030 - 01
// Oct. 24, 2018
// Progject 1


#include <iostream>
using std::cout;
using std::endl;
using std::cin;

struct node
{
	float sumTotalBlood;
	float maxBlood;
	float minBlood;
	int entryCount;
};

const unsigned int MAX_DAYS(14);
void displayDaySummary(unsigned int day);
void displayWeekSummary(void);
node *days[MAX_DAYS];


int main()
{
	char choice;
	unsigned int cnt_day = 0;
	float data = 0.0;
	float sumBlood_day = 0.0;
	float maxBlood_day = 0.0;
	float minBlood_day = INFINITY;
	unsigned int currentDay = 0;


	for (unsigned int j = 0; j < MAX_DAYS; j++)
	{

		cout << "Enter blood sugar data for day " << j+1 << " separated by a space (enter 'q' to stop): ";
		days[j] = new node;

		while (cin >> data)
		{
			if (data > 0)
			{
				sumBlood_day += data;
				cnt_day += 1;

				if (data > maxBlood_day)
					maxBlood_day = data;

				if (data < minBlood_day)
					minBlood_day = data;

			}
		}

		days[j]->sumTotalBlood = sumBlood_day;
		days[j]->maxBlood = maxBlood_day;
		days[j]->minBlood = minBlood_day;
		days[j]->entryCount = cnt_day;
		
		// Re-int variables
		sumBlood_day = maxBlood_day = 0;
		minBlood_day = INFINITY;
		cnt_day = 0;

		cin.clear();
		cin.ignore();
	}

	
	do
	{
		cout << "Enter your command for summary ('D' for the day, 'N' for the next day, 'W' for the week): ";
		cin >> choice;

		choice = toupper(choice);

		switch (choice)
		{
		case 'D':
			displayDaySummary(currentDay);
			break;
		case 'N':
			if (currentDay == MAX_DAYS - 1) {
				currentDay = 0;
			}
			else {
				currentDay += 1;
			}
			
			displayDaySummary(currentDay);
			break;
		case 'W':
			displayWeekSummary();
			break;
		case 'Q':
			break;
		default:
			cout << "Invalid! Try again..." << endl;
		}
	} while (choice != 'Q');

	return 0;
}


void displayDaySummary(unsigned int day) {
	cout << "Day " << day + 1 << " : " << "\tSum = " << days[day]->sumTotalBlood;
	cout << "\tMax = " << days[day]->maxBlood;
	cout << "\tMin = " << days[day]->minBlood;
	cout << "\tTotal Readings =  " << days[day]->entryCount << endl;
}

void displayWeekSummary(void) {
	float sumBlood_week;
	float maxBlood_week;
	float minBlood_week;
	unsigned int max_delta, day_max_delta;
	unsigned int day_day_delta;
	unsigned int cnt_week;

	for (unsigned int j = 0; j < 2; j++)
	{
		cnt_week = 0;
		max_delta = day_max_delta = day_day_delta = 0;
		sumBlood_week = 0;
		maxBlood_week = days[7*j]->maxBlood;
		minBlood_week = days[7*j]->minBlood;

		for (unsigned int i = 7*j; i < 7*(j+1); i++)
		{
			sumBlood_week += days[i]->sumTotalBlood;

			if (days[i]->maxBlood > maxBlood_week)
				maxBlood_week = days[i]->maxBlood;

			if (days[i]->minBlood < minBlood_week)
				minBlood_week = days[i]->minBlood;

			cnt_week += days[i]->entryCount;

			if (i != 7 * j)
				day_day_delta = abs(days[i]->entryCount - days[i - 1]->entryCount);
			if (max_delta < day_day_delta) {
				max_delta = day_day_delta;
				day_max_delta = i + 1;
			}
		}

		cout << "Week " << j + 1 << " : " << "\tSum = " << sumBlood_week;
		cout << "\tMax = " << maxBlood_week;
		cout << "\tMin = " << minBlood_week;
		cout << "\tTotal Readings =  " << cnt_week;
		cout << "\tDay with biggest Delta = " << day_max_delta << endl;

	}
}



