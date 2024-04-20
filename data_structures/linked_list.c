/*
Chapter 4, exercises 1 and 2

Implements a linked list with elements inserted at the end.
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

void insertElement(Element **head, int value) {
  // insertElement needs to take an Element** instead of an Element*
  // because it potentially modifies the head pointer itself
  // O(n)
  Element *new_element = (Element *)malloc(sizeof(Element));
  if (!new_element) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }
  new_element->value = value;
  new_element->next = NULL;

  if (!*head) {
    *head = new_element;
    return;
  }

  Element *current = *head;
  while (current->next) {
    current = current->next;
  }
  current->next = new_element;
}

Element *searchElement(Element *element, int value) {
  // O(n)
  if (!element || value == element->value) {
    return element;
  }
  return searchElement(element->next, value);
}

Element *nonRecursiveSearchElement(Element *head, int value) {
  // O(n)
  Element *current = head;
  while (current) {
    if (value == current->value) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void deleteElement(struct Element **head, int index) {
  // O(n)
  // takes an Element ** because it must be able to delete the head
  if (!*head || index < 0) {
    return;
  }

  if (index == 0) {
    Element *to_delete = *head;
    *head = (*head)->next;
    free(to_delete);
    return;
  }

  Element *current = *head;
  int i = 0;
  while (current && i < index - 1) {
    current = current->next;
    i++;
  }

  if (current && current->next) {
    Element *to_delete = current->next; // save so we can free() later
    current->next = to_delete->next;
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

int main() {
  Element *head = NULL;

  insertElement(&head, 0);
  insertElement(&head, 1);
  insertElement(&head, 2);
  insertElement(&head, 3);
  printList(head);

  int index = 5;
  printf("Deleting %d\n", index);
  deleteElement(&head, index);
  printList(head);
  printf("Deleting 3\n");
  deleteElement(&head, 3);
  printList(head);

  printf("Reversing list\n");
  reverseList(&head);
  printList(head);

  printf("Searching for 0\n");
  Element *node_zero = searchElement(head, 0);
  printList(node_zero);

  printf("Searching for 1\n");
  Element *node_one = nonRecursiveSearchElement(head, 1);
  printList(node_one);

  printf("Searching for 10\n");
  Element *node_ten = nonRecursiveSearchElement(head, 10);
  printList(node_ten);

  freeList(head);

  return 0;
}