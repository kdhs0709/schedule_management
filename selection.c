#include <stdio.h>
#include <string.h>
#include "selection.h"

void initBasket(Basket *b) {
    b->count = 0;
    b->remainCredit = 21.5;
}

int addSubject(Basket *b, Lecture lec) {
    if(b->remainCredit < lec.credit) {
        printf("[경고] 잔여 가능 학점 부족.\n");
        return 0;
    }

    for(int i=0;i<b->count;i++) {
        if(strcmp(b->list[i].code, lec.code)==0) {
            printf("[경고] 이미 신청한 과목입니다.\n");
            return 0;
        }
    }

    b->list[b->count++] = lec;
    b->remainCredit -= lec.credit;

    printf("[성공] %s 과목이 신청되었습니다.\n", lec.name);
    return 1;
}

void printSelected(Basket *b) {
    printf("\n=== 신청한 과목 목록 ===\n");
    for(int i=0;i<b->count;i++)
        printf("%d) %s (%s)\n", i+1, b->list[i].name, b->list[i].time);

    printf("잔여 학점: %.1lf / 21.5\n\n", b->remainCredit);
}
