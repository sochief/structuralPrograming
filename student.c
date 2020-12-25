#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <stdbool.h>

// !TODO adding a node
// !TODO deleting a node
//  !TODO searching a node
//  !TODO update node
// !TODO print all nodes
//  !TODO read from file, create a double linked list
typedef enum
{
    CHAR = char,
    INT = int,
} TYPE;
typedef struct studentNode
{
    int id;
    char name[20];
    char surname[20];
    int limit;
    int numOfClasses;
    struct studentNode *next;
    struct studentNode *prev;
} StudentNode;

typedef struct studList
{
    struct node *head;
    struct node *tail;
} StudList;
void addStudent(StudList *, int *, char *, char *, int *, int *);  // done
void deleteStudent(StudentNode *nodeToDelete, StudList *studList); // done
StudentNode *searchStudent(int *id, StudList *studList);           // done
void updateStudent(StudentNode *nodeToUpdate, StudList *studList);
void printStudents(StudentNode *);
void deleteLast(StudList *studList);

void addStudent(StudList *studList, int *new_id, char *new_name,
                char *new_surname, int *new_limit, int *new_numOfClasses)
{
    // basically, we add a new node in the beginning of the double linked list
    // allocate node
    StudentNode *new_student;
    new_student = (StudentNode *)malloc(sizeof(StudentNode));

    // put id, name, surname, limit, numOfClasses
    new_student->id = new_id;
    strcpy(new_student->name, new_name);
    strcpy(new_student->surname, new_surname);
    new_student->limit = new_limit;
    new_student->numOfClasses = new_numOfClasses;

    // make next of next node as prev and prev as null
    if (studList->head)
    {
        studList->head->prev->new_student;
    }
    else
    {
        studList->tail = new_student
    }
    // make new node as a head
    studList->head = new_student;
}

void printStudents(StudentNode *studentNode)
{
    if (!studentNode)
        return;

    while ((studentNode->next) != NULL)
    {
        printf("ID:%d NAME:%s SURNAME:%s LIMIT:%d NUMBER OF CLASSES:%d \n", studentNode->id, studentNode->name, studentNode->surname, studentNode->limit, studentNode->numOfClasses);
        studentNode = studentNode->next;
    }
    // for the last node
    printf("ID:%d NAME:%s SURNAME:%s LIMIT:%d NUMBER OF CLASSES:%d \n", studentNode->id, studentNode->name, studentNode->surname, studentNode->limit, studentNode->numOfClasses);
}

StudentNode *searchStudent(int *id, StudList *studList)
{
    StudentNode *current;
    current = studList->head;
    while (current)
    {
        if (id == current->id)
        {
            return current;
        }
        current = current->next;
    }
    return current;
}
void updateStudent(int *id, TYPE dataToChange, StudList *studList, int choise)
{
    StudentNode *studentToChange;
    studentToChange = searchStudent(id, studList);

    switch (choise)
    {
        // name
    case choise == 1:
        if (TYPE == char)
        {
            studentToChange->name = dataToChange;
            print("Name changed");
        }
        else
        {
            printf("Wrong data type/ Wrong choise")
        }

        break;
        // surname
    case choise == 2:
        if (TYPE == char)
        {
            studentToChange->surname = dataToChange;
        }
        else
        {
            printf("Wrong data type/ Wrong choise")
        }
        break;
        // limit
    case choise == 3:
        if (TYPE == int)
        {
            studentToChange->limit = dataToChange
        }
        else
        {
            printf("Wrong data type/ Wrong choise")
        }
        break;
        // numberOfclasses
    case choise == 4:
        if (TYPE == int)
        {
            studentToChange->numOfClasses = dataToChange;
        }
        else
        {
            printf("Wrong data type/ Wrong choise")
        }
        break;
    }
}
void deleteStudent(int *id, StudList *studList)
{
    StudentNode *nodeToDelete;
    nodeToDelete = searchStudent(id, studList);
    if (nodeToDelete)
    {
        if (studList->tail = nodeToDelete)
            studList->tail = nodeToDelete->prev;

        if (nodeToDelete->prev)
            nodeToDelete->prev->next = nodeToDelete->next;

        if (nodeToDelete->next)
            nodeToDelete->next->prev = nodeToDelete->prev;

        free(nodeToDelete);
    }
}
void deleteLast(StudList *studList)
{
    StudentNode *nodeToDelete;
    if (studList && (studList->tail))
    {
        nodeToDelete = studList->tail;
        studList->tail = nodeToDelete->prev;
        studList->tail->next = NULL;
    }
}
