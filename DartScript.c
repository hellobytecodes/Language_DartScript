/*
 * DartScript Interpreter v1.0
 * Windows Keyboard Automation Language
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 2048
#define MAX_LINES 10000

/* Global Variables */
char lines[MAX_LINES][MAX_LINE_LENGTH];
int totalLines = 0;
int defaultDelay = 0;

/* ═══════════════════════════════════════════════════════════
 *                    Helper Functions
 * ═══════════════════════════════════════════════════════════*/

void delay(int ms) {
    Sleep(ms);
}

int isNumber(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

char *trim(char *str) {
    while (*str == ' ') str++;
    char *end = str + strlen(str) - 1;
    while (end > str && *end == ' ') *end-- = '\0';
    return str;
}

/* ═══════════════════════════════════════════════════════════
 *                    Virtual Key Code Lookup
 * ═══════════════════════════════════════════════════════════*/

BYTE getVkCode(const char *key) {
    char upperKey[64];
    strcpy(upperKey, key);
    for (int i = 0; upperKey[i]; i++) upperKey[i] = toupper(upperKey[i]);
    
    if (strcmp(upperKey, "ENTER") == 0 || strcmp(upperKey, "RETURN") == 0) return VK_RETURN;
    if (strcmp(upperKey, "BACK") == 0 || strcmp(upperKey, "BACKSPACE") == 0) return VK_BACK;
    if (strcmp(upperKey, "TAB") == 0) return VK_TAB;
    if (strcmp(upperKey, "ESC") == 0 || strcmp(upperKey, "ESCAPE") == 0) return VK_ESCAPE;
    if (strcmp(upperKey, "SPACE") == 0) return VK_SPACE;
    if (strcmp(upperKey, "DELETE") == 0 || strcmp(upperKey, "DEL") == 0) return VK_DELETE;
    if (strcmp(upperKey, "INSERT") == 0 || strcmp(upperKey, "INS") == 0) return VK_INSERT;
    if (strcmp(upperKey, "HOME") == 0) return VK_HOME;
    if (strcmp(upperKey, "END") == 0) return VK_END;
    if (strcmp(upperKey, "PAGEUP") == 0) return VK_PRIOR;
    if (strcmp(upperKey, "PAGEDOWN") == 0) return VK_NEXT;
    if (strcmp(upperKey, "UP") == 0) return VK_UP;
    if (strcmp(upperKey, "DOWN") == 0) return VK_DOWN;
    if (strcmp(upperKey, "LEFT") == 0) return VK_LEFT;
    if (strcmp(upperKey, "RIGHT") == 0) return VK_RIGHT;
    if (strcmp(upperKey, "CAPS") == 0 || strcmp(upperKey, "CAPSLOCK") == 0) return VK_CAPITAL;
    if (strcmp(upperKey, "PRTSC") == 0 || strcmp(upperKey, "PRINTSCREEN") == 0) return VK_SNAPSHOT;
    if (strcmp(upperKey, "PAUSE") == 0) return VK_PAUSE;
    
    if (strcmp(upperKey, "F1") == 0) return VK_F1;
    if (strcmp(upperKey, "F2") == 0) return VK_F2;
    if (strcmp(upperKey, "F3") == 0) return VK_F3;
    if (strcmp(upperKey, "F4") == 0) return VK_F4;
    if (strcmp(upperKey, "F5") == 0) return VK_F5;
    if (strcmp(upperKey, "F6") == 0) return VK_F6;
    if (strcmp(upperKey, "F7") == 0) return VK_F7;
    if (strcmp(upperKey, "F8") == 0) return VK_F8;
    if (strcmp(upperKey, "F9") == 0) return VK_F9;
    if (strcmp(upperKey, "F10") == 0) return VK_F10;
    if (strcmp(upperKey, "F11") == 0) return VK_F11;
    if (strcmp(upperKey, "F12") == 0) return VK_F12;
    
    if (strcmp(upperKey, "CTRL") == 0 || strcmp(upperKey, "CONTROL") == 0) return VK_CONTROL;
    if (strcmp(upperKey, "ALT") == 0) return VK_MENU;
    if (strcmp(upperKey, "SHIFT") == 0) return VK_SHIFT;
    if (strcmp(upperKey, "WIN") == 0 || strcmp(upperKey, "WINDOWS") == 0) return VK_LWIN;
    
    if (strlen(upperKey) == 1 && isalpha(upperKey[0])) return upperKey[0];
    if (strlen(upperKey) == 1 && isdigit(upperKey[0])) return upperKey[0];
    
    return 0;
}

/* ═══════════════════════════════════════════════════════════
 *                    Keyboard Functions
 * ═══════════════════════════════════════════════════════════*/

void pressKey(BYTE vkCode) {
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressCtrl(BYTE vkCode) {
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressAlt(BYTE vkCode) {
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressShift(BYTE vkCode) {
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressWin(BYTE vkCode) {
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressCtrlAlt(BYTE vkCode) {
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressCtrlShift(BYTE vkCode) {
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressWinShift(BYTE vkCode) {
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void pressWinCtrl(BYTE vkCode) {
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(vkCode, 0, 0, 0);
    keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    delay(10);
}

void typeString(const char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        
        if (c >= 'A' && c <= 'Z') {
            pressShift(c);
        } else if (c >= 'a' && c <= 'z') {
            pressKey(toupper(c));
        } else {
            switch (c) {
                case ' ': pressKey(VK_SPACE); break;
                case '\n': pressKey(VK_RETURN); break;
                case '\t': pressKey(VK_TAB); break;
                case '!': pressShift('1'); break;
                case '@': pressShift('2'); break;
                case '#': pressShift('3'); break;
                case '$': pressShift('4'); break;
                case '%': pressShift('5'); break;
                case '^': pressShift('6'); break;
                case '&': pressShift('7'); break;
                case '*': pressShift('8'); break;
                case '(': pressShift('9'); break;
                case ')': pressShift('0'); break;
                case '-': pressKey(VK_OEM_MINUS); break;
                case '=': pressKey(VK_OEM_PLUS); break;
                case '[': pressKey(VK_OEM_4); break;
                case ']': pressKey(VK_OEM_6); break;
                case '\\': pressKey(VK_OEM_5); break;
                case ';': pressKey(VK_OEM_1); break;
                case '\'': pressKey(VK_OEM_7); break;
                case ',': pressKey(VK_OEM_COMMA); break;
                case '.': pressKey(VK_OEM_PERIOD); break;
                case '/': pressKey(VK_OEM_2); break;
                case '`': pressKey(VK_OEM_3); break;
                case '_': pressShift(VK_OEM_MINUS); break;
                case '+': pressShift(VK_OEM_PLUS); break;
                case '{': pressShift(VK_OEM_4); break;
                case '}': pressShift(VK_OEM_6); break;
                case '|': pressShift(VK_OEM_5); break;
                case ':': pressShift(VK_OEM_1); break;
                case '"': pressShift(VK_OEM_7); break;
                case '<': pressShift(VK_OEM_COMMA); break;
                case '>': pressShift(VK_OEM_PERIOD); break;
                case '?': pressShift(VK_OEM_2); break;
                case '~': pressShift(VK_OEM_3); break;
                default: pressKey(c); break;
            }
        }
    }
}

/* ═══════════════════════════════════════════════════════════
 *                    Command Processors
 * ═══════════════════════════════════════════════════════════*/

void processPress(const char *args, int lineNum) {
    if (strlen(args) == 0) {
        printf("[ERROR] Line %d: PRESS command requires at least one key\n", lineNum);
        return;
    }
    
    char *argsCopy = strdup(args);
    char *token = strtok(argsCopy, "+");
    
    int ctrl = 0, alt = 0, shift = 0, win = 0;
    BYTE mainKey = 0;
    
    while (token != NULL) {
        token = trim(token);
        
        char upperToken[64];
        strcpy(upperToken, token);
        for (int i = 0; upperToken[i]; i++) upperToken[i] = toupper(upperToken[i]);
        
        if (strcmp(upperToken, "CTRL") == 0 || strcmp(upperToken, "CONTROL") == 0) {
            ctrl = 1;
        } else if (strcmp(upperToken, "ALT") == 0) {
            alt = 1;
        } else if (strcmp(upperToken, "SHIFT") == 0) {
            shift = 1;
        } else if (strcmp(upperToken, "WIN") == 0 || strcmp(upperToken, "WINDOWS") == 0) {
            win = 1;
        } else {
            mainKey = getVkCode(token);
            if (mainKey == 0) {
                printf("[ERROR] Line %d: Unknown key '%s'\n", lineNum, token);
                free(argsCopy);
                return;
            }
        }
        
        token = strtok(NULL, "+");
    }
    
    free(argsCopy);
    
    if (mainKey == 0) {
        printf("[ERROR] Line %d: No key specified to press\n", lineNum);
        return;
    }
    
    if (ctrl) keybd_event(VK_CONTROL, 0, 0, 0);
    if (alt) keybd_event(VK_MENU, 0, 0, 0);
    if (shift) keybd_event(VK_SHIFT, 0, 0, 0);
    if (win) keybd_event(VK_LWIN, 0, 0, 0);
    
    keybd_event(mainKey, 0, 0, 0);
    keybd_event(mainKey, 0, KEYEVENTF_KEYUP, 0);
    
    if (win) keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    if (shift) keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    if (alt) keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    if (ctrl) keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

void processWindows(const char *args, int lineNum) {
    if (strlen(args) == 0) {
        pressKey(VK_LWIN);
    } else {
        char key[32];
        strcpy(key, args);
        for (int i = 0; key[i]; i++) key[i] = toupper(key[i]);
        BYTE vk = getVkCode(key);
        if (vk) {
            pressWin(vk);
        } else {
            printf("[ERROR] Line %d: Unknown key '%s' after WINDOWS\n", lineNum, args);
        }
    }
}

void processControl(const char *args, int lineNum) {
    if (strlen(args) == 0) {
        printf("[ERROR] Line %d: CONTROL requires a key argument\n", lineNum);
        return;
    }
    
    char key[32];
    strcpy(key, args);
    for (int i = 0; key[i]; i++) key[i] = toupper(key[i]);
    
    if (strlen(key) == 1) {
        pressCtrl(key[0]);
    } else {
        printf("[ERROR] Line %d: CONTROL requires a single character key\n", lineNum);
    }
}

void processAlt(const char *args, int lineNum) {
    if (strlen(args) == 0) {
        printf("[ERROR] Line %d: ALT requires a key argument\n", lineNum);
        return;
    }
    
    char key[32];
    strcpy(key, args);
    for (int i = 0; key[i]; i++) key[i] = toupper(key[i]);
    BYTE vk = getVkCode(key);
    if (vk) {
        pressAlt(vk);
    } else {
        printf("[ERROR] Line %d: Unknown key '%s' after ALT\n", lineNum, args);
    }
}

void processShift(const char *args, int lineNum) {
    if (strlen(args) == 0) {
        printf("[ERROR] Line %d: SHIFT requires a key argument\n", lineNum);
        return;
    }
    
    char key[32];
    strcpy(key, args);
    for (int i = 0; key[i]; i++) key[i] = toupper(key[i]);
    BYTE vk = getVkCode(key);
    if (vk) {
        pressShift(vk);
    } else {
        printf("[ERROR] Line %d: Unknown key '%s' after SHIFT\n", lineNum, args);
    }
}

void processCtrlShortcut(const char *key, int lineNum) {
    char upperKey[32];
    strcpy(upperKey, key);
    for (int i = 0; upperKey[i]; i++) upperKey[i] = toupper(upperKey[i]);
    
    if (strlen(upperKey) != 1) {
        printf("[ERROR] Line %d: CTRL_C, CTRL_V, etc. require single character\n", lineNum);
        return;
    }
    
    pressCtrl(upperKey[0]);
}

/* ═══════════════════════════════════════════════════════════
 *                    Main Interpreter
 * ═══════════════════════════════════════════════════════════*/

void executeLine(const char *line, int lineNum);

void executeRepeat(const char *args, int lineNum) {
    if (strlen(args) == 0) {
        printf("[ERROR] Line %d: REPEAT requires a number\n", lineNum);
        return;
    }
    if (!isNumber(args)) {
        printf("[ERROR] Line %d: REPEAT requires a valid number\n", lineNum);
        return;
    }
    int repeatCount = atoi(args);
    if (repeatCount <= 0) {
        printf("[ERROR] Line %d: REPEAT count must be positive\n", lineNum);
        return;
    }
    
    /* Find matching END */
    int endLine = -1;
    for (int j = lineNum + 1; j < totalLines; j++) {
        char lineCopy[MAX_LINE_LENGTH];
        strcpy(lineCopy, lines[j]);
        char *trimmed = trim(lineCopy);
        
        char checkCmd[64] = {0};
        sscanf(trimmed, "%s", checkCmd);
        for (int k = 0; checkCmd[k]; k++) checkCmd[k] = toupper(checkCmd[k]);
        
        if (strcmp(checkCmd, "END") == 0) {
            endLine = j;
            break;
        }
    }
    
    if (endLine == -1) {
        printf("[ERROR] Line %d: REPEAT without END\n", lineNum);
        return;
    }
    
    /* Execute loop */
    for (int r = 0; r < repeatCount; r++) {
        for (int j = lineNum + 1; j < endLine; j++) {
            executeLine(lines[j], j + 1);
        }
    }
}

void executeLine(const char *line, int lineNum) {
    char lineCopy[MAX_LINE_LENGTH];
    strcpy(lineCopy, line);
    
    char *trimmed = trim(lineCopy);
    
    if (strlen(trimmed) == 0) return;
    
    char command[64] = {0};
    char args[MAX_LINE_LENGTH] = {0};
    
    sscanf(trimmed, "%s %[^\n]", command, args);
    
    for (int i = 0; command[i]; i++) command[i] = toupper(command[i]);
    
    /* COMMENT - ignored */
    if (strcmp(command, "COMMENT") == 0) {
        return;
    }
    
    /* TYPE */
    else if (strcmp(command, "TYPE") == 0) {
        if (strlen(args) == 0) {
            printf("[ERROR] Line %d: TYPE requires text argument\n", lineNum);
            return;
        }
        typeString(args);
    }
    
    /* TIME */
    else if (strcmp(command, "TIME") == 0) {
        if (strlen(args) == 0) {
            printf("[ERROR] Line %d: TIME requires delay value in milliseconds\n", lineNum);
            return;
        }
        if (!isNumber(args)) {
            printf("[ERROR] Line %d: TIME requires a valid number, got '%s'\n", lineNum, args);
            return;
        }
        int ms = atoi(args);
        if (ms < 0) {
            printf("[ERROR] Line %d: TIME delay cannot be negative\n", lineNum);
            return;
        }
        delay(ms);
    }
    
    /* DEFAULT_DELAY */
    else if (strcmp(command, "DEFAULT_DELAY") == 0 || strcmp(command, "DEFAULTDELAY") == 0) {
        if (strlen(args) == 0) {
            printf("[ERROR] Line %d: DEFAULT_DELAY requires delay value\n", lineNum);
            return;
        }
        if (!isNumber(args)) {
            printf("[ERROR] Line %d: DEFAULT_DELAY requires a valid number\n", lineNum);
            return;
        }
        defaultDelay = atoi(args);
    }
    
    /* PRESS */
    else if (strcmp(command, "PRESS") == 0) {
        processPress(args, lineNum);
    }
    
    /* ENTER */
    else if (strcmp(command, "ENTER") == 0) {
        pressKey(VK_RETURN);
    }
    
    /* BACK */
    else if (strcmp(command, "BACK") == 0) {
        pressKey(VK_BACK);
    }
    
    /* TAB */
    else if (strcmp(command, "TAB") == 0) {
        pressKey(VK_TAB);
    }
    
    /* ESC */
    else if (strcmp(command, "ESC") == 0) {
        pressKey(VK_ESCAPE);
    }
    
    /* SPACE */
    else if (strcmp(command, "SPACE") == 0) {
        pressKey(VK_SPACE);
    }
    
    /* DELETE */
    else if (strcmp(command, "DELETE") == 0) {
        pressKey(VK_DELETE);
    }
    
    /* INSERT */
    else if (strcmp(command, "INSERT") == 0) {
        pressKey(VK_INSERT);
    }
    
    /* UP */
    else if (strcmp(command, "UP") == 0) {
        pressKey(VK_UP);
    }
    
    /* DOWN */
    else if (strcmp(command, "DOWN") == 0) {
        pressKey(VK_DOWN);
    }
    
    /* LEFT */
    else if (strcmp(command, "LEFT") == 0) {
        pressKey(VK_LEFT);
    }
    
    /* RIGHT */
    else if (strcmp(command, "RIGHT") == 0) {
        pressKey(VK_RIGHT);
    }
    
    /* HOME */
    else if (strcmp(command, "HOME") == 0) {
        pressKey(VK_HOME);
    }
    
    /* END - keyboard key */
    else if (strcmp(command, "END") == 0) {
        pressKey(VK_END);
    }
    
    /* PAGEUP */
    else if (strcmp(command, "PAGEUP") == 0) {
        pressKey(VK_PRIOR);
    }
    
    /* PAGEDOWN */
    else if (strcmp(command, "PAGEDOWN") == 0) {
        pressKey(VK_NEXT);
    }
    
    /* CAPS */
    else if (strcmp(command, "CAPS") == 0) {
        pressKey(VK_CAPITAL);
    }
    
    /* PRTSC */
    else if (strcmp(command, "PRTSC") == 0) {
        pressKey(VK_SNAPSHOT);
    }
    
    /* PAUSE */
    else if (strcmp(command, "PAUSE") == 0) {
        pressKey(VK_PAUSE);
    }
    
    /* WINDOWS / WIN */
    else if (strcmp(command, "WINDOWS") == 0 || strcmp(command, "WIN") == 0) {
        processWindows(args, lineNum);
    }
    
    /* CONTROL / CTRL */
    else if (strcmp(command, "CONTROL") == 0 || strcmp(command, "CTRL") == 0) {
        processControl(args, lineNum);
    }
    
    /* ALT */
    else if (strcmp(command, "ALT") == 0) {
        processAlt(args, lineNum);
    }
    
    /* SHIFT */
    else if (strcmp(command, "SHIFT") == 0) {
        processShift(args, lineNum);
    }
    
    /* F1-F12 */
    else if (strcmp(command, "F1") == 0) pressKey(VK_F1);
    else if (strcmp(command, "F2") == 0) pressKey(VK_F2);
    else if (strcmp(command, "F3") == 0) pressKey(VK_F3);
    else if (strcmp(command, "F4") == 0) pressKey(VK_F4);
    else if (strcmp(command, "F5") == 0) pressKey(VK_F5);
    else if (strcmp(command, "F6") == 0) pressKey(VK_F6);
    else if (strcmp(command, "F7") == 0) pressKey(VK_F7);
    else if (strcmp(command, "F8") == 0) pressKey(VK_F8);
    else if (strcmp(command, "F9") == 0) pressKey(VK_F9);
    else if (strcmp(command, "F10") == 0) pressKey(VK_F10);
    else if (strcmp(command, "F11") == 0) pressKey(VK_F11);
    else if (strcmp(command, "F12") == 0) pressKey(VK_F12);
    
    /* CTRL shortcuts */
    else if (strcmp(command, "CTRL_C") == 0) processCtrlShortcut("C", lineNum);
    else if (strcmp(command, "CTRL_V") == 0) processCtrlShortcut("V", lineNum);
    else if (strcmp(command, "CTRL_X") == 0) processCtrlShortcut("X", lineNum);
    else if (strcmp(command, "CTRL_A") == 0) processCtrlShortcut("A", lineNum);
    else if (strcmp(command, "CTRL_S") == 0) processCtrlShortcut("S", lineNum);
    else if (strcmp(command, "CTRL_Z") == 0) processCtrlShortcut("Z", lineNum);
    else if (strcmp(command, "CTRL_F") == 0) processCtrlShortcut("F", lineNum);
    else if (strcmp(command, "CTRL_W") == 0) processCtrlShortcut("W", lineNum);
    else if (strcmp(command, "CTRL_T") == 0) processCtrlShortcut("T", lineNum);
    else if (strcmp(command, "CTRL_N") == 0) processCtrlShortcut("N", lineNum);
    else if (strcmp(command, "CTRL_P") == 0) processCtrlShortcut("P", lineNum);
    else if (strcmp(command, "CTRL_R") == 0) processCtrlShortcut("R", lineNum);
    else if (strcmp(command, "CTRL_E") == 0) processCtrlShortcut("E", lineNum);
    else if (strcmp(command, "CTRL_D") == 0) processCtrlShortcut("D", lineNum);
    else if (strcmp(command, "CTRL_G") == 0) processCtrlShortcut("G", lineNum);
    else if (strcmp(command, "CTRL_H") == 0) processCtrlShortcut("H", lineNum);
    else if (strcmp(command, "CTRL_K") == 0) processCtrlShortcut("K", lineNum);
    else if (strcmp(command, "CTRL_L") == 0) processCtrlShortcut("L", lineNum);
    
    /* REPEAT - loop */
    else if (strcmp(command, "REPEAT") == 0) {
        executeRepeat(args, lineNum);
    }
    
    /* END - loop end marker (ignored when executed normally) */
    else if (strcmp(command, "END") == 0) {
        return;
    }
    
    /* Unknown command */
    else {
        printf("[ERROR] Line %d: Unknown command '%s'\n", lineNum, command);
    }
    
    /* Apply default delay if set */
    if (defaultDelay > 0) {
        delay(defaultDelay);
    }
}

/* ═══════════════════════════════════════════════════════════
 *                    File Reading
 * ═══════════════════════════════════════════════════════════*/

int readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("[ERROR] Cannot open file: %s\n", filename);
        return 0;
    }
    
    totalLines = 0;
    while (fgets(lines[totalLines], MAX_LINE_LENGTH, fp) != NULL) {
        lines[totalLines][strcspn(lines[totalLines], "\r\n")] = 0;
        totalLines++;
        if (totalLines >= MAX_LINES) {
            printf("[ERROR] File too large (max %d lines)\n", MAX_LINES);
            fclose(fp);
            return 0;
        }
    }
    
    fclose(fp);
    return 1;
}

/* ═══════════════════════════════════════════════════════════
 *                    Main Function
 * ═══════════════════════════════════════════════════════════*/

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        // حالت عادی: اجرای فایل اسکریپت از آرگومان
        if (!readFile(argv[1])) {
            return 1;
        }
        printf("Executing %s (%d lines)...\n", argv[1], totalLines);
    } else {
        // حالت باندل شده: اسکریپت به انتهای همین exe الصاق شده
        char exePath[MAX_PATH];
        GetModuleFileName(NULL, exePath, MAX_PATH);

        FILE *self = fopen(exePath, "rb");
        if (!self) {
            printf("[ERROR] Cannot open self executable.\n");
            return 1;
        }

        // ۴ بایت آخر فایل = اندازه اسکریپت (unsigned int)
        fseek(self, -4, SEEK_END);
        unsigned int scriptSize = 0;
        fread(&scriptSize, sizeof(unsigned int), 1, self);

        // برگشت به ابتدای بخش اسکریپت
        fseek(self, -4 - (long)scriptSize, SEEK_END);

        // خواندن اسکریپت خط به خط (دقیقاً مثل readFile)
        totalLines = 0;
        char lineBuf[MAX_LINE_LENGTH];
        long bytesRead = 0;

        while (bytesRead < scriptSize && fgets(lineBuf, MAX_LINE_LENGTH, self)) {
            // حذف کاراکترهای خط جدید
            lineBuf[strcspn(lineBuf, "\r\n")] = 0;
            strcpy(lines[totalLines], lineBuf);
            totalLines++;
            // +1 برای \n که fgets مصرف کرده ولی ما حذف کردیم
            bytesRead += strlen(lineBuf) + 1;
            if (totalLines >= MAX_LINES) {
                printf("[ERROR] Bundled script too large.\n");
                fclose(self);
                return 1;
            }
        }
        fclose(self);

        printf("Executing bundled script (%d lines)...\n", totalLines);
    }

    // اجرای خطوط (بدون تغییر)
    for (int i = 0; i < totalLines; i++) {
        executeLine(lines[i], i + 1);
    }

    printf("Done!\n");
    return 0;
}
