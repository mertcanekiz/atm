/*********************************************************************
* Filename:   screens.c
* Author:     Mertcan Ekiz (ekiz.mertcan@gmail.com)
*********************************************************************/
#include "screens.h"
#include "application.h"

void welcome_screen()
{
    current_user = NULL;
    int x = MARGIN_LEFT, y = print_title("WELCOME");
    mvprintw(y++, x, "[1] Log in");
    mvprintw(y++, x, "[2] Sign up");
    mvprintw(y++, x, "[q] Quit");
    BOLD(mvprintw(row - 1, 1, "Enter your choice: "));
    refresh();
    char c = getch();
    switch (c) {
        case '1':
            if ((current_user = login()) != NULL) {
                main_menu();
            } else {
                welcome_screen();
            }
            break;
        case '2':
            if ((current_user = signup()) != NULL) {
                main_menu();
            } else {
                welcome_screen();
            }
            break;
        case 'q':
            quit();
            break;
        default:
            welcome_screen();
    }
}

void main_menu()
{
    int x = MARGIN_LEFT, y = print_title("MAIN MENU");
    mvprintw(y++, x, "[1] View account details");
    mvprintw(y++, x, "[2] Withdraw / deposit money");
    mvprintw(y++, x, "[3] Transactions");
    mvprintw(y++, x, "[4] Settings");
    mvprintw(y++, x, "[5] List of customers");
    mvprintw(y++, x, "[q] Logout");

    BOLD(mvprintw(row - 1, 1, "Enter your choice: "));
    refresh();
    char c = getch();
    switch(c) {
        case '1':
            account_details();
            break;
        case '2':
            withdraw_and_deposit();
            break;
        case '3':
            transactions();
            break;
        case '4':
            settings();
            break;
        case '5':
            customer_list();
            break;
        case 'q':
            welcome_screen();
            break;
        default:
            main_menu();
    }
}

void settings()
{
    int x = MARGIN_LEFT, y = print_title("UPDATE ACCOUNT");
    mvprintw(y++, x, "[1] Change username");
    mvprintw(y++, x, "[2] Change password");
    mvprintw(y++, x, "[3] Delete account");
    mvprintw(y++, x, "[q] Cancel");
    BOLD(mvprintw(row-1, 0, "Enter your choice: "));
    int c = getch();
    switch (c) {
        case '1':
            change_username();
            break;
        case '2':
            change_password();
            break;
        case '3':
            delete_account();
            break;
        case 'q':
            main_menu();
    }
    settings();
}

void change_username()
{
    int x = MARGIN_LEFT, y = print_title("CHANGE USERNAME");
    char newname[BUFFER_SIZE];
    char newname_confirm[BUFFER_SIZE];
    BOLD(mvprintw(row / 2, x, "New username: "));
    BOLD(mvprintw(row / 2 + 1, x, "Confirm new username: "));
    move(row / 2, x + strlen("New username: "));
    getstr(newname);
    move(row / 2 + 1, x + strlen("Confirm new username: "));
    getstr(newname_confirm);
    if (strcmp(newname, newname_confirm) == 0) {
        strcpy(current_user->name, newname);
        mvprintw(row / 2 + 2, x, "Username successfully changed to %s", newname);
    } else {
        mvprintw(row / 2 + 2, x, "Usernames don't match");
    }
    getch();
}

void change_password()
{
    int x = MARGIN_LEFT, y = print_title("CHANGE PASSWORD");
    char newpassword[BUFFER_SIZE];
    char newpassword_confirm[BUFFER_SIZE];
    noecho();
    BOLD(mvprintw(row / 2, x, "New Password: "));
    BOLD(mvprintw(row / 2 + 1, x, "Confirm new Password: "));
    move(row / 2, x + strlen("New Password: "));
    getstr(newpassword);
    move(row / 2 + 1, x + strlen("Confirm new Password: "));
    getstr(newpassword_confirm);
    if (strcmp(newpassword, newpassword_confirm) == 0) {
        md5_encode(newpassword, current_user->password);
        mvprintw(row / 2 + 2, x, "Password successfully changed");
    } else {
        mvprintw(row / 2 + 2, x, "Passwords don't match");
    }
    echo();
    getch();
}

void delete_account()
{
    int x = MARGIN_LEFT, y = print_title("DELETE ACCOUNT");
    mvprintw(row / 2, MARGIN_LEFT, "Type \"DELETE\" to confirm account deletion: ");
    getstr(input);
    if (strcmp(_strlwr(input), "delete") != 0) {
        main_menu();
    }

    char username[BUFFER_SIZE];
    strcpy(username, current_user->name);
    for (int i = 0; i < num_users; i++) {
        if (users[i]) {
            if (strcmp(username, users[i]->name) == 0) {
                users[i] = NULL;
            }
        }
    }
    mvprintw(row / 2, MARGIN_LEFT, "User %s successfully deleted", username);
    clrtoeol();
    getch();
    welcome_screen();
}

void account_details()
{
    int x = MARGIN_LEFT, y = print_title("ACCOUNT DETAILS");
    char msg[BUFFER_SIZE];
    sprintf(msg, "Name: %s", current_user->name);
    // BOLD(mvprintw(row / 2, (col - strlen(msg)) / 2, "Name: ")); printw("%s", current_user->name);
    sprintf(msg, "Balance: %u TRY", current_user->balance);
    BOLD(mvprintw(row / 2, (col - strlen(msg)) / 2, "Balance: ")); printw("%u TRY", current_user->balance);
    BOLD(mvprintw(row - 1, 0, "Press any key to return to the main menu..."));
    getch();
    main_menu();
}

void withdraw_and_deposit()
{
    int x = MARGIN_LEFT, y = print_title("WITHDRAW / DEPOSIT MONEY");
    mvprintw(y++, x, "[1] Withdraw money");
    mvprintw(y++, x, "[2] Deposit Money");
    mvprintw(y++, x, "[q] Main menu");
    BOLD(mvprintw(row - 1, 1, "Enter your choice: "));
    refresh();
    char c = getch();
    switch (c) {
        case '1':
            withdraw_money();
        break;
        case '2':
            deposit_money();
        break;
        case 'q':
            main_menu();
        break;
    }
    withdraw_and_deposit();
}

void withdraw_money()
{
    int x = MARGIN_LEFT, y = print_title("WITHDRAW MONEY");
    BOLD(mvprintw(y++, x, "Enter amount or type q to cancel: "));
    getstr(input);
    if (strcmp(input, "q") == 0) {
        return;
    }
    unsigned int amount = (unsigned int) atoi(input);
    unsigned int currencies[5] = { 200, 100, 50, 20, 10 };
    unsigned int amounts[5] = { 0, 0, 0, 0, 0 };
    if (current_user->balance < amount) {
        mvprintw(y++, x, "Insufficient funds");
        getch();
    }
    else if (amount % 10 != 0) {
        mvprintw(y++, x, "You can only withdraw multiples of 10");
        getch();
    } else {
        unsigned int large = (unsigned int) (amount * 0.8f);
        unsigned int small = amount - large;
        mvprintw(y++, x, "%%80: %u, %%20: %u", large, small);
        int i = 0;
        while (1) {
            if (large >= currencies[i]) {
                large -= currencies[i];
                amounts[i]++;
            } else {
                if (i < 4)
                    i++;
                else
                    break;
            }
        }

        amounts[4] += (small / 10) + (large % 10 == 0 ? 0 : 1);

        for (i = 0; i < 5; i++) {
            if (amounts[i] != 0) {
                mvprintw(y++, x, "%u: %u", currencies[i], amounts[i]);
            }
        }
        current_user->balance -= amount;
        getch();
    }
}

void deposit_money()
{
    int x = MARGIN_LEFT, y = print_title("DEPOSIT MOENY");
    unsigned int currencies[5] = { 200, 100, 50, 20, 10 };
    unsigned int amounts[5];
    unsigned int total = 0;
    mvprintw(y++, x, "[200TL] x ");
    mvprintw(y++, x, "[100TL] x ");
    mvprintw(y++, x, "[ 50TL] x ");
    mvprintw(y++, x, "[ 20TL] x ");
    mvprintw(y++, x, "[ 10TL] x ");
    for (int i = 0; i < 5; i++) {
        move(y-5+i, x + strlen("[200TL] x "));
        getstr(input);
        amounts[i] = (unsigned int) atoi(input);
        total += currencies[i] * amounts[i];
    }
    mvprintw(y++, x, "%uTL has been added to your balance", total);
    current_user->balance += total;
    getch();
}

void transactions()
{
    int x = MARGIN_LEFT, y = print_title("TRANSACTIONS");
    User *other = NULL;
    mvprintw(y++, x, "Send to user with ID: ");
    getstr(input);
    unsigned int id = (unsigned int) atoi(input);
    other = get_user_by_id(id);
    if (other == NULL) {
        mvprintw(y++, x, "Could not find a user with ID %u", id);
        getch();
        main_menu();
    }
    mvprintw(y++, x, "Amount: ");
    getstr(input);
    unsigned int amount = (unsigned int) atoi(input);
    if (amount > current_user->balance) {
        mvprintw(y++, x, "Insufficient funds");
    } else {
        current_user->balance -= amount;
        other->balance += amount;
        mvprintw(y++, x, "Transaction successful");
    }
    getch();
    main_menu();
}

void customer_list()
{
    int x = MARGIN_LEFT, y = print_title("CUSTOMER LIST");
    mvprintw(y++, x, "ID   :: Name");
    mvprintw(y++, x, "--------------------");
    for (int i = 0; i < num_users; i++) {
        if (users[i])
            mvprintw(y++, x, "%04u :: %s\n", users[i]->id, users[i]->name, users[i]->balance);
    }
    BOLD(mvprintw(row-1, 0, "Press any key to return to the main menu..."));
    getch();
    main_menu();
}

int print_title(char *title)
{
    char msg[80] = "ATM SIMULATOR";
    int x, y = 2;
    clear();
    if (current_user)
        mvprintw(1, 1, "Logged in as: %s", current_user->name);
    x = (col - strlen(msg)) / 2;
    BOLD(mvprintw(y++, x, "%s", msg);
    move(y++, 0);
    for (int i = 0; i < col; i++) {
        printw("%c", '-');
    }
    );
    strcpy(msg, title);
    x = (col - strlen(msg)) / 2;
    mvprintw(y++, x, "%s", msg);
    move(y++, 0);
    for (int i = 0; i < col; i++) {
        printw("%c", '-');
    }
    return y+2;
}
