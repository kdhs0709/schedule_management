#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <locale.h>
#include <stdio.h>

#include "util.h"
#include "account.h"
#include "lecture.h"
#include "selection.h"
#include "timetable.h"
#include "gradecalc.h"

int main(void) {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    const char* USER_FILE = "user.txt";
    const char* LEC_FILE = "lectures.csv";
    const char* SELECT_FILE = "selected.csv";

    Account user;
    Lecture lectures[MAX_LECTURES];
    Basket basket;

    int lectureCount = 0;
    int menu = 0;
    int running = 1;

    printf("===== 수강신청 관리 시스템 =====\n");

    while (1) {
        int first;
        printf("\n1. 계정 생성\n2. 로그인\n선택: ");
        scanf("%d", &first);
        clearInputBuffer();

        if (first == 1)
            createAccount(USER_FILE);

        if (login(USER_FILE, &user))
            break;
    }

    lectureCount = loadLectures(LEC_FILE, lectures, MAX_LECTURES);
    basketLoad(&basket, SELECT_FILE);
    loadGPA();

    printf("\n[알림] 강의 %d개 로드 완료\n", lectureCount);

    while (running) {

        printf("1. 전체 강의 보기 (페이지)\n");
        printf("2. 수강 신청\n");
        printf("3. 신청 목록\n");
        printf("4. 시간표 출력\n");
        printf("5. 학점 계산\n");
        printf("6. 계열별 강의 보기\n");
        printf("7. 수강 취소\n");
        printf("8. 저장 후 종료\n");

        scanf("%d", &menu);
        clearInputBuffer();

        switch (menu) {

        case 1:
            printLecturesPaged(lectures, lectureCount);
            break;

        case 2: {
            int index = selectLecturePaged(lectures, lectureCount);

            if (index < 0) break;

            if (hasTimeConflict(&basket, &lectures[index])) {
                printf("[실패] 시간표가 충돌합니다.\n");
                system("pause");
            }
            else {
                basketAddLecture(&basket, &lectures[index]);
            }
            break;
        }

        case 3:
            basketPrint(&basket);
            break;

        case 4:
            printTimetable(&basket);
            break;

        case 5:
            runGradeCalculator(&basket);
            break;

        case 6:
            printLecturesByCategory(lectures, lectureCount);
            break;

        case 7:
            basketRemoveLecture(&basket);
            break;

        case 8:
            basketSave(&basket, SELECT_FILE);
            printf("저장 완료. 종료합니다.\n");
            running = 0;
            break;

        default:
            printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}
