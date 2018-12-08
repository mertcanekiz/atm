#include "application.h"

void init()
{
    load_users();
    initscr();
    refresh();
    keypad(stdscr, true);
    cbreak();
    getmaxyx(stdscr, row, col);
    welcome_screen();
    quit();
}

void quit()
{
    save_users();
    endwin();
    exit(EXIT_SUCCESS);
}

void md5_encode(char* src, char* dst)
{
    MD5_CTX ctx;
    BYTE digest[16];
    md5_init(&ctx);
    md5_update(&ctx, src, strlen(src));
    md5_final(&ctx,  digest);
    for (int i = 0; i < 16; i++) {
        sprintf(&dst[i*2], "%02x", (BYTE) digest[i]);
    }
}

char* strip(char* str)
{
    for (int i = strlen(str); i > 0; i--) {
        if (str[i] == '\b' || str[i] == KEY_BACKSPACE) {
            memmove(&str[i-1], &str[i + 1], strlen(str) - i);
        }
    }
    return str;
}


int main(int argc, char *argv[])
{
    init();
    return 0;
}

