#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student
{
    int id;
    char name;
    char surname;
    int limit;
    int numOfClasses;
};
typedef struct teacher
{
    int id;
    char name;
    char surname;
    char title;
};

typedef struct class
{
    int id;
    int credits;
    int capacity;
    int profId;
};

int main()
{
    !TODO
        // read the txt doc's
        void
        addTeacher();        // add node
    void addStudent();       // add ->>-
    void addSubject();       // add ->>-
    void removeTeacher();    // delete node -> reassign to the previous
    void removeStudent();    // delete node -> reassign to the previous node
    void removeSubject();    // delete node
    void updateTeacher();    // node
    void updateSubject();    // node
    void updateStudent();    // node
    void printClass();       //
    void printClassesProf(); //
    void printClassesStd();  //
    void saveStudents();     //
    void readStd();          //filename
    void readPrf();          // ->>-
    void readCls();          // ->>-
}