
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct classNode
{
    int id;
    int credits;
    int capacity;
    int profId;
    struct classNode *next;
    struct classNode *prev;
} ClassNode;

typedef struct classList
{
    struct node *head;
    struct node *tail;
} ClassList;

void addClass(ClassList *classList, int *new_id, int *new_credits,
              int *new_capacity, int *new_profId)
{
    // basically, we add a new node in the beginning of the double linked list
    // allocate node
    ClassNode *new_class;
    new_class = (ClassNode *)malloc(sizeof(ClassNode));

    new_class->id = new_id;
    new_class->credits = new_credits;
    new_class->capacity = new_capacity;
    new_class->profId = new_profId;
    if (classList->head)
    {
        classList->head->prev->new_class;
    }
    else
    {
        classList->tail = new_class
    }
    classList->head = new_class;
}

void printClass(ClassNode *classNode)
{
    if (!classNode)
        return;

    while ((classNode->next) != NULL)
    {
        printf("ID:%d CREDITS:%d CAPACITY:%d PROFFESORS ID:%d \n", classNode->id, classNode->credits, classNode->capacity, classNode->profId);
        classNode = classNode->next;
    }
    // for the last node
    printf("ID:%d CREDITS:%d CAPACITY:%d PROFFESORS ID:%d \n", classNode->id, classNode->credits, classNode->capacity, classNode->profId);
}

ClassNode *searchClass(int *id, ClassList *classList)
{
    ClassNode *current;
    current = ClassList->head;
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

void updateClass(int *id, ClassList *classList, int choise, int data)
{
    ClassNode *classToChange;
    classToChange = searchClass(id, classList);
    switch (choise)
    {
    case choise == 1:
        classToChange->id = data;
        break;
    case choise == 2:
        classToChange->credits = data;
        break;
    case choise == 3:
        classToChange->capacity = data;
        break;
    case choise == 4:
        classToChange->profId = data;
        break;
    }
}

void deleteClass(int *id, ClassList *classList)
{
    ClassNode *nodeToDelete;
    nodeToDelete = searchClass(id, classList);
    if (nodeToDelete)
    {
        if (ClassList->tail = nodeToDelete)
            ClassList->tail = nodeToDelete->prev;

        if (nodeToDelete->prev)
            nodeToDelete->prev->next = nodeToDelete->next;

        if (nodeToDelete->next)
            nodeToDelete->next->prev = nodeToDelete->prev;

        free(nodeToDelete);
    }
}

void deleteLast(ClassList *classList)
{
    ClassNode *nodeToDelete;
    if (classList && (classList->tail))
    {
        nodeToDelete = classList->tail;
        classList->tail = nodeToDelete->prev;
        classList->tail->next = NULL;
    }
}