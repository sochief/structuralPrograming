#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
// student
// !TODO fix delete function variable types
// !TODO Cases 4,5,6 list dumping for all the data
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
    char name[20];
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
void addStudent(StudList *studList, char *char_id, char *new_name, char *new_surname, char *char_limit, char *char_numOfClasses);
void printStudents(StudentNode *studentNode);
void printSingleStudent(StudentNode *studentNode);
StudentNode *searchStudent(int *id, StudList *studList);
void updateStudent(char *id, StudList *studList, char *select, char *dataToChange);
void deleteStudent(int *id, StudList *studList);
void deleteLastStudent(StudList *studList);
void loadStudent();

void addTeacher(TeacherList *teacherList, char *new_id, char *new_name, char *new_surname, char *new_title);
void printTeachers(TeacherNode *teacherNode);
void printSingleTeacher(TeacherNode *teacherNode);
TeacherNode *searchTeacher(int *id, TeacherList *teacherList);
void updateTeacher(char *char_id, TeacherList *teacherList, char *char_choise, char *data);
void deleteTeacher(int *id, TeacherList *teacherList);
void deleteLastTeacher(TeacherList *teacherList);
void loadTeachers();

void addClass(ClassList *classList, char *char_id, char *char_credits, char *char_capacity, char *char_profId, char *name);
void printClasses(ClassNode *classNode);
void printSingleClass(ClassNode *classNode);
ClassNode *searchClass(int *id, ClassList *classList);
void updateClass(char *char_id, ClassList *classList, char *char_choise, char *char_data);
void deleteClass(int *id, ClassList *classList);
void deleteLastClass(ClassList *classList);
void addRelation(RelationList *relationList, int *new_studentId, int *new_classId, char *new_registDate, char *status);
RelationNode *searchRelation(int *id, RelationList *relationList);
void updateRelationStatus(RelationList *relationList, int *id);
void printRelations(RelationNode *relationNode);
void printSingleRelation(RelationNode *relationNode);

void (*addFunct[4])() = {addStudent, addTeacher, addClass, addRelation};
void (*deleteFunct[3])() = {deleteStudent, deleteTeacher, deleteClass};
void (*updateFunct[4])() = {updateStudent, updateTeacher, updateClass, updateRelationStatus};
void (*printSingle[4])() = {printSingleStudent, printSingleTeacher, printSingleClass, printSingleRelation};
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
    int exit = 0;
    printf("---------------Welcome to the system---------------");
    while (exit != 1)
    {
        int iter = 0;
        int select, subselect, subSubs, choice, data, new_id, new_prof_id;
        char name[20], surname[20], title[20], info[20], empty, id[10], limit[10], numOfClasses[10], credits[10], capacity[20], subSubSelect[10], sub, prof_id[20];

        printMenu();
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("Add:\n1)Student\n2)Teacher\n3)Class\n");
            scanf("%d", &subselect);
            scanf("%c", &empty);
            switch (subselect)
            {
            case 1:
                printf("Adding a student");
                printf("Enter a name:\n");
                gets(name);
                printf("Print surname:\n");
                gets(surname);
                printf("Enter id:\n");
                gets(id);
                new_id = atoi(id);
                while (searchStudent(new_id, studList) != NULL)
                {
                    printf("Student with this id exist, enter anothe id:\n");
                    gets(id);
                    new_id = atoi(id);
                }
                printf("Enter number of credits:\n");
                gets(limit);
                printf("Enter number of classes:\n");
                gets(numOfClasses);
                (*addFunct[0])(studList, id, name, surname, limit, numOfClasses);
                printStudents(studList->head);
                break;
            case 2:
                printf("Adding a teacher");
                printf("Enter a name:\n");
                gets(name);
                printf("Print surname:\n");
                gets(surname);
                printf("Enter id:\n");
                gets(id);
                new_id = atoi(id);
                while (searchTeacher(new_id, teacherList) != NULL)
                {
                    printf("Teacher with this id exist, enter another id:\n");
                    gets(id);
                    new_id = atoi(id);
                }
                printf("Enter title:\n");
                gets(title);
                (*addFunct[1])(teacherList, id, name, surname, title);
                printTeachers(teacherList->head);
                break;
            case 3:
                printf("Adding a class");
                printf("Enter credits:\n");
                gets(credits);
                printf("Print capacity:\n");
                gets(capacity);
                printf("Enter id:\n");
                gets(id);
                new_id = atoi(id);
                while (searchClass(new_id, classList) != NULL)
                {
                    printf("Class with this id exist, enter another id:\n");
                    gets(id);
                    new_id = atoi(id);
                }

                // CHECK
                printf("Enter professor's id:\n");
                gets(prof_id);
                new_id = atoi(prof_id);
                while (searchTeacher(new_id, teacherList) == NULL)
                {
                    printf("Teacher with this doesn't, enter another id:\n");
                    gets(id);
                    new_id = atoi(id);
                }
                printf("Enter name:\n");
                gets(name);
                (*addFunct[2])(classList, id, credits, capacity, prof_id, name);
                printClasses(classList->head);
                break;
            default:
                printf("Wrong input");
                break;
            }
            break;

        case 2:
            printf("\n\n\nUpdate:\n1)Student\n2)Teacher\n3)Class\n");
            scanf("%d", &subselect);
            scanf("%c", &sub);
            switch (subselect)
            {
            case 1:
                printf("\nEnter student's ID:\n");
                gets(id);
                new_id = atoi(id);
                while (searchStudent(new_id, studList) == NULL)
                {
                    printf("Student with this id doesn't exist, enter another id:\n");
                    gets(id);
                    new_id = atoi(id);
                }
                printf("\nUpdating a student\nData to change:\n1)Name\n2)Surname\n");
                gets(subSubSelect);
                subSubs = atoi(subSubSelect);
                switch (subSubs)
                {
                case 1:
                    printf("\nEnter a Name:\n");
                    gets(info);
                    (*updateFunct[0])(id, studList, subSubSelect, info);
                    break;
                case 2:
                    printf("\nEnter a Surname:\n");
                    gets(info);
                    (*updateFunct[0])(id, studList, subSubSelect, info);
                    break;
                default:
                    printf("\nWrong input.\n");
                    break;
                }
                printStudents(studList->head);
                break;
            case 2:
                printf("Updating a professor");
                printf("\nEnter professors's ID:\n");
                gets(id);
                new_id = atoi(id);
                while (searchTeacher(new_id, teacherList) == NULL)
                {
                    printf("Professor with this id doesn't exist, enter another id:\n");
                    gets(id);
                    new_id = atoi(id);
                }
                printf("\nUpdating a professor\nData to change:\n1)Name\n2)Surname\n3)Title\n");
                gets(subSubSelect);
                subSubs = atoi(subSubSelect);
                switch (subSubs)
                {
                case 1:
                    printf("\nEnter a Name:\n");
                    gets(info);
                    (*updateFunct[1])(id, teacherList, subSubSelect, info);
                    break;
                case 2:
                    printf("\nEnter a Surname:\n");
                    gets(info);
                    (*updateFunct[1])(id, teacherList, subSubSelect, info);
                    break;
                case 3:
                    printf("\nEnter a title:\n");
                    gets(info);
                    (*updateFunct[1])(id, teacherList, subSubSelect, info);
                    break;
                default:
                    printf("\nWrong input.\n");
                    break;
                }
                printTeachers(teacherList->head);
                break;
            case 3:
                printf("Updating a class");
                printf("\nEnter class ID:\n");
                gets(id);
                new_id = atoi(id);
                while (searchClass(new_id, classList) == NULL)
                {
                    printf("Class with this id doesn't exist, enter another id:\n");
                    gets(id);
                    new_id = atoi(id);
                }
                printf("\nUpdating a class\nData to change:\n1)Credits\n2)Capacity\n3)Professor's ID\n4)Name\n");
                gets(subSubSelect);
                subSubs = atoi(subSubSelect);
                switch (subSubs)
                {
                case 1:
                    printf("\nEnter credits:\n");
                    gets(info);
                    (*updateFunct[2])(id, classList, subSubSelect, info);
                    break;
                case 2:
                    printf("\nEnter capacity:\n");
                    gets(info);
                    (*updateFunct[2])(id, classList, subSubSelect, info);
                    break;
                case 3:
                    printf("\nEnter a Professors's ID:\n");
                    gets(prof_id);
                    new_prof_id = atoi(prof_id);
                    while (searchTeacher(new_prof_id, teacherList) == NULL)
                    {
                        printf("Professor with this id doesn't exist, enter another id:\n");
                        gets(prof_id);
                        new_prof_id = atoi(prof_id);
                    }
                    (*updateFunct[2])(id, classList, subSubSelect, prof_id);
                    break;
                case 4:
                    printf("Enter a name:\n");
                    gets(info);
                    (*updateFunct[2])(id, classList, subSubSelect, info);
                    break;
                default:
                    printf("\nWrong input.\n");
                    break;
                }
                printClasses(classList->head);
                break;
            default:
                break;
            }
            break;
        case 3:
            printf("\n\n\nRemove:\n1)Student\n2)Teacher\n3)Class\n");
            scanf("%d", &subselect);

            switch (subselect)
            {
            case 1:
                printf("Enter id of a student to remove:\n");
                scanf("%d", &data);
                (*deleteFunct[0])(data, studList);
                (*printAll[0])(studList->head);
                break;
            case 2:
                printf("Enter id of a teacher to remove:\n");
                scanf("%d", &data);
                (*deleteFunct[1])(data, teacherList);
                (*printAll[1])(teacherList->head);
                break;
            case 3:
                printf("Enter id of a class to remove:\n");
                scanf("%d", &data);
                (*deleteFunct[2])(data, classList);
                (*printAll[2])(classList->head);
                break;

            default:
                printf("\nWrong input.\n");
                break;
            }
            break;
        case 4:
            printf("Register for the class.\nPrint your Student id as well as Class Id");
            break;
        case 5:
            printf("List all the classes chosen by a student.\nPlease provide student id:\n");
            break;
        case 6:
            printf("To save all student, who took the class, please provide the Id of the class.\n");
            break;
        default:
            printf("Wrong input.");
            break;
        }
    }

    return (0);
}
void printMenu()
{
    printf("Choose your operation:\n1)Add student/teacher/class\n2)Update student/teacher/class\n3)Delete student/teacher/class\n4)Register/Cancel for a class\n5)Print all courses taken by student\n6)Load to the txt all student, who took certain class\n");
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
        char id[10];
        int count = 0;
        char name[20];
        char surname[20];
        char limit[10];
        char numberOfClasses[10];
        while (tok != NULL)
        {
            switch (count)
            {
            case 0:
                strcpy(id, tok);
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
                strcpy(limit, tok);
                count++;
                break;
            case 4:
                strcpy(numberOfClasses, tok);
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
        char char_id[10];
        int count = 0;
        char name[20];
        char surname[20];
        char title[20];
        while (tok != NULL)
        {
            switch (count)
            {
            case 0:
                strcpy(char_id, tok);
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
        (*addFunct[1])(teacherList, char_id, name, surname, title);
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
        char id[20];
        int count = 0;
        char credits[20];
        char capacity[20];
        char profId[20];
        char name[20];
        while (tok != NULL)
        {
            switch (count)
            {
            case 0:
                strcpy(id, tok);
                count++;
                break;

            case 1:
                strcpy(credits, tok);
                count++;
                break;
            case 2:
                strcpy(capacity, tok);
                count++;
                break;
            case 3:
                strcpy(profId, tok);
                count++;
                break;
            case 4:
                strcpy(name, tok);
                count++;
                break;
            }
            tok = strtok(NULL, delim);
        }
        (*addFunct[2])(classList, id, credits, capacity, profId, name);
    }
}
void addStudent(StudList *studList, char *char_id, char *new_name, char *new_surname, char *char_limit, char *char_numOfClasses)
{
    // basically, we add a new node in the beginning of the double linked list
    // allocate node
    StudentNode *new_student;
    new_student = (StudentNode *)malloc(sizeof(StudentNode));
    int int_id = atoi(char_id);

    new_student->id = int_id;
    strcpy(new_student->name, new_name);
    strcpy(new_student->surname, new_surname);
    int int_limit = atoi(char_limit);
    int int_numOfClasses = atoi(char_numOfClasses);
    new_student->limit = int_limit;
    new_student->numOfClasses = int_numOfClasses;

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
void updateStudent(char *char_id, StudList *studList, char *char_choice, char *dataToChange)
{
    // !TODO wrong choise for all updates
    StudentNode *studentToChange;
    int int_id = atoi(char_id);
    studentToChange = searchStudent(int_id, studList);
    int choice = atoi(char_choice);
    if (studentToChange == NULL)
    {
        printf("Student not found");
        return NULL;
    }
    switch (choice)
    {
    case 1:
    {
        printf("%s\n", dataToChange);
        strcpy(studentToChange->name, dataToChange);
        printf("Name changed.\n");
        break;
    }
    case 2:
    {
        strcpy(studentToChange->surname, dataToChange);
        printf("Surname changed.");
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

void addTeacher(TeacherList *teacherList, char *char_id, char *new_name, char *new_surname, char *new_title)
{
    // basically, we add a new node in the beginning of the double linked list
    // allocate node
    TeacherNode *new_teacher;
    new_teacher = (TeacherNode *)malloc(sizeof(TeacherNode));
    int int_id = atoi(char_id);
    // put id, name, surname, limit, numOfClasses
    new_teacher->id = int_id;
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
void updateTeacher(char *char_id, TeacherList *teacherList, char *char_choise, char *data)
{
    TeacherNode *teacherToChange;
    int int_id = atoi(char_id);
    int int_choise = atoi(char_choise);
    teacherToChange = searchTeacher(int_id, teacherList);
    switch (int_choise)
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
void addClass(ClassList *classList, char *char_id, char *char_credits, char *char_capacity, char *char_profId, char *name)
{
    ClassNode *new_class;
    new_class = (ClassNode *)malloc(sizeof(ClassNode));
    int int_id = atoi(char_id);
    int int_credits = atoi(char_credits);
    int int_capacity = atoi(char_capacity);
    int int_profId = atoi(char_profId);
    new_class->id = int_id;
    new_class->credits = int_credits;
    new_class->capacity = int_capacity;
    new_class->profId = int_profId;
    strcpy(new_class->name, name);
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
    printf("ID:%d CREDITS:%d CAPACITY:%d PROFFESORS ID:%d NAME:%s \n", classNode->id, classNode->credits, classNode->capacity, classNode->profId, classNode->name);
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
void updateClass(char *char_id, ClassList *classList, char *char_choise, char *char_data)
{
    int int_id = atoi(char_id);
    int int_choise = atoi(char_choise);
    int int_data = atoi(char_data);
    ClassNode *classToChange;
    classToChange = searchClass(int_id, classList);
    switch (int_choise)
    {
    case 1:
        classToChange->credits = int_data;
        break;
    case 2:
        classToChange->capacity = int_data;
        break;
    case 3:
        classToChange->profId = int_data;
        break;
    case 4:
        strcpy(classToChange->name, char_data);
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
