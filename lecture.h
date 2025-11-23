#ifndef LECTURE_H
#define LECTURE_H

#include "util.h"

typedef struct {
    char code[30];
    char name[50];
    char prof[50];
    char time[50];
    double credit;
} Lecture;

int loadLectures(Lecture arr[]);
void printLectures(Lecture arr[], int n);

#endif
