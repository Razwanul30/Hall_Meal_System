/* meal/meal.c */
#include <stdio.h>
#include <time.h>

#include "../config.h"
#include "meal.h"
#include "../student/student.h"

/* Default prices (modifiable by admin) */
static double price_breakfast = 20.0;
static double price_lunch = 50.0;
static double price_dinner = 40.0;

void display_menu(void) {
    printf("\n--- Today's Menu & Prices ---\n");
    printf("1) Breakfast : %.2lf tk\n", price_breakfast);
    printf("2) Lunch     : %.2lf tk\n", price_lunch);
    printf("3) Dinner    : %.2lf tk\n", price_dinner);
}

double get_price_for_meal(int meal_type) {
    switch (meal_type) {
        case MEAL_BREAKFAST: return price_breakfast;
        case MEAL_LUNCH:     return price_lunch;
        case MEAL_DINNER:    return price_dinner;
        default: return 0.0;
    }
}

int book_meal(const char *roll, int day, int meal_type) {
    if (day < 1 || day > DAYS_IN_MONTH) {
        printf("Invalid day: choose 1..%d\n", DAYS_IN_MONTH);
        return 0;
    }
    if (meal_type < 0 || meal_type >= MEALS_PER_DAY) {
        printf("Invalid meal type.\n");
        return 0;
    }

    Student *s = get_student_by_roll(roll);
    if (!s) { printf("Student not found.\n"); return 0; }

    if (s->meals[day-1][meal_type]) {
        printf("Already booked for day %d meal %d.\n", day, meal_type+1);
        return 0;
    }

    double price = get_price_for_meal(meal_type);
    if (s->balance < price) {
        printf("Insufficient balance. Need %.2lf tk.\n", price);
        return 0;
    }

    s->meals[day-1][meal_type] = 1;
    s->balance -= price;

    /* persist */
    save_students_storage();
    printf("Booked day %d, meal %d. %.2lf tk deducted. New balance: %.2lf\n", day, meal_type+1, price, s->balance);
    return 1;
}

int cancel_meal(const char *roll, int day, int meal_type) {
    if (day < 1 || day > DAYS_IN_MONTH) {
        printf("Invalid day: choose 1..%d\n", DAYS_IN_MONTH);
        return 0;
    }
    if (meal_type < 0 || meal_type >= MEALS_PER_DAY) {
        printf("Invalid meal type.\n");
        return 0;
    }

    Student *s = get_student_by_roll(roll);
    if (!s) { printf("Student not found.\n"); return 0; }

    if (!s->meals[day-1][meal_type]) {
        printf("No booking exists to cancel for day %d meal %d.\n", day, meal_type+1);
        return 0;
    }

    /* Cancel policy: cannot cancel dinner after 16:00 */
    if (meal_type == MEAL_DINNER) {
        time_t t = time(NULL);
        struct tm *lt = localtime(&t);
        if (lt && lt->tm_hour >= 16) {
            printf("Dinner cannot be cancelled after 16:00 local time.\n");
            return 0;
        }
    }

    double price = get_price_for_meal(meal_type);
    double refund = price * 0.8; /* 80% refund */
    s->meals[day-1][meal_type] = 0;
    s->balance += refund;

    save_students_storage();
    printf("Cancelled day %d meal %d. Refund: %.2lf tk credited. New balance: %.2lf\n",
           day, meal_type+1, refund, s->balance);
    return 1;
}

void admin_update_price(int meal_type, double price) {
    if (price < 0.0) {
        printf("Price cannot be negative.\n");
        return;
    }
    switch (meal_type) {
        case MEAL_BREAKFAST: price_breakfast = price; break;
        case MEAL_LUNCH:     price_lunch = price; break;
        case MEAL_DINNER:    price_dinner = price; break;
        default: printf("Invalid meal type.\n"); return;
    }
    printf("Price updated.\n");
}
