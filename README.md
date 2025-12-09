# Mess Management System (C Project)

A modular Mess Management System built in **C**, designed for university-level project submission.  
This project uses **binary file storage**, a **layered architecture**, and separate modules for students, meals, billing, authentication, and file handling.

## Features

### 1. Student Management
- Register student  
- View profile  
- Update room  
- Store data in a binary file (`students.bin`)  
- Functions:
  - register_student()
  - get_student_by_roll()
  - list_all_students()
  - update_room()

### 2. Meal Management
- Book meals  
- Cancel meals  
- View menu & prices  
- Dynamic price update by admin  
- Functions:
  - book_meal()
  - cancel_meal()
  - get_price_for_meal()
  - display_menu()

### 3. Billing System
- Individual monthly bill calculation  
- Monthly summary generation  
- Balance adjust system  
- Functions:
  - calculate_monthly_bill_individual()
  - generate_monthly_report()
  - adjust_student_balance()

### 4. Authentication (Simple)
- Admin login  
- Student login by roll number  
- No password required for student login  

### 5. File Handling (Binary Storage)
- Creates data/ folder automatically  
- Saves students in binary format  
- Loads binary data on startup  
- Functions:
  - fh_save_students()
  - fh_load_students()
  - fh_ensure_data_dir()

## Project Structure

MessSystem/
├── main.c  
├── config.h  
├── auth/  
├── student/  
├── meal/  
├── billing/  
├── file_handler/  
└── data/  
    └── students.bin  

## Compilation

```bash
gcc main.c auth/*.c student/*.c meal/*.c billing/*.c file_handler/*.c -o mess
````

Run:

```bash
./mess
```

## Binary Files

`data/students.bin` – Stores all student data in binary.

## Conclusion

This project demonstrates modular C programming, binary storage, billing, meal tracking, and admin–student workflow.
Suitable for academic project submission.

```

---

