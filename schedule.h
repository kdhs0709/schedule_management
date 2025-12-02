#ifndef SCHEDULE_H
#define SCHEDULE_H

#define MAX_SCHEDULE 100

typedef struct {
	char title[64];
	char date[16];
	char memo[128];
} Schedule;

typedef struct {
	Schedule list[MAX_SCHEDULE];
	int count;
} ScheduleManager;

void loadSchedule(ScheduleManager* sm);
void saveSchedule(ScheduleManager* sm);

void addSchedule(ScheduleManager* sm);
void removeSchedule(ScheduleManager* sm);
void printSchedule(const ScheduleManager* sm);
void showUpcoming(const ScheduleManager* sm);

#endif
