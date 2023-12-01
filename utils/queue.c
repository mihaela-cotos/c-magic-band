#include "../utils.h"

/* QUEUE FUNCTIONS */

QueueNode* create_queue_node(char* command) {
    QueueNode* node = malloc (sizeof(QueueNode));
    node->element = malloc ((strlen(command) + 1) * sizeof(char));
    strcpy(node->element, command);
    node->element[strlen(command)] = '\0';
    node->next = NULL;
    return node;
}

Queue* create_queue() {
    Queue *queue = (Queue*) malloc (sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

int is_queue_empty(Queue* queue) {
    return (queue == NULL || queue->head == NULL || queue->size == 0);
}

void enqueue(Queue* queue, char* command) {
    QueueNode* node = create_queue_node(command);
    if (is_queue_empty(queue)) {
        queue->head = queue->tail = node;
        queue->head->next = NULL;
    } else {
        queue->tail->next = node;
        queue->tail->next->next = NULL;
        queue->tail = queue->tail->next;
    }

    queue->size++;
}

char* dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("ERROR EMPTY QUEUE\n");
        return NULL;
    }

    char* command; 

    if(queue->head == queue->tail) {
        command = queue->head->element;
        free(queue->head);
        queue->head = queue->tail = NULL;
        queue->size--;
        return command;
    }

    QueueNode *tmp = queue->head;
    command = queue->head->element;
    queue->head = queue->head->next;
    free(tmp);
    queue->size--;

    return command;
}

void free_queue(Queue *queue) {
    if(is_queue_empty(queue)) {
        free(queue);
        return;
    }

    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
    queue = NULL;
}
