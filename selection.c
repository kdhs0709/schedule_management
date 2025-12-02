#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "selection.h"

void basketLoad(Basket* b, const char* filename) {
    FILE* fp = fopen(filename, "r");
    b->count = 0;

    if (!fp) return;

    while (fscanf(fp, "%31[^,],%63[^,],%63[^,],%63[^,],%lf\n",
        b->list[b->count].code,
        b->list[b->count].name,
        b->list[b->count].professor,
        b->list[b->count].time,
        &b->list[b->count].credit) == 5) {

        b->count++;
        if (b->count >= MAX_SELECTED) break;
    }

    fclose(fp);
}

int basketSave(Basket* b, const char* filename) {
    FILE* fp = fopen(filename, "w");

    if (!fp) {
        printf("[오류] 저장 실패\n");
        return 0;
    }

    for (int i = 0; i < b->count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%.1f\n",
            b->list[i].code,
            b->list[i].name,
            b->list[i].professor,
            b->list[i].time,
            b->list[i].credit);
    }

    fclose(fp);
    return 1;
}

void basketAddLecture(Basket* b, const Lecture* lec) {

    for (int i = 0; i < b->count; i++) {
        if (!strcmp(b->list[i].code, lec->code)) {
            printf("[경고] 이미 신청한 과목입니다.\n");
            return;
        }
    }

    if (b->count >= MAX_SELECTED) {
        printf("[오류] 신청 가능 개수를 초과했습니다.\n");
        return;
    }

    b->list[b->count++] = *lec;
    printf("[완료] %s 신청됨\n", lec->name);
}

void basketPrint(const Basket* b) {

    printf("\n===== 신청 목록 =====\n");

    if (b->count == 0) {
        printf("신청한 과목이 없습니다.\n");
        return;
    }

    for (int i = 0; i < b->count; i++) {
        printf("%2d. %-12s | %-20s | %.1f학점 | %s\n",
            i + 1,
            b->list[i].code,
            b->list[i].name,
            b->list[i].credit,
            b->list[i].time);
    }
}
void basketRemoveLecture(Basket* b) {

    if (b->count == 0) {
        printf("[안내] 신청한 과목이 없습니다.\n");
        return;
    }

    basketPrint(b);

    int num;
    printf("\n취소할 과목 번호 입력 (0: 취소): ");
    scanf("%d", &num);

    if (num == 0) {
        printf("취소되었습니다.\n");
        return;
    }

    if (num < 1 || num > b->count) {
        printf("[오류] 잘못된 번호입니다.\n");
        return;
    }

    int idx = num - 1;
    Lecture removed = b->list[idx];

    for (int i = idx; i < b->count - 1; i++)
        b->list[i] = b->list[i + 1];
    b->count--;

    printf("[완료] \"%s\" 취소됨\n", removed.name);

    printf("\n[충돌 확인 로그]\n");
    int found = 0;
    for (int i = 0; i < b->count; i++) {
        if (hasTimeConflict(b, &b->list[i])) {
            printf(" - \"%s\" (%s)\n", b->list[i].name, b->list[i].time);
            found = 1;
        }
    }

    if (!found)
        printf("충돌 과목 없음\n");

    system("pause");
}
