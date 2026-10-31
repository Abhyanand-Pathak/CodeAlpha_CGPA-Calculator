#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>
#include <sstream>

// ============================================================================
// Course Structure
// ============================================================================
struct Course {
    std::string code;
    std::string name;
    double credits;
    std::string letterGrade;
    double gradePoint;

    double getTotalGradePoints() const {
        return credits * gradePoint;
    }
};

// ============================================================================
// Grading System Enumeration & Conversion
// ============================================================================
enum class GradingScale {
    SCALE_10 = 1,
    SCALE_4 = 2,
    CUSTOM_NUMERIC = 3
};

// Utility to trim and convert string to uppercase
std::string toUpper(std::string str) {
    for (char &c : str) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    // Trim leading and trailing whitespace
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Map letter grade to grade point based on chosen scale
bool convertGradeToPoints(const std::string& input, GradingScale scale, double& outPoint, std::string& outGrade) {
    std::string grade = toUpper(input);
    
    // Check if user entered a direct numeric value
    std::istringstream iss(grade);
    double numericVal;
    if (iss >> numericVal && iss.eof()) {
        if (scale == GradingScale::SCALE_10) {
            if (numericVal >= 0.0 && numericVal <= 10.0) {
                outPoint = numericVal;
                outGrade = std::to_string(numericVal);
                // Strip trailing zeros for clean display
                outGrade.erase(outGrade.find_last_not_of('0') + 1, std::string::npos);
                if (outGrade.back() == '.') outGrade.pop_back();
                return true;
            }
        } else if (scale == GradingScale::SCALE_4) {
            if (numericVal >= 0.0 && numericVal <= 4.0) {
                outPoint = numericVal;
                outGrade = std::to_string(numericVal);
                outGrade.erase(outGrade.find_last_not_of('0') + 1, std::string::npos);
                if (outGrade.back() == '.') outGrade.pop_back();
                return true;
            }
        } else {
            if (numericVal >= 0.0) {
                outPoint = numericVal;
                outGrade = std::to_string(numericVal);
                return true;
            }
        }
        return false;
    }

    if (scale == GradingScale::SCALE_10) {
        // Standard 10.0 Scale (UGC / AICTE Indian University Pattern)
        if (grade == "O" || grade == "A++") { outPoint = 10.0; outGrade = "O"; return true; }
        if (grade == "A+" || grade == "EX") { outPoint = 9.0; outGrade = "A+"; return true; }
        if (grade == "A")                  { outPoint = 8.0; outGrade = "A";  return true; }
        if (grade == "B+")                 { outPoint = 7.0; outGrade = "B+"; return true; }
        if (grade == "B")                  { outPoint = 6.0; outGrade = "B";  return true; }
        if (grade == "C")                  { outPoint = 5.0; outGrade = "C";  return true; }
        if (grade == "P" || grade == "D")  { outPoint = 4.0; outGrade = "P";  return true; }
        if (grade == "F" || grade == "AB") { outPoint = 0.0; outGrade = "F";  return true; }
    } else if (scale == GradingScale::SCALE_4) {
        // Standard 4.0 Scale (US / International Pattern)
        if (grade == "A+" || grade == "A")  { outPoint = 4.0; outGrade = grade; return true; }
        if (grade == "A-")                 { outPoint = 3.7; outGrade = "A-"; return true; }
        if (grade == "B+")                 { outPoint = 3.3; outGrade = "B+"; return true; }
        if (grade == "B")                  { outPoint = 3.0; outGrade = "B";  return true; }
        if (grade == "B-")                 { outPoint = 2.7; outGrade = "B-"; return true; }
        if (grade == "C+")                 { outPoint = 2.3; outGrade = "C+"; return true; }
        if (grade == "C")                  { outPoint = 2.0; outGrade = "C";  return true; }
        if (grade == "C-")                 { outPoint = 1.7; outGrade = "C-"; return true; }
        if (grade == "D+")                 { outPoint = 1.3; outGrade = "D+"; return true; }
        if (grade == "D")                  { outPoint = 1.0; outGrade = "D";  return true; }
        if (grade == "F")                  { outPoint = 0.0; outGrade = "F";  return true; }
    }

    return false;
}

// Performance remark
std::string getPerformanceRemark(double cgpa, GradingScale scale) {
    if (scale == GradingScale::SCALE_10) {
        if (cgpa >= 9.0) return "Outstanding (First Class with Distinction)";
        if (cgpa >= 8.0) return "Excellent (First Class)";
        if (cgpa >= 7.0) return "Very Good";
        if (cgpa >= 6.0) return "Good (Second Class)";
        if (cgpa >= 5.0) return "Average / Satisfactory";
        if (cgpa >= 4.0) return "Pass";
        return "Fail / Needs Significant Improvement";
    } else {
        if (cgpa >= 3.8) return "Summa Cum Laude (Outstanding)";
        if (cgpa >= 3.5) return "Magna Cum Laude (Excellent)";
        if (cgpa >= 3.0) return "Cum Laude (Very Good)";
        if (cgpa >= 2.5) return "Good / Average";
        if (cgpa >= 2.0) return "Satisfactory (Minimum Passing)";
        return "Academic Probation / Unsatisfactory";
    }
}

// ============================================================================
// Semester Class
// ============================================================================
class Semester {
private:
    int semesterNumber;
    std::vector<Course> courses;

public:
    Semester(int semNum = 1) : semesterNumber(semNum) {}

    void addCourse(const Course& course) {
        courses.push_back(course);
    }

    int getSemesterNumber() const {
        return semesterNumber;
    }

    const std::vector<Course>& getCourses() const {
        return courses;
    }

    double getTotalCredits() const {
        double total = 0.0;
        for (const auto& c : courses) {
            total += c.credits;
        }
        return total;
    }

    double getTotalGradePoints() const {
        double total = 0.0;
        for (const auto& c : courses) {
            total += c.getTotalGradePoints();
        }
        return total;
    }

    double getGPA() const {
        double credits = getTotalCredits();
        if (credits <= 0.0) return 0.0;
        return getTotalGradePoints() / credits;
    }
};

// ============================================================================
// Safe Input Helper Functions
// ============================================================================
int getPositiveInt(const std::string& prompt, int minVal = 1, int maxVal = 100) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "  [!] Invalid input. Please enter a whole number between " 
                  << minVal << " and " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double getPositiveDouble(const std::string& prompt, double minVal = 0.1, double maxVal = 50.0) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "  [!] Invalid input. Please enter a numeric value between " 
                  << minVal << " and " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getNonEmptyString(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        // Trim leading and trailing whitespace
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            size_t last = line.find_last_not_of(" \t\r\n");
            return line.substr(first, (last - first + 1));
        }
        std::cout << "  [!] Input cannot be blank. Please try again.\n";
    }
}

// ============================================================================
// Display & Reporting Functions
// ============================================================================
void displayHeader() {
    std::cout << "\n====================================================================\n";
    std::cout << "             CODEALPHA INTERNSHIP TASK 1: CGPA CALCULATOR          \n";
    std::cout << "====================================================================\n";
}

void printGradingGuide(GradingScale scale) {
    std::cout << "\n----------------------- GRADING REFERENCE TABLE --------------------\n";
    if (scale == GradingScale::SCALE_10) {
        std::cout << " Grade:   O (10) | A+ (9) | A (8) | B+ (7) | B (6) | C (5) | P (4) | F (0)\n";
        std::cout << " * You can enter the letter grade (e.g. A+, B) or exact numeric points.\n";
    } else if (scale == GradingScale::SCALE_4) {
        std::cout << " Grade:   A (4.0) | A- (3.7) | B+ (3.3) | B (3.0) | B- (2.7)\n";
        std::cout << "          C+ (2.3) | C (2.0) | C- (1.7) | D (1.0) | F (0.0)\n";
        std::cout << " * You can enter the letter grade (e.g. A, B+) or exact numeric points.\n";
    } else {
        std::cout << " * Direct numeric grade points will be used.\n";
    }
    std::cout << "--------------------------------------------------------------------\n";
}

void printSemesterTable(const Semester& sem, std::ostream& out) {
    out << "\n" << std::string(72, '-') << "\n";
    out << "                       SEMESTER " << sem.getSemesterNumber() << " GRADE REPORT\n";
    out << std::string(72, '-') << "\n";
    out << std::left  << std::setw(6)  << "No."
        << std::left  << std::setw(14) << "Course Code"
        << std::left  << std::setw(24) << "Course Name"
        << std::right << std::setw(8)  << "Credits"
        << std::right << std::setw(8)  << "Grade"
        << std::right << std::setw(12) << "Grade Pts" << "\n";
    out << std::string(72, '-') << "\n";

    int index = 1;
    for (const auto& c : sem.getCourses()) {
        std::string shortName = c.name;
        if (shortName.length() > 22) {
            shortName = shortName.substr(0, 19) + "...";
        }
        out << std::left  << std::setw(6)  << index++
            << std::left  << std::setw(14) << (c.code.empty() ? "-" : c.code)
            << std::left  << std::setw(24) << shortName
            << std::right << std::setw(8)  << std::fixed << std::setprecision(1) << c.credits
            << std::right << std::setw(8)  << c.letterGrade
            << std::right << std::setw(12) << std::fixed << std::setprecision(2) << c.getTotalGradePoints()
            << "\n";
    }

    out << std::string(72, '-') << "\n";
    out << std::left  << std::setw(44) << "Semester Total:"
        << std::right << std::setw(8)  << std::fixed << std::setprecision(1) << sem.getTotalCredits()
        << std::right << std::setw(8)  << ""
        << std::right << std::setw(12) << std::fixed << std::setprecision(2) << sem.getTotalGradePoints()
        << "\n";
    out << std::string(72, '=') << "\n";
    out << "  >> Semester " << sem.getSemesterNumber() << " GPA (SGPA): " 
        << std::fixed << std::setprecision(2) << sem.getGPA() << "\n";
    out << std::string(72, '=') << "\n";
}

void saveReportToFile(const std::string& studentName,
                      const std::string& studentId,
                      const std::vector<Semester>& semesters,
                      double prevCredits,
                      double prevGradePoints,
                      GradingScale scale,
                      double finalCGPA) {
    std::string filename = "CGPA_Report.txt";
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "\n[!] Warning: Could not create report file " << filename << "\n";
        return;
    }

    outFile << "========================================================================\n";
    outFile << "                     STUDENT ACADEMIC PERFORMANCE REPORT                \n";
    outFile << "                           CodeAlpha Internship                         \n";
    outFile << "========================================================================\n";
    outFile << " Student Name : " << (studentName.empty() ? "N/A" : studentName) << "\n";
    outFile << " Student ID   : " << (studentId.empty() ? "N/A" : studentId) << "\n";
    outFile << " Scale Used   : " << (scale == GradingScale::SCALE_10 ? "10.0 Scale" : (scale == GradingScale::SCALE_4 ? "4.0 Scale" : "Custom Numeric")) << "\n";
    outFile << "========================================================================\n";

    if (prevCredits > 0) {
        outFile << "\n[Previous Academic Record]\n";
        outFile << " - Previous Credits Earned     : " << std::fixed << std::setprecision(1) << prevCredits << "\n";
        outFile << " - Previous Total Grade Points : " << std::fixed << std::setprecision(2) << prevGradePoints << "\n";
        outFile << " - Previous Cumulative GPA     : " << std::fixed << std::setprecision(2) << (prevGradePoints / prevCredits) << "\n";
    }

    for (const auto& sem : semesters) {
        printSemesterTable(sem, outFile);
    }

    double totalSemCredits = 0.0;
    double totalSemGradePoints = 0.0;
    for (const auto& sem : semesters) {
        totalSemCredits += sem.getTotalCredits();
        totalSemGradePoints += sem.getTotalGradePoints();
    }

    double cumulativeCredits = prevCredits + totalSemCredits;
    double cumulativeGradePoints = prevGradePoints + totalSemGradePoints;

    outFile << "\n========================================================================\n";
    outFile << "                           FINAL SUMMARY                                \n";
    outFile << "========================================================================\n";
    outFile << " Total Cumulative Credits Earned     : " << std::fixed << std::setprecision(1) << cumulativeCredits << "\n";
    outFile << " Total Cumulative Grade Points       : " << std::fixed << std::setprecision(2) << cumulativeGradePoints << "\n";
    outFile << " Overall CGPA                        : " << std::fixed << std::setprecision(2) << finalCGPA << "\n";
    outFile << " Academic Standing / Remark          : " << getPerformanceRemark(finalCGPA, scale) << "\n";
    outFile << "========================================================================\n";

    outFile.close();
    std::cout << "\n[+] Successfully exported complete report to file: " << filename << "\n";
}

// ============================================================================
// Main Application Logic
// ============================================================================
int main() {
    displayHeader();

    // 1. Optional Student Details
    std::cout << "\nEnter Student Details (press Enter to skip):\n";
    std::cout << " Student Name: ";
    std::string studentName;
    std::getline(std::cin, studentName);
    std::cout << " Student ID / Roll No: ";
    std::string studentId;
    std::getline(std::cin, studentId);

    // 2. Select Grading Scale
    std::cout << "\nSelect University Grading Scale:\n";
    std::cout << "  1. 10.0 Scale (Standard UGC / Engineering / University scale - O, A+, A, B, etc.)\n";
    std::cout << "  2. 4.0 Scale  (US / International scale - 4.0, 3.7, 3.3, 3.0, etc.)\n";
    std::cout << "  3. Direct Numeric Grade Point (Custom)\n";
    int scaleChoice = getPositiveInt(" Enter your choice (1-3): ", 1, 3);
    GradingScale scale = static_cast<GradingScale>(scaleChoice);

    printGradingGuide(scale);

    // 3. Calculation Workflow Mode
    std::cout << "\nSelect Calculation Mode:\n";
    std::cout << "  1. Single Semester Calculation (with optional previous CGPA integration)\n";
    std::cout << "  2. Multi-Semester Cumulative Calculation (Semester-by-Semester)\n";
    int modeChoice = getPositiveInt(" Enter your choice (1-2): ", 1, 2);

    std::vector<Semester> semesters;
    double prevCredits = 0.0;
    double prevGradePoints = 0.0;

    if (modeChoice == 1) {
        // Mode 1: Single Semester
        int semNumber = getPositiveInt("\nEnter Current Semester Number (e.g. 1 to 12): ", 1, 12);
        Semester currentSem(semNumber);

        // Previous semester CGPA input if not Semester 1
        if (semNumber > 1) {
            std::cout << "\nDo you want to include previous semesters to calculate cumulative CGPA? (y/n): ";
            std::string ans;
            std::getline(std::cin, ans);
            if (!ans.empty() && (ans[0] == 'y' || ans[0] == 'Y')) {
                double maxScale = (scale == GradingScale::SCALE_10 ? 10.0 : (scale == GradingScale::SCALE_4 ? 4.0 : 100.0));
                prevCredits = getPositiveDouble("  Enter Total Credits earned in previous semesters: ", 0.5, 300.0);
                double prevCGPA = getPositiveDouble("  Enter your previous cumulative CGPA: ", 0.0, maxScale);
                prevGradePoints = prevCredits * prevCGPA;
            }
        }

        int numCourses = getPositiveInt("\nEnter the number of courses taken in Semester " + std::to_string(semNumber) + ": ", 1, 30);
        std::cout << "\n--- Entering Details for " << numCourses << " Courses ---\n";

        for (int i = 1; i <= numCourses; ++i) {
            std::cout << "\nCourse " << i << " of " << numCourses << ":\n";
            std::string code = getNonEmptyString("  Course Code (e.g. CS101 / MATH): ");
            std::string name = getNonEmptyString("  Course Name/Title: ");
            double credits = getPositiveDouble("  Credit Hours (e.g. 3, 4, 1.5): ", 0.5, 12.0);

            double gradePoint = 0.0;
            std::string confirmedGrade;
            while (true) {
                std::string gInput = getNonEmptyString("  Grade (Letter like A+, B or Grade Point): ");
                if (convertGradeToPoints(gInput, scale, gradePoint, confirmedGrade)) {
                    break;
                }
                std::cout << "  [!] Invalid grade format for the selected scale. Please try again.\n";
            }

            Course c;
            c.code = code;
            c.name = name;
            c.credits = credits;
            c.letterGrade = confirmedGrade;
            c.gradePoint = gradePoint;
            currentSem.addCourse(c);
        }

        semesters.push_back(currentSem);

    } else {
        // Mode 2: Multi-Semester Calculation
        int numSemesters = getPositiveInt("\nEnter the total number of semesters to calculate: ", 1, 12);

        for (int s = 1; s <= numSemesters; ++s) {
            std::cout << "\n====================================================================\n";
            std::cout << "                     DATA ENTRY FOR SEMESTER " << s << "\n";
            std::cout << "====================================================================\n";
            Semester sem(s);

            int numCourses = getPositiveInt("Enter the number of courses in Semester " + std::to_string(s) + ": ", 1, 30);

            for (int i = 1; i <= numCourses; ++i) {
                std::cout << "\nCourse " << i << " of " << numCourses << " (Semester " << s << "):\n";
                std::string code = getNonEmptyString("  Course Code (e.g. CS" + std::to_string(s) + "0" + std::to_string(i) + "): ");
                std::string name = getNonEmptyString("  Course Name: ");
                double credits = getPositiveDouble("  Credit Hours: ", 0.5, 12.0);

                double gradePoint = 0.0;
                std::string confirmedGrade;
                while (true) {
                    std::string gInput = getNonEmptyString("  Grade (Letter or Point): ");
                    if (convertGradeToPoints(gInput, scale, gradePoint, confirmedGrade)) {
                        break;
                    }
                    std::cout << "  [!] Invalid grade for selected scale. Try again.\n";
                }

                Course c;
                c.code = code;
                c.name = name;
                c.credits = credits;
                c.letterGrade = confirmedGrade;
                c.gradePoint = gradePoint;
                sem.addCourse(c);
            }
            semesters.push_back(sem);
        }
    }

    // ========================================================================
    // Display Results & Compute CGPA
    // ========================================================================
    std::cout << "\n\n====================================================================\n";
    std::cout << "                     ACADEMIC EVALUATION RESULTS                    \n";
    std::cout << "====================================================================\n";
    if (!studentName.empty()) {
        std::cout << " Student Name : " << studentName << "\n";
    }
    if (!studentId.empty()) {
        std::cout << " Student ID   : " << studentId << "\n";
    }

    double totalSemCredits = 0.0;
    double totalSemGradePoints = 0.0;

    for (const auto& sem : semesters) {
        printSemesterTable(sem, std::cout);
        totalSemCredits += sem.getTotalCredits();
        totalSemGradePoints += sem.getTotalGradePoints();
    }

    double grandTotalCredits = prevCredits + totalSemCredits;
    double grandTotalGradePoints = prevGradePoints + totalSemGradePoints;
    double finalCGPA = (grandTotalCredits > 0.0) ? (grandTotalGradePoints / grandTotalCredits) : 0.0;

    std::cout << "\n====================================================================\n";
    std::cout << "                     FINAL CUMULATIVE SUMMARY                       \n";
    std::cout << "====================================================================\n";
    if (prevCredits > 0.0) {
        std::cout << " Previous Credits Carried Over  : " << std::fixed << std::setprecision(1) << prevCredits << "\n";
        std::cout << " Previous Grade Points          : " << std::fixed << std::setprecision(2) << prevGradePoints << "\n";
    }
    std::cout << " New Semester(s) Credits        : " << std::fixed << std::setprecision(1) << totalSemCredits << "\n";
    std::cout << " New Semester(s) Grade Points   : " << std::fixed << std::setprecision(2) << totalSemGradePoints << "\n";
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << " Grand Total Credits            : " << std::fixed << std::setprecision(1) << grandTotalCredits << "\n";
    std::cout << " Grand Total Grade Points       : " << std::fixed << std::setprecision(2) << grandTotalGradePoints << "\n";
    std::cout << " OVERALL CGPA                   : " << std::fixed << std::setprecision(2) << finalCGPA << "\n";
    std::cout << " Performance Remark             : " << getPerformanceRemark(finalCGPA, scale) << "\n";
    std::cout << "====================================================================\n";

    // 4. Ask to save report
    std::cout << "\nWould you like to export this report to a text file (CGPA_Report.txt)? (y/n): ";
    std::string exportAns;
    std::getline(std::cin, exportAns);
    if (!exportAns.empty() && (exportAns[0] == 'y' || exportAns[0] == 'Y')) {
        saveReportToFile(studentName, studentId, semesters, prevCredits, prevGradePoints, scale, finalCGPA);
    }

    std::cout << "\nThank you for using the CGPA Calculator. Best of luck with your internship!\n";
    return 0;
}
