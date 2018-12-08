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
User* get_user(char* username);
bool validate_username(char* username);
bool validate_password(char* password);

#endif