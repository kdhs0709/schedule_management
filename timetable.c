#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "timetable.h"

int dayIndex(char d) {
    switch (d) {
    case 'M': return 0;
    case 'T': return 1;
    case 'W': return 2;
    case 'R': return 3;
    case 'F': return 4;
    default:  return -1;
    }
}


void parseTime(const char* timeStr, int table[5][10]) {

    char buf[256];
    strcpy(buf, timeStr);

    char* token = strtok(buf, "/");

    while (token != NULL) {

        while (*token == ' ' || *token == '\t')
            token++;

        char day = token[0];
        int d = dayIndex(day);

        if (d == -1) {
            token = strtok(NULL, "/");
            continue;
        }

        int start = 0, end = 0;
        int i = 1;

        while (isdigit((unsigned char)token[i])) {
            start = start * 10 + (token[i] - '0');
            i++;
        }

        if (token[i] == '-') {
            i++;
            while (isdigit((unsigned char)token[i])) {
                end = end * 10 + (token[i] - '0');
                i++;
            }
        }
        else {
            end = start;
        }

        if (start >= 1 && start <= 9 && end >= 1 && end <= 9) {
            for (int t = start; t <= end; t++) {
                table[d][t] = 1;
            }
        }

        token = strtok(NULL, "/");
    }
}


// ✅ 시간표 출력
void printTimetable(const Basket* b) {

    int table[5][10] = { 0 };

    for (int i = 0; i < b->count; i++) {
        parseTime(b->list[i].time, table);
    }

    system("cls");

    printf("\n========== 나의 시간표 ==========\n\n");
    printf("       월    화    수    목    금\n");
    printf("---------------------------------\n");

    for (int t = 1; t <= 9; t++) {
        printf("%d교시 ", t);
        for (int d = 0; d < 5; d++) {
            printf(table[d][t] ? "  ■  " : "  □  ");
        }
        printf("\n");
    }

    printf("\n■ : 수업 있음   □ : 비어있음\n");
    printf("=================================\n");
    system("pause");
}


// ✅ 시간 충돌 검사
int hasTimeConflict(const Basket* b, const Lecture* lec) {

    int newTable[5][10] = { 0 };
    parseTime(lec->time, newTable);

    for (int i = 0; i < b->count; i++) {

        int exist[5][10] = { 0 };
        parseTime(b->list[i].time, exist);

        for (int d = 0; d < 5; d++) {
            for (int t = 1; t <= 9; t++) {
                if (newTable[d][t] && exist[d][t])
                    return 1;
            }
        }
    }

    return 0;
}
