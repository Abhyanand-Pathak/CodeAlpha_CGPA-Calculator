# CodeAlpha Internship - Task 1: CGPA Calculator

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2FC%2B%2B17-blue.svg)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)
![Internship](https://img.shields.io/badge/Internship-CodeAlpha-orange.svg)

A professional, object-oriented C++ application developed for **CodeAlpha Internship (Task 1)** that computes **Semester Grade Point Average (SGPA)** and **Cumulative Grade Point Average (CGPA)** with support for multiple grading scales, individual course breakdown, input validation, and report file export.

---

## 📌 Task Requirements Addressed

| Requirement | Implementation Detail |
|---|---|
| **Take input for number of courses** | Dynamic user input with validation for number of courses. |
| **Input grade and credit hours for each course** | Course code, title, credits, and grade (supports letter grades or exact numeric points). |
| **Calculate total credits and total grade points** | Computes `Total Points = Credit Hours × Grade Point` per course and aggregated sums. |
| **Compute Semester GPA and Overall CGPA** | Handles single-semester with previous record carry-over or multi-semester calculation. |
| **Display individual course grades and final CGPA** | Formatted ASCII tabular report with performance remarks and text file export. |

---

## 🚀 Key Features

1. **Dual Grading Scale Support**:
   - **10.0 Scale (UGC / AICTE / Indian Universities)**:
     - `O` (10.0) | `A+` (9.0) | `A` (8.0) | `B+` (7.0) | `B` (6.0) | `C` (5.0) | `P` (4.0) | `F` (0.0)
   - **4.0 Scale (US / International Standard)**:
     - `A`/`A+` (4.0) | `A-` (3.7) | `B+` (3.3) | `B` (3.0) | `B-` (2.7) | `C+` (2.3) | `C` (2.0) | `C-` (1.7) | `D` (1.0) | `F` (0.0)
   - **Direct Numeric Input**: Accepts numerical grade points directly (e.g. `8.75`, `3.65`).

2. **Flexible Calculation Modes**:
   - **Mode 1 (Single Semester)**: Compute current semester SGPA with an option to carry forward previous semester credits and CGPA to evaluate updated overall CGPA.
   - **Mode 2 (Multi-Semester)**: Input semester-by-semester records for complete degree tracking.

3. **Input Validation**:
   - Handles non-numeric inputs, negative numbers, out-of-range credits, and invalid grade symbols gracefully without program crashes.

4. **Academic Standing & Performance Remarks**:
   - Automatically classifies the student's final CGPA (e.g., *Outstanding / First Class with Distinction*, *Summa Cum Laude*, *Very Good*, etc.).

5. **File Export Option**:
   - Option to automatically save the formatted grade sheet to `CGPA_Report.txt` for documentation or submission.

---

## 📂 Project Structure

```text
CodeAlpha/
│
├── Task1_CGPA_Calculator/
│   ├── main.cpp                 # Complete C++ source code
│   └── README.md                # Task-specific documentation
│
├── cgpa_calculator.cpp          # Root source file for quick access
├── cgpa_calculator.exe          # Compiled Windows executable
├── CGPA_Report.txt              # Sample generated report
└── README.md                    # Repository overview
```

---

## 🛠️ How to Compile and Run

### Prerequisites
- GCC / MinGW (`g++`) or any C++11/C++14/C++17 compliant compiler.

### Compilation
Using terminal (PowerShell / Command Prompt / Bash):

```bash
# Navigate to the task directory
cd Task1_CGPA_Calculator

# Compile using g++
g++ -O2 -std=c++14 main.cpp -o cgpa_calculator.exe
```

### Execution
```bash
./cgpa_calculator.exe
```

---

## 📊 Sample Program Execution

```text
====================================================================
             CODEALPHA INTERNSHIP TASK 1: CGPA CALCULATOR          
====================================================================

Enter Student Details (press Enter to skip):
 Student Name: Abhyanand Pathak
 Student ID / Roll No: CA-2026-001

Select University Grading Scale:
  1. 10.0 Scale (Standard UGC / Engineering / University scale - O, A+, A, B, etc.)
  2. 4.0 Scale  (US / International scale - 4.0, 3.7, 3.3, 3.0, etc.)
  3. Direct Numeric Grade Point (Custom)
 Enter your choice (1-3): 1

----------------------- GRADING REFERENCE TABLE --------------------
 Grade:   O (10) | A+ (9) | A (8) | B+ (7) | B (6) | C (5) | P (4) | F (0)
 * You can enter the letter grade (e.g. A+, B) or exact numeric points.
--------------------------------------------------------------------

Select Calculation Mode:
  1. Single Semester Calculation (with optional previous CGPA integration)
  2. Multi-Semester Cumulative Calculation (Semester-by-Semester)
 Enter your choice (1-2): 1

Enter Current Semester Number (e.g. 1 to 12): 5

Do you want to include previous semesters to calculate cumulative CGPA? (y/n): y
  Enter Total Credits earned in previous semesters: 80.0
  Enter your previous cumulative CGPA: 8.50

Enter the number of courses taken in Semester 5: 4

--- Entering Details for 4 Courses ---

Course 1 of 4:
  Course Code (e.g. CS101 / MATH): CS501
  Course Name/Title: Database Management Systems
  Credit Hours (e.g. 3, 4, 1.5): 4.0
  Grade (Letter like A+, B or Grade Point): O

Course 2 of 4:
  Course Code (e.g. CS101 / MATH): CS502
  Course Name/Title: Operating Systems
  Credit Hours (e.g. 3, 4, 1.5): 4.0
  Grade (Letter like A+, B or Grade Point): A+

Course 3 of 4:
  Course Code (e.g. CS101 / MATH): CS503
  Course Name/Title: Design and Analysis of Algorithms
  Credit Hours (e.g. 3, 4, 1.5): 4.0
  Grade (Letter like A+, B or Grade Point): A

Course 4 of 4:
  Course Code (e.g. CS101 / MATH): CS504
  Course Name/Title: Operating Systems Lab
  Credit Hours (e.g. 3, 4, 1.5): 2.0
  Grade (Letter like A+, B or Grade Point): O

====================================================================
                     ACADEMIC EVALUATION RESULTS                    
====================================================================
 Student Name : Abhyanand Pathak
 Student ID   : CA-2026-001

------------------------------------------------------------------------
                       SEMESTER 5 GRADE REPORT
------------------------------------------------------------------------
No.   Course Code   Course Name              Credits   Grade   Grade Pts
------------------------------------------------------------------------
1     CS501         Database Management...       4.0       O       40.00
2     CS502         Operating Systems            4.0      A+       36.00
3     CS503         Design and Analysis...       4.0       A       32.00
4     CS504         Operating Systems Lab        2.0       O       20.00
------------------------------------------------------------------------
Semester Total:                                 14.0              128.00
========================================================================
  >> Semester 5 GPA (SGPA): 9.14
========================================================================

====================================================================
                     FINAL CUMULATIVE SUMMARY                       
====================================================================
 Previous Credits Carried Over  : 80.0
 Previous Grade Points          : 680.00
 New Semester(s) Credits        : 14.0
 New Semester(s) Grade Points   : 128.00
--------------------------------------------------------------------
 Grand Total Credits            : 94.0
 Grand Total Grade Points       : 808.00
 OVERALL CGPA                   : 8.60
 Performance Remark             : Excellent (First Class)
====================================================================

Would you like to export this report to a text file (CGPA_Report.txt)? (y/n): y
[+] Successfully exported complete report to file: CGPA_Report.txt
```

---

## 📐 Mathematical Formulas

1. **Course Grade Points**:
   $$\text{Grade Points}_i = \text{Credits}_i \times \text{Grade Value}_i$$

2. **Semester GPA (SGPA)**:
   $$\text{SGPA} = \frac{\sum_{i=1}^{n} (\text{Credits}_i \times \text{Grade Value}_i)}{\sum_{i=1}^{n} \text{Credits}_i}$$

3. **Cumulative Grade Point Average (CGPA)**:
   $$\text{CGPA} = \frac{\text{Previous Grade Points} + \sum \text{Current Grade Points}}{\text{Previous Credits} + \sum \text{Current Credits}}$$

---

## 👨‍💻 Author
- **Intern**: Abhyanand Pathak
- **Company**: CodeAlpha
- **Task**: Task 1 - CGPA Calculator
