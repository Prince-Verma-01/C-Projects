1. 🎓 Student Record Management System (C)

A simple and efficient Student Record Management System built using C and binary file handling. This project demonstrates core system programming concepts with a clean, menu-driven interface.

✨ Features
Add new student records
Search records by roll number
Delete records safely
Display all stored records
Persistent data storage using binary files

🛠️ Tech Stack
Language: C
Concepts: Structures, File I/O, Pointers
Storage: Binary files (students.dat)

🚀 Compile & Run
gcc main.c -o student_records
./student_records

🧱 Data Model
Each record stores:
Student Name
Roll Number
Address

📌 Highlights
Safe deletion using a temporary file
Input validation to prevent errors
Modular and readable code
Automatically creates data file


2. 🍽️ Restaurant Management System (C)

A console-based Restaurant Management System developed in C, focused on managing admins, customers, and food products using file handling. This project demonstrates core C programming concepts through a clean, menu-driven interface.

🚀 Features
Admin Authentication (limited login attempts)
Product Management (add & view items)
Customer Registration & Login
Order Placement
Persistent Data Storage using binary files

🛠️ Technologies
Language: C (ANSI C)
Concepts: Structures, File Handling, Strings, Input Validation
Libraries: stdio.h, stdlib.h, string.h, unistd.h

📁 Files Used
restaurant.txt – Admin credentials
rest.txt – Customer records
product.txt – Product inventory

▶️ How to Run
gcc main.c -o restaurant
./restaurant

🔐 Improvements Applied
Removed unsafe functions (gets, fflush(stdin))
Proper input handling
File safety checks

📌 Purpose
Designed as an academic & learning project to understand real-world C programming, data persistence, and structured program design.


3. 🎯 Kaun Banega Crorepati (KBC) – Console Quiz Application

A feature-rich C-based console quiz application inspired by Kaun Banega Crorepati. This project supports Admin and Student modes, enabling secure question management and an engaging quiz experience with prize tracking.

🚀 Features
Admin Mode
Secure login authentication
Add, delete, update, and view questions
Modify prize money
Persistent storage using file handling (ques.txt)
Student Mode
Interactive question navigation (previous / next)
Answer validation with real-time prize accumulation
Automatic termination on wrong answer
Cross-Platform Support
Works on Windows & Linux (Sleep() / sleep() handled)
Dynamic Memory Management
Uses malloc() and realloc() efficiently

📂 File Structure
main.c – Core application logic
ques.txt – Question bank (text-based database)

🔐 Default Admin Credentials
Username: admin
Password: admin123

🛠 Compilation
gcc main.c -o kbc
./kbc

🎓 Learning Highlights
File handling
Structures & pointers
Dynamic memory allocation

Modular programming
✨ Built for learning, scalability, and clean code practices.
