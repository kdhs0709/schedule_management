#include <stdio.h>
#include <string.h>
#include "account.h"

void createAccount() {
    Account acc;

    printf("아이디: "); scanf("%s", acc.id);
    printf("비밀번호: "); scanf("%s", acc.pw);
    printf("이름: "); scanf("%s", acc.name);
    printf("학과: "); scanf("%s", acc.dept);
    printf("Email: "); scanf("%s", acc.email);

    FILE *fp = fopen("user.txt", "w");
    fprintf(fp, "%s,%s,%s,%s,%s\n",
        acc.id, acc.pw, acc.name, acc.dept, acc.email);
    fclose(fp);

    printf("\n[알림] 계정이 성공적으로 생성되었습니다.\n\n");
}

int login(Account *loggedIn) {
    char id[50], pw[50];
    printf("로그인 ID: "); scanf("%s", id);
    printf("비밀번호: "); scanf("%s", pw);

    FILE *fp = fopen("user.txt", "r");
    if(!fp) return 0;

    fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%s",
        loggedIn->id, loggedIn->pw, loggedIn->name,
        loggedIn->dept, loggedIn->email);

    fclose(fp);

    if(strcmp(id, loggedIn->id)==0 && strcmp(pw, loggedIn->pw)==0)
        return 1;

    return 0;
}
