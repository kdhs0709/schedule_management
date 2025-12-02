#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_LECTURES 200
#define MAX_SELECTED 20
#define COL_RESET  "\033[0m"
#define COL_TITLE  "\033[1;36m"
#define COL_MENU   "\033[1;33m"
#define COL_WARN   "\033[1;31m"
#define COL_OK     "\033[1;32m"

void clearBuffer();
void clearInputBuffer(void);
#endif