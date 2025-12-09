#ifndef MEAL_H
#define MEAL_H

#include "../config.h"

/* meal types */
#define MEAL_BREAKFAST 0
#define MEAL_LUNCH     1
#define MEAL_DINNER    2

/* Meal module API */

/* Display current menu & prices (prints to stdout). */
void display_menu(void);

/* Book a meal for a student (roll), specified day (1..DAYS_IN_MONTH) and meal_type.
   Returns 1 on success, 0 on failure. */
int book_meal(const char *roll, int day, int meal_type);

/* Cancel a previously booked meal. Returns 1 on success, 0 on failure.
   Cancellation policy (e.g., dinner after 16:00) enforced in implementation. */
int cancel_meal(const char *roll, int day, int meal_type);

/* Admin: update price for a meal type */
void admin_update_price(int meal_type, double price);

/* Get current price for a meal type */
double get_price_for_meal(int meal_type);

#endif /* MEAL_H */
