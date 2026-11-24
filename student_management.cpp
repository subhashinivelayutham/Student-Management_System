#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Student {
    string id, name, department, year, phone;
};

const string FILE_NAME = "students.txt";


vector<Student> readStudents() {
    vector<Student> students;
    ifstream file(FILE_NAME);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Student s;

        getline(ss, s.id, '|');
        getline(ss, s.name, '|');
        getline(ss, s.department, '|');
        getline(ss, s.year, '|');
        getline(ss, s.phone, '|');

        if (!s.id.empty())
            students.push_back(s);
    }

    file.close();
    return students;
}


void saveStudents(const vector<Student>& students) {
    ofstream file(FILE_NAME);

    for (const Student& s : students) {
        file << s.id << "|" << s.name << "|"
             << s.department << "|" << s.year
             << "|" << s.phone << "\n";
    }

    file.close();
}


void addStudent() {
    Student s;

    cout << "\nEnter Student ID: ";
    getline(cin, s.id);

    vector<Student> students = readStudents();

    for (const Student& x : students) {
        if (x.id == s.id) {
            cout << "Student ID already exists!\n";
            return;
        }
    }

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Department: ";
    getline(cin, s.department);

    cout << "Enter Year: ";
    getline(cin, s.year);

    cout << "Enter Phone Number: ";
    getline(cin, s.phone);

    ofstream file(FILE_NAME, ios::app);

    file << s.id << "|" << s.name << "|"
         << s.department << "|" << s.year
         << "|" << s.phone << "\n";

    file.close();

    cout << "\nStudent added successfully!\n";
}


void displayStudents() {
    vector<Student> students = readStudents();

    if (students.empty()) {
        cout << "\nNo student records found!\n";
        return;
    }

    cout << "\n----- STUDENT RECORDS -----\n";

    for (const Student& s : students) {
        cout << "\nID: " << s.id;
        cout << "\nName: " << s.name;
        cout << "\nDepartment: " << s.department;
        cout << "\nYear: " << s.year;
        cout << "\nPhone: " << s.phone;
        cout << "\n---------------------------\n";
    }
}


void searchStudent() {
    string id;
    cout << "\nEnter Student ID to search: ";
    getline(cin, id);

    vector<Student> students = readStudents();

    for (const Student& s : students) {
        if (s.id == id) {
            cout << "\nStudent Found!\n";
            cout << "Name: " << s.name << "\n";
            cout << "Department: " << s.department << "\n";
            cout << "Year: " << s.year << "\n";
            cout << "Phone: " << s.phone << "\n";
            return;
        }
    }

    cout << "\nStudent not found!\n";
}


void updateStudent() {
    string id;
    cout << "\nEnter Student ID to update: ";
    getline(cin, id);

    vector<Student> students = readStudents();
    bool found = false;

    for (Student& s : students) {
        if (s.id == id) {
            found = true;

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Department: ";
            getline(cin, s.department);

            cout << "Enter New Year: ";
            getline(cin, s.year);

            cout << "Enter New Phone: ";
            getline(cin, s.phone);

            break;
        }
    }

    if (found) {
        saveStudents(students);
        cout << "\nStudent updated successfully!\n";
    } else {
        cout << "\nStudent not found!\n";
    }
}


void deleteStudent() {
    string id;
    cout << "\nEnter Student ID to delete: ";
    getline(cin, id);

    vector<Student> students = readStudents();
    vector<Student> updated;
    bool found = false;

    for (const Student& s : students) {
        if (s.id == id) {
            found = true;
        } else {
            updated.push_back(s);
        }
    }

    if (found) {
        saveStudents(updated);
        cout << "\nStudent deleted successfully!\n";
    } else {
        cout << "\nStudent not found!\n";
    }
}


int main() {
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nThank you! Exiting...\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
