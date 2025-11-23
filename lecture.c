#include <stdio.h>
#include <string.h>
#include "lecture.h"

int loadLectures(Lecture arr[]) {
    FILE *fp = fopen("lectures.csv", "r");
    if(!fp) {
        printf("[오류] lectures.csv 파일을 찾을 수 없습니다.\n");
        return 0;
    }

    int i = 0;
    while(!feof(fp)) {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%lf\n",
            arr[i].code, arr[i].name, arr[i].prof,
            arr[i].time, &arr[i].credit
        );
        i++;
    }

    fclose(fp);
    return i;
}

void printLectures(Lecture arr[], int n) {
    printf("번호 | 학정번호 | 과목명 | 교수 | 시간 | 학점\n");
    printf("--------------------------------------------------------\n");
    for(int i=0;i<n;i++)
        printf("%d | %s | %s | %s | %s | %.1lf\n",
            i+1, arr[i].code, arr[i].name, arr[i].prof,
            arr[i].time, arr[i].credit);
}
