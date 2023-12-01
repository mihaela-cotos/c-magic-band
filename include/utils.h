#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct ListNode{
    char element;
    struct ListNode *right;
    struct ListNode *left;
} ListNode;

typedef struct Band{
    struct ListNode *head;
    struct ListNode *finger;
    struct ListNode *sentinel;
    struct Stack *undo_stack, *redo_stack;
} Band;

typedef struct StackNode{
    struct ListNode *element;
    struct StackNode *next;
} StackNode;

typedef struct Stack{
    struct StackNode *head;
    long size;
} Stack;

typedef struct QueueNode{
    char *element;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue{
    struct QueueNode *head;
    struct QueueNode *tail;
    long size;
} Queue;

ListNode* create_node(char symbol);

Band* create_band();

void move_left(Band *Band);

void move_right(Band *Band);

void move_left_char(Band *Band, char elem, FILE *file);

void move_right_char(Band *Band, char elem);

void write_c (Band *Band, char elem);

void insert_left (Band *Band, char elem, FILE *file);

void insert_right (Band *Band, char elem);

void show_current (Band *Band, FILE *file);

void show (Band *Band, FILE *file);

Stack* create_stack();

int is_stack_empty(Stack* stack);

void push_stack(Stack *stack, ListNode *elem);

ListNode* pop_stack(Stack *stack);

StackNode* create_stack_node(ListNode *ptr);

void undo(Band *band);

void redo(Band *band);

void delete_stack_elements(Stack *stack);

QueueNode* create_queue_node(char *command);

Queue* create_queue();

int is_queue_empty(Queue *queue);

void enqueue(Queue *queue, char *command);

char* dequeue(Queue *queue);

void execute(Band *band, Queue *queue, FILE *file);

void free_stack(Stack *stack);

void free_queue(Queue *queue);

void free_band(Band *band);
