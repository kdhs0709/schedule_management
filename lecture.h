#ifndef LECTURE_H
#define LECTURE_H

typedef struct {
    char code[30];
    char name[100];
    char professor[50];
    char time[50];
    char room[50];
    int grade;
    double credit;
} Lecture;

void loadLectures(const char *filename);
void printLectures();

#endif
