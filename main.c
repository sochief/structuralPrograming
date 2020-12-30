#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
// student

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
    struct classNode *head;
    struct classNode *tail;
} ClassList;

// !TODO check if the id is not used, if it is, ask for the other one
typedef struct relationNode
{
    char status[20];
    int id;
    int studentId;
    int classId;
    char registDate[64];
    struct relationNode *next;
    struct relationNode *prev;
} RelationNode;
typedef struct relationList
{
    int counter;
    struct relationNode *head;
    struct relationNode *tail;
} RelationList;
// Function Declaration
void addStudent(StudList *studList, int *new_id, char *new_name, char *new_surname, int *new_limit, int *new_numOfClasses);
void printStudents(StudentNode *studentNode);
void printSingleStudent(StudentNode *studentNode);
StudentNode *searchStudent(int *id, StudList *studList);
void updateStudent(int *id, StudList *studList, int *select, char *dataToChange);
void deleteStudent(int *id, StudList *studList);
void deleteLastStudent(StudList *studList);
void loadStudent();

void addTeacher(TeacherList *teacherList, int *new_id, char *new_name, char *new_surname, char *new_title);
void printTeachers(TeacherNode *teacherNode);
void printSingleTeacher(TeacherNode *teacherNode);
TeacherNode *searchTeacher(int *id, TeacherList *teacherList);
void updateTeacher(int *id, TeacherList *teacherList, int choise, char data);
void deleteTeacher(int *id, TeacherList *teacherList);
void deleteLastTeacher(TeacherList *teacherList);
void loadTeachers();

void addClass(ClassList *classList, int *new_id, int *new_credits, int *new_capacity, int *new_profId);
void printClasses(ClassNode *classNode);
void printSingleClass(ClassNode *classNode);
ClassNode *searchClass(int *id, ClassList *classList);
void updateClass(int *id, ClassList *classList, int choise, int data);
void deleteClass(int *id, ClassList *classList);
void deleteLastClass(ClassList *classList);
void addRelation(RelationList *relationList, int *new_studentId, int *new_classId, char *new_registDate, char *status);
RelationNode *searchRelation(int *id, RelationList *relationList);
void updateRelationStatus(RelationList *relationList, int *id);
void printRelations(RelationNode *relationNode);
void printSingleRelation(RelationNode *relationNode);

void (*addFunct[4])() = {addStudent, addTeacher, addClass, addRelation};
void (*deleteFunct[3])() = {deleteStudent, deleteTeacher, deleteClass};
void (*updateFunct[4])() = {updateClass, updateStudent, updateTeacher, updateRelationStatus};
void (*printSingle[4])() = {printSingleClass, printSingleStudent, printSingleTeacher, printSingleRelation};
void (*printAll[4])() = {printStudents, printTeachers, printClasses, printRelations};

int main()
{
    // !TODO function to dump the data
    //  !TODO create a main flow
    StudList *studList;
    studList = (StudList *)malloc(sizeof(StudList));
    studList->head = NULL;
    studList->tail = NULL;

    TeacherList *teacherList;
    teacherList = (TeacherList *)malloc(sizeof(TeacherList));
    teacherList->head = NULL;
    teacherList->tail = NULL;

    ClassList *classList;
    classList = (ClassList *)malloc(sizeof(ClassList));
    classList->head = NULL;
    classList->tail = NULL;

    loadStudent(studList);
    loadTeachers(teacherList);
    loadClasses(classList);
    (*printAll[0])(studList->head);
    (*printAll[1])(teacherList->head);
    (printAll[2])(classList->head);
    return (0);
}
void loadStudent(StudList *studList)
{
    char line[100];
    char element;
    int i;
    char *tok, *delim;
    FILE *fptr;

    delim = "/";
    printf("Reading students.\n");

    fptr = fopen("./data/stdList.txt", "r");
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
        (*addFunct[0])(studList, id, name, surname, limit, numberOfClasses);
        //addStudent(studList, id, name, surname, limit, numberOfClasses);
    }
}
void loadTeachers(TeacherList *teacherList)
{
    char line[100];
    char element;
    int i;
    char *tok, *delim;
    FILE *fptr;

    delim = "/";
    printf("Reading teacher.\n");

    fptr = fopen("./data/profList.txt", "r");
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
        char title[20];
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
                strcpy(title, tok);
                count++;
                break;
            default:
                break;
            }
            tok = strtok(NULL, delim);
        }
        (*addFunct[1])(teacherList, id, name, surname, title);
    }
}
void loadClasses(ClassList *classList)
{
    char line[100];
    char element;
    int i;
    char *tok, *delim;
    FILE *fptr;

    delim = "/";
    printf("Reading classes.\n");

    fptr = fopen("./data/classList.txt", "r");
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
        int credits;
        int capacity;
        int profId;
        while (tok != NULL)
        {
            switch (count)
            {
            case 0:
                id = atoi(tok);
                count++;
                break;

            case 1:
                credits = atoi(tok);
                count++;
                break;
            case 2:
                capacity = atoi(tok);
                count++;
                break;
            case 3:
                profId = atoi(tok);
                count++;
                break;
            default:
                break;
            }
            tok = strtok(NULL, delim);
        }
        (*addFunct[2])(classList, id, credits, capacity, profId);
    }
}
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
        printSingleStudent(studentNode);
        studentNode = studentNode->next;
    }
    // for the last node
    printSingleStudent(studentNode);
}
void printSingleStudent(StudentNode *studentNode)
{
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
    // !TODO wrong choise for all updates
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
void deleteLastStudent(StudList *studList)
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

// Teacher Section

void addTeacher(TeacherList *teacherList, int *new_id, char *new_name, char *new_surname, char *new_title)
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

    new_teacher->next = teacherList->head;
    new_teacher->prev = NULL;

    // make next of next node as prev and prev as null
    if (teacherList->head)
    {
        teacherList->head->prev = new_teacher;
    }
    else
    {
        teacherList->tail = new_teacher;
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
        printSingleTeacher(teacherNode);
        teacherNode = teacherNode->next;
    }
    // for the last node
    printSingleTeacher(teacherNode);
}
void printSingleTeacher(TeacherNode *teacherNode)
{
    printf("ID:%d NAME:%s SURNAME:%s TITLE:%s \n", teacherNode->id, teacherNode->name, teacherNode->surname, teacherNode->title);
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
    case 1:
        strcpy(teacherToChange->name, data);
        break;
    // surname
    case 2:
        strcpy(teacherToChange->surname, data);
        break;
    // title
    case 3:
        strcpy(teacherToChange->title, data);
        break;
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

// Classes Section

void deleteLastTeacher(TeacherList *teacherList)
{
    TeacherNode *nodeToDelete;
    if (teacherList && (teacherList->tail))
    {
        nodeToDelete = teacherList->tail;
        teacherList->tail = nodeToDelete->prev;
        teacherList->tail->next = NULL;
    }
}
void addClass(ClassList *classList, int *new_id, int *new_credits, int *new_capacity, int *new_profId)
{
    ClassNode *new_class;
    new_class = (ClassNode *)malloc(sizeof(ClassNode));

    new_class->id = new_id;
    new_class->credits = new_credits;
    new_class->capacity = new_capacity;
    new_class->profId = new_profId;

    new_class->next = classList->head;
    new_class->prev = NULL;
    if (classList->head)
    {
        classList->head->prev = new_class;
    }
    else
    {
        classList->tail = new_class;
    }
    classList->head = new_class;
}
void printClasses(ClassNode *classNode)
{
    if (!classNode)
        return;

    while ((classNode->next) != NULL)
    {
        printSingleClass(classNode);
        classNode = classNode->next;
    }
    printSingleClass(classNode);
}
void printSingleClass(ClassNode *classNode)
{
    printf("ID:%d CREDITS:%d CAPACITY:%d PROFFESORS ID:%d \n", classNode->id, classNode->credits, classNode->capacity, classNode->profId);
}
ClassNode *searchClass(int *id, ClassList *classList)
{
    ClassNode *current;
    current = classList->head;
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
    case 1:
        classToChange->id = data;
        break;
    case 2:
        classToChange->credits = data;
        break;
    case 3:
        classToChange->capacity = data;
        break;
    case 4:
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
        if (classList->tail = nodeToDelete)
            classList->tail = nodeToDelete->prev;

        if (nodeToDelete->prev)
            nodeToDelete->prev->next = nodeToDelete->next;

        if (nodeToDelete->next)
            nodeToDelete->next->prev = nodeToDelete->prev;

        free(nodeToDelete);
    }
}
void deleteLastClass(ClassList *classList)
{
    ClassNode *nodeToDelete;
    if (classList && (classList->tail))
    {
        nodeToDelete = classList->tail;
        classList->tail = nodeToDelete->prev;
        classList->tail->next = NULL;
    }
}

// Relations Section

void addRelation(RelationList *relationList, int *new_studentId, int *new_classId, char *new_registDate, char *status)
{

    RelationNode *new_relation;
    new_relation = (RelationNode *)malloc(sizeof(RelationNode));
    // Counter stays for amount of all relations, so we can give them id's starting from 1.
    (relationList->counter)++;
    int new_relationID = relationList->counter;
    new_relation->id = new_relationID;
    char stat = "Registered";
    strcpy(new_relation->status, stat);
    new_relation->id = relationList->counter;
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    assert(strftime(new_relation->registDate, sizeof(new_relation->registDate), "%c", now));
    new_relation->next = relationList->head;
    new_relation->prev = NULL;
    if (relationList->head)
    {
        relationList->head->prev = new_relation;
    }
    else
    {
        relationList->tail = new_relation;
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
void updateRelationStatus(RelationList *relationList, int *id)
{
    RelationNode *relationToUpdate;
    relationToUpdate = searchRelation(id, relationList);
    if (strcmp(relationToUpdate->status, "Registered"))
    {
        strcpy(relationToUpdate->status, "Cancelled");
        time_t now = time(NULL);
        struct tm *tm = localtime(&now);
        assert(strftime(relationToUpdate->registDate, sizeof(relationToUpdate->registDate), "%c", now));
        printf("Changed status to Cancelled");
    }
    else
    {
        strcpy(relationToUpdate->status, "Registered");
        time_t now = time(NULL);
        struct tm *tm = localtime(&now);
        assert(strftime(relationToUpdate->registDate, sizeof(relationToUpdate->registDate), "%c", now));
        printf("Changed status to Applied");
    }
}
void printRelations(RelationNode *relationNode)
{
    if (!relationNode)
    {
        return;
    }
    while ((relationNode->next) != NULL)
    {
        printSingleRelation(relationNode);
        relationNode = relationNode->next;
    }
    printSingleRelation(relationNode);
}
void printSingleRelation(RelationNode *relationNode)
{
    printf("CLASS ID:%d    STUDENT ID:%d    RELATION ID:%d    STATUS:%s    REGISTRATION DATE:%c\n", relationNode->id, relationNode->studentId, relationNode->status, relationNode->registDate);
}
