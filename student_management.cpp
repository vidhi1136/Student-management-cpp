#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "Roll No: " << roll << ", Name: " << name << ", Marks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);
    s.input();
    file << s.roll << "|" << s.name << "|" << s.marks << "\n";
    file.close();
    cout << "Student added successfully!\n";
}

void viewStudents() {
    ifstream file("students.txt");
    Student s;
    string line;
    cout << "\nAll Student Records:\n";
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        s.roll = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.marks = stof(line.substr(pos2 + 1));
        s.display();
    }
    file.close();
}

void searchStudent() {
    int r;
    cout << "Enter roll number to search: ";
    cin >> r;
    ifstream file("students.txt");
    Student s;
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        s.roll = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.marks = stof(line.substr(pos2 + 1));
        if (s.roll == r) {
            s.display();
            found = true;
        }
    }
    if (!found)
        cout << "Student not found!\n";
    file.close();
}

void deleteStudent() {
    int r;
    cout << "Enter roll number to delete: ";
    cin >> r;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        int roll = stoi(line.substr(0, pos1));
        if (roll != r) {
            temp << line << "\n";
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

void updateStudent() {
    int r;
    cout << "Enter roll number to update: ";
    cin >> r;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        s.roll = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.marks = stof(line.substr(pos2 + 1));

        if (s.roll == r) {
            cout << "Enter new details:\n";
            s.input();
            temp << s.roll << "|" << s.name << "|" << s.marks << "\n";
            found = true;
        } else {
            temp << line << "\n";
        }
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student updated successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n====== Student Record System ======\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: viewStudents(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: updateStudent(); break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
