#ifndef CONFIG_H
#define CONFIG_H

/* Paths for data files (relative to executable working directory).
   You can change these to absolute paths if needed. */
#define DATA_DIR          "data"
#define STUDENTS_FILE     DATA_DIR "/students.bin"
#define MEALS_FILE        DATA_DIR "/meals.bin"
#define MENU_FILE         DATA_DIR "/menu.bin"
#define BILLING_FILE      DATA_DIR "/billing.bin"

/* Constants */
#define DAYS_IN_MONTH     30
#define MEALS_PER_DAY     3   /* 0:Breakfast, 1:Lunch, 2:Dinner */
#define MAX_STUDENTS      500

/* Admin default password (override in auth.c for deployment) */
#define DEFAULT_ADMIN_PASSWORD "admin123"

#endif /* CONFIG_H */
