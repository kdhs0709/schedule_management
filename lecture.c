#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"

#define MAX_LECTURES 200

Lecture lectureList[MAX_LECTURES];
int lectureCount = 0;

void loadLectures(const char *filename) {
    lectureCount = 0;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("강의 데이터 파일을 읽을 수 없습니다.\n");
        return;
    }

    while (!feof(fp) && lectureCount < MAX_LECTURES) {
        Lecture *lec = &lectureList[lectureCount];

        fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lf\n",
               lec->code, lec->name, lec->professor,
               lec->time, lec->room, &lec->grade, &lec->credit);

        lectureCount++;
    }

    fclose(fp);
}

void printLectures() {
    printf("\n==== 전체 강의 목록 ====\n");
    for (int i = 0; i < lectureCount; i++) {
        Lecture *lec = &lectureList[i];
        printf("[%d] %s | %s | %s | %s | %d학년 | %.1f학점\n",
               i + 1,
               lec->code, lec->name,
               lec->professor, lec->time,
               lec->grade, lec->credit);
    }
    printf("==========================\n");
}
