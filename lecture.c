#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"

static void trim(char* s) {
    char* p = s;
    int len = strlen(p);

    while (len > 0 && (p[len - 1] == '\n' || p[len - 1] == '\r' || p[len - 1] == ' ' || p[len - 1] == '\t'))
        p[--len] = '\0';

    while (*p && (*p == ' ' || *p == '\t'))
        ++p, --len;

    memmove(s, p, len + 1);
}

int parseCSV(char* line, char fields[][128], int maxFields) {

    int field = 0;
    int pos = 0;
    int inQuotes = 0;

    for (int i = 0; i < maxFields; i++)
        fields[i][0] = '\0';

    for (int i = 0; line[i] && field < maxFields; i++) {

        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes) {
            fields[field][pos] = '\0';
            trim(fields[field]);
            field++;
            pos = 0;
        }
        else if (c != '\n' && c != '\r') {
            if (pos < 127)
                fields[field][pos++] = c;
        }
    }

    fields[field][pos] = '\0';
    trim(fields[field]);
    field++;

    return field;
}


int loadLectures(const char* filename, Lecture* arr, int max) {

    FILE* fp = fopen(filename, "r");
    char line[1024];
    char fields[8][128];
    int count = 0;

    if (!fp) {
        printf("[오류] CSV 파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {

        if (strlen(line) < 3) continue;
        if (count >= max) break;

        int f = parseCSV(line, fields, 8);
        if (f < 4) continue;

        strncpy(arr[count].code, fields[0], sizeof(arr[count].code) - 1);
        arr[count].code[sizeof(arr[count].code) - 1] = '\0';

        strncpy(arr[count].name, fields[1], sizeof(arr[count].name) - 1);
        arr[count].name[sizeof(arr[count].name) - 1] = '\0';

        strncpy(arr[count].professor, fields[2], sizeof(arr[count].professor) - 1);
        arr[count].professor[sizeof(arr[count].professor) - 1] = '\0';

        strncpy(arr[count].time, fields[3], sizeof(arr[count].time) - 1);
        arr[count].time[sizeof(arr[count].time) - 1] = '\0';

        if (f >= 5)
            arr[count].credit = atof(fields[4]);
        else
            arr[count].credit = 0.0;

        count++;
    }

    fclose(fp);
    return count;
}


void printLectures(const Lecture* arr, int count) {

    printf("\n================ 강의 목록 ================\n");
    printf("번호 | 과목코드        | 과목명               | 교수명          | 시간       | 학점\n");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%3d | %-14s | %-20s | %-15s | %-9s | %.1f\n",
            i + 1,
            arr[i].code,
            arr[i].name,
            arr[i].professor,
            arr[i].time,
            arr[i].credit
        );
    }

    printf("===============================================================================\n");
}
void printLecturesPaged(const Lecture* arr, int count) {

    const int pageSize = 30;
    int page = 0;
    int totalPages = (count + pageSize - 1) / pageSize;

    while (1) {
        system("cls");  

        int start = page * pageSize;
        int end = start + pageSize;
        if (end > count) end = count;

        printf("\n================ 강의 목록 (%d / %d 페이지) ================\n",
            page + 1, totalPages);
        printf("번호 | 과목코드        | 과목명               | 교수명          | 시간       | 학점\n");
        printf("-------------------------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%3d | %-14s | %-20s | %-15s | %-9s | %.1f\n",
                i + 1,
                arr[i].code,
                arr[i].name,
                arr[i].professor,
                arr[i].time,
                arr[i].credit);
        }

        printf("\n[n] 다음 페이지  [p] 이전 페이지  [q] 나가기\n");
        printf("선택: ");

        char cmd;
        scanf(" %c", &cmd);

        if (cmd == 'n' && page < totalPages - 1)
            page++;
        else if (cmd == 'p' && page > 0)
            page--;
        else if (cmd == 'q')
            break;
    }
}
void printLecturesByCategory(const Lecture* arr, int count) {

    char prefix[4];
    printf("보고 싶은 계열 코드 입력 (예: YHL, YHX, DES): ");
    scanf("%s", prefix);

    printf("\n=== [%s] 계열 강의 목록 ===\n", prefix);
    printf("번호 | 과목코드        | 과목명               | 교수명          | 시간       | 학점\n");
    printf("-------------------------------------------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strncmp(arr[i].code, prefix, 3) == 0) {
            printf("%3d | %-14s | %-20s | %-15s | %-9s | %.1f\n",
                i + 1,
                arr[i].code,
                arr[i].name,
                arr[i].professor,
                arr[i].time,
                arr[i].credit);
            found = 1;
        }
    }

    if (!found)
        printf("\n해당 계열 강의가 없습니다.\n");
}
int selectLecturePaged(const Lecture* arr, int count) {

    const int pageSize = 30;
    int page = 0;
    int totalPages = (count + pageSize - 1) / pageSize;

    while (1) {

        system("cls");

        int start = page * pageSize;
        int end = start + pageSize;
        if (end > count) end = count;

        printf("\n======= 수강 신청 (%d / %d 페이지) =======\n", page + 1, totalPages);
        printf("번호 | 과목코드        | 과목명               | 교수명          | 시간       | 학점\n");
        printf("-------------------------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%3d | %-14s | %-20s | %-15s | %-9s | %.1f\n",
                i + 1,
                arr[i].code,
                arr[i].name,
                arr[i].professor,
                arr[i].time,
                arr[i].credit);
        }

        printf("\n[n] 다음 페이지   [p] 이전 페이지   [번호] 수강신청   [q] 뒤로가기\n");
        printf("선택: ");

        char input[10];
        scanf("%s", input);

        if (strcmp(input, "q") == 0)
            return -1;

        if (strcmp(input, "n") == 0 && page < totalPages - 1) {
            page++;
            continue;
        }

        if (strcmp(input, "p") == 0 && page > 0) {
            page--;
            continue;
        }

        int sel = atoi(input);
        if (sel >= 1 && sel <= count) {
            return sel - 1;
        }

        printf("잘못된 입력입니다.\n");
        system("pause");
    }
}
