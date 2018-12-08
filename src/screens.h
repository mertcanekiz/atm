#ifndef SCREENS_H
#define SCREENS_H

#include "definitions.h"
#include "user.h"

void welcome_screen();
void main_menu();
void settings();
void change_username();
void change_password();
void delete_account();
void transaction();
void account_details();
void customer_list();

int print_title(char *title);

#endif