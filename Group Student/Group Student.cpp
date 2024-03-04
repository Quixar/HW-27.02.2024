#include <iostream>
#include <ctime>
#include <string>
#include <set>
#include "Student.h"
using namespace std;

class Group {
private:
    set<Student> students;
    int studentCount = students.size();
    string groupName;
    string groupSpecialization;
    int classNumber = 2;
    int passingGrade = 7;
    friend ostream& operator << (ostream& o, Group& g);
    friend istream& operator >> (istream& i, Group& g);
public:

    Group() : Group("P26", "Prog") {}

    Group(string groupName, string groupSpecialization)
    {
        //cout << "GROUP CONSTRUCTOR" << "\n";
        SetGroupName(groupName);
        SetGroupSpecialization(groupSpecialization);
    }

    Group(const Group& original)
    {
        this->groupName = original.groupName;
        this->groupSpecialization = original.groupSpecialization;
        this->studentCount = original.studentCount;
        for (const Student& student : original.students) {
            students.insert(student);
        }
    }

    void ShowGroup()
    {
        cout << "Group: " << groupName << ", Specialization: " << groupSpecialization << "\n";
        cout << "Students:\n";
        for (auto i = students.begin(); i != students.end(); i++)
        {
            cout << *i ;
        }
    }

    void AddStudent(Student& student)
    {
        students.insert(student);
    }

    void MergeGroup(Group& g2)
    {
        int otherStudentCount = g2.studentCount;
        for (auto i = students.end(); i != g2.students.end(); i++) {
            students.insert(*i);
        }
    }

    void TransferStudent(Student& student, Group& g2)
    {
        auto current = students.find(student);
        if (current != students.end()) {
            Student transfer = *current;
            g2.AddStudent(transfer);
            students.erase(current);
        }
        else {
            cout << "Student not found in group\n";
        }
    }

    void ExpelStudents()
    {
        for (auto i = students.begin(); i != students.end();) {
            bool passed_exam = false;
            int j = 1;
            if (i->GetExamRatesCount(j) >= passingGrade) {
                passed_exam = true;
                i++;
            }

            else {
                cout << "Expelling student " << i->GetName() << " for failing exam.\n";
                students.erase(i);
            }
            j++;
        }
    }

    void ExpelBadStudent()
    {
        if (students.empty())
        {
            cout << "No students in the group to expel.\n";
            return;
        }

        auto bad_student = students.begin();
        double minAverageGrade = bad_student->CalculateAverageGrade();
        for (auto i = students.begin(); i != students.end(); i++)
        {
            double averageGrade = i->CalculateAverageGrade();
            if (averageGrade < minAverageGrade)
            {
                bad_student = i;
                minAverageGrade = averageGrade;
            }
        }

        cout << "Expelling the least performing student " << bad_student->GetName() << "\n";
        students.erase(bad_student);
    }

    void SetGroupName(string groupName)
    {
        this->groupName = groupName;
    }

    string GetGroupName() const
    {
        return groupName;
    }

    void SetGroupSpecialization(string groupSpecialization)
    {
        this->groupSpecialization = groupSpecialization;
    }

    string GetGroupSpecialization() const
    {
        return groupSpecialization;
    }

    void SetPassingGrade(int passingGrade)
    {
        this->passingGrade = passingGrade;
    }

    int GetPassingGrade() const
    {
        return passingGrade;
    }

    void SetStudentCount(int studentCount)
    {
        this->studentCount = studentCount;
    }

    int GetStudentCount() const
    {
        return studentCount;
    }

    operator string()
    {
        return groupName + " " + groupSpecialization + " " + to_string(studentCount) + " students\n";
    }

    ~Group() {}

};

istream& operator >> (const istream& i, Student s)
{
    string answer;
    cout << "Какая у тебя фамилия: ";
    cin >> answer;
    s.SetSurname(answer);
    cout << "Как тебя зовут: ";
    cin >> answer;
    s.SetName(answer);
    cout << "Какое у тебя отчество: ";
    cin >> answer;
    s.SetMiddlName(answer);
    return cin;
}

ostream& operator << (ostream& o, Student s)
{
    s.PrintStudent();
    return cout;
}

ostream& operator << (ostream& o, Group& g)
{
    g.ShowGroup();
    return cout;
}

istream& operator>>(istream& i, Group& g)
{
    cout << "Enter group name: ";
    cin >> g.groupName;
    cout << "Enter group specialization: ";
    cin >> g.groupSpecialization;
    return cin;
}

Group operator + (Group& g, Group& g2)
{ 
    Group result = g;
    result.MergeGroup(g2); 
    return result; 
}

bool operator > (Group& g, Group& g2)
{
    if (g.GetStudentCount() > g2.GetStudentCount())
    {
        cout << "First group greater then second\n";
        return true;
    }
    return false;
}

bool operator < (Group& g, Group& g2)
{
    if (g.GetStudentCount() < g2.GetStudentCount())
    {
        cout << "First group less then second\n";
        return true;
    }
    return false;
}

bool operator >= (Group& g, Group& g2)
{
    if (g.GetStudentCount() >= g2.GetStudentCount())
    {
        cout << "First group greater or equal then second\n";
        return true;
    }
    return false;
}

bool operator <= (Group& g, Group& g2)
{
    if (g.GetStudentCount() <= g2.GetStudentCount())
    {
        cout << "First group less or equal then second\n";
        return true;
    }
    return false;
}

bool operator == (Group& g, Group& g2)
{
    if (g.GetStudentCount() == g2.GetStudentCount())
    {
        cout << "First group equal to second\n";
        return true;
    }
    return false;
}

bool operator != (Group& g, Group& g2)
{
    if (g.GetStudentCount() != g2.GetStudentCount())
    {
        cout << "First group not equal to second\n";
        return true;
    }
    return false;
}

bool operator < (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() < s2.CalculateAverageGrade())
    {
        cout << "The first student has a lower average score than the second\n";
        return true;
    }
    return false;
}

bool operator > (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() > s2.CalculateAverageGrade())
    {
        cout << "The first student has a higher average score than the second\n";
        return true;
    }
    return false;
}

bool operator <= (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() <= s2.CalculateAverageGrade())
    {
        cout << "The first student has a lower or equal average score than the second\n";
        return true;
    }
    return false;
}

bool operator >= (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() >= s2.CalculateAverageGrade())
    {
        cout << "The first student has a higher or equal average score than the second\n";
        return true;
    }
    return false;
}

bool operator == (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() == s2.CalculateAverageGrade())
    {
        cout << "Students have the same average score\n";
        return true;
    }
    return false;
}

bool operator != (Student& s, Student& s2)
{
    if (s.CalculateAverageGrade() != s2.CalculateAverageGrade())
    {
        cout << "Students dont have the same average score\n";
        return true;
    }
    return false;
}

Group operator += (Group& g, Student& s)
{
    g.AddStudent(s);
    return g;
}

int operator - (const Date& left, const Date& right)
{
    int days = 0;
    bool leapYear = false;

    for (int i = left.GetYear(); i < right.GetYear(); ++i)
    {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
        {
            leapYear = true;
            days += 366;
        }
        else
        {
            leapYear = false;
            days += 365;
        }
    }

    days += right.GetDay() - left.GetDay();

    for (int i = left.GetMonth(); i < right.GetMonth(); ++i)
    {
        switch (i)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days += 31;
            break;
        case 4: case 6: case 9: case 11:
            days += 30;
            break;
        case 2:
            if (leapYear)
                days += 29;
            else
                days += 28;
            break;
        }
    }

    return days;
}

ostream& operator << (ostream& o, Date& d)
{
    d.PrintDate();
    return cout;;
}

int main()
{

    //Cat c;
    //c.name = "Barsik";
    //c.Meow();
    //
    //Dog d = c; // это должно работать
    //d.Bark();
    //cout << d.name << "\n"; // Barsik
    //
    //Cat x = d; // это должно работать
    //x.Meow();
    //cout << x.name << "\n"; // Barsik
    //
    //Date date(31, 12, 2024);
    //++date;
    //cout << date;
    //date++;
    //cout << date;
    //--date;
    //cout << date;
    //date--;
    //cout << date;
    Student s;
    Student s2;
    Student s3;
    Student s4;
    
    s.AddExam(8);
    s2.AddExam(7);
    s3.AddExam(9);
    s4.AddExam(9);
    s.AddHomeWork(6);
    s2.AddHomeWork(6);
    s3.AddHomeWork(8);
    s4.AddHomeWork(8);

    //s > s2;
    //s >= s2;
    //s2 < s;
    //s2 <= s;
    //s3 == s4;
    //s != s2;


    Group g;
    Group g2("P25", "prog");
    string str = g;
    cout << str << "\n";
    str = s;
    cout << str << "\n";
    g.AddStudent(s);
    g.AddStudent(s2);
    g.TransferStudent(s, g2);
    g.ExpelStudents();
    g.ExpelBadStudent();

    //cin >> g;
    //g += s3;
    //cout << g << "\n";

    //g < g2;
    //g2 > g;
    //g <= g2;
    //g2 >= g;
    //g == g2;
    //g != g2;

    //Group g;
    //Group g2("P25", "prog");
    //
    //g.AddStudent(s);
    //g.AddStudent(s2);
    //
    //g2.AddStudent(s3);
    //g2.AddStudent(s4);
    //g2.AddStudent(s);
    //
    //Group c = g + g2;
    //cout << c << "\n";

    //Date d(23, 1, 2024);
    //Date d2(11, 4, 2024);
    //int days = d - d2;
    //cout << days << "\n";
}
