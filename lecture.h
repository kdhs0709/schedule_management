#ifndef LECTURE_H
#define LECTURE_H

#define _CRT_SECURE_NO_WARNINGS

#define MAX_LECTURES 512 

typedef struct {
	char code[32];       
	char name[64];       
	char professor[64];  
	char time[32];       
	double credit;       
} Lecture;

int loadLectures(const char* filename, Lecture* arr, int max);
void printLectures(const Lecture* arr, int count);
void printLecturesPaged(const Lecture* arr, int count);
void printLecturesByCategory(const Lecture* arr, int count);
int selectLecturePaged(const Lecture* arr, int count);

#endif
