/*
Chapter 4, exercises 1 and 2

Implements a linked list with elements inserted at the end.
To compile: gcc linked_list.c
*/
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void printList(Element *head) {
  // Pass by value as we don't need to change the head
  while (head) {
    printf("%d -> ", head->value);
    head = head->next;
  }
  printf("NULL\n");
}

void freeList(Element *head) {
  // Pass by value as it's not necessary to change the head pointer
  while (head) {
    Element *temp = head;
    head = head->next;
    free(temp);
  }
}

void addElement(Element **head, int value) {
  // O(n)
  // Pass by reference as we might need to change the head of the list.
  Element *new_element = (Element *)malloc(sizeof(Element));
  if (!new_element) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }
  new_element->value = value;
  new_element->next = NULL;

  if (!*head) {
    *head = new_element;
  } else {
    Element *current = *head;
    while (current->next) {
      current = current->next;
    }
    current->next = new_element;
  }
}

void deleteElement(struct Element **head, int index) {
  // O(n)
  // Pass by reference because we might need to delete 'head'
  if (!*head || index < 0) {
    return;
  }

  Element **current = head;
  int i = 0;
  while (*current && i < index) {
    current = &(*current)->next;
    i++;
  }

  if (*current) {
    Element *to_delete = *current; // save so we can free() later
    *current = to_delete->next;
    free(to_delete);
  }
}

void reverseList(Element **head) {
  // O(n)
  // Pass by reference as we'll have to change 'head'
  Element *temp = *head;
  Element *prev = NULL;
  while (temp) {
    // save the next guy
    Element *next = temp->next;

    // point the current guy to the previous guy
    temp->next = prev;
    // set previous guy to current guy
    prev = temp;
    // set current guy to next guy
    temp = next;
  }
  *head = prev;
}

// int main() {
//   Element *head = NULL;

//   addElement(&head, 0);
//   addElement(&head, 1);
//   addElement(&head, 2);
//   addElement(&head, 3);
//   printList(head);
//   printf("Deleting -1\n");
//   deleteElement(&head, -1);
//   printList(head);
//   printf("Deleting 3\n");
//   deleteElement(&head, 3);
//   printList(head);

//   printf("Reversing list\n");
//   reverseList(&head);
//   printList(head);

//   freeList(head);

//   return 0;
// }