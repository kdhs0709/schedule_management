#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "account.h"

void createAccount(const char* filename) {
    FILE* fp = fopen(filename, "a");
    Account a;

    if (!fp) {
        printf("[오류] 계정 파일을 열 수 없습니다.\n");
        return;
    }

    printf("===== 계정 생성 =====\n");

    printf("아이디: ");
    scanf("%31s", a.id);

    printf("비밀번호: ");
    scanf("%31s", a.pw);

    printf("이름: ");
    scanf("%63s", a.name);

    getchar();
    printf("학과: ");
    fgets(a.major, sizeof(a.major), stdin);
    a.major[strcspn(a.major, "\n")] = 0; 

    fprintf(fp, "%s,%s,%s,%s\n", a.id, a.pw, a.name, a.major);
    fclose(fp);

    printf("[완료] 계정이 생성되었습니다.\n");
}

// ===============================
// 로그인
// ===============================
int login(const char* filename, Account* out) {

    FILE* fp = fopen(filename, "r");
    char id[32], pw[32];

    if (!fp) {
        printf("[알림] 계정 파일이 없습니다. 먼저 계정을 생성하세요.\n");
        return 0;
    }

    printf("===== 로그인 =====\n");
    printf("아이디: ");
    scanf("%31s", id);
    printf("비밀번호: ");
    scanf("%31s", pw);

    // CSV 형식으로 읽기
    while (fscanf(fp, "%31[^,],%31[^,],%63[^,],%127[^\n]\n",
        out->id, out->pw, out->name, out->major) == 4) {

        if (!strcmp(id, out->id) && !strcmp(pw, out->pw)) {
            fclose(fp);
            printf("[성공] 로그인 완료\n");
            return 1;
        }
    }

    fclose(fp);
    printf("[실패] 아이디 또는 비밀번호가 틀렸습니다.\n");
    return 0;
}
