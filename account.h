#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    char id[50];
    char pw[50];
    char name[50];
    char dept[50];
    char email[100];
} Account;

void createAccount();
int login(Account *loggedIn);

#endif
