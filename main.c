/* main.c */
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "auth/auth.h"
#include "student/student.h"
#include "meal/meal.h"
#include "billing/billing.h"

void admin_menu(void);
void student_menu(const char *roll);

int main(void) {
    init_students();

    while (1) {
        printf("\n=== Mess Management System ===\n");
        printf("1) Admin Login\n");
        printf("2) Student Login\n");
        printf("3) Quick Register (Admin required)\n");
        printf("4) Exit\n");
        printf("Choose: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            if (admin_login()) admin_menu();
        } else if (choice == 2) {
            char roll[16];
            if (!student_login(roll)) { printf("Login failed.\n"); continue; }
            Student *s = get_student_by_roll(roll);
            if (!s) {
                printf("No student with that roll. Ask admin to register you.\n");
            } else {
                student_menu(roll);
            }
        } else if (choice == 3) {
            if (admin_login()) register_student();
        } else if (choice == 4) {
            printf("Exiting... Goodbye.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}

void admin_menu(void) {
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1) List Students\n");
        printf("2) Register Student\n");
        printf("3) Update Meal Prices\n");
        printf("4) Generate Monthly Report\n");
        printf("5) Back to Main\n");
        printf("Choose: ");
        int op;
        if (scanf("%d", &op) != 1) { while (getchar()!='\n'); continue; }

        if (op == 1) {
            list_all_students();
        } else if (op == 2) {
            register_student();
        } else if (op == 3) {
            display_menu();
            printf("Choose meal to update (1-Breakfast,2-Lunch,3-Dinner): ");
            int m; scanf("%d", &m);
            if (m < 1 || m > 3) { printf("Invalid meal.\n"); continue; }
            printf("Enter new price: ");
            double p; scanf("%lf", &p);
            admin_update_price(m-1, p);
        } else if (op == 4) {
            generate_monthly_report();
        } else if (op == 5) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
}

void student_menu(const char *roll) {
    while (1) {
        printf("\n--- Student Menu (%s) ---\n", roll);
        printf("1) View Profile\n");
        printf("2) Update Room\n");
        printf("3) Display Menu & Prices\n");
        printf("4) Book Meal\n");
        printf("5) Cancel Meal\n");
        printf("6) Calculate My Monthly Bill\n");
        printf("7) Back\n");
        printf("Choose: ");
        int op;
        if (scanf("%d", &op) != 1) { while (getchar()!='\n'); continue; }

        if (op == 1) {
            view_profile(roll);
        } else if (op == 2) {
            update_room(roll);
        } else if (op == 3) {
            display_menu();
        } else if (op == 4) {
            printf("Enter day (1-%d): ", DAYS_IN_MONTH);
            int day; scanf("%d", &day);
            printf("Meal type (1-Breakfast,2-Lunch,3-Dinner): ");
            int mt; scanf("%d", &mt);
            if (mt < 1 || mt > 3) { printf("Invalid meal.\n"); continue; }
            book_meal(roll, day, mt-1);
        } else if (op == 5) {
            printf("Enter day (1-%d): ", DAYS_IN_MONTH);
            int day; scanf("%d", &day);
            printf("Meal type (1-Breakfast,2-Lunch,3-Dinner): ");
            int mt; scanf("%d", &mt);
            if (mt < 1 || mt > 3) { printf("Invalid meal.\n"); continue; }
            cancel_meal(roll, day, mt-1);
        } else if (op == 6) {
            calculate_monthly_bill_individual(roll);
        } else if (op == 7) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
}
