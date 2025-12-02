#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
	char id[32];
	char pw[32];
	char name[32];
	char major[64];
} Account;

int login(const char* filename, Account* out);
void createAccount(const char* filename);

#endif
