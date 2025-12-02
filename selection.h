#ifndef SELECTION_H
#define SELECTION_H

#include "lecture.h"

#define MAX_SELECTED 50

typedef struct {
	Lecture list[MAX_SELECTED];
	int count;
} Basket;

void basketLoad(Basket* b, const char* filename);
int  basketSave(Basket* b, const char* filename);
void basketAddLecture(Basket* b, const Lecture* lec);
void  basketRemoveLecture(Basket* b);
void basketPrint(const Basket* b);

#endif
