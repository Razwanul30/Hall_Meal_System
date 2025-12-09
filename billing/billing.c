/* billing/billing.c */
#include <stdio.h>
#include "../student/student.h"
#include "billing.h"
#include "../meal/meal.h"

void calculate_monthly_bill_individual(const char *roll) {
    Student *s = get_student_by_roll(roll);
    if (!s) {
        printf("Student not found.\n");
        return;
    }

    double total = 0.0;
    for (int d = 0; d < DAYS_IN_MONTH; ++d) {
        if (s->meals[d][MEAL_BREAKFAST]) total += get_price_for_meal(MEAL_BREAKFAST);
        if (s->meals[d][MEAL_LUNCH])     total += get_price_for_meal(MEAL_LUNCH);
        if (s->meals[d][MEAL_DINNER])    total += get_price_for_meal(MEAL_DINNER);
    }

    printf("\n--- Monthly Bill for %s (%s) ---\n", s->name, s->roll_no);
    printf("Total meal cost this month : %.2lf tk\n", total);
    printf("Current balance            : %.2lf tk\n", s->balance);
    if (s->balance < 0.0) {
        printf("Due (negative balance)    : %.2lf tk\n", -s->balance);
    }
}

void generate_monthly_report(void) {
    Student *arr = get_all_students_array();
    int n = get_student_count();
    double grand_total = 0.0;
    printf("\n--- Monthly Summary Report (%d students) ---\n", n);
    for (int i = 0; i < n; ++i) {
        double total = 0.0;
        for (int d = 0; d < DAYS_IN_MONTH; ++d) {
            if (arr[i].meals[d][MEAL_BREAKFAST]) total += get_price_for_meal(MEAL_BREAKFAST);
            if (arr[i].meals[d][MEAL_LUNCH])     total += get_price_for_meal(MEAL_LUNCH);
            if (arr[i].meals[d][MEAL_DINNER])    total += get_price_for_meal(MEAL_DINNER);
        }
        grand_total += total;
        printf("%s | %s | Total: %.2lf | Balance: %.2lf\n",
               arr[i].roll_no, arr[i].name, total, arr[i].balance);
    }
    printf("Grand total for month: %.2lf tk\n", grand_total);
}

int adjust_student_balance(const char *roll, double amount, const char *reason) {
    Student *s = get_student_by_roll(roll);
    if (!s) return 0;
    s->balance += amount;
    /* reason currently unused, could be logged */
    save_students_storage();
    return 1;
}
