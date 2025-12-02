#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "lecture.h"
#include "selection.h"

int dayIndex(char d);
void parseTime(const char* timeStr, int table[5][10]);
void printTimetable(const Basket* b);
int hasTimeConflict(const Basket* b, const Lecture* lec);

#endif
