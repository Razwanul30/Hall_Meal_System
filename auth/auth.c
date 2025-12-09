/* auth/auth.c */
#include <stdio.h>
#include <string.h>

#include "../config.h"
#include "auth.h"

int admin_login(void) {
    char pass[128];
    printf("\n[Admin] Enter password: ");
    if (scanf("%127s", pass) != 1) {
        while (getchar() != '\n');
        return 0;
    }

    if (strcmp(pass, DEFAULT_ADMIN_PASSWORD) == 0) {
        printf("Admin login successful.\n");
        return 1;
    } else {
        printf("Invalid password.\n");
        return 0;
    }
}

int student_login(char *roll) {
    if (!roll) return 0;
    printf("\n[Student] Enter Roll No: ");
    if (scanf("%15s", roll) != 1) {
        while (getchar() != '\n');
        return 0;
    }
    return 1;
}
