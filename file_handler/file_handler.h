#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../config.h"
#include "../student/student.h"

/* File handler API */

/* Save students array (count) to STUDENTS_FILE.
   Returns 0 on success, -1 on error. */
int fh_save_students(const Student *list, int count);

/* Load students into preallocated array 'list' up to max_count.
   Returns number of students loaded (>=0), or -1 on error. */
int fh_load_students(Student *list, int max_count);

/* Ensure data directory exists (creates DATA_DIR). Returns 0 on success. */
int fh_ensure_data_dir(void);

/* (Optional) other functions for meals/menu/billing persistence */
int fh_save_menu(const void *menu_data, size_t bytes);
int fh_load_menu(void *menu_data, size_t bytes);

#endif /* FILE_HANDLER_H */
