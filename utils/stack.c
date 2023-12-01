#include "../utils.h"

/* STACK FUNCTIONS */

StackNode* create_stack_node(ListNode *ptr) {
    StackNode *node = malloc (sizeof(StackNode));
    node->element = ptr;
    node->next = NULL;
    return node;
}

Stack* create_stack() {
    Stack *new_stack = malloc (sizeof(Stack));
    new_stack->head = NULL;
    new_stack->size = 0;
    return new_stack;
}

int is_stack_empty(Stack *stack) {
    return stack->head == NULL;
}

void push_stack(Stack *stack, ListNode *elem) {
    StackNode *node = create_stack_node(elem);
    if (is_stack_empty(stack)) {
        stack->head = node;
        stack->size++;
        return;
    }

    node->element = elem;
    node->next = stack->head;

    stack->head = node;
    stack->size++;
}

ListNode* pop_stack(Stack *stack) {
    if (is_stack_empty(stack)) {
        return NULL;
    }

    StackNode *tmp = stack->head;
    ListNode *element = stack->head->element;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;

    return element;
}

void free_stack(Stack *stack) {
    if (is_stack_empty(stack)) {
        free(stack);
        return;
    }

    while (!is_stack_empty(stack)) {
        pop_stack(stack);
    }

    free(stack);
    stack = NULL;
}
