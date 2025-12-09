/* file_handler/file_handler.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "file_handler.h"

#if defined(_WIN32)
  #include <direct.h>
  #define MKDIR(path) _mkdir(path)
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #define MKDIR(path) mkdir(path, 0755)
#endif

int fh_ensure_data_dir(void) {
    /* Try to create DATA_DIR; if exists, MKDIR may fail but that's ok. */
    int rc = MKDIR(DATA_DIR);
    (void)rc; /* ignore return (exists -> non-zero) */
    return 0;
}

int fh_save_students(const Student *list, int count) {
    FILE *fp = fopen(STUDENTS_FILE, "wb");
    if (!fp) {
        perror("fh_save_students: open for write failed");
        return -1;
    }

    if (fwrite(&count, sizeof(int), 1, fp) != 1) {
        perror("fh_save_students: write count failed");
        fclose(fp);
        return -1;
    }

    if (count > 0) {
        if (fwrite(list, sizeof(Student), (size_t)count, fp) != (size_t)count) {
            perror("fh_save_students: write records failed");
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

int fh_load_students(Student *list, int max_count) {
    FILE *fp = fopen(STUDENTS_FILE, "rb");
    if (!fp) {
        /* file may not exist yet */
        return 0;
    }

    int count = 0;
    if (fread(&count, sizeof(int), 1, fp) != 1) {
        perror("fh_load_students: read count failed");
        fclose(fp);
        return -1;
    }

    if (count < 0) {
        fclose(fp);
        return -1;
    }

    if (count > max_count) {
        /* read only up to max_count */
        if (fread(list, sizeof(Student), (size_t)max_count, fp) != (size_t)max_count) {
            perror("fh_load_students: read truncated records failed");
            fclose(fp);
            return -1;
        }
        fclose(fp);
        return max_count;
    } else if (count == 0) {
        fclose(fp);
        return 0;
    } else {
        if (fread(list, sizeof(Student), (size_t)count, fp) != (size_t)count) {
            perror("fh_load_students: read records failed");
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return count;
}

/* Stubs for menu persistence (optional) */
int fh_save_menu(const void *menu_data, size_t bytes) {
    (void)menu_data; (void)bytes;
    /* implement if menu persistence required */
    return 0;
}
int fh_load_menu(void *menu_data, size_t bytes) {
    (void)menu_data; (void)bytes;
    /* implement if menu persistence required */
    return 0;
}
