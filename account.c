#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"

#define MAX_LINE 256
#define USER_FILE "userData.txt"

typedef struct {
    char id[50];
    char password[50];
    char name[50];
    char department[50];
    char tel[50];
    char email[50];
} User;

int createAccount() {
    User u;

    printf("\n=== 계정 생성 ===\n");

    printf("아이디: ");
    fgets(u.id, sizeof(u.id), stdin);
    u.id[strcspn(u.id, "\n")] = 0;

    printf("비밀번호: ");
    fgets(u.password, sizeof(u.password), stdin);
    u.password[strcspn(u.password, "\n")] = 0;

    printf("이름: ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = 0;

    printf("소속: ");
    fgets(u.department, sizeof(u.department), stdin);
    u.department[strcspn(u.department, "\n")] = 0;

    printf("전화번호: ");
    fgets(u.tel, sizeof(u.tel), stdin);
    u.tel[strcspn(u.tel, "\n")] = 0;

    printf("이메일: ");
    fgets(u.email, sizeof(u.email), stdin);
    u.email[strcspn(u.email, "\n")] = 0;

    FILE *fp = fopen(USER_FILE, "w");
    if (!fp) {
        printf("파일 열기 실패.\n");
        return 0;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
            u.id, u.password, u.name, u.department, u.tel, u.email);

    fclose(fp);
    printf("계정 생성 완료!\n");

    return 1;
}

int loginAccount() {
    User u;
    char inputID[50], inputPW[50];

    printf("\n=== 로그인 ===\n");
    printf("아이디: ");
    fgets(inputID, sizeof(inputID), stdin);
    inputID[strcspn(inputID, "\n")] = 0;

    printf("비밀번호: ");
    fgets(inputPW, sizeof(inputPW), stdin);
    inputPW[strcspn(inputPW, "\n")] = 0;

    FILE *fp = fopen(USER_FILE, "r");
    if (!fp) {
        printf("회원 정보가 없습니다. 먼저 계정을 생성하세요.\n");
        return 0;
    }

    fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%s",
           u.id, u.password, u.name, u.department, u.tel, u.email);

    fclose(fp);

    if (strcmp(inputID, u.id) == 0 && strcmp(inputPW, u.password) == 0)
        return 1;

    return 0;
}
