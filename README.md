# Student-Mess-Management-System (C Project)

A simple and modular **Student Mess Management System** written in
**C**, designed for university-level projects.\
It includes **student management**, **meal tracking**,
**authentication**, and file-based storage with a clean layered
architecture.

------------------------------------------------------------------------

## 📌 Features

### ✅ 1. Authentication System

-   Username + password login\
-   Password verification\
-   File-based storage (`auth.bin`)

### ✅ 2. Student Management

-   Add student\
-   List students\
-   Student file storage\
-   Functions:
    -   add_student()
    -   list_students()
    -   find_student_by_id()

### ✅ 3. Meal Management

-   Add meal entry\
-   List meals\
-   Student-wise meal records\
-   Functions:
    -   add_meal()
    -   list_meals()
    -   list_meals_for_student()

------------------------------------------------------------------------

## 🧩 Project Structure

project/ │ ├── main.c ├── auth/ │ ├── auth.c │ └── auth.h │ ├── student/
│ ├── student.c │ └── student.h │ ├── meal/ │ ├── meal.c │ └── meal.h │
├── file_handler/ │ ├── file_handler.c │ └── file_handler.h │ ├──
config.h └── README.md

------------------------------------------------------------------------

## ⚙️ How to Compile

### Linux / Mac:

gcc main.c auth/auth.c student/student.c meal/meal.c
file_handler/file_handler.c -o mess

### Windows (MinGW):

gcc main.c auth/auth.c student/student.c meal/meal.c
file_handler/file_handler.c -o mess.exe

------------------------------------------------------------------------

## ▶️ How to Run

./mess

Windows: mess.exe

------------------------------------------------------------------------

## 📁 File Storage Format

auth.bin username password

students.bin ID Name

meals.bin student_id date meal_count

------------------------------------------------------------------------

## 🚀 Future Improvements

-   Monthly meal calculation\
-   Cost calculator\
-   Admin dashboard\
-   Password hashing\
-   Export to CSV/JSON

------------------------------------------------------------------------

## ✔️ Conclusion

This is a clean, modular, and fully functional **C-based Student Mess
Management System**, perfect for university-level project submission.\
It demonstrates: - File Handling\
- Modular Programming\
- Authentication\
- Structured Data Storage

**Thank you for using this project!**
