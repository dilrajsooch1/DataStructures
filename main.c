

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enum for factions
enum Faction {
    RED,
    BLUE,
    GREEN
};

struct UserInfo {       //struct for userinfo
    char username[9];
    int level;
    enum Faction faction;
};

struct QNode {          //linked list node
    struct UserInfo userinfo;
    struct QNode* next;
};

struct Queue {              //queue struct
    struct QNode* front, *rear;
};

char generateRandomChar() {                 //random char function for username
    char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int charsetSize = sizeof(charset) - 1;
    return charset[rand() % charsetSize];               //using charset as an array and the rand value is choosing the index based on the parameters of the size
}

void generateRandomUsername(char* username, int length) {       //for loop for 10 characters but coded it as it could be any length for futire purposes
    for (int i = 0; i < length - 1; ++i) {
        username[i] = generateRandomChar();
    }
    username[length - 1] = '\0'; // Null-terminate the string
}

struct QNode* createNewNode() {
    struct QNode* newNode = (struct QNode*)malloc(sizeof(struct QNode));    //allocate memory
    generateRandomUsername(newNode->userinfo.username, 11);                 //username generator from above functions
    newNode->userinfo.level = rand() % 60 + 1;                              //1-60

    //Randomly choose faction (red, blue, or green)
    enum Faction factionChoice = rand() % 3;                //faction can be 0,1,2
    newNode->userinfo.faction = factionChoice;              //red blue or green

    newNode->next = NULL;           //pointing at next node //pusing to rear
    return newNode;
}

//init emptyqueue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL, q->rear = NULL;
    return q;
}

//adding a node to end of queue
void enqueue(struct Queue* q) {
    struct QNode* temp = createNewNode();
    if (q->rear == NULL) {              //if rear is emppty node will be front and rear
        q->front = q->rear = temp;
    } else {                    //moving rear pointer to the newly added node
        q->rear->next = temp;
        q->rear = temp;
    }
}

//must dequeue the front node and move front node to next and print to dequeued node to system
void dequeue(struct Queue* q) {
    if (q->front == NULL)
        return;                 //nothing in queue

    struct QNode* temp = q->front;      //temp ptr to placehold for front while front ptr moves to the next node
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;             //nothing in queue
    }

    char* factionStr;                   //variable for string colour
    switch (temp->userinfo.faction) {
        case RED:                       //enum to string
            factionStr = "RED";
            break;
        case BLUE:
            factionStr = "BLUE";
            break;
        case GREEN:
            factionStr = "GREEN";
            break;
    }

    printf("The Dequeued Node from Queue is: Username: %s, Level: %d, Faction: %s\n",
           temp->userinfo.username, temp->userinfo.level, factionStr);

    free(temp);
}


void printQueue(struct Queue* p) {
    if (p->front == NULL) {
        printf("Queue is empty.\n");            //empty check
        return;
    }
    //printing queue function

    struct QNode* current = p->front;

    while (current != NULL) {
        char* factionStr;
        switch (current->userinfo.faction) {
            case RED:
                factionStr = "RED";             //enum to string
                break;
            case BLUE:
                factionStr = "BLUE";
                break;
            case GREEN:
                factionStr = "GREEN";
                break;

        }

        printf("Username: %s, Level: %d, Faction: %s\n",
               current->userinfo.username, current->userinfo.level, factionStr);
        current = current->next;
    }
}

int main() {
    srand(time(NULL));          //seed
    // Create a queue
    struct Queue* queue = createQueue();

    // Hardcoded number of users
    int numUsers = 3;           //control for number of users generated

    // Enqueue users using a for loop
    for (int i = 0; i < numUsers; ++i) {
        enqueue(queue);
    }

    // Print the initial state of the queue
    printf("Initial Queue:\n\n");
    printQueue(queue);

    // Dequeue and print each user until the queue is empty
    while (queue->front != NULL) {
        printf("\nAfter Dequeue:\n\n");
        dequeue(queue);
        printf("\nPresent Queue:\n");
        printQueue(queue);
    }

    return 0;
}




























