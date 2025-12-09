#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>
#include "../config.h"

/* Student data structure */
typedef struct {
    char roll_no[16];                /* null-terminated roll */
    char name[64];                   /* full name */
    int room;                        /* room number */
    double balance;                  /* current balance (can be negative) */
    int meals[DAYS_IN_MONTH][MEALS_PER_DAY]; /* 0/1 flags for each day and meal */
} Student;

/* Student module API */

/* Initialize in-memory students array from storage.
   Returns number of students loaded (>=0). */
int init_students(void);

/* Register a new student by interactive prompt (admin). 
   Returns 1 on success, 0 on failure. */
int register_student(void);

/* Find student by roll; returns pointer to internal array or NULL if not found.
   NOTE: pointer is valid until next load/save that reallocates internal storage (we keep static array). */
Student* get_student_by_roll(const char *roll);

/* Print profile to stdout (interactive). */
void view_profile(const char *roll);

/* Update room number interactively (saves internally). */
int update_room(const char *roll);

/* List all students (for admin). */
void list_all_students(void);

/* Get pointer to internal students array (for file_handler / billing), and count */
Student* get_all_students_array(void);
int get_student_count(void);

/* Save current students to storage (calls file_handler). Returns 1 on success. */
int save_students_storage(void);

#endif /* STUDENT_H */
