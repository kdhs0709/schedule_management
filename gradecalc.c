#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "gradecalc.h"

void loadGPA(void) {
    FILE* fp = fopen("gpa.txt", "r");
    if (!fp) return;

    double gpa, credit;
    if (fscanf(fp, "%lf %lf", &gpa, &credit) == 2) {
        printf("\n[이전 성적 기록]\n");
        printf("총 학점 : %.1f / GPA : %.2f\n", credit, gpa);
    }

    fclose(fp);
}

double gradeToPoint(char grade[]) {

    if (!strcmp(grade, "A+")) return 4.5;
    if (!strcmp(grade, "A"))  return 4.0;
    if (!strcmp(grade, "B+")) return 3.5;
    if (!strcmp(grade, "B"))  return 3.0;
    if (!strcmp(grade, "C+")) return 2.5;
    if (!strcmp(grade, "C"))  return 2.0;
    if (!strcmp(grade, "D+")) return 1.5;
    if (!strcmp(grade, "D"))  return 1.0;
    if (!strcmp(grade, "F"))  return 0.0;

    return -1.0;
}

void runGradeCalculator(const Basket* b) {

    if (b->count == 0) {
        printf("[안내] 신청한 과목이 없습니다.\n");
        return;
    }

    double totalCredit = 0.0;
    double weightedSum = 0.0;
    char grade[8];

    printf("\n===== GPA 계산기 =====\n");

    for (int i = 0; i < b->count; i++) {

        printf("\n[%d] %s (%s)\n",
            i + 1,
            b->list[i].name,
            b->list[i].code);

        printf("성적 입력 (A+, A, B+, B, C+, C, D+, D, F): ");
        scanf("%s", grade);

        double point = gradeToPoint(grade);

        if (point < 0) {
            printf("[오류] 잘못된 성적입니다. 다시 입력하세요.\n");
            i--;
            continue;
        }

        weightedSum += point * b->list[i].credit;
        totalCredit += b->list[i].credit;
    }

    double gpa = weightedSum / totalCredit;

    printf("\n========================\n");
    printf("총 학점 : %.1f\n", totalCredit);
    printf("GPA     : %.2f / 4.5\n", gpa);
    printf("========================\n");
    saveGPA(gpa, totalCredit);

    system("pause");
}

void saveGPA(double gpa, double credit) {
    FILE* fp = fopen("gpa.txt", "w");
    if (!fp) return;
    fprintf(fp, "%.2f %.1f\n", gpa, credit);
    fclose(fp);
}
