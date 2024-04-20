#ifndef LINKED_LIST_H // Prevent multiple inclusions
#define LINKED_LIST_H

typedef struct Element {
  int value;
  struct Element *next;
} Element;

void printList(Element *head);
void freeList(Element *head);
void insertElement(Element **head, int value);
Element *searchElement(Element *element, int value);
Element *nonRecursiveSearchElement(Element *element, int value);
void deleteElement(Element **head, int index);
void reverseList(Element **head);

#endif // LINKED_LIST_H