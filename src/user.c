#include "user.h"
#include "screens.h"

bool validate_username(char* username)
{
    strip(username);
    if (strlen(username) < 1) return false;
    for (int i = 0; i < strlen(username); i++) {
        if (isalpha(username[i]) || username[i] == ' ') continue;
        else return false;
    }
    return true;
}

bool validate_password(char* password)
{
    strip(password);
    if (strlen(password) < 6) return false;
    return true;
}

User* get_user(char* username)
{
    for (int i = 0; i < num_users; i++) {
        if (users[i]) {
            if (strcmp(users[i]->name, username) == 0) {
                return users[i];
            }
        }
    }
    return NULL;
}

User* signup()
{
    User* user =  malloc(sizeof(User));
    int x = MARGIN_LEFT, y = print_title("SIGN UP");
    BOLD(mvprintw(y++, x, "User name: "));
    BOLD(mvprintw(y, x, "Password: "));
    move(y - 1, x + strlen("User name: "));
    for (int i = 0; i < MAX_LOGIN_ATTEMPT; i++) {
        refresh();
        getstr(input);
        if (!validate_username(input)) {
            mvprintw(y - 2, MARGIN_LEFT, "Please enter a valid user name");
            move(y - 1, MARGIN_LEFT + strlen("User name: "));
            clrtoeol();
            refresh();
            continue;
        } else {
            if (get_user(input)) {
                mvprintw(y - 2, MARGIN_LEFT, "User name already exists");
                move(y - 1, MARGIN_LEFT + strlen("User name: "));
                clrtoeol();
                refresh();
                continue;
            } else {
                strcpy(user->name, input);
                break;
            }
        }
    }

    move(y, x + strlen("Password: "));
    noecho();
    while (1) {
        refresh();
        getstr(input);
        unsigned char digest[16];
        if (!validate_password(input)) {
            mvprintw(y - 2, MARGIN_LEFT, "Password must be at least 6 characters long");
            move(y, MARGIN_LEFT + strlen("Password: "));
            refresh();
            continue;
        } else {
            md5_encode(input, user->password);
            break;
        }
    }
    echo();
    user->balance = 0;
    user->id = ++id_counter;
    users[num_users++] = user;
    return user;
}

User* login()
{
    int x = MARGIN_LEFT, y = print_title("LOG IN") + 1;
    BOLD(mvprintw(y++, MARGIN_LEFT, "User name: "));
    BOLD(mvprintw(y, MARGIN_LEFT, "Password: "));
    move(y-1, MARGIN_LEFT + strlen("User name: "));
    for (int i = 0; i < MAX_LOGIN_ATTEMPT; i++) {
        refresh();
        getstr(input);
        if (!validate_username(input)) {
            mvprintw(y-2, MARGIN_LEFT, "Invalid username");
            move(y-1, MARGIN_LEFT + strlen("User name: "));
            clrtoeol();
            refresh();
            continue;
        } else {
            User *user = get_user(input);
            if (user) {
                move(y, MARGIN_LEFT + strlen("Password: "));
                noecho();
                while (true) {
                    refresh();
                    getstr(input);
                    
                    char login_password[33];
                    md5_encode(input, login_password);
                    if (strcmp(user->password, login_password) == 0) {
                        echo();
                        return user;
                    } else {
                        mvprintw(y-2, MARGIN_LEFT, "Incorrect password");
                        clrtoeol();
                        move(y-1, MARGIN_LEFT + strlen("User name: "));
                        clrtoeol();
                        refresh();
                        break;
                    }
                    
                }
                echo();
            } else {
                mvprintw(y-2, MARGIN_LEFT, "No such user found");
                move(y-1, MARGIN_LEFT + strlen("User name: "));
                clrtoeol();
                refresh();
                continue;
            }
        }
    }

    return NULL;
}

void load_users()
{
    FILE *f;
    char buffer[BUFFER_SIZE];

    f = fopen("users.csv", "r+");
    if (f == NULL) {
        mvprintw(0, 0, "Error while loading users from file");
        getch();
    }
    
    int i = 0;
    unsigned int largest_id = 0;
    while (fgets(buffer, BUFFER_SIZE, (FILE*) f)) {
        User* user = malloc(sizeof(User));
        char user_data[4][BUFFER_SIZE];
        const char delim[3] = ",\n";
        char * token;
        token = strtok(buffer, delim);
        int j = 0;
        while (token != NULL) {
            strcpy(user_data[j], token);
            token = strtok(NULL, delim);
            j++;
        }
	if (j != 4) {
	    free(user);
	    break;
	}
        user->id = (unsigned int) atoi(user_data[0]);
        strcpy(user->name, user_data[1]);
        strcpy(user->password, user_data[2]);
        user->balance = (unsigned int) atoi(user_data[3]);
        users[i] = user;
        if (user->id > largest_id) {
            largest_id = user->id;
        }
        i++;
    }
    num_users = i;
    id_counter = largest_id;
}

void save_users()
{
    FILE *f;
    f = fopen("users.csv", "w+");
    if (f == NULL) {
        mvprintw(0, 0, "ERROR");
        getch();
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_users; i++) {
        if (users[i]) {
            fprintf(f, "%u,%s,%s,%u\n", users[i]->id, users[i]->name, users[i]->password, users[i]->balance);
            free(users[i]);
        }
    }
}
