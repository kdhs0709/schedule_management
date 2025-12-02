#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "schedule.h"

void saveSchedule(ScheduleManager* sm) {
    FILE* fp = fopen("personal.txt", "w");
    if (!fp) return;

    for (int i = 0; i < sm->count; i++) {
        fprintf(fp, "%s|%s|%s\n",
            sm->list[i].title,
            sm->list[i].date,
            sm->list[i].memo);
    }
    fclose(fp);
}

void loadSchedule(ScheduleManager* sm) {
    FILE* fp = fopen("personal.txt", "r");
    sm->count = 0;
    if (!fp) return;

    while (fscanf(fp, "%63[^|]|%15[^|]|%127[^\n]\n",
        sm->list[sm->count].title,
        sm->list[sm->count].date,
        sm->list[sm->count].memo) == 3) {

        sm->count++;
        if (sm->count >= MAX_SCHEDULE) break;
    }

    fclose(fp);
}

void addSchedule(ScheduleManager* sm) {

    if (sm->count >= MAX_SCHEDULE) {
        printf("더 이상 일정 추가 불가.\n");
        return;
    }

    Schedule s;
    printf("일정 제목: "); gets(s.title);
    printf("날짜 (YYYY-MM-DD): "); gets(s.date);
    printf("메모: "); gets(s.memo);

    sm->list[sm->count++] = s;
    saveSchedule(sm);

    printf("[추가 완료]\n");
}

void removeSchedule(ScheduleManager* sm) {

    if (sm->count == 0) {
        printf("[일정 없음]\n");
        return;
    }

    printSchedule(sm);

    int num;
    printf("삭제할 번호 입력: ");
    scanf("%d", &num); getchar();

    if (num < 1 || num > sm->count) return;

    for (int i = num - 1; i < sm->count - 1; i++) {
        sm->list[i] = sm->list[i + 1];
    }

    sm->count--;
    saveSchedule(sm);

    printf("[삭제 완료]\n");
}

void printSchedule(const ScheduleManager* sm) {

    printf("\n[개인 일정]\n");

    for (int i = 0; i < sm->count; i++) {
        printf("%2d. %s | %s | %s\n",
            i + 1,
            sm->list[i].date,
            sm->list[i].title,
            sm->list[i].memo);
    }
}

void showUpcoming(const ScheduleManager* sm) {

    time_t now = time(NULL);
    struct tm* today = localtime(&now);

    printf("\n[임박 일정]\n");

    for (int i = 0; i < sm->count; i++) {

        struct tm t = { 0 };
        sscanf(sm->list[i].date, "%d-%d-%d",
            &t.tm_year, &t.tm_mon, &t.tm_mday);

        t.tm_year -= 1900;
        t.tm_mon -= 1;

        double diff = difftime(mktime(&t), now) / (60 * 60 * 24);

        if (diff >= 0 && diff <= 3) {
            printf("⚠ %s (%s)\n", sm->list[i].title, sm->list[i].date);
        }
    }
}
