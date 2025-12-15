#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

/* ===================== DATA STRUCTURES ===================== */

struct Student 
{
    int id;
    string name;
    float gpa;
    int earned_credits;
    Student* next;
};

struct Course 
{
    string code;
    string name;
    int credits;
    int capacity;
    int enrolled_count;
    string* prereqs;
    int prereq_count;
    Course* next;
};

struct Enrollment 
{
    int student_id;
    string course_code;
    string semester;
    char grade; // A B C D F W or '\0'
    Enrollment* next;
};

/* ===================== UTILITY ===================== */

bool valid_grade(char g) 
{
    return g=='A'||g=='B'||g=='C'||g=='D'||g=='F'||g=='W';
}

int grade_points(char g) 
{
    switch (g) 
    {
        case 'A': return 4;
        case 'B': return 3;
        case 'C': return 2;
        case 'D': return 1;
        case 'F': return 0;
        default: return -1;
    }
}

/* ===================== FINDERS ===================== */

Student* find_student(Student* head, int id) 
{
    while (head) 
    {
        if (head->id == id) return head;
        head = head->next;
    }
    return nullptr;
}

Course* find_course(Course* head, const string& code) 
{
    while (head) 
    {
        if (head->code == code) return head;
        head = head->next;
    }
    return nullptr;
}

Enrollment* find_enrollment(Enrollment* head, int sid,
                            const string& code,
                            const string& sem) 
{
    while (head) 
    {
        if (head->student_id == sid &&
            head->course_code == code &&
            head->semester == sem)
            return head;
        head = head->next;
    }
    return nullptr;
}

/* ===================== ADD FUNCTIONS ===================== */

bool add_student(Student*& head, int id, const string& name) 
{
    if (find_student(head, id)) return false; // duplicate ID
    Student* s = new Student{id, name, 0.0f, 0, head};
    head = s;
    return true;
}

bool add_course(Course*& head, const string& code, const string& name,
                int credits, int cap,
                string* prereqs, int pcount) 
{
    if (find_course(head, code)) return false;

    Course* c = new Course;
    c->code = code;
    c->name = name;
    c->credits = credits;
    c->capacity = cap;
    c->enrolled_count = 0;
    c->prereq_count = pcount;
    c->prereqs = (pcount > 0) ? new string[pcount] : nullptr;
    for (int i = 0; i < pcount; i++) c->prereqs[i] = prereqs[i];
    c->next = head;
    head = c;
    return true;
}

/* ===================== CHECKS ===================== */

bool prereqs_met(Enrollment* e, Course* c, int sid) 
{
    for (int i = 0; i < c->prereq_count; i++) 
    {
        bool passed = false;
        Enrollment* cur = e;
        while (cur) 
        {
            if (cur->student_id == sid &&
                cur->course_code == c->prereqs[i] &&
                grade_points(cur->grade) >= 2)
                passed = true;
            cur = cur->next;
        }
        if (!passed) return false;
    }
    return true;
}

int semester_credits(Enrollment* e, Course* courses,
                     int sid, const string& sem) 
{
    int sum = 0;
    while (e) 
    {
        if (e->student_id == sid && e->semester == sem) 
	{
            Course* c = find_course(courses, e->course_code);
            if (c) sum += c->credits;
        }
        e = e->next;
    }
    return sum;
}

/* ===================== ENROLL ===================== */

bool enroll_student(Enrollment*& e, Student* students,
                    Course* courses,
                    int sid, const string& code,
                    const string& sem) 
{

    Student* s = find_student(students, sid);
    Course* c = find_course(courses, code);

    if (!s || !c) return false;                     // null safety
    if (find_enrollment(e, sid, code, sem)) return false;
    if (c->enrolled_count >= c->capacity) return false;
    if (!prereqs_met(e, c, sid)) return false;

    int cur = semester_credits(e, courses, sid, sem);
    if (cur + c->credits > 18) return false;        // credit limit

    Enrollment* n = new Enrollment{sid, code, sem, '\0', e};
    e = n;
    c->enrolled_count++;
    return true;
}

/* ===================== GPA ===================== */

void update_gpa(Student* s, Enrollment* e, Course* courses) 
{
    int points = 0, attempted = 0, earned = 0;

    while (e) 
    {
        if (e->student_id == s->id && grade_points(e->grade) >= 0) 
	{
            Course* c = find_course(courses, e->course_code);
            if (c) 
	    {
                attempted += c->credits;
                points += grade_points(e->grade) * c->credits;
                if (grade_points(e->grade) >= 2)
                    earned += c->credits;
            }
        }
        e = e->next;
    }

    s->earned_credits = earned;
    s->gpa = (attempted == 0) ? 0.0f : (float)points / attempted;
}

/* ===================== ASSIGN GRADE ===================== */

bool assign_grade(Student* students, Course* courses,
                  Enrollment* enrollments,
                  int sid, const string& code,
                  const string& sem, char grade) 
{

    if (!valid_grade(grade)) return false;

    Student* s = find_student(students, sid);
    if (!s) return false; // student does not exist

    Enrollment* e = find_enrollment(enrollments, sid, code, sem);
    if (!e) return false; // enrollment does not exist

    e->grade = grade;
    update_gpa(s, enrollments, courses);
    return true;
}

/* ===================== REMOVE STUDENT ===================== */

void remove_student(Student*& students,
                    Enrollment*& enrollments,
                    Course* courses,
                    int sid) 
{

    Enrollment* cur = enrollments;
    Enrollment* prev = nullptr;

    while (cur) 
   {
        if (cur->student_id == sid) 
	{
            Course* c = find_course(courses, cur->course_code);
            if (c) c->enrolled_count--;
            Enrollment* del = cur;
            cur = cur->next;
            if (prev) prev->next = cur;
            else enrollments = cur;
            delete del;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

    Student* s = students;
    Student* ps = nullptr;
    while (s) 
    {
        if (s->id == sid) 
	{
            if (ps) ps->next = s->next;
            else students = s->next;
            delete s;
            return;
        }
        ps = s;
        s = s->next;
    }
}

/* ===================== FILE I/O ===================== */

void save_system(Student* s, Course* c, Enrollment* e) 
{
    ofstream fs("students.txt"), fc("courses.txt"), fe("enrollments.txt");

    while (s) 
    {
        fs << s->id << "," << s->name << "," << s->gpa
           << "," << s->earned_credits << "\n";
        s = s->next;
    }

    while (c) 
    {
        fc << c->code << "," << c->name << "," << c->credits
           << "," << c->capacity << "," << c->enrolled_count << "\n";
        c = c->next;
    }

    while (e) 
    {
        fe << e->student_id << "," << e->course_code
           << "," << e->semester << "," << e->grade << "\n";
        e = e->next;
    }
}

/* ===================== MAIN ===================== */

int main() 
{
    Student* students = nullptr;
    Course* courses = nullptr;
    Enrollment* enrollments = nullptr;

    int choice;

    do {
        cout << "\n===== UNIVERSITY ENROLLMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Course\n";
        cout << "3. Enroll Student\n";
        cout << "4. Assign Grade\n";
        cout << "5. Remove Student\n";
        cout << "6. Save System to Files\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) 
	{
            int id;
            string name;
            cout << "Enter student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter student name: ";
            getline(cin, name);

            if (add_student(students, id, name))
                cout << "Student added successfully.\n";
            else
                cout << "Error: Duplicate student ID.\n";
        }

        else if (choice == 2) 
	{
            string code, name;
            int credits, cap, pc;

            cout << "Enter course code: ";
            cin >> code;
            cin.ignore();
            cout << "Enter course name: ";
            getline(cin, name);
            cout << "Enter credits: ";
            cin >> credits;
            cout << "Enter capacity: ";
            cin >> cap;
            cout << "Number of prerequisites: ";
            cin >> pc;

            string* prereqs = nullptr;
            if (pc > 0) 
	    {
                prereqs = new string[pc];
                for (int i = 0; i < pc; i++) 
		{
                    cout << "Prerequisite " << i + 1 << ": ";
                    cin >> prereqs[i];
                }
            }

            if (add_course(courses, code, name, credits, cap, prereqs, pc))
                cout << "Course added successfully.\n";
            else
                cout << "Error: Duplicate course code.\n";

            delete[] prereqs; // prevent memory leak
        }

        else if (choice == 3) 
	{
            int sid;
            string code, sem;

            cout << "Enter student ID: ";
            cin >> sid;
            cout << "Enter course code: ";
            cin >> code;
            cout << "Enter semester (e.g. Fall25): ";
            cin >> sem;

            if (enroll_student(enrollments, students, courses, sid, code, sem))
                cout << "Enrollment successful.\n";
            else
                cout << "Enrollment failed (check prerequisites, credits, capacity, or IDs).\n";
        }

        else if (choice == 4) 
	{
            int sid;
            string code, sem;
            char grade;

            cout << "Enter student ID: ";
            cin >> sid;
            cout << "Enter course code: ";
            cin >> code;
            cout << "Enter semester: ";
            cin >> sem;
            cout << "Enter grade (A B C D F W): ";
            cin >> grade;

            if (assign_grade(students, courses, enrollments,
                             sid, code, sem, toupper(grade)))
                cout << "Grade assigned successfully.\n";
            else
                cout << "Error: Invalid student, enrollment, or grade.\n";
        }

        else if (choice == 5) 
	{
            int sid;
            cout << "Enter student ID to remove: ";
            cin >> sid;

            if (find_student(students, sid)) 
	    {
                remove_student(students, enrollments, courses, sid);
                cout << "Student and enrollments removed.\n";
            } else 
	    {
                cout << "Error: Student not found.\n";
            }
        }

        else if (choice == 6) 
	{
            save_system(students, courses, enrollments);
            cout << "System saved to files.\n";
        }

        else if (choice == 0) 
	{
            cout << "Exiting program...\n";
        }

        else 
	{
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
