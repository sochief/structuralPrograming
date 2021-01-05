#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXIMUM 1024
// L = Volume T = threshold
#define VOLUME 4
#define THRESHOLD 3
#define STRSIZE 64
/* Shafkat Nurtdinov St.No: 16011141 
В каждом узле:
1) Адрес страницы.(DONE)
2) Количество запросов(DONE)
3) next previous(DONE)
Функции:
1) Навигация по узлам(Вывести все nodes)(TO DO)
2) Вывести счётчик запросов(Find out!)
3) Add-delete operations(Almost check!)
4) Input -- .txt(Almost check!)
5) If the address is not in the buffer -- create a node for that
    if it is -- increase a requests counter
        if the counter exceeds threshold:
            make it head
also, there is a volume limit of cache - L
    if the volume is more than L -- delete the last node
In the end of the day, ask user does he want to delete the cache after all og the actions. If user wants to quit, erase everythong.
Use doubly linked lists!
*/

typedef struct node
{
    char address[STRSIZE];
    int requests;
    struct node *next;
    struct node *prev;
} Node;

typedef struct llist
{
    struct node *head;
    struct node *tail;
    int len;

} LLIST;

void addToBeginning(LLIST *, char *, int);
void printForward(Node *);
void moveNode(Node *move, LLIST *llist);
Node *searchNode(char *address, LLIST *llist);
void deleteNode(Node *nodeToDelete, LLIST *llist);
void deleteLast(LLIST *llist);
void processToken(char *str, LLIST *llist);

// Read in the data
int main()
{
    LLIST *llist;
    char line[MAXIMUM];
    char element;
    int i;
    char *tok, *delim;
    FILE *fptr;

    llist = (LLIST *)malloc(sizeof(LLIST));
    llist->head = NULL;
    llist->tail = NULL;
    llist->len = 0;

    delim = " ";
    fptr = fopen("data.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening a file!");
        exit(1);
    }
    while (fgets(line, MAXIMUM, fptr))
    {
        tok = strtok(line, delim);
        processToken(tok, llist);
        while (tok = strtok(NULL, delim))
            processToken(tok, llist);
    }
    fclose(fptr);
    return 0;
}
//Add a check for biggest request
//Add a node in the beginning

void addToBeginning(LLIST *llist, char *new_address, int new_requests)
{
    // Allocate node
    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));

    // put in new data
    strcpy(new_node->address, new_address);
    new_node->requests = new_requests;

    // make next next node as prev and prev as null
    new_node->next = llist->head;
    new_node->prev = NULL;

    // change previous of head node to the new node
    if (llist->head)
    {
        llist->head->prev = new_node;
    }
    else
    {
        llist->tail = new_node;
    }
    // move the head to point to the new node
    llist->head = new_node;
}

void printForward(Node *node)
{
    if (!node)
        return;

    while ((node->next) != NULL)
    {
        printf("%s:%d <-> ", node->address, node->requests);
        node = node->next;
    }
    printf("%s:%d\n", node->address, node->requests);
}
void moveNode(Node *move, LLIST *llist)
{
    char address[STRSIZE];
    int requests;
    strcpy(address, move->address);
    requests = move->requests;
    deleteNode(move, llist);
    addToBeginning(llist, address, requests);
}
Node *searchNode(char *address, LLIST *llist)
{
    Node *curr;
    curr = llist->head;
    while (curr)
    {
        if (!strcmp(address, curr->address))
        {
            // search functionality
            return curr;
        }

        curr = curr->next;
    }
    return curr;
}
void deleteNode(Node *nodeToDelete, LLIST *llist)
{
    if (nodeToDelete)
    {
        if (llist->tail == nodeToDelete)
            llist->tail = nodeToDelete->prev;

        if (nodeToDelete->prev)
            nodeToDelete->prev->next = nodeToDelete->next;

        if (nodeToDelete->next)
            nodeToDelete->next->prev = nodeToDelete->prev;

        free(nodeToDelete);
    }
}
void deleteLast(LLIST *llist)
{
    Node *node;
    if (llist && (llist->tail))
    {
        node = llist->tail;
        llist->tail = node->prev;
        llist->tail->next = NULL;
        if (node)
            free(node);
    }
}

void processToken(char *str, LLIST *llist)
{
    Node *node;
    if (!str)
        return;
    node = searchNode(str, llist);
    if (node)
    {
        // address already exits
        (node->requests)++;
        if ((node->requests > THRESHOLD) && (llist->head != node))
        {
            moveNode(node, llist);
        }
    }
    else
    {
        addToBeginning(llist, str, 1);
        (llist->len)++;
    }

    if (llist->len > VOLUME)
    {
        deleteLast(llist);
        (llist->len)--;
    }

    printForward(llist->head);
}