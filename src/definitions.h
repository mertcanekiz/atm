#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <ncursesw/ncurses.h>
#include <md5.h>

#define BUFFER_SIZE 80
#define MAX_USERS 100
#define MARGIN_LEFT 10
#define MAX_LOGIN_ATTEMPT 3

#define BOLD(x) attron(A_BOLD); x; attroff(A_BOLD);

typedef struct User User;

void md5_encode(char* src, char* dst);
char* strip(char* str);

int num_users;
int id_counter;
int row, col;
char input[BUFFER_SIZE];
User* users[MAX_USERS];
User* current_user;

#endif