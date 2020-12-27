#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <stdbool.h>

// !TODO search by a class id

typedef struct teacherNode
{
    int id;
    char name[20];
    char surname[20];
    char title[20];
    struct teacherNode *next;
    struct teacherNode *prev;
} TeacherNode;
typedef struct teacherList
{
    struct teacherNode *head;
    struct teacherNode *tail;
} TeacherList;

void addTeacher(TeacherList *teacherList, int *new_id, char *new_name,
                char *new_surname, char *new_title)
{
    // basically, we add a new node in the beginning of the double linked list
    // allocate node
    TeacherNode *new_teacher;
    new_teacher = (TeacherNode *)malloc(sizeof(TeacherNode));

    // put id, name, surname, limit, numOfClasses
    new_teacher->id = new_id;
    strcpy(new_teacher->name, new_name);
    strcpy(new_teacher->surname, new_surname);
    strcpy(new_teacher->title, new_title);

    // make next of next node as prev and prev as null
    if (teacherList->head)
    {
        teacherList->head->prev->new_teacher;
    }
    else
    {
        teacherList->tail = new_teacher
    }
    // make new node as a head
    teacherList->head = new_teacher;
}

void printTeachers(TeacherNode *teacherNode)
{
    if (!teacherNode)
        return;

    while ((teacherNode->next) != NULL)
    {
        printf("ID:%d NAME:%s SURNAME:%s TITLE:%s \n", teacherNode->id, teacherNode->name, teacherNode->surname, teacherNode->title);
        teacherNode = teacherNode->next;
    }
    // for the last node
    printf("ID:%d NAME:%s SURNAME:%s LIMIT:%d NUMBER OF CLASSES:%d \n", teacherNode->id, teacherNode->name, teacherNode->surname, teacherNode->title);
}

TeacherNode *searchTeacher(int *id, TeacherList *teacherList)
{
    TeacherNode *current;
    current = teacherList->head;
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

void updateTeacher(int *id, TeacherList *teacherList, int choise, char data)
{
    TeacherNode *teacherToChange;
    teacherToChange = searchTeacher(id, teacherList);
    switch (choise)
    {
        // name
    case choise == 1:
        teacherToChange->name = data;
        break;
    // surname
    case choise == 2:
        teacherToChange->surname = data;
        break;
    // title
    case choise == 3:
        teacherToChange->title = data;
    }
}

void deleteTeacher(int *id, TeacherList *teacherList)
{
    TeacherNode *nodeToDelete;
    nodeToDelete = searchTeacher(id, teacherList);
    if (nodeToDelete)
    {
        if (teacherList->tail = nodeToDelete)
            teacherList->tail = nodeToDelete->prev;

        if (nodeToDelete->prev)
            nodeToDelete->prev->next = nodeToDelete->next;

        if (nodeToDelete->next)
            nodeToDelete->next->prev = nodeToDelete->prev;

        free(nodeToDelete);
    }
}

void deleteLast(TeacherList *teacherList)
{
    TeacherNode *nodeToDelete;
    if (teacherList && (teacherList->tail))
    {
        nodeToDelete = teacherList->tail;
        teacherList->tail = nodeToDelete->prev;
        teacherList->tail->next = NULL;
    }
}
