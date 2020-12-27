
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct relationNode
{
    bool status;
    int id;
    int studentId;
    int classId;
    char registDate[30];
    struct relationNode *next;
    struct relationNode *prev;
} RelationNode;

typedef struct relationList
{
    int counter = 0;
    struct relationNode *head;
    struct relationNode *tail;
} RelationList;

void addRelation(RelationList *relationList, int *new_studentId, int *new_classId, char *new_registDate)
{
    RelationNode *new_relation;
    new_relation = (RelationNode *)malloc(sizeof(RelationNode));
    // Counter stays for amount of all relations, so we can give them id's starting from 1.
    (relationList->counter)++;
    int new_relationID = relationList->counter;
    new_relation->id = new_relationID;

    new_relation->status = true;

    new_relation->studentId = new_studentId;
    if (relationList->head)
    {
        relationList->head->prev->new_relation;
    }
    else
    {
        relationList->tail = new_relation
    }
    relationList->head = new_relation;
}

RelationNode *searchRelation(int *id, RelationList *relationList)
{
    RelationNode *current;
    current = relationList->head;
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
void updateStatus(RelationNode *relationToUpdate, )
{
    RelationNode *relationToUpdate;
    if (relationToUpdate->status == true)
        relationToUpdate->status = false;
    else
        relationToUpdate->status = true;
}
