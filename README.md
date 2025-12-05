# SRMS_Project.
<<<<<<< HEAD
# Student Result Management System (SRMS)
“Student Result Management System in C with Dashboard UI”
Features:
- Add, Delete, Update, Search Students
- Attendance Module
- CGPA, Percentage & Pass/Fail
- Sorting & Search by Name
- Hidden Password Input
- Console Dashboard UI
=======
# 📚 Student Result Management System (SRMS)

A Console-based Student Result Management System implemented in C, featuring a dashboard-style user interface and various student, result, and attendance management modules.

## ✨ Features

The system is built to provide comprehensive management functionalities:

* [cite_start]**Student Management** [cite: 1][cite_start]: Allows for adding new students, displaying all records, and deleting existing student records[cite: 1].
* [cite_start]**Results & Grading**: Automatically calculates **CGPA** (by dividing marks by 10) [cite: 1] [cite_start]and displays **Pass/Fail** status (pass mark is 40)[cite: 1].
* [cite_start]**Result Metrics**[cite: 1]: Displays Marks, **CGPA**, Percentage, Grade, and the overall Result (PASS/FAIL).
* [cite_start]**Grading System**: Grades are assigned based on marks[cite: 1]:
    * $>= 90$: A+
    * $>= 80$: A
    * $>= 70$: B
    * $>= 60$: C
    * $< 60$: F
* [cite_start]**Attendance Module**[cite: 1]: Users can **Mark Attendance** (P/A for Present/Absent) and **View Attendance** percentage for individual students by Roll No.
* [cite_start]**Search Functionality**: Allows searching for students by **Roll No** or **Name**[cite: 1].
* **Sorting Functionality**: Provides options to sort the student list by:
    * [cite_start]Name (A-Z) [cite: 1]
    * [cite_start]Marks (High-Low) [cite: 1]
    * [cite_start]Roll No (Low-High) [cite: 1]
* **Security & UI**:
    * [cite_start]Secure **Login** system [cite: 1] [cite_start]with an initial default password (**admin123** is the default)[cite: 1].
    * [cite_start]Option to **Change Password**[cite: 1].
    * [cite_start]**Hidden Password Input** (using `*` masking)[cite: 1].
    * [cite_start]Colorful **Console Dashboard UI** (using `windows.h` for colored text)[cite: 1].

## 🛠️ Project Structure

* `srms_dashboard.c` / `srms.c`: The main C source code file containing all logic, functions, and the dashboard menu.
* [cite_start]`students.txt`: Stores student records in a comma-separated format (`RollNo,Name,Marks,Grade\n`)[cite: 1694].
* [cite_start]`attendance.txt`: Stores attendance records in a comma-separated format (`RollNo,Status\n`)[cite: 1].
* [cite_start]`password.txt`: Stores the administrator's password[cite: 1695].
* `README.md`: This file.

## ⚙️ How to Compile and Run

[cite_start]This project uses system-specific libraries (`conio.h`, `windows.h`) for features like hidden password input and colored text, making it primarily compatible with **Windows** and compilers like MinGW/GCC (as indicated by the compiler details in the executable files [cite: 86]).

### Prerequisites

* [cite_start]A C compiler (e.g., GCC/MinGW, version 4.9.2 was used for the provided executables [cite: 86]).
* A Windows operating system (for full functionality).

### Steps

1.  **Compile the source code**:
    ```bash
    gcc srms_dashboard.c -o srms_dashboard.exe -m64
    ```
2.  **Run the executable**:
    ```bash
    ./srms_dashboard.exe
    ```

## 🔐 Credentials (Default)

The system is initialized with a default administrator password.

| User | Default Password | Role |
| :--- | :--- | :--- |
| `admin` | [cite_start]`admin123` [cite: 1695] | Administrator (Full Access) |

[cite_start]The first time the program runs, it will automatically create `password.txt` if it doesn't exist, containing the default password[cite: 1].
