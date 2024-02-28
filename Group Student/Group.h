#pragma once
#include <iostream>
#include "Student.h"
using namespace std;

class Group {
private:
    int studentCount = 0;
    Student** students = nullptr;
    string groupName;
    string groupSpecialization;
    int classNumber = 2;
    int passingGrade = 7;

public:
    Group();
    Group(string groupName, string groupSpecialization);
    Group(const Group& original);
    void ShowGroup();
    void AddStudent(Student& student);
    void MergeGroup(Group& g2);
    void TransferStudent(int index, Group& g2);
    void ExpelStudents();
    void ExpelBadStudent();
    void SetGroupName(string groupName);
    string GetGroupName() const;
    void SetGroupSpecialization(string groupSpecialization);
    string GetGroupSpecialization() const;
    void SetPassingGrade(int passingGrade);
    int GetPassingGrade() const;
    friend  ostream& operator<<(ostream& os, const Group& group);
    ~Group();
};