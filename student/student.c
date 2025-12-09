/* student/student.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../config.h"
#include "student.h"
#include "../file_handler/file_handler.h"

/* Internal storage */
static Student students[MAX_STUDENTS];
static int student_count = 0;

int init_students(void) {
    /* ensure data dir exists */
    fh_ensure_data_dir();
    int loaded = fh_load_students(students, MAX_STUDENTS);
    if (loaded < 0) {
        student_count = 0;
        return 0;
    }
    student_count = loaded;
    return student_count;
}

int register_student(void) {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot register: max capacity reached.\n");
        return 0;
    }

    Student s;
    memset(&s, 0, sizeof(Student));
    printf("\n--- Register New Student ---\n");
    printf("Enter Roll (max 15 chars): ");
    if (scanf("%15s", s.roll_no) != 1) { while(getchar()!='\n'); return 0; }

    /* check duplicate */
    for (int i = 0; i < student_count; ++i) {
        if (strcmp(students[i].roll_no, s.roll_no) == 0) {
            printf("Student with roll '%s' already exists.\n", s.roll_no);
            return 0;
        }
    }

    printf("Enter Full Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Room number: ");
    if (scanf("%d", &s.room) != 1) { while(getchar()!='\n'); return 0; }

    s.balance = 1000.0; /* default initial deposit */
    for (int d = 0; d < DAYS_IN_MONTH; ++d)
        for (int m = 0; m < MEALS_PER_DAY; ++m)
            s.meals[d][m] = 0;

    students[student_count++] = s;
    if (fh_save_students(students, student_count) != 0) {
        printf("Warning: failed to persist new student.\n");
    }
    printf("Student '%s' registered successfully.\n", s.roll_no);
    return 1;
}

Student* get_student_by_roll(const char *roll) {
    if (!roll) return NULL;
    for (int i = 0; i < student_count; ++i) {
        if (strcmp(students[i].roll_no, roll) == 0)
            return &students[i];
    }
    return NULL;
}

void view_profile(const char *roll) {
    Student *s = get_student_by_roll(roll);
    if (!s) {
        printf("Student with roll '%s' not found.\n", roll);
        return;
    }
    printf("\n--- Profile ---\n");
    printf("Roll : %s\n", s->roll_no);
    printf("Name : %s\n", s->name);
    printf("Room : %d\n", s->room);
    printf("Balance : %.2lf\n", s->balance);
    int cnt = 0;
    for (int d = 0; d < DAYS_IN_MONTH; ++d)
        for (int m = 0; m < MEALS_PER_DAY; ++m)
            if (s->meals[d][m]) cnt++;
    printf("Meals booked this month: %d\n", cnt);
}

int update_room(const char *roll) {
    Student *s = get_student_by_roll(roll);
    if (!s) {
        printf("Student not found.\n");
        return 0;
    }
    printf("Current room: %d\n", s->room);
    printf("Enter new room number: ");
    int new_room;
    if (scanf("%d", &new_room) != 1) { while(getchar()!='\n'); return 0; }
    s->room = new_room;
    if (fh_save_students(students, student_count) != 0) {
        printf("Warning: failed to save updated room.\n");
    }
    printf("Room updated.\n");
    return 1;
}

void list_all_students(void) {
    printf("\n--- Registered Students (%d) ---\n", student_count);
    for (int i = 0; i < student_count; ++i) {
        printf("%d) %s | %s | Room:%d | Balance: %.2lf\n",
               i+1, students[i].roll_no, students[i].name, students[i].room, students[i].balance);
    }
}

Student* get_all_students_array(void) {
    return students;
}

int get_student_count(void) {
    return student_count;
}

int save_students_storage(void) {
    return (fh_save_students(students, student_count) == 0) ? 1 : 0;
}
