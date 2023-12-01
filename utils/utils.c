#include "../utils.h"

ListNode *create_node(char symbol) {
    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->element = symbol;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

Band* create_band() {
    Band *new_band = malloc(sizeof(Band));

    if (new_band == NULL) {
        return NULL;
    }

    // sentinel is the first node of the band
    // it doesn't contain useful information
    new_band->sentinel = create_node('-');
    new_band->head = create_node('#');
    new_band->sentinel->right = new_band->head;
    new_band->head->left = new_band->sentinel;
    new_band->undo_stack = create_stack();
    new_band->redo_stack = create_stack();

    new_band->finger = new_band->head;

    return new_band;
}

/* 
UPDATE operations :

1. move finger one position to the left or to the right 
*/

void move_left(Band *band) {
    if (band->finger->left == band->sentinel) {
        return;
    }

    // adding the pointer to the current position in the undo stack
    push_stack(band->undo_stack, band->finger);
    band->finger = band->finger->left;
}

void move_right(Band *band) {
    if (band->finger->right == NULL) {
        ListNode* new_node = create_node('#');
        new_node->left = band->finger;
        band->finger->right = new_node;
    }

    // adding the pointer to the current position in the undo stack
    push_stack(band->undo_stack, band->finger);
    band->finger = band->finger->right;
}


/* 
2. move to the left or to the right 
until found the element (first occurrence in the band) */

void move_left_char(Band *band, char symbol, FILE *file) {
    ListNode *tmp = band->finger;

    while (tmp != band->sentinel) {
        if (tmp->element == symbol) {
            band->finger = tmp;
            return;
        }
        tmp = tmp->left;
    }

    fprintf(file, "%s\n", "ERROR");
}

void move_right_char(Band *band, char symbol) {
    while (band->finger->right != NULL) {
        if (band->finger->element == symbol) {
            return;
        }
        band->finger = band->finger->right;
    }

    if (band->finger->element == symbol) {
        return;
    }

    ListNode* node = create_node('#');
    band->finger->right = node;
    node->left = band->finger;
    band->finger = node;
}


/* 3. modify current element */

void write_c(Band *band, char symbol) {
    band->finger->element = symbol;

    // delete the elements from undo/redo stacks after write operation
    delete_stack_elements(band->undo_stack);
    delete_stack_elements(band->redo_stack);
}


/* 4. insert a character to the left/right side of finger */

void insert_left(Band *band, char symbol, FILE *file) {
    if (band->finger->left == band->sentinel) {
        fprintf(file, "%s\n", "ERROR");
        return;
    }
    
    ListNode* node = create_node(symbol);
    band->finger->left->right = node;
    node->left = band->finger->left;
    band->finger->left = node;
    node->right = band->finger;

    band->finger = band->finger->left;
}

void insert_right(Band *band, char symbol) {
    ListNode *node = create_node(symbol);

    if (band->finger->right == NULL) {
        band->finger->right = node;
        node->left = band->finger;

    } else {
        band->finger->right->left = node;
        node->right = band->finger->right;
        band->finger->right = node;
        node->left = band->finger;
    }

    band->finger = band->finger->right;
}

/* QUERY operations
1. show current element */

void show_current(Band *band, FILE *file) {
    fprintf(file, "%c\n", band->finger->element);
}

/* 2. show all elements from band */

void show(Band *band, FILE *file) {
    ListNode *tmp = band->head;
    while (tmp != NULL) {
        if(tmp == band->finger){
            fprintf(file, "|%c|", tmp->element);
        } else {
            fprintf(file, "%c", tmp->element);
        }
        tmp = tmp->right;
    }

    fprintf(file, "\n");
}

/* UNDO/REDO operations */

void undo(Band *band) {
    if (is_stack_empty(band->undo_stack)) {
        return;
    }
    push_stack(band->redo_stack, band->finger);
    ListNode *tmp = pop_stack(band->undo_stack);
    band->finger = tmp;
}

void redo(Band *band) {
    if (is_stack_empty(band->redo_stack)) {
        return;
    }
    push_stack(band->undo_stack, band->finger);
    ListNode *tmp = pop_stack(band->redo_stack);
    band->finger = tmp;
}

/* EXECUTE operation */

void execute(Band *band, Queue *queue, FILE *file) {
    // dequeue the command that will be executed
    char *command = dequeue(queue);

    int len = strlen(command);
    char tmp_command[len + 1];
    tmp_command[len] = '\0';
    char cmd_chr;    // the character from commands (ex. WRITE <C> )

    if (strchr(command, ' ') == NULL) {
        // if there is no space in the command => move_left/move_right
        if (!strcmp(command, "MOVE_LEFT\n")) {
            move_left(band);

        } else if (!strcmp(command, "MOVE_RIGHT\n")) {
            move_right(band);
        }
    } else {
        // determine the char from commands (it is last element from command)
        cmd_chr = command[len - 2];
        strncpy(tmp_command, command, (len - 2));
        tmp_command[len - 3] = '\0';

        if (strcmp(tmp_command, "WRITE") == 0) {
            write_c(band, cmd_chr);

        } else if (strcmp(tmp_command, "MOVE_LEFT_CHAR") == 0) {
            move_left_char(band, cmd_chr, file);

        } else if (strcmp(tmp_command, "MOVE_RIGHT_CHAR") == 0) {
            move_right_char(band, cmd_chr);

        } else if (strcmp(tmp_command, "INSERT_LEFT") == 0) {
            insert_left(band, cmd_chr, file);

        } else if (strcmp(tmp_command, "INSERT_RIGHT") == 0) {
            insert_right(band, cmd_chr);
        }
    } 
    free(command);
}

void delete_stack_elements(Stack *stack) {
    if (is_stack_empty(stack)) {
        return;
    }

    while (stack->size != 0) {
        ListNode *tmp = pop_stack(stack);
    }
}

void free_band(Band *band) {
    if (band == NULL) {
        return;
    }

    ListNode *iter = band->head;
    while(iter != NULL) {
        ListNode *tmp = iter;
        iter = iter->right;
        free(tmp);
    }
    free_stack(band->undo_stack);
    free_stack(band->redo_stack);
    free(band->sentinel);
    free(band);
    band = NULL;
}
