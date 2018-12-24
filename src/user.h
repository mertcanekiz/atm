/*********************************************************************
* Filename:   user.h
* Author:     Mertcan Ekiz (ekiz.mertcan@gmail.com)
*********************************************************************/
#ifndef USER_H
#define USER_H

#include "definitions.h"

typedef struct User {
    unsigned int id;
    char name[BUFFER_SIZE];
    char password[33];
    unsigned int balance;
} User;

void load_users();
void save_users();
User* signup();
User* login();
User* get_user_by_name(char* username);
User* get_user_by_id(unsigned int id);
bool validate_username(char* username);
bool validate_password(char* password);

#endif
