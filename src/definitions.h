/*********************************************************************
* Filename:   definitions.h
* Author:     Mertcan Ekiz (ekiz.mertcan@gmail.com)
*********************************************************************/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#if defined _WIN32 || defined __CYGWIN__
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <md5.h>

#define BUFFER_SIZE 80
#define MAX_USERS 100
#define MARGIN_LEFT 10
#define MAX_LOGIN_ATTEMPT 3

#define BOLD(x) attron(A_BOLD); x; attroff(A_BOLD);

typedef struct User User; // Originally defined in "user.h"

void md5_encode(char* src, char* dst);
char* strip(char* str);

#if !defined(_WIN32) && !defined(__CYGWIN__)
char* _strlwr(char* str);
#endif

int num_users;
int id_counter;
int row, col;
char input[BUFFER_SIZE];
User* users[MAX_USERS];
User* current_user;

#endif
