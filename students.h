#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student
{
    int roll;
    char *name;
    char *branchName;
    int batch;
    struct Student *next;
}Student;

void addStudent();
void allStudents();
void updateStudent();
void deleteStudents();

#endif