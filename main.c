#include <stdio.h>
#include "account.h"
#include "lecture.h"
#include "selection.h"

int main() {
    Account acc;
    Lecture lectures[200];
    Basket basket;

    int choice;

    printf("===== 수강신청 시스템 =====\n");
    printf("1. 계정 생성\n");
    printf("2. 로그인\n");
    printf("선택: ");
    scanf("%d", &choice);

    if(choice == 1) createAccount();
    if(!login(&acc)) {
        printf("[오류] 로그인 실패\n");
        return 0;
    }

    printf("\n\n[로그인 성공] %s님 환영합니다.\n", acc.name);

    int cnt = loadLectures(lectures);
    initBasket(&basket);

    while(1) {
        printf("\n=== 메뉴 ===\n");
        printf("1. 전체 강의 조회\n");
        printf("2. 수강 신청\n");
        printf("3. 신청 목록 보기\n");
        printf("4. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        if(choice == 1)
            printLectures(lectures, cnt);

        else if(choice == 2) {
            int n;
            printLectures(lectures, cnt);
            printf("신청할 번호: ");
            scanf("%d", &n);
            addSubject(&basket, lectures[n-1]);
        }

        else if(choice == 3)
            printSelected(&basket);

        else if(choice == 4)
            break;
    }
}
