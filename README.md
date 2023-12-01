# c-magic-band

A C program that simulates a (simplified) Turing Machine.

## Overview
This project involves the creation of a "magic band", that works like a Turing Machine but with the distinction that the implemented tape is infinite only to the right.

## Band Implementation
The magic band is implemented using a doubly linked list with a sentinel, a pointer indicating the current position on the band (referred to as a finger), and two stacks. Stacks are implemented with singly linked lists. Additionally, certain band operations needed the use of a queue, implemented similarly with a singly linked list.

### Operations

The functionalities of a magic band :

- UPDATE
    - move to the left/right, insert and modify a character
- QUERY
    - show current/all elements
- UNDO/REDO
    - undo/redo last action using implemented stacks and queue
- EXECUTE
    - executes all encountered actions


## File Handling
In the main.c file, commands are read from a file named data.in, and their results are written to the data.out file. 
