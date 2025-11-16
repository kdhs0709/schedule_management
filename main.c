#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "lecture.h"

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;

    while (1) {
        printf("\n==== 메인 메뉴 ====\n");
        printf("1. 계정 생성\n");
        printf("2. 로그인\n");
        printf("3. 전체 강의 목록 보기\n");
        printf("4. 종료\n");
        printf("입력: ");
        
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                if (loginAccount()) {
                    printf("\n>> 로그인 성공!\n");
                } else {
                    printf("\n>> 로그인 실패!\n");
                }
                break;

            case 3:
                loadLectures("subData.csv");
                printLectures();
                break;

            case 4:
                printf("\n프로그램 종료.\n");
                return 0;

            default:
                printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}
