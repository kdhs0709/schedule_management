#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "dday.h"

#define SCHEDULE_FILE "personal.txt"

void showDday(void) {

    FILE* fp = fopen(SCHEDULE_FILE, "r");

    if (!fp) {
        printf("\n[일정 알림] 등록된 일정이 없습니다.\n");
        return;
    }

    printf("\n========== D-DAY 알림 ==========\n");

    char title[64];
    char date[16];
    char memo[128];

    time_t now = time(NULL);

    struct tm today = *localtime(&now);
    today.tm_hour = 0;
    today.tm_min = 0;
    today.tm_sec = 0;

    time_t tnow = mktime(&today);

    int found = 0;

    while (fscanf(fp, "%63[^|]|%15[^|]|%127[^\n]\n",
        title, date, memo) == 3) {

        int y, m, d;
        sscanf(date, "%d-%d-%d", &y, &m, &d);

        struct tm target = { 0 };
        target.tm_year = y - 1900;
        target.tm_mon = m - 1;
        target.tm_mday = d;

        time_t ttarget = mktime(&target);
        int days = (int)((ttarget - tnow) / (60 * 60 * 24));

        if (days < 0) continue;

        found = 1;

        if (days == 0)
            printf("D-DAY!  %s (%s)\n", title, memo);
        else
            printf("D-%d  %s (%s)\n", days, title, memo);
    }

    if (!found)
        printf("예정된 일정이 없습니다!\n");

    printf("=================================\n");

    fclose(fp);
}
