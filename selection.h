#ifndef SELECTION_H
#define SELECTION_H

#include "lecture.h"

typedef struct {
    Lecture list[MAX_SUBJECT];
    int count;
    double remainCredit;
} Basket;

void initBasket(Basket *b);
int addSubject(Basket *b, Lecture lec);
void printSelected(Basket *b);

#endif
