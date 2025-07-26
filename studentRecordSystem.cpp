#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;


class Student {
public:
    int id;
    string name;
    int age;
    float marks;

    Student() {}

    Student(int id, string name, int age, float marks) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->marks = marks;
    }

    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Age: " << age << ", Marks: " << marks << endl;
    }
};


map<int, Student> studentDB;


void loadFromFile() {
    ifstream infile("students.txt");
    if (!infile) return;

    int id, age;
    string name;
    float marks;

    while (infile >> id >> name >> age >> marks) {
        studentDB[id] = Student(id, name, age, marks);
    }

    infile.close();
}


void saveToFile() {
    ofstream outfile("students.txt");
    for (auto &entry : studentDB) {
        Student s = entry.second;
        outfile << s.id << " " << s.name << " " << s.age << " " << s.marks << endl;
    }
    outfile.close();
}


void addStudent() {
    int id, age;
    string name;
    float marks;

    cout << "Enter ID: ";
    cin >> id;
    if (studentDB.find(id) != studentDB.end()) {
        cout << "Student with ID " << id << " already exists.\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Marks: ";
    cin >> marks;

    studentDB[id] = Student(id, name, age, marks);
    cout << "Student added successfully.\n";
    saveToFile();
}

void searchStudent() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    if (studentDB.find(id) != studentDB.end()) {
        studentDB[id].display();
    } else {
        cout << "Student not found.\n";
    }
}


void updateStudent() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    if (studentDB.find(id) == studentDB.end()) {
        cout << "Student not found.\n";
        return;
    }

    string name;
    int age;
    float marks;

    cout << "Enter new Name: ";
    cin >> name;
    cout << "Enter new Age: ";
    cin >> age;
    cout << "Enter new Marks: ";
    cin >> marks;

    studentDB[id] = Student(id, name, age, marks);
    cout << "Student updated successfully.\n";
    saveToFile();
}


void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    if (studentDB.erase(id)) {
        cout << "Student deleted successfully.\n";
        saveToFile();
    } else {
        cout << "Student not found.\n";
    }
}


void displayAll() {
    if (studentDB.empty()) {
        cout << "No records found.\n";
        return;
    }

    for (auto &entry : studentDB) {
        entry.second.display();
    }
}


int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Student\n2. Search Student\n3. Update Student\n4. Delete Student\n5. Display All\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: displayAll(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}