#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <stdbool.h>

// !TODO adding a node
//  !TODO read from file, create a double linked list

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
    struct studentNode *head;
    struct studentNode *tail;
} StudList;

void addStudent(StudList *studList, int *new_id, char *new_name, char *new_surname, int *new_limit, int *new_numOfClasses)
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

    new_student->next = studList->head;
    new_student->prev = NULL;
    // make next of next node as prev and prev as null
    if (studList->head)
    {
        studList->head->prev = new_student;
    }
    else
    {
        studList->tail = new_student;
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
void updateStudent(int *id, StudList *studList, int *select, char *dataToChange)
{
    StudentNode *studentToChange;
    studentToChange = searchStudent(id, studList);
    int choise = select;
    switch (choise)
    {
    case 1:
    {
        printf("%s\n", dataToChange);
        strcpy(studentToChange->name, dataToChange);
        printf("Name changed./n");
        break;
    }
    case 2:
    {
        strcpy(studentToChange->surname, dataToChange);
        printf("Surname changed.");
        break;
    }
    case 3:
    {
        // make it int
        dataToChange = atoi(dataToChange);
        studentToChange->limit = dataToChange;
        printf("Students limit changed.");
        break;
    }
    case 4:
    {
        dataToChange = atoi(dataToChange);
        studentToChange->numOfClasses = dataToChange;
        printf("Number of classes changed.");
        break;
    }
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
        if (nodeToDelete)
            free(nodeToDelete);
    }
}

int main()
{
    StudList *studList;
    char line[100];
    char element;
    int i;
    char *tok, *delim;
    FILE *fptr;

    studList = (StudList *)malloc(sizeof(StudList));
    studList->head = NULL;
    studList->tail = NULL;

    delim = "/";
    printf("Entering a programm.\n");
    fptr = fopen("stdList.txt", "r");
    if (fptr == NULL)
    {
        printf("Error reading a file.");
        exit(0);
    }
    while (fgets(line, 100, fptr))
    {
        tok = strtok(line, delim);
        int id;
        int count = 0;
        char name[20];
        char surname[20];
        int limit;
        int numberOfClasses;
        while (tok != NULL)
        {
            switch (count)
            {
            case 0:
                id = atoi(tok);
                count++;
                break;

            case 1:
                strcpy(name, tok);
                count++;
                break;
            case 2:
                strcpy(surname, tok);
                count++;
                break;
            case 3:
                limit = atoi(tok);
                count++;
                break;
            case 4:
                numberOfClasses = atoi(tok);
                count++;
                break;
            default:
                break;
            }
            tok = strtok(NULL, delim);
        }
        addStudent(studList, id, name, surname, limit, numberOfClasses);
    }
    fclose(fptr);
    int testId = 2;
    char name[20] = "15";
    int choise = 3;
    printStudents(studList->head);
    printf("Updating...\n");
    updateStudent(testId, studList, choise, name);
    printf("Finished updateing...\n");
    printStudents(studList->head);
    return (0);
}
