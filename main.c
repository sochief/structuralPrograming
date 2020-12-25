#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <stdbool.h>

// add delete change

typedef struct relationNode
{
    bool status;
    int date;
    int id;
    int stdId;
    int classId;
    char regDate[8];
    struct relationNode *next;
    struct relationNode *prev;
};

int main()
{
    // read the txt doc's
    void addTeacher();       // add node
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

// !TODO adding a node
// !TODO deleting a node
//  !TODO searching a node
//  !TODO update node
// !TODO print all nodes
//  !TODO read from file, create a double linked list
